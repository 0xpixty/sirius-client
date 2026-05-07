// https://github.com/wxj881027/QmClient
#include <base/detect.h>

#ifndef MEDIA_PLAYER_DBUS
#define MEDIA_PLAYER_DBUS 0
#endif

#if defined(CONF_FAMILY_WINDOWS) && __has_include(<winrt/Windows.Foundation.h>)
#define MEDIA_PLAYER_WINRT 1
#endif

#if MEDIA_PLAYER_WINRT
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef NOGDI
#undef NOGDI
#endif

#include <Windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.Media.Audio.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Media.Render.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/base.h>

#ifdef ERROR
#undef ERROR
#endif

#elif MEDIA_PLAYER_DBUS
#include <curl/curl.h>
#include <dbus/dbus.h>
#define STB_IMAGE_IMPLEMENTATION
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#endif
#include <engine/external/stb_image.h>
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
#endif

#ifndef MEDIA_PLAYER_WINRT
#define MEDIA_PLAYER_WINRT 0
#endif

#include "media_player.h"

#include <base/system.h>

#include <engine/image.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <deque>
#include <mutex>
#include <numbers>
#include <string>
#include <vector>
#define IStorage EngineIStorage
#include <engine/shared/config.h>
#undef IStorage

#if MEDIA_PLAYER_WINRT
using namespace winrt::Windows::Media::Control;

class CMediaViewer::CWinrt
{
public:
	CMediaViewer::CState m_State = {};
	bool m_HasMedia = false;
	std::vector<uint8_t> m_AlbumArtPendingRgba;
	int m_AlbumArtPendingWidth = 0;
	int m_AlbumArtPendingHeight = 0;
};
#endif

#if MEDIA_PLAYER_WINRT || MEDIA_PLAYER_DBUS
class CPlainState
{
public:
	bool m_CanPlay = false;
	bool m_CanPause = false;
	bool m_CanPrev = false;
	bool m_CanNext = false;
	bool m_Playing = false;
	std::string m_ServiceId;
	std::string m_Title;
	std::string m_Artist;
	std::string m_Album;
	int64_t m_PositionMs = 0;
	int64_t m_DurationMs = 0;
	CMediaViewer::CAlbumArtColors m_AlbumArtColors;
	std::string m_AlbumArtUrl;
	std::string m_TrackId;
};

enum class ECommand
{
	Prev,
	PlayPause,
	Next,
};

class CMediaViewer::CShared
{
public:
	std::mutex m_Mutex;
	CPlainState m_State{};
	bool m_HasMedia = false;
	std::deque<ECommand> m_Commands;
	std::vector<uint8_t> m_AlbumArtRgba;
	int m_AlbumArtWidth = 0;
	int m_AlbumArtHeight = 0;
	bool m_AlbumArtDirty = false;
};
#endif

#if MEDIA_PLAYER_WINRT
class CMediaViewer::CAudioCapture
{
public:
	std::mutex m_Mutex;
	std::array<float, CMediaViewer::CVisualizer::NUM_FREQUENCY_BANDS> m_aFrequencyBands{};
	bool m_Active = false;

	int64_t m_LastFrequencyChange = 0;
};
#endif

#if MEDIA_PLAYER_DBUS
class CMediaViewer::CDbus
{
public:
	std::mutex m_Mutex;
	CPlainState m_State{};
	bool m_HasMedia = false;
	std::deque<ECommand> m_Commands;
	std::string m_ServiceName;
	std::string m_PendingAlbumArtUrl;
	bool m_AlbumArtDirty = false;
	CMediaViewer::CAlbumArt m_AlbumArt;
	CMediaViewer::CAlbumArt m_PrevAlbumArt;
	std::vector<uint8_t> m_AlbumArtPendingRgba;
	int m_AlbumArtPendingWidth = 0;
	int m_AlbumArtPendingHeight = 0;
};
#endif

namespace FFT
{
	constexpr int FFT_SIZE = 768;

	class CComplex
	{
	public:
		float Real;
		float Imag;

		CComplex(float r = 0.0f, float i = 0.0f) :
			Real(r), Imag(i) {}

		CComplex operator+(const CComplex &other) const
		{
			return CComplex(Real + other.Real, Imag + other.Imag);
		}

		CComplex operator-(const CComplex &other) const
		{
			return CComplex(Real - other.Real, Imag - other.Imag);
		}

		CComplex operator*(const CComplex &other) const
		{
			return CComplex(
				Real * other.Real - Imag * other.Imag,
				Real * other.Imag + Imag * other.Real);
		}

		float Magnitude() const
		{
			return std::sqrt(Real * Real + Imag * Imag);
		}
	};

	void FFTRecursive(std::vector<CComplex> &x)
	{
		const int N = x.size();
		if(N <= 1)
			return;

		// Divide
		std::vector<CComplex> even(N / 2);
		std::vector<CComplex> odd(N / 2);
		for(int i = 0; i < N / 2; ++i)
		{
			even[i] = x[i * 2];
			odd[i] = x[i * 2 + 1];
		}

		// Conquer
		FFTRecursive(even);
		FFTRecursive(odd);

		// Combine
		for(int k = 0; k < N / 2; ++k)
		{
			const float angle = -2.0f * std::numbers::pi_v<float> * k / N;
			const CComplex t = CComplex(std::cos(angle), std::sin(angle)) * odd[k];
			x[k] = even[k] + t;
			x[k + N / 2] = even[k] - t;
		}
	}

	void ComputeFFT(const float *pSamples, int NumSamples, std::vector<CComplex> &Output)
	{
		const int N = std::min(NumSamples, FFT_SIZE);
		Output.resize(FFT_SIZE);

		// Apply Hamming window and copy samples
		for(int i = 0; i < N; ++i)
		{
			const float window = 0.54f - 0.46f * std::cos(2.0f * std::numbers::pi_v<float> * i / (N - 1));
			Output[i] = CComplex(pSamples[i] * window, 0.0f);
		}

		// Zero padding
		for(int i = N; i < FFT_SIZE; ++i)
		{
			Output[i] = CComplex(0.0f, 0.0f);
		}

		FFTRecursive(Output);
	}
}

#if MEDIA_PLAYER_WINRT
template<typename TAsyncOp>
static bool WaitForAsync(const TAsyncOp &Operation, const std::atomic_bool &StopFlag)
{
	using winrt::Windows::Foundation::AsyncStatus;
	while(true)
	{
		const AsyncStatus Status = Operation.Status();
		if(Status == AsyncStatus::Completed)
			return true;
		if(Status == AsyncStatus::Canceled || Status == AsyncStatus::Error)
			return false;
		if(StopFlag.load(std::memory_order_relaxed))
			return false;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

static void ClearAlbumArtLocal(CMediaViewer::CWinrt *pWinrt, IGraphics *pGraphics)
{
	if(pGraphics && pWinrt->m_State.m_AlbumArt.m_Texture.IsValid())
	{
		pGraphics->UnloadTexture(&pWinrt->m_State.m_AlbumArt.m_Texture);
	}
	if(pGraphics && pWinrt->m_State.m_PrevAlbumArt.m_Texture.IsValid())
	{
		pGraphics->UnloadTexture(&pWinrt->m_State.m_PrevAlbumArt.m_Texture);
	}
	pWinrt->m_State.m_AlbumArt.m_Texture.Invalidate();
	pWinrt->m_State.m_AlbumArt.m_Width = 0;
	pWinrt->m_State.m_AlbumArt.m_Height = 0;
	pWinrt->m_State.m_AlbumArt.m_Colors = CMediaViewer::CAlbumArtColors{};
	pWinrt->m_State.m_PrevAlbumArt.m_Texture.Invalidate();
	pWinrt->m_State.m_PrevAlbumArt.m_Width = 0;
	pWinrt->m_State.m_PrevAlbumArt.m_Height = 0;
	pWinrt->m_State.m_PrevAlbumArt.m_Colors = CMediaViewer::CAlbumArtColors{};
	pWinrt->m_AlbumArtPendingRgba.clear();
	pWinrt->m_AlbumArtPendingWidth = 0;
	pWinrt->m_AlbumArtPendingHeight = 0;
}
#endif
#if MEDIA_PLAYER_WINRT
static void ClearState(CMediaViewer::CWinrt *pWinrt, IGraphics *pGraphics)
{
	ClearAlbumArtLocal(pWinrt, pGraphics);
	pWinrt->m_State = CMediaViewer::CState{};
	pWinrt->m_HasMedia = false;
}
#endif

#if MEDIA_PLAYER_WINRT || MEDIA_PLAYER_DBUS
static void ClearSharedAlbumArt(CMediaViewer::CShared *pShared)
{
	std::scoped_lock Lock(pShared->m_Mutex);
	pShared->m_AlbumArtRgba.clear();
	pShared->m_AlbumArtWidth = 0;
	pShared->m_AlbumArtHeight = 0;
	pShared->m_AlbumArtDirty = true;
}

static void SetSharedAlbumArt(CMediaViewer::CShared *pShared, std::vector<uint8_t> &&Pixels, int Width, int Height)
{
	std::scoped_lock Lock(pShared->m_Mutex);
	pShared->m_AlbumArtRgba = std::move(Pixels);
	pShared->m_AlbumArtWidth = Width;
	pShared->m_AlbumArtHeight = Height;
	pShared->m_AlbumArtDirty = true;
}

static void ClearAlbumArtColors(CPlainState &State)
{
	State.m_AlbumArtColors = CMediaViewer::CAlbumArtColors{};
}

#if MEDIA_PLAYER_WINRT
static void ClearMediaText(CPlainState &State)
{
	State.m_ServiceId.clear();
	State.m_Title.clear();
	State.m_Artist.clear();
	State.m_Album.clear();
}

static void ClearMediaDetails(CPlainState &State, std::string &AlbumArtKey, CMediaViewer::CShared *pShared)
{
	ClearMediaText(State);
	ClearAlbumArtColors(State);
	AlbumArtKey.clear();
	ClearSharedAlbumArt(pShared);
}

static void ResetSharedState(CMediaViewer::CShared *pShared, CPlainState &State, bool &HasMedia, std::string &AlbumArtKey)
{
	HasMedia = false;
	State = CPlainState{};
	AlbumArtKey.clear();
	ClearSharedAlbumArt(pShared);
	std::scoped_lock Lock(pShared->m_Mutex);
	pShared->m_State = State;
	pShared->m_HasMedia = false;
}
#endif

class CColorAccumulator
{
public:
	float m_Weight = 0.0f;
	float m_SumR = 0.0f;
	float m_SumG = 0.0f;
	float m_SumB = 0.0f;

	void Add(const ColorRGBA &Color, float Weight)
	{
		if(Weight <= 0.0f)
			return;

		m_Weight += Weight;
		m_SumR += Color.r * Weight;
		m_SumG += Color.g * Weight;
		m_SumB += Color.b * Weight;
	}

	void Add(const CColorAccumulator &Other)
	{
		m_Weight += Other.m_Weight;
		m_SumR += Other.m_SumR;
		m_SumG += Other.m_SumG;
		m_SumB += Other.m_SumB;
	}

	[[nodiscard]] ColorRGBA Average() const
	{
		if(m_Weight <= 0.0f)
			return ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);

		const float InvWeight = 1.0f / m_Weight;
		return ColorRGBA(
			std::clamp(m_SumR * InvWeight, 0.0f, 1.0f),
			std::clamp(m_SumG * InvWeight, 0.0f, 1.0f),
			std::clamp(m_SumB * InvWeight, 0.0f, 1.0f),
			1.0f);
	}
};

static float ColorDistance(const ColorRGBA &A, const ColorRGBA &B)
{
	const float Dr = A.r - B.r;
	const float Dg = A.g - B.g;
	const float Db = A.b - B.b;
	return std::sqrt(Dr * Dr + Dg * Dg + Db * Db);
}

static int CircularBinDistance(int A, int B, int BinCount)
{
	const int Dist = std::abs(A - B);
	return std::min(Dist, BinCount - Dist);
}

static bool IsColorDistinctEnough(const ColorRGBA &Primary, const ColorRGBA &Candidate)
{
	const ColorHSLA PrimaryHsl = color_cast<ColorHSLA>(Primary);
	const ColorHSLA CandidateHsl = color_cast<ColorHSLA>(Candidate);
	const float HueDistance = std::min(std::abs(PrimaryHsl.h - CandidateHsl.h), 1.0f - std::abs(PrimaryHsl.h - CandidateHsl.h));
	const float LightnessDistance = std::abs(PrimaryHsl.l - CandidateHsl.l);
	const float SaturationDistance = std::abs(PrimaryHsl.s - CandidateHsl.s);
	const float RgbDistance = ColorDistance(Primary, Candidate);

	return HueDistance >= 0.10f ||
	       LightnessDistance >= 0.16f ||
	       SaturationDistance >= 0.22f ||
	       RgbDistance >= 0.25f;
}

static void ComputeAlbumArtColors(const std::vector<uint8_t> &Pixels, int Width, int Height, CPlainState &State)
{
	ClearAlbumArtColors(State);

	if(Width <= 0 || Height <= 0 || Pixels.size() < (size_t)Width * (size_t)Height * 4)
		return;

	constexpr int HUE_BIN_COUNT = 24;
	constexpr float MIN_ALPHA = 8.0f / 255.0f;
	constexpr float MIN_SATURATION = 0.10f;
	std::array<CColorAccumulator, HUE_BIN_COUNT> aHueBins{};
	CColorAccumulator NeutralBin;
	float TotalWeight = 0.0f;
	for(size_t Index = 0; Index + 3 < Pixels.size(); Index += 4)
	{
		const float Alpha = Pixels[Index + 3] / 255.0f;
		if(Alpha <= MIN_ALPHA)
			continue;

		float R = Pixels[Index + 0] / 255.0f;
		float G = Pixels[Index + 1] / 255.0f;
		float B = Pixels[Index + 2] / 255.0f;
		if(Alpha < 1.0f)
		{
			const float InvAlpha = 1.0f / Alpha;
			R = std::clamp(R * InvAlpha, 0.0f, 1.0f);
			G = std::clamp(G * InvAlpha, 0.0f, 1.0f);
			B = std::clamp(B * InvAlpha, 0.0f, 1.0f);
		}

		const ColorRGBA Color(R, G, B, 1.0f);
		const ColorHSLA Hsl = color_cast<ColorHSLA>(Color);
		const float Weight = Alpha * (0.30f + 0.70f * Hsl.s);
		if(Weight <= 0.0f)
			continue;

		TotalWeight += Weight;
		if(Hsl.s < MIN_SATURATION)
		{
			NeutralBin.Add(Color, Weight * 0.85f);
			continue;
		}

		const int Bin = std::clamp((int)(Hsl.h * HUE_BIN_COUNT), 0, HUE_BIN_COUNT - 1);
		aHueBins[Bin].Add(Color, Weight);
	}

	if(TotalWeight <= 0.0f)
		return;

	auto CombinedBinScore = [&](int Bin) {
		return aHueBins[Bin].m_Weight +
		       aHueBins[(Bin + HUE_BIN_COUNT - 1) % HUE_BIN_COUNT].m_Weight * 0.65f +
		       aHueBins[(Bin + 1) % HUE_BIN_COUNT].m_Weight * 0.65f;
	};

	auto CombinedAccumulator = [&](int Bin) {
		CColorAccumulator Result;
		Result.Add(aHueBins[(Bin + HUE_BIN_COUNT - 1) % HUE_BIN_COUNT]);
		Result.Add(aHueBins[Bin]);
		Result.Add(aHueBins[(Bin + 1) % HUE_BIN_COUNT]);
		return Result;
	};

	bool PrimaryIsNeutral = NeutralBin.m_Weight > 0.0f;
	int PrimaryBin = -1;
	float BestPrimaryScore = NeutralBin.m_Weight * 0.90f;
	for(int Bin = 0; Bin < HUE_BIN_COUNT; ++Bin)
	{
		const float Score = CombinedBinScore(Bin);
		if(Score > BestPrimaryScore)
		{
			BestPrimaryScore = Score;
			PrimaryBin = Bin;
			PrimaryIsNeutral = false;
		}
	}

	if(PrimaryIsNeutral)
	{
		if(NeutralBin.m_Weight <= 0.0f)
			return;
		State.m_AlbumArtColors.m_Primary = NeutralBin.Average();
	}
	else
	{
		const CColorAccumulator PrimaryAccumulator = CombinedAccumulator(PrimaryBin);
		if(PrimaryAccumulator.m_Weight <= 0.0f)
			return;
		State.m_AlbumArtColors.m_Primary = PrimaryAccumulator.Average();
	}
	State.m_AlbumArtColors.m_HasPrimary = true;

	const ColorRGBA PrimaryColor = State.m_AlbumArtColors.m_Primary;
	float BestSecondaryScore = 0.0f;
	ColorRGBA SecondaryColor = PrimaryColor;

	if(NeutralBin.m_Weight >= TotalWeight * 0.04f)
	{
		const ColorRGBA NeutralColor = NeutralBin.Average();
		if(IsColorDistinctEnough(PrimaryColor, NeutralColor))
		{
			BestSecondaryScore = NeutralBin.m_Weight;
			SecondaryColor = NeutralColor;
		}
	}

	for(int Bin = 0; Bin < HUE_BIN_COUNT; ++Bin)
	{
		if(!PrimaryIsNeutral && CircularBinDistance(Bin, PrimaryBin, HUE_BIN_COUNT) < 3)
			continue;

		const float Score = CombinedBinScore(Bin);
		if(Score < TotalWeight * 0.04f || Score <= BestSecondaryScore)
			continue;

		const CColorAccumulator CandidateAccumulator = CombinedAccumulator(Bin);
		if(CandidateAccumulator.m_Weight <= 0.0f)
			continue;

		const ColorRGBA CandidateColor = CandidateAccumulator.Average();
		if(!IsColorDistinctEnough(PrimaryColor, CandidateColor))
			continue;

		BestSecondaryScore = Score;
		SecondaryColor = CandidateColor;
	}

	if(BestSecondaryScore > 0.0f)
	{
		State.m_AlbumArtColors.m_Secondary = SecondaryColor;
		State.m_AlbumArtColors.m_HasSecondary = true;
	}
	dbg_msg("test", "Primary (%.3f, %.3f, %.3f), Secondary (%.3f, %.3f, %.3f)",
		State.m_AlbumArtColors.m_Primary.r, State.m_AlbumArtColors.m_Primary.g, State.m_AlbumArtColors.m_Primary.b,
		State.m_AlbumArtColors.m_Secondary.r, State.m_AlbumArtColors.m_Secondary.g, State.m_AlbumArtColors.m_Secondary.b);
}

static void ApplyRoundedMask(std::vector<uint8_t> &Pixels, int Width, int Height, float Radius)
{
	if(Pixels.empty() || Width <= 0 || Height <= 0 || Radius <= 0.0f)
		return;

	const float MaxRadius = 0.5f * (float)std::min(Width, Height);
	const float R = std::min(Radius, MaxRadius);
	if(R <= 0.0f)
		return;

	const float Left = R;
	const float Right = (float)Width - R;
	const float Top = R;
	const float Bottom = (float)Height - R;
	const float OuterR2 = R * R;
	const float InnerR = R - 1.0f;
	const float InnerR2 = InnerR > 0.0f ? InnerR * InnerR : 0.0f;
	const bool UseSoftEdge = InnerR > 0.0f;

	for(int y = 0; y < Height; ++y)
	{
		const float Fy = (float)y + 0.5f;
		for(int x = 0; x < Width; ++x)
		{
			const float Fx = (float)x + 0.5f;
			float Dx = 0.0f;
			float Dy = 0.0f;
			bool Corner = false;

			if(Fx < Left && Fy < Top)
			{
				Dx = Left - Fx;
				Dy = Top - Fy;
				Corner = true;
			}
			else if(Fx > Right && Fy < Top)
			{
				Dx = Fx - Right;
				Dy = Top - Fy;
				Corner = true;
			}
			else if(Fx < Left && Fy > Bottom)
			{
				Dx = Left - Fx;
				Dy = Fy - Bottom;
				Corner = true;
			}
			else if(Fx > Right && Fy > Bottom)
			{
				Dx = Fx - Right;
				Dy = Fy - Bottom;
				Corner = true;
			}

			if(!Corner)
				continue;

			const float Dist2 = Dx * Dx + Dy * Dy;
			if(Dist2 <= (UseSoftEdge ? InnerR2 : OuterR2))
				continue;

			float Alpha = 0.0f;
			if(UseSoftEdge && Dist2 < OuterR2)
			{
				const float Dist = std::sqrt(Dist2);
				Alpha = std::clamp(R - Dist, 0.0f, 1.0f);
			}

			const size_t Index = (size_t)(y * Width + x) * 4;
			if(Alpha <= 0.0f)
			{
				Pixels[Index + 0] = 0;
				Pixels[Index + 1] = 0;
				Pixels[Index + 2] = 0;
				Pixels[Index + 3] = 0;
			}
			else if(Alpha < 1.0f)
			{
				Pixels[Index + 0] = (uint8_t)std::round(Pixels[Index + 0] * Alpha);
				Pixels[Index + 1] = (uint8_t)std::round(Pixels[Index + 1] * Alpha);
				Pixels[Index + 2] = (uint8_t)std::round(Pixels[Index + 2] * Alpha);
				Pixels[Index + 3] = (uint8_t)std::round(Pixels[Index + 3] * Alpha);
			}
		}
	}
}
#endif

#if MEDIA_PLAYER_WINRT
static bool UpdateAlbumArtData(CMediaViewer::CShared *pShared, CPlainState &State, const winrt::Windows::Storage::Streams::IRandomAccessStreamReference &Thumbnail, const std::atomic_bool &StopFlag)
{
	if(!Thumbnail)
	{
		ClearAlbumArtColors(State);
		ClearSharedAlbumArt(pShared);
		return false;
	}

	try
	{
		const auto StreamOp = Thumbnail.OpenReadAsync();
		if(!WaitForAsync(StreamOp, StopFlag))
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}
		const auto Stream = StreamOp.GetResults();
		if(!Stream)
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}

		const auto DecoderOp = winrt::Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(Stream);
		if(!WaitForAsync(DecoderOp, StopFlag))
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}
		const auto Decoder = DecoderOp.GetResults();
		if(!Decoder)
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}
		const uint32_t Width = Decoder.PixelWidth();
		const uint32_t Height = Decoder.PixelHeight();
		if(Width == 0 || Height == 0)
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}

		const auto PixelDataOp = Decoder.GetPixelDataAsync(
			winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Rgba8,
			winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Premultiplied,
			winrt::Windows::Graphics::Imaging::BitmapTransform(),
			winrt::Windows::Graphics::Imaging::ExifOrientationMode::IgnoreExifOrientation,
			winrt::Windows::Graphics::Imaging::ColorManagementMode::DoNotColorManage);
		if(!WaitForAsync(PixelDataOp, StopFlag))
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}
		const auto PixelData = PixelDataOp.GetResults();
		if(!PixelData)
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}

		const auto Pixels = PixelData.DetachPixelData();
		const size_t ExpectedSize = (size_t)Width * (size_t)Height * 4;
		if(Pixels.size() < ExpectedSize)
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}

		if(StopFlag.load(std::memory_order_relaxed))
		{
			ClearAlbumArtColors(State);
			ClearSharedAlbumArt(pShared);
			return false;
		}

		std::vector<uint8_t> Copy(Pixels.begin(), Pixels.begin() + ExpectedSize);
		ComputeAlbumArtColors(Copy, (int)Width, (int)Height, State);
		SetSharedAlbumArt(pShared, std::move(Copy), (int)Width, (int)Height);
		return true;
	}
	catch(const winrt::hresult_error &)
	{
		ClearAlbumArtColors(State);
		ClearSharedAlbumArt(pShared);
		return false;
	}
}

static void ApplySharedAlbumArt(CMediaViewer::CShared *pShared, CMediaViewer::CWinrt *pWinrt, IGraphics *pGraphics)
{
	if(!pShared || !pWinrt || !pGraphics)
		return;

	bool AlbumArtDirty = false;
	int AlbumArtWidth = 0;
	int AlbumArtHeight = 0;
	std::vector<uint8_t> AlbumArtPixels;
	{
		std::scoped_lock Lock(pShared->m_Mutex);
		if(pShared->m_AlbumArtDirty)
		{
			AlbumArtDirty = true;
			AlbumArtWidth = pShared->m_AlbumArtWidth;
			AlbumArtHeight = pShared->m_AlbumArtHeight;
			AlbumArtPixels = std::move(pShared->m_AlbumArtRgba);
			pShared->m_AlbumArtRgba.clear();
			pShared->m_AlbumArtDirty = false;
		}
	}

	if(AlbumArtDirty)
	{
		const size_t ExpectedSize = (size_t)AlbumArtWidth * (size_t)AlbumArtHeight * 4;
		if(AlbumArtWidth > 0 && AlbumArtHeight > 0 && AlbumArtPixels.size() >= ExpectedSize)
		{
			const float RoundingRatio = 2.0f / 14.0f;
			const float Radius = (float)std::min(AlbumArtWidth, AlbumArtHeight) * RoundingRatio;
			ApplyRoundedMask(AlbumArtPixels, AlbumArtWidth, AlbumArtHeight, Radius);

			pWinrt->m_AlbumArtPendingRgba = std::move(AlbumArtPixels);
			pWinrt->m_AlbumArtPendingWidth = AlbumArtWidth;
			pWinrt->m_AlbumArtPendingHeight = AlbumArtHeight;
		}
		else
		{
			ClearAlbumArtLocal(pWinrt, pGraphics);
			return;
		}
	}

	if(pWinrt->m_AlbumArtPendingRgba.empty() || pWinrt->m_AlbumArtPendingWidth <= 0 || pWinrt->m_AlbumArtPendingHeight <= 0)
		return;

	const size_t ExpectedSize = (size_t)pWinrt->m_AlbumArtPendingWidth * (size_t)pWinrt->m_AlbumArtPendingHeight * 4;
	CImageInfo Image;
	Image.m_Width = (size_t)pWinrt->m_AlbumArtPendingWidth;
	Image.m_Height = (size_t)pWinrt->m_AlbumArtPendingHeight;
	Image.m_Format = CImageInfo::FORMAT_RGBA;
	Image.m_pData = static_cast<uint8_t *>(malloc(ExpectedSize));
	if(!Image.m_pData)
		return;

	mem_copy(Image.m_pData, pWinrt->m_AlbumArtPendingRgba.data(), ExpectedSize);
	const IGraphics::CTextureHandle NewAlbumArt = pGraphics->LoadTextureRawMove(Image, 0, "smtc_album_art");
	if(Image.m_pData)
		Image.Free();

	if(NewAlbumArt.IsValid())
	{
		if(pWinrt->m_State.m_PrevAlbumArt.m_Texture.IsValid())
			pGraphics->UnloadTexture(&pWinrt->m_State.m_PrevAlbumArt.m_Texture);
		pWinrt->m_State.m_PrevAlbumArt = pWinrt->m_State.m_AlbumArt;
		pWinrt->m_State.m_AlbumArt.m_Texture = NewAlbumArt;
		pWinrt->m_State.m_AlbumArt.m_Width = pWinrt->m_AlbumArtPendingWidth;
		pWinrt->m_State.m_AlbumArt.m_Height = pWinrt->m_AlbumArtPendingHeight;

		pWinrt->m_AlbumArtPendingRgba.clear();
		pWinrt->m_AlbumArtPendingWidth = 0;
		pWinrt->m_AlbumArtPendingHeight = 0;
	}
}
#elif MEDIA_PLAYER_DBUS

static void ApplyDbusSharedAlbumArt(CMediaViewer::CShared *pShared, CMediaViewer::CDbus *pDbus, IGraphics *pGraphics)
{
	if(!pShared || !pDbus || !pGraphics)
		return;

	bool AlbumArtDirty = false;
	int AlbumArtWidth = 0;
	int AlbumArtHeight = 0;
	std::vector<uint8_t> AlbumArtPixels;
	{
		std::scoped_lock Lock(pShared->m_Mutex);
		if(pShared->m_AlbumArtDirty)
		{
			AlbumArtDirty = true;
			AlbumArtWidth = pShared->m_AlbumArtWidth;
			AlbumArtHeight = pShared->m_AlbumArtHeight;
			AlbumArtPixels = std::move(pShared->m_AlbumArtRgba);
			pShared->m_AlbumArtRgba.clear();
			pShared->m_AlbumArtDirty = false;
		}
	}

	if(AlbumArtDirty)
	{
		const size_t ExpectedSize = (size_t)AlbumArtWidth * (size_t)AlbumArtHeight * 4;
		if(AlbumArtWidth > 0 && AlbumArtHeight > 0 && AlbumArtPixels.size() >= ExpectedSize)
		{
			const float RoundingRatio = 2.0f / 14.0f;
			const float Radius = (float)std::min(AlbumArtWidth, AlbumArtHeight) * RoundingRatio;
			ApplyRoundedMask(AlbumArtPixels, AlbumArtWidth, AlbumArtHeight, Radius);

			std::scoped_lock Lock(pDbus->m_Mutex);
			pDbus->m_AlbumArtPendingRgba = std::move(AlbumArtPixels);
			pDbus->m_AlbumArtPendingWidth = AlbumArtWidth;
			pDbus->m_AlbumArtPendingHeight = AlbumArtHeight;
		}
		else
		{
			std::scoped_lock Lock(pDbus->m_Mutex);
			pDbus->m_AlbumArtPendingRgba.clear();
			pDbus->m_AlbumArtPendingWidth = 0;
			pDbus->m_AlbumArtPendingHeight = 0;
		}
	}

	std::scoped_lock Lock(pDbus->m_Mutex);
	if(pDbus->m_AlbumArtPendingRgba.empty() || pDbus->m_AlbumArtPendingWidth <= 0 || pDbus->m_AlbumArtPendingHeight <= 0)
		return;

	const size_t ExpectedSize = (size_t)pDbus->m_AlbumArtPendingWidth * (size_t)pDbus->m_AlbumArtPendingHeight * 4;
	CImageInfo Image;
	Image.m_Width = (size_t)pDbus->m_AlbumArtPendingWidth;
	Image.m_Height = (size_t)pDbus->m_AlbumArtPendingHeight;
	Image.m_Format = CImageInfo::FORMAT_RGBA;
	Image.m_pData = static_cast<uint8_t *>(malloc(ExpectedSize));
	if(!Image.m_pData)
		return;

	mem_copy(Image.m_pData, pDbus->m_AlbumArtPendingRgba.data(), ExpectedSize);
	const IGraphics::CTextureHandle NewAlbumArt = pGraphics->LoadTextureRawMove(Image, 0, "dbus_album_art");
	if(Image.m_pData)
		Image.Free();

	if(NewAlbumArt.IsValid())
	{
		if(pDbus->m_AlbumArt.m_Texture.IsValid())
			pGraphics->UnloadTexture(&pDbus->m_AlbumArt.m_Texture);
		pDbus->m_PrevAlbumArt = pDbus->m_AlbumArt;
		pDbus->m_AlbumArt.m_Texture = NewAlbumArt;
		pDbus->m_AlbumArt.m_Width = pDbus->m_AlbumArtPendingWidth;
		pDbus->m_AlbumArt.m_Height = pDbus->m_AlbumArtPendingHeight;
		pDbus->m_AlbumArt.m_Colors = pDbus->m_State.m_AlbumArtColors;
		pDbus->m_AlbumArtPendingRgba.clear();
		pDbus->m_AlbumArtPendingWidth = 0;
		pDbus->m_AlbumArtPendingHeight = 0;
	}
}

static std::string UrlDecode(const std::string &Encoded)
{
	std::string Decoded;
	Decoded.reserve(Encoded.size());

	for(size_t i = 0; i < Encoded.size(); ++i)
	{
		const char c = Encoded[i];
		if(c == '%' && i + 2 < Encoded.size())
		{
			auto HexToInt = [](char h) {
				if(h >= '0' && h <= '9')
					return h - '0';
				if(h >= 'A' && h <= 'F')
					return h - 'A' + 10;
				if(h >= 'a' && h <= 'f')
					return h - 'a' + 10;
				return 0;
			};
			const char hi = Encoded[i + 1];
			const char lo = Encoded[i + 2];
			if(std::isxdigit(hi) && std::isxdigit(lo))
			{
				Decoded += (char)((HexToInt(hi) << 4) | HexToInt(lo));
				i += 2;
				continue;
			}
		}
		if(c == '+')
			Decoded += ' ';
		else
			Decoded += c;
	}

	return Decoded;
}

static std::string DecodeFileUri(const std::string &Uri)
{
	const std::string Prefix = "file:";
	if(Uri.rfind(Prefix, 0) != 0)
		return Uri;

	std::string Path = Uri.substr(Prefix.size());

	// file:///path or file:/path
	if(Path.rfind("///", 0) == 0)
	{
		Path = Path.substr(2);
	}
	// file://localhost/path
	else if(Path.rfind("//localhost/", 0) == 0)
	{
		Path = Path.substr(11);
	}
	// file://host/path
	else if(Path.rfind("//", 0) == 0)
	{
		Path = Path.substr(2);
	}

	return UrlDecode(Path);
}

static size_t CurlWriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	const size_t total = size * nmemb;
	if(total == 0)
		return 0;
	auto *pVec = static_cast<std::vector<uint8_t> *>(userp);
	const uint8_t *pData = static_cast<uint8_t *>(contents);
	// Enforce max download size (10 MB)
	if(pVec->size() + total > 10 * 1024 * 1024)
		return 0; // abort
	pVec->insert(pVec->end(), pData, pData + total);
	return total;
}

static bool DownloadUrlToVector(const std::string &Url, std::vector<uint8_t> &Out)
{
	static std::once_flag s_CurlInitFlag;
	std::call_once(s_CurlInitFlag, []() {
		curl_global_init(CURL_GLOBAL_DEFAULT);
	});

	CURL *pEasy = curl_easy_init();
	if(!pEasy)
		return false;
	CURLM *pMulti = curl_multi_init();
	if(!pMulti)
	{
		curl_easy_cleanup(pEasy);
		return false;
	}

	curl_easy_setopt(pEasy, CURLOPT_URL, Url.c_str());
	curl_easy_setopt(pEasy, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(pEasy, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
	curl_easy_setopt(pEasy, CURLOPT_WRITEDATA, &Out);
	curl_easy_setopt(pEasy, CURLOPT_ACCEPT_ENCODING, "");
	curl_easy_setopt(pEasy, CURLOPT_USERAGENT, "DDNetMediaViewer/1.0");
	curl_easy_setopt(pEasy, CURLOPT_TIMEOUT, 10L);
	curl_easy_setopt(pEasy, CURLOPT_MAXFILESIZE, 10 * 1024 * 1024L);

	if(curl_multi_add_handle(pMulti, pEasy) != CURLM_OK)
	{
		curl_multi_cleanup(pMulti);
		curl_easy_cleanup(pEasy);
		return false;
	}

	CURLcode Result = CURLE_FAILED_INIT;
	bool GotResult = false;
	auto ReadResult = [&]() {
		int MessagesLeft = 0;
		while(CURLMsg *pMsg = curl_multi_info_read(pMulti, &MessagesLeft))
		{
			if(pMsg->msg == CURLMSG_DONE && pMsg->easy_handle == pEasy)
			{
				Result = pMsg->data.result;
				GotResult = true;
				return true;
			}
		}
		return false;
	};

	int RunningHandles = 0;
	CURLMcode MultiResult = curl_multi_perform(pMulti, &RunningHandles);
	while(MultiResult == CURLM_OK && !GotResult)
	{
		ReadResult();
		if(GotResult)
			break;
		if(RunningHandles == 0)
			break;

		int NumFds = 0;
		MultiResult = curl_multi_poll(pMulti, nullptr, 0, 1000, &NumFds);
		if(MultiResult != CURLM_OK)
			break;

		MultiResult = curl_multi_perform(pMulti, &RunningHandles);
	}

	ReadResult();
	curl_multi_remove_handle(pMulti, pEasy);
	curl_multi_cleanup(pMulti);
	curl_easy_cleanup(pEasy);
	return MultiResult == CURLM_OK && GotResult && Result == CURLE_OK && !Out.empty();
}

static bool DecodeImageFromBuffer(const std::vector<uint8_t> &Data, std::vector<uint8_t> &OutRgba, int &OutWidth, int &OutHeight)
{
	OutWidth = 0;
	OutHeight = 0;
	OutRgba.clear();

	if(Data.empty())
	{
		dbg_msg("mediaviewer", "Cannot decode empty image buffer");
		return false;
	}

	int Channels = 0;
	int Width = 0, Height = 0;
	uint8_t *ImageData = stbi_load_from_memory(Data.data(), (int)Data.size(), &Width, &Height, &Channels, 4);

	if(!ImageData)
	{
		dbg_msg("mediaviewer", "Failed to load image from buffer: %s", stbi_failure_reason());
		return false;
	}

	if(Width <= 0 || Height <= 0)
	{
		dbg_msg("mediaviewer", "Invalid image dimensions: %dx%d", Width, Height);
		stbi_image_free(ImageData);
		return false;
	}

	// Copy RGBA data
	const size_t PixelCount = (size_t)Width * (size_t)Height;
	const size_t ByteCount = PixelCount * 4;
	OutRgba.resize(ByteCount);
	memcpy(OutRgba.data(), ImageData, ByteCount);

	OutWidth = Width;
	OutHeight = Height;
	stbi_image_free(ImageData);
	return true;
}

static bool DecodeAlbumArtUrl(const std::string &Url, std::vector<uint8_t> &OutRgba, int &OutWidth, int &OutHeight)
{
	OutRgba.clear();
	OutWidth = 0;
	OutHeight = 0;

	std::vector<uint8_t> Data;

	// Handle file:// URLs (local files)
	if(Url.rfind("file:", 0) == 0)
	{
		// Parse the file path from the URL
		std::string FilePath = DecodeFileUri(Url);

		// Read the file into memory
		FILE *File = fopen(FilePath.c_str(), "rb");
		if(!File)
		{
			dbg_msg("mediaviewer", "Failed to open local album art file: %s", FilePath.c_str());
			return false;
		}

		// Get file size
		fseek(File, 0, SEEK_END);
		long FileSize = ftell(File);
		fseek(File, 0, SEEK_SET);

		if(FileSize <= 0 || FileSize > 10 * 1024 * 1024) // 10 MB max
		{
			dbg_msg("mediaviewer", "Album art file too large or empty: %s", FilePath.c_str());
			fclose(File);
			return false;
		}

		Data.resize(FileSize);
		if(fread(Data.data(), 1, FileSize, File) != (size_t)FileSize)
		{
			dbg_msg("mediaviewer", "Failed to read album art file: %s", FilePath.c_str());
			fclose(File);
			return false;
		}
		fclose(File);
	}
	// Handle HTTP(S) URLs
	else if(Url.rfind("http://", 0) == 0 || Url.rfind("https://", 0) == 0)
	{
		if(!DownloadUrlToVector(Url, Data))
		{
			dbg_msg("mediaviewer", "Failed to download album art from %s", Url.c_str());
			return false;
		}
	}
	else
	{
		dbg_msg("mediaviewer", "Unsupported album art URL scheme: %s", Url.c_str());
		return false;
	}

	if(!DecodeImageFromBuffer(Data, OutRgba, OutWidth, OutHeight))
	{
		dbg_msg("mediaviewer", "Failed to decode album art image from %s", Url.c_str());
		return false;
	}

	return true;
}
#endif

CMediaViewer::CMediaViewer() = default;
CMediaViewer::~CMediaViewer() = default;

#if MEDIA_PLAYER_DBUS

static bool DBusGetPropertyString(DBusConnection *pConnection, const char *pService, const char *pPath, const char *pInterface, const char *pProperty, std::string &Value)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call(pService, pPath, "org.freedesktop.DBus.Properties", "Get");
	if(!pMessage)
	{
		dbus_error_free(&Error);
		return false;
	}

	const char *pIface = pInterface;
	const char *pProp = pProperty;
	dbus_message_append_args(pMessage, DBUS_TYPE_STRING, &pIface, DBUS_TYPE_STRING, &pProp, DBUS_TYPE_INVALID);

	DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
	dbus_message_unref(pMessage);
	if(!pReply)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessageIter Iter;
	if(!dbus_message_iter_init(pReply, &Iter) || dbus_message_iter_get_arg_type(&Iter) != DBUS_TYPE_VARIANT)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Variant;
	dbus_message_iter_recurse(&Iter, &Variant);
	if(dbus_message_iter_get_arg_type(&Variant) != DBUS_TYPE_STRING)
	{
		dbus_message_unref(pReply);
		return false;
	}

	const char *pValue = nullptr;
	dbus_message_iter_get_basic(&Variant, &pValue);
	if(pValue)
		Value = pValue;
	dbus_message_unref(pReply);
	return true;
}

static bool DBusGetPropertyBool(DBusConnection *pConnection, const char *pService, const char *pPath, const char *pInterface, const char *pProperty, bool &Value)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call(pService, pPath, "org.freedesktop.DBus.Properties", "Get");
	if(!pMessage)
	{
		dbus_error_free(&Error);
		return false;
	}

	const char *pIface = pInterface;
	const char *pProp = pProperty;
	dbus_message_append_args(pMessage, DBUS_TYPE_STRING, &pIface, DBUS_TYPE_STRING, &pProp, DBUS_TYPE_INVALID);

	DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
	dbus_message_unref(pMessage);
	if(!pReply)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessageIter Iter;
	if(!dbus_message_iter_init(pReply, &Iter) || dbus_message_iter_get_arg_type(&Iter) != DBUS_TYPE_VARIANT)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Variant;
	dbus_message_iter_recurse(&Iter, &Variant);
	if(dbus_message_iter_get_arg_type(&Variant) != DBUS_TYPE_BOOLEAN)
	{
		dbus_message_unref(pReply);
		return false;
	}

	dbus_bool_t RawValue = false;
	dbus_message_iter_get_basic(&Variant, &RawValue);
	Value = RawValue != 0;
	dbus_message_unref(pReply);
	return true;
}

static bool DBusGetPropertyInt64(DBusConnection *pConnection, const char *pService, const char *pPath, const char *pInterface, const char *pProperty, int64_t &Value)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call(pService, pPath, "org.freedesktop.DBus.Properties", "Get");
	if(!pMessage)
	{
		dbus_error_free(&Error);
		return false;
	}

	const char *pIface = pInterface;
	const char *pProp = pProperty;
	dbus_message_append_args(pMessage, DBUS_TYPE_STRING, &pIface, DBUS_TYPE_STRING, &pProp, DBUS_TYPE_INVALID);

	DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
	dbus_message_unref(pMessage);
	if(!pReply)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessageIter Iter;
	if(!dbus_message_iter_init(pReply, &Iter) || dbus_message_iter_get_arg_type(&Iter) != DBUS_TYPE_VARIANT)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Variant;
	dbus_message_iter_recurse(&Iter, &Variant);
	if(dbus_message_iter_get_arg_type(&Variant) != DBUS_TYPE_INT64)
	{
		dbus_message_unref(pReply);
		return false;
	}

	dbus_int64_t RawValue = 0;
	dbus_message_iter_get_basic(&Variant, &RawValue);
	Value = static_cast<int64_t>(RawValue);
	dbus_message_unref(pReply);
	return true;
}

static bool DBusGetNames(DBusConnection *pConnection, std::vector<std::string> &Names)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call("org.freedesktop.DBus", "/org/freedesktop/DBus", "org.freedesktop.DBus", "ListNames");
	if(!pMessage)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
	dbus_message_unref(pMessage);
	if(!pReply)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessageIter Iter;
	if(!dbus_message_iter_init(pReply, &Iter) || dbus_message_iter_get_arg_type(&Iter) != DBUS_TYPE_ARRAY)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Array;
	dbus_message_iter_recurse(&Iter, &Array);

	while(dbus_message_iter_get_arg_type(&Array) == DBUS_TYPE_STRING)
	{
		const char *pName = nullptr;
		dbus_message_iter_get_basic(&Array, &pName);
		if(pName)
			Names.emplace_back(pName);
		dbus_message_iter_next(&Array);
	}

	dbus_message_unref(pReply);
	return true;
}

static bool DBusGetMetadata(DBusConnection *pConnection, const char *pService, CPlainState &State)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call(pService, "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", "Get");
	if(!pMessage)
	{
		dbus_error_free(&Error);
		return false;
	}

	const char *pIface = "org.mpris.MediaPlayer2.Player";
	const char *pProp = "Metadata";
	dbus_message_append_args(pMessage, DBUS_TYPE_STRING, &pIface, DBUS_TYPE_STRING, &pProp, DBUS_TYPE_INVALID);

	DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
	dbus_message_unref(pMessage);
	if(!pReply)
	{
		dbus_error_free(&Error);
		return false;
	}

	DBusMessageIter Iter;
	if(!dbus_message_iter_init(pReply, &Iter) || dbus_message_iter_get_arg_type(&Iter) != DBUS_TYPE_VARIANT)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Variant;
	dbus_message_iter_recurse(&Iter, &Variant);
	if(dbus_message_iter_get_arg_type(&Variant) != DBUS_TYPE_ARRAY)
	{
		dbus_message_unref(pReply);
		return false;
	}

	DBusMessageIter Dict;
	dbus_message_iter_recurse(&Variant, &Dict);

	while(dbus_message_iter_get_arg_type(&Dict) == DBUS_TYPE_DICT_ENTRY)
	{
		DBusMessageIter Entry;
		dbus_message_iter_recurse(&Dict, &Entry);

		const char *pKey = nullptr;
		dbus_message_iter_get_basic(&Entry, &pKey);
		dbus_message_iter_next(&Entry);

		if(dbus_message_iter_get_arg_type(&Entry) == DBUS_TYPE_VARIANT)
		{
			DBusMessageIter ValueIter;
			dbus_message_iter_recurse(&Entry, &ValueIter);
			int ArgType = dbus_message_iter_get_arg_type(&ValueIter);

			if(pKey && strcmp(pKey, "xesam:title") == 0 && ArgType == DBUS_TYPE_STRING)
			{
				const char *pString = nullptr;
				dbus_message_iter_get_basic(&ValueIter, &pString);
				if(pString)
					State.m_Title = pString;
			}
			else if(pKey && strcmp(pKey, "xesam:album") == 0 && ArgType == DBUS_TYPE_STRING)
			{
				const char *pString = nullptr;
				dbus_message_iter_get_basic(&ValueIter, &pString);
				if(pString)
					State.m_Album = pString;
			}
			else if(pKey && strcmp(pKey, "xesam:artist") == 0 && ArgType == DBUS_TYPE_ARRAY)
			{
				std::vector<std::string> Artists;
				DBusMessageIter ArrayIter;
				dbus_message_iter_recurse(&ValueIter, &ArrayIter);
				while(dbus_message_iter_get_arg_type(&ArrayIter) == DBUS_TYPE_STRING)
				{
					const char *pString = nullptr;
					dbus_message_iter_get_basic(&ArrayIter, &pString);
					if(pString)
						Artists.emplace_back(pString);
					dbus_message_iter_next(&ArrayIter);
				}
				if(!Artists.empty())
					State.m_Artist = Artists.front();
			}
			else if(pKey && (strcmp(pKey, "mpris:artUrl") == 0 || strcmp(pKey, "xesam:artUrl") == 0) && (ArgType == DBUS_TYPE_STRING || ArgType == DBUS_TYPE_OBJECT_PATH))
			{
				const char *pString = nullptr;
				dbus_message_iter_get_basic(&ValueIter, &pString);
				if(pString)
				{
					State.m_AlbumArtUrl = pString;
				}
			}
			else if(pKey && strcmp(pKey, "mpris:trackid") == 0 && (ArgType == DBUS_TYPE_STRING || ArgType == DBUS_TYPE_OBJECT_PATH))
			{
				const char *pString = nullptr;
				dbus_message_iter_get_basic(&ValueIter, &pString);
				if(pString)
				{
					State.m_TrackId = pString;
				}
			}
			else if(pKey && strcmp(pKey, "mpris:length") == 0 && ArgType == DBUS_TYPE_INT64)
			{
				dbus_int64_t Length = 0;
				dbus_message_iter_get_basic(&ValueIter, &Length);
				if(Length > 0)
					State.m_DurationMs = Length / 1000;
			}
		}

		dbus_message_iter_next(&Dict);
	}

	dbus_message_unref(pReply);
	return true;
}

static std::string DBusChoosePlayer(DBusConnection *pConnection)
{
	std::vector<std::string> Names;
	if(!DBusGetNames(pConnection, Names))
		return std::string();

	std::string Best;
	for(const std::string &Name : Names)
	{
		if(Name.rfind("org.mpris.MediaPlayer2.", 0) != 0)
			continue;

		std::string PlaybackStatus;
		if(DBusGetPropertyString(pConnection, Name.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "PlaybackStatus", PlaybackStatus))
		{
			if(PlaybackStatus == "Playing")
				return Name;
			if(Best.empty())
				Best = Name;
		}
	}

	return Best;
}

static void DBusSendPlayerCommand(DBusConnection *pConnection, const std::string &Service, const char *pCommand)
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusMessage *pMessage = dbus_message_new_method_call(Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", pCommand);
	if(pMessage)
	{
		dbus_connection_send_with_reply_and_block(pConnection, pMessage, 1000, &Error);
		dbus_message_unref(pMessage);
	}
	dbus_error_free(&Error);
}

static bool DBusUpdatePlayerState(DBusConnection *pConnection, const std::string &Service, CPlainState &State)
{
	std::string PlaybackStatus;
	if(!DBusGetPropertyString(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "PlaybackStatus", PlaybackStatus))
		return false;

	State.m_Playing = PlaybackStatus == "Playing";

	std::string Identity;
	if(DBusGetPropertyString(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2", "Identity", Identity) && !Identity.empty())
		State.m_ServiceId = Identity;
	else
		State.m_ServiceId = Service;

	DBusGetPropertyBool(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "CanPlay", State.m_CanPlay);
	DBusGetPropertyBool(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "CanPause", State.m_CanPause);
	DBusGetPropertyBool(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "CanGoPrevious", State.m_CanPrev);
	DBusGetPropertyBool(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "CanGoNext", State.m_CanNext);

	int64_t Position = 0;
	if(DBusGetPropertyInt64(pConnection, Service.c_str(), "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "Position", Position) && Position > 0)
		State.m_PositionMs = Position / 1000;

	DBusGetMetadata(pConnection, Service.c_str(), State);

	return true;
}

void CMediaViewer::ThreadMain()
{
	DBusError Error;
	dbus_error_init(&Error);

	DBusConnection *pConnection = dbus_bus_get(DBUS_BUS_SESSION, &Error);
	if(!pConnection)
	{
		dbus_error_free(&Error);
		return;
	}

	dbus_connection_set_exit_on_disconnect(pConnection, false);

	std::string PrevAlbumArtUrl;
	std::string PrevTrackId;
	CMediaViewer::CAlbumArtColors AlbumArtColors;

	while(!m_StopThread.load(std::memory_order_relaxed))
	{
		CPlainState State;
		bool HasMedia = false;
		const std::string Service = DBusChoosePlayer(pConnection);
		if(!Service.empty())
		{
			HasMedia = DBusUpdatePlayerState(pConnection, Service, State);
		}

		// Decode album art once per track: compare trackid and artUrl
		const bool TrackChanged = (State.m_TrackId != PrevTrackId) || (State.m_AlbumArtUrl != PrevAlbumArtUrl);
		if(TrackChanged)
		{
			PrevAlbumArtUrl = State.m_AlbumArtUrl;
			PrevTrackId = State.m_TrackId;
			AlbumArtColors = CMediaViewer::CAlbumArtColors{};

			if(!State.m_AlbumArtUrl.empty())
			{
				std::vector<uint8_t> RgbaPixels;
				int Width = 0, Height = 0;
				if(DecodeAlbumArtUrl(State.m_AlbumArtUrl, RgbaPixels, Width, Height))
				{
					dbg_msg("Info", "computing album art colors and set shared album art");
					ComputeAlbumArtColors(RgbaPixels, Width, Height, State);
					AlbumArtColors = State.m_AlbumArtColors;
					SetSharedAlbumArt(m_pShared.get(), std::move(RgbaPixels), Width, Height);
				}
				else
				{
					ClearSharedAlbumArt(m_pShared.get());
				}
			}
			else
			{
				ClearSharedAlbumArt(m_pShared.get());
			}
		}
		else
		{
			State.m_AlbumArtColors = AlbumArtColors;
		}

		std::deque<ECommand> Commands;
		{
			std::scoped_lock Lock(m_pShared->m_Mutex);
			m_pShared->m_State = State;
			m_pShared->m_HasMedia = HasMedia;
			Commands.swap(m_pShared->m_Commands);
		}

		if(HasMedia && !Service.empty())
		{
			for(const ECommand Command : Commands)
			{
				switch(Command)
				{
				case ECommand::Prev:
					DBusSendPlayerCommand(pConnection, Service, "Previous");
					break;
				case ECommand::PlayPause:
					DBusSendPlayerCommand(pConnection, Service, "PlayPause");
					break;
				case ECommand::Next:
					DBusSendPlayerCommand(pConnection, Service, "Next");
					break;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
#endif

#if MEDIA_PLAYER_WINRT
void CMediaViewer::ThreadMain()
{
	try
	{
		winrt::init_apartment(winrt::apartment_type::multi_threaded);
	}
	catch(const winrt::hresult_error &)
	{
		return;
	}

	constexpr int NoManagerSleep = 500;
	constexpr int SessionSleep = 150;

	{
		// Release WinRT objects before tearing down the apartment.
		GlobalSystemMediaTransportControlsSessionManager Manager{nullptr};
		GlobalSystemMediaTransportControlsSession Session{nullptr};
		CPlainState State{};
		bool HasMedia = false;
		std::string AlbumArtKey;
		bool AlbumArtLoaded = false;
		auto LastPropsUpdate = std::chrono::steady_clock::now() - std::chrono::seconds(2);
		auto LastAlbumArtAttempt = std::chrono::steady_clock::now() - std::chrono::seconds(10);

		while(!m_StopThread)
		{
			try
			{
				if(!Manager)
				{
					try
					{
						const auto RequestOp = GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
						if(!WaitForAsync(RequestOp, m_StopThread))
						{
							if(m_StopThread.load(std::memory_order_relaxed))
								break;
							Manager = nullptr;
						}
						else
						{
							Manager = RequestOp.GetResults();
						}
					}
					catch(const winrt::hresult_error &)
					{
						Manager = nullptr;
					}
				}

				if(!Manager)
				{
					if(HasMedia)
					{
						ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
						AlbumArtLoaded = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(NoManagerSleep));
					continue;
				}

				Session = Manager.GetCurrentSession();
				if(!Session)
				{
					if(HasMedia)
					{
						ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
						AlbumArtLoaded = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(SessionSleep));
					continue;
				}

				const auto PlaybackInfo = Session.GetPlaybackInfo();
				if(!PlaybackInfo)
				{
					if(HasMedia)
					{
						ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
						AlbumArtLoaded = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(SessionSleep));
					continue;
				}
				const auto Controls = PlaybackInfo.Controls();
				if(!Controls)
				{
					if(HasMedia)
					{
						ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
						AlbumArtLoaded = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(SessionSleep));
					continue;
				}
				State.m_CanPlay = Controls.IsPlayEnabled();
				State.m_CanPause = Controls.IsPauseEnabled();
				State.m_CanPrev = Controls.IsPreviousEnabled();
				State.m_CanNext = Controls.IsNextEnabled();
				State.m_Playing = PlaybackInfo.PlaybackStatus() == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;

				const auto Timeline = Session.GetTimelineProperties();
				if(!Timeline)
				{
					if(HasMedia)
					{
						ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
						AlbumArtLoaded = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(SessionSleep));
					continue;
				}
				const int64_t Start100ns = Timeline.StartTime().count();
				const int64_t End100ns = Timeline.EndTime().count();
				const int64_t Position100ns = Timeline.Position().count();
				const int64_t Duration100ns = End100ns - Start100ns;
				const int64_t PositionRel100ns = Position100ns - Start100ns;
				State.m_DurationMs = Duration100ns > 0 ? Duration100ns / 10000 : 0;
				State.m_PositionMs = PositionRel100ns > 0 ? PositionRel100ns / 10000 : 0;
				HasMedia = true;

				const auto Now = std::chrono::steady_clock::now();
				if(Now - LastPropsUpdate >= std::chrono::seconds(1))
				{
					LastPropsUpdate = Now;
					try
					{
						const auto MediaPropsOp = Session.TryGetMediaPropertiesAsync();
						if(!WaitForAsync(MediaPropsOp, m_StopThread))
						{
							if(m_StopThread.load(std::memory_order_relaxed))
								break;
							ClearMediaDetails(State, AlbumArtKey, m_pShared.get());
							AlbumArtLoaded = false;
						}
						else
						{
							const auto MediaProps = MediaPropsOp.GetResults();
							if(!MediaProps)
							{
								ClearMediaDetails(State, AlbumArtKey, m_pShared.get());
								AlbumArtLoaded = false;
							}
							else
							{
								const std::string ServiceId = Session ? winrt::to_string(Session.SourceAppUserModelId()) : std::string();
								const std::string Title = winrt::to_string(MediaProps.Title());
								const std::string Artist = winrt::to_string(MediaProps.Artist());
								const std::string Album = winrt::to_string(MediaProps.AlbumTitle());

								if(!ServiceId.empty())
								{
									State.m_ServiceId = ServiceId;
								}
								else
								{
									State.m_ServiceId.clear();
								}

								if(!Title.empty())
								{
									State.m_Title = Title;
								}
								else
								{
									State.m_Title.clear();
								}

								if(!Artist.empty())
								{
									State.m_Artist = Artist;
								}
								else
								{
									State.m_Artist.clear();
								}

								if(!Album.empty())
								{
									State.m_Album = Album;
								}
								else
								{
									State.m_Album.clear();
								}

								const bool HasText = !Title.empty() || !Artist.empty() || !Album.empty();
								if(HasText)
								{
									const std::string NewKey = Title + "\n" + Artist + "\n" + Album;
									const bool TrackChanged = NewKey != AlbumArtKey;
									const bool RetryAlbumArt = !AlbumArtLoaded && Now - LastAlbumArtAttempt >= std::chrono::seconds(3);
									if(TrackChanged || RetryAlbumArt)
									{
										AlbumArtKey = NewKey;
										LastAlbumArtAttempt = Now;
										const auto Thumbnail = MediaProps.Thumbnail();
										if(Thumbnail)
											AlbumArtLoaded = UpdateAlbumArtData(m_pShared.get(), State, Thumbnail, m_StopThread);
										else
										{
											ClearAlbumArtColors(State);
											ClearSharedAlbumArt(m_pShared.get());
											AlbumArtLoaded = false;
										}
									}
								}
								else
								{
									ClearMediaDetails(State, AlbumArtKey, m_pShared.get());
									AlbumArtLoaded = false;
								}
							}
						}
					}
					catch(const winrt::hresult_error &)
					{
						ClearMediaDetails(State, AlbumArtKey, m_pShared.get());
						AlbumArtLoaded = false;
					}
				}

				{
					std::scoped_lock Lock(m_pShared->m_Mutex);
					m_pShared->m_State = State;
					m_pShared->m_HasMedia = HasMedia;
				}

				std::deque<ECommand> Commands;
				{
					std::scoped_lock Lock(m_pShared->m_Mutex);
					Commands.swap(m_pShared->m_Commands);
				}
				if(Session)
				{
					for(const auto Command : Commands)
					{
						try
						{
							switch(Command)
							{
							case ECommand::Prev:
								Session.TrySkipPreviousAsync();
								break;
							case ECommand::PlayPause:
								Session.TryTogglePlayPauseAsync();
								break;
							case ECommand::Next:
								Session.TrySkipNextAsync();
								break;
							}
						}
						catch(const winrt::hresult_error &)
						{
						}
					}
				}
			}
			catch(const winrt::hresult_error &)
			{
				ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
				AlbumArtLoaded = false;
			}
			catch(...)
			{
				ResetSharedState(m_pShared.get(), State, HasMedia, AlbumArtKey);
				AlbumArtLoaded = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(SessionSleep));
		}
	}

	winrt::uninit_apartment();
}

void CMediaViewer::AudioThreadMain()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	IMMDeviceEnumerator *pEnumerator = nullptr;
	IMMDevice *pDevice = nullptr;
	IAudioClient *pAudioClient = nullptr;
	IAudioCaptureClient *pCaptureClient = nullptr;

	HRESULT hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		nullptr,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void **)&pEnumerator);

	if(SUCCEEDED(hr))
	{
		// Get default audio endpoint (speakers/headphones - loopback capture)
		hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	}

	if(SUCCEEDED(hr))
	{
		hr = pDevice->Activate(
			__uuidof(IAudioClient),
			CLSCTX_ALL,
			nullptr,
			(void **)&pAudioClient);
	}

	WAVEFORMATEX *pWaveFormat = nullptr;
	if(SUCCEEDED(hr))
	{
		hr = pAudioClient->GetMixFormat(&pWaveFormat);
	}

	if(SUCCEEDED(hr))
	{
		// Initialize audio client in loopback mode
		hr = pAudioClient->Initialize(
			AUDCLNT_SHAREMODE_SHARED,
			AUDCLNT_STREAMFLAGS_LOOPBACK,
			10000000, // 1 second buffer
			0,
			pWaveFormat,
			nullptr);
	}

	if(SUCCEEDED(hr))
	{
		hr = pAudioClient->GetService(
			__uuidof(IAudioCaptureClient),
			(void **)&pCaptureClient);
	}

	if(SUCCEEDED(hr))
	{
		hr = pAudioClient->Start();
	}

	const int SampleRate = pWaveFormat ? pWaveFormat->nSamplesPerSec : 48000;
	const int Channels = pWaveFormat ? pWaveFormat->nChannels : 2;

	std::vector<float> SampleBuffer;
	SampleBuffer.reserve(FFT::FFT_SIZE);

	while(!m_StopAudioThread && SUCCEEDED(hr))
	{
		UINT32 PacketLength = 0;
		hr = pCaptureClient->GetNextPacketSize(&PacketLength);

		while(SUCCEEDED(hr) && PacketLength != 0)
		{
			BYTE *pData = nullptr;
			UINT32 NumFramesAvailable = 0;
			DWORD Flags = 0;

			hr = pCaptureClient->GetBuffer(
				&pData,
				&NumFramesAvailable,
				&Flags,
				nullptr,
				nullptr);

			if(SUCCEEDED(hr))
			{
				if(!(Flags & AUDCLNT_BUFFERFLAGS_SILENT) && pData)
				{
					// Convert to mono float samples
					const float *pFloatData = reinterpret_cast<const float *>(pData);
					for(UINT32 i = 0; i < NumFramesAvailable; ++i)
					{
						float sample = 0.0f;
						for(int ch = 0; ch < Channels; ++ch)
						{
							sample += pFloatData[i * Channels + ch];
						}
						sample /= (float)Channels;

						SampleBuffer.push_back(sample);

						// Process when we have enough samples
						if(SampleBuffer.size() >= FFT::FFT_SIZE)
						{
							ProcessAudioFrame(SampleBuffer.data(), SampleBuffer.size(), SampleRate);
							SampleBuffer.clear();
						}
					}
				}

				pCaptureClient->ReleaseBuffer(NumFramesAvailable);
			}

			hr = pCaptureClient->GetNextPacketSize(&PacketLength);
		}
		// sleep for 1ms
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	if(pAudioClient)
		pAudioClient->Stop();

	if(pCaptureClient)
		pCaptureClient->Release();
	if(pAudioClient)
		pAudioClient->Release();
	if(pDevice)
		pDevice->Release();
	if(pEnumerator)
		pEnumerator->Release();
	if(pWaveFormat)
		CoTaskMemFree(pWaveFormat);

	CoUninitialize();
}

void CMediaViewer::ProcessAudioFrame(const float *pSamples, int NumSamples, int SampleRate)
{
	std::vector<FFT::CComplex> fftResult;
	FFT::ComputeFFT(pSamples, NumSamples, fftResult);

	// Convert FFT bins to frequency bands (logarithmic scale sounds better)
	const int NumBands = CVisualizer::NUM_FREQUENCY_BANDS;
	std::array<float, CVisualizer::NUM_FREQUENCY_BANDS> bands{};

	const int UsableBins = FFT::FFT_SIZE / 2; // Only use first half (Nyquist)
	const float FreqPerBin = (float)SampleRate / FFT::FFT_SIZE;

	// Logarithmic frequency mapping
	const float MinFreq = 48000.0f / FFT::FFT_SIZE; // Calculate at 48kHz sampling rate
	const float MaxFreq = 20000.0f; // 20 kHz
	const float LogMin = std::log10(MinFreq);
	const float LogMax = std::log10(MaxFreq);

	bool AllZero = true;
	for(int band = 0; band < NumBands; ++band)
	{
		const float t0 = (float)band / NumBands;
		const float t1 = (float)(band + 1) / NumBands;
		const float freq0 = std::pow(10.0f, LogMin + t0 * (LogMax - LogMin));
		const float freq1 = std::pow(10.0f, LogMin + t1 * (LogMax - LogMin));

		const int bin0 = std::clamp((int)(freq0 / FreqPerBin), 0, UsableBins - 1);
		const int bin1 = std::clamp((int)(freq1 / FreqPerBin), bin0 + 1, UsableBins);

		// Average magnitude in this frequency range
		float sum = 0.0f;
		int count = 0;
		for(int bin = bin0; bin < bin1; ++bin)
		{
			sum += fftResult[bin].Magnitude();
			++count;
		}

		if(count > 0)
		{
			float magnitude = sum / count;
			// Apply logarithmic scaling and normalize
			magnitude = std::log10(1.0f + magnitude * 100.0f) / 2.0f;
			bands[band] = std::clamp(magnitude, 0.0f, 1.0f);
			if(magnitude > 0.001f)
				AllZero = false;
		}
	}

	// Smooth with previous values
	{
		std::scoped_lock lock(m_pAudioCapture->m_Mutex);
		const float smoothing = 0.7f; // Higher = smoother
		for(int i = 0; i < NumBands; ++i)
		{
			m_pAudioCapture->m_aFrequencyBands[i] =
				m_pAudioCapture->m_aFrequencyBands[i] * smoothing +
				bands[i] * (1.0f - smoothing);
		}
		m_pAudioCapture->m_Active = true;

		if(!AllZero)
			m_pAudioCapture->m_LastFrequencyChange = time_get();

		const int TimeoutSec = 10;
		const int64_t Now = time_get();
		const int64_t Elapsed = Now - m_pAudioCapture->m_LastFrequencyChange;

		// If we've never seen audio (last == 0) or elapsed time exceeds timeout, deactivate
		if(m_pAudioCapture->m_LastFrequencyChange == 0 || Elapsed > time_freq() * TimeoutSec)
		{
			m_pAudioCapture->m_Active = false;
		}
	}
}
#endif

void CMediaViewer::OnInit()
{
#if MEDIA_PLAYER_WINRT
	m_pWinrt = std::make_unique<CWinrt>();
	m_pShared = std::make_unique<CShared>();
	m_pAudioCapture = std::make_unique<CAudioCapture>();

	m_StopThread.store(false, std::memory_order_relaxed);
	m_StopAudioThread.store(false, std::memory_order_relaxed);

	m_Thread = std::thread(&CMediaViewer::ThreadMain, this);
	m_AudioThread = std::thread(&CMediaViewer::AudioThreadMain, this);
#elif MEDIA_PLAYER_DBUS
	m_pDbus = std::make_unique<CDbus>();
	m_pShared = std::make_unique<CShared>();
	m_StopThread.store(false, std::memory_order_relaxed);
	m_Thread = std::thread(&CMediaViewer::ThreadMain, this);
#endif
}

void CMediaViewer::OnShutdown()
{
#if MEDIA_PLAYER_WINRT
	m_StopThread.store(true, std::memory_order_relaxed);
	m_StopAudioThread.store(true, std::memory_order_relaxed);

	if(m_Thread.joinable())
		m_Thread.join();
	if(m_AudioThread.joinable())
		m_AudioThread.join();

	ClearState(m_pWinrt.get(), Graphics());

	m_pAudioCapture.reset();
	m_pShared.reset();
	m_pWinrt.reset();
#elif MEDIA_PLAYER_DBUS
	m_StopThread.store(true, std::memory_order_relaxed);
	if(m_Thread.joinable())
		m_Thread.join();
	m_pDbus.reset();
#endif
}

void CMediaViewer::OnUpdate()
{
#if MEDIA_PLAYER_WINRT
	if(!m_pWinrt)
		return;

	if(!m_pShared)
		return;

	CPlainState SharedState{};
	bool HasMedia = false;
	{
		std::scoped_lock Lock(m_pShared->m_Mutex);
		SharedState = m_pShared->m_State;
		HasMedia = m_pShared->m_HasMedia;
	}

	if(!HasMedia)
	{
		if(m_pWinrt->m_HasMedia)
			ClearState(m_pWinrt.get(), Graphics());
		m_pWinrt->m_HasMedia = false;
	}
	else
	{
		m_pWinrt->m_HasMedia = true;
		m_pWinrt->m_State.m_CanPlay = SharedState.m_CanPlay;
		m_pWinrt->m_State.m_CanPause = SharedState.m_CanPause;
		m_pWinrt->m_State.m_CanPrev = SharedState.m_CanPrev;
		m_pWinrt->m_State.m_CanNext = SharedState.m_CanNext;
		m_pWinrt->m_State.m_Playing = SharedState.m_Playing;
		m_pWinrt->m_State.m_ServiceId = SharedState.m_ServiceId;
		m_pWinrt->m_State.m_Title = SharedState.m_Title;
		m_pWinrt->m_State.m_Artist = SharedState.m_Artist;
		m_pWinrt->m_State.m_Album = SharedState.m_Album;
		m_pWinrt->m_State.m_PositionMs = SharedState.m_PositionMs;
		m_pWinrt->m_State.m_DurationMs = SharedState.m_DurationMs;
		m_pWinrt->m_State.m_AlbumArt.m_Colors = SharedState.m_AlbumArtColors;
	}

	ApplySharedAlbumArt(m_pShared.get(), m_pWinrt.get(), Graphics());
#elif MEDIA_PLAYER_DBUS
	if(!m_pShared || !m_pDbus)
		return;

	CPlainState SharedState{};
	bool HasMedia = false;
	{
		std::scoped_lock Lock(m_pShared->m_Mutex);
		SharedState = m_pShared->m_State;
		HasMedia = m_pShared->m_HasMedia;
	}

	if(!HasMedia)
	{
		if(m_pDbus->m_HasMedia)
		{
			std::scoped_lock Lock(m_pDbus->m_Mutex);
			m_pDbus->m_HasMedia = false;
		}
	}
	else
	{
		std::scoped_lock Lock(m_pDbus->m_Mutex);
		m_pDbus->m_HasMedia = true;
		m_pDbus->m_State.m_CanPlay = SharedState.m_CanPlay;
		m_pDbus->m_State.m_CanPause = SharedState.m_CanPause;
		m_pDbus->m_State.m_CanPrev = SharedState.m_CanPrev;
		m_pDbus->m_State.m_CanNext = SharedState.m_CanNext;
		m_pDbus->m_State.m_Playing = SharedState.m_Playing;
		m_pDbus->m_State.m_ServiceId = SharedState.m_ServiceId;
		m_pDbus->m_State.m_Title = SharedState.m_Title;
		m_pDbus->m_State.m_Artist = SharedState.m_Artist;
		m_pDbus->m_State.m_Album = SharedState.m_Album;
		m_pDbus->m_State.m_PositionMs = SharedState.m_PositionMs;
		m_pDbus->m_State.m_DurationMs = SharedState.m_DurationMs;
		m_pDbus->m_State.m_AlbumArtColors = SharedState.m_AlbumArtColors;
	}

	ApplyDbusSharedAlbumArt(m_pShared.get(), m_pDbus.get(), Graphics());
#endif
}

bool CMediaViewer::GetStateSnapshot(CMediaViewer::CState &State) const
{
	if(!g_Config.m_ClMediaIsland)
	{
		State = CMediaViewer::CState{};
		return false;
	}

#if MEDIA_PLAYER_WINRT
	if(!m_pShared || !m_pWinrt || !m_pAudioCapture)
	{
		State = CMediaViewer::CState{};
		return false;
	}

	if(m_pWinrt && m_pWinrt->m_HasMedia)
	{
		State = m_pWinrt->m_State;
		/* Visualizer Data */
		{
			std::scoped_lock lock(m_pAudioCapture->m_Mutex);
			State.m_Visualizer.m_aFrequencyBands = m_pAudioCapture->m_aFrequencyBands;
			State.m_Visualizer.m_Active = m_pAudioCapture->m_Active;
			State.m_Visualizer.m_LastFrequencyChange = m_pAudioCapture->m_LastFrequencyChange;
		}
		return true;
	}
#elif MEDIA_PLAYER_DBUS
	if(!m_pDbus)
	{
		State = CMediaViewer::CState{};
		return false;
	}

	{
		std::scoped_lock Lock(m_pDbus->m_Mutex);
		if(!m_pDbus->m_HasMedia)
		{
			State = CMediaViewer::CState{};
			return false;
		}

		State.m_CanPlay = m_pDbus->m_State.m_CanPlay;
		State.m_CanPause = m_pDbus->m_State.m_CanPause;
		State.m_CanPrev = m_pDbus->m_State.m_CanPrev;
		State.m_CanNext = m_pDbus->m_State.m_CanNext;
		State.m_Playing = m_pDbus->m_State.m_Playing;
		State.m_ServiceId = m_pDbus->m_State.m_ServiceId;
		State.m_Title = m_pDbus->m_State.m_Title;
		State.m_Artist = m_pDbus->m_State.m_Artist;
		State.m_Album = m_pDbus->m_State.m_Album;
		State.m_PositionMs = m_pDbus->m_State.m_PositionMs;
		State.m_DurationMs = m_pDbus->m_State.m_DurationMs;
		State.m_AlbumArt = m_pDbus->m_AlbumArt;
		State.m_AlbumArt.m_Colors = m_pDbus->m_State.m_AlbumArtColors;
		State.m_PrevAlbumArt = m_pDbus->m_PrevAlbumArt;

		// Simple synthetic visualizer fallback for DBus builds (animated bands)
		// Only show when music is actually playing
		if(State.m_Playing)
		{
			const int NumBands = CVisualizer::NUM_FREQUENCY_BANDS;
			const double t = (double)time_get() / (double)time_freq();
			for(int i = 0; i < NumBands; ++i)
			{
				const double freq = 0.8 + (double)i / (double)NumBands * 3.0;
				double s = std::sin(t * freq * 2.0 + i * 0.13);
				double v = 0.15 + 0.35 * std::pow(std::abs(s), 1.3);
				// slow LFO for gentle breathing
				double lfo = 0.5 + 0.5 * std::sin(t * 0.15 + i * 0.19);
				v *= 0.55 + 0.45 * lfo;
				State.m_Visualizer.m_aFrequencyBands[i] = (float)std::clamp(v, 0.0, 1.0);
			}
			State.m_Visualizer.m_Active = true;
		}
		else
		{
			// When paused, clear visualizer
			for(int i = 0; i < CVisualizer::NUM_FREQUENCY_BANDS; ++i)
			{
				State.m_Visualizer.m_aFrequencyBands[i] = 0.0f;
			}
			State.m_Visualizer.m_Active = false;
		}
		State.m_Visualizer.m_LastFrequencyChange = time_get();
	}
	return true;
#endif

	State = CMediaViewer::CState{};
	return false;
}

void CMediaViewer::Previous()
{
#if MEDIA_PLAYER_WINRT
	if(!m_pShared)
		return;

	std::scoped_lock Lock(m_pShared->m_Mutex);
	m_pShared->m_Commands.push_back(ECommand::Prev);
#elif MEDIA_PLAYER_DBUS
	if(!m_pDbus)
		return;

	std::scoped_lock Lock(m_pDbus->m_Mutex);
	m_pDbus->m_Commands.push_back(ECommand::Prev);
#endif
}

void CMediaViewer::PlayPause()
{
#if MEDIA_PLAYER_WINRT
	if(!m_pShared)
		return;

	std::scoped_lock Lock(m_pShared->m_Mutex);
	m_pShared->m_Commands.push_back(ECommand::PlayPause);
#elif MEDIA_PLAYER_DBUS
	if(!m_pDbus)
		return;

	std::scoped_lock Lock(m_pDbus->m_Mutex);
	m_pDbus->m_Commands.push_back(ECommand::PlayPause);
#endif
}

void CMediaViewer::Next()
{
#if MEDIA_PLAYER_WINRT
	if(!m_pShared)
		return;

	std::scoped_lock Lock(m_pShared->m_Mutex);
	m_pShared->m_Commands.push_back(ECommand::Next);
#elif MEDIA_PLAYER_DBUS
	if(!m_pDbus)
		return;

	std::scoped_lock Lock(m_pDbus->m_Mutex);
	m_pDbus->m_Commands.push_back(ECommand::Next);
#endif
}

void CMediaViewer::CVisualizer::GetBands(float *pOutBands, int NumBands) const
{
	const int CopyCount = std::min(NumBands, NUM_FREQUENCY_BANDS);
	for(int i = 0; i < CopyCount; ++i)
	{
		pOutBands[i] = m_aFrequencyBands[i];
	}
}

float CMediaViewer::CVisualizer::GetAverageBand() const
{
	float Sum = 0.0f;
	for(float Band : m_aFrequencyBands)
	{
		Sum += Band;
	}
	return Sum / NUM_FREQUENCY_BANDS;
}
