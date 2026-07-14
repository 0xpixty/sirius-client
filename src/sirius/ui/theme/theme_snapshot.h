/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_SNAPSHOT_H
#define SIRIUS_UI_THEME_THEME_SNAPSHOT_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace sirius::ui::theme
{

	class CThemeId final
	{
	public:
		explicit CThemeId(std::string Value);
		~CThemeId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CThemeId &Other) const noexcept;
		bool operator!=(const CThemeId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CThemeTokenId final
	{
	public:
		explicit CThemeTokenId(std::string Value);
		~CThemeTokenId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CThemeTokenId &Other) const noexcept;
		bool operator!=(const CThemeTokenId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CThemeVersion final
	{
	public:
		explicit CThemeVersion(std::uint32_t Value) noexcept;
		~CThemeVersion() noexcept;

		std::uint32_t Value() const noexcept;
		bool IsInitial() const noexcept;

	private:
		std::uint32_t m_Value = 0;
	};

	enum class EThemeTokenCategory
	{
		Color,
		Spacing,
		Radius,
		Border,
		Typography,
		Opacity,
		ElevationGlow,
		AnimationDurationEasing,
		IconReference,
		StateOverlay,
	};

	enum class EThemeStateDimension
	{
		Normal,
		Hovered,
		Focused,
		Pressed,
		Captured,
		Disabled,
		Selected,
		Error,
		Warning,
		Success,
	};

	enum class EThemeAccessibilityModifier
	{
		ReducedMotion,
		HighContrast,
		MinimumTextSize,
		FocusIndicator,
		ColorBlindSafeSemanticTokens,
	};

	class CThemeTokenSnapshot final
	{
	public:
		CThemeTokenSnapshot(
			CThemeTokenId Id,
			EThemeTokenCategory Category,
			EThemeStateDimension State,
			std::string StablePayload,
			bool Required,
			std::size_t StableOrderIndex);
		~CThemeTokenSnapshot() noexcept;

		const CThemeTokenId &Id() const noexcept;
		EThemeTokenCategory Category() const noexcept;
		EThemeStateDimension State() const noexcept;
		const std::string &StablePayload() const noexcept;
		bool Required() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		CThemeTokenId m_Id;
		EThemeTokenCategory m_Category = EThemeTokenCategory::Color;
		EThemeStateDimension m_State = EThemeStateDimension::Normal;
		std::string m_StablePayload;
		bool m_Required = true;
		std::size_t m_StableOrderIndex = 0;
	};

	class CThemeSnapshot final
	{
	public:
		CThemeSnapshot(
			CThemeId Id,
			CThemeVersion Version,
			std::vector<CThemeTokenSnapshot> Tokens,
			std::vector<CThemeId> FallbackChain,
			std::vector<EThemeAccessibilityModifier> AccessibilityModifiers);
		~CThemeSnapshot() noexcept;

		const CThemeId &Id() const noexcept;
		const CThemeVersion &Version() const noexcept;
		const std::vector<CThemeTokenSnapshot> &Tokens() const noexcept;
		const std::vector<CThemeId> &FallbackChain() const noexcept;
		const std::vector<EThemeAccessibilityModifier> &AccessibilityModifiers() const noexcept;
		std::size_t TokenCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		CThemeId m_Id;
		CThemeVersion m_Version;
		std::vector<CThemeTokenSnapshot> m_Tokens;
		std::vector<CThemeId> m_FallbackChain;
		std::vector<EThemeAccessibilityModifier> m_AccessibilityModifiers;
	};

} // namespace sirius::ui::theme

#endif
