/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_validation.h"

#include <cmath>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::render
{
	namespace
	{
		bool IsFinite(float Value) noexcept
		{
			return std::isfinite(Value);
		}

		bool IsNonNegativeFinite(const sirius::ui::layout::CLayoutScalar &Value) noexcept
		{
			return IsFinite(Value.Value()) && Value.Value() >= 0.0f;
		}

		bool IsFiniteBounds(const sirius::ui::layout::CLayoutRect &Bounds) noexcept
		{
			return IsFinite(Bounds.X().Value()) &&
				IsFinite(Bounds.Y().Value()) &&
				IsNonNegativeFinite(Bounds.Width()) &&
				IsNonNegativeFinite(Bounds.Height());
		}

		bool IsColorChannelValid(float Value) noexcept
		{
			return IsFinite(Value) && Value >= 0.0f && Value <= 1.0f;
		}

		bool IsColorValid(const CRenderColor &Color) noexcept
		{
			return IsColorChannelValid(Color.Red()) &&
				IsColorChannelValid(Color.Green()) &&
				IsColorChannelValid(Color.Blue()) &&
				IsColorChannelValid(Color.Alpha());
		}

		bool IsSupportedRenderCommandKind(ERenderCommandKind Kind) noexcept
		{
			switch(Kind)
			{
			case ERenderCommandKind::PushClip:
			case ERenderCommandKind::PopClip:
			case ERenderCommandKind::Rectangle:
			case ERenderCommandKind::GradientRectangle:
			case ERenderCommandKind::Outline:
			case ERenderCommandKind::Text:
			case ERenderCommandKind::IconText:
			case ERenderCommandKind::ImageSpriteReference:
			case ERenderCommandKind::CursorRequest:
			case ERenderCommandKind::DebugBounds:
				return true;
			}

			return false;
		}

		void AddDiagnostic(
			std::vector<CRenderDiagnostic> &Diagnostics,
			ERenderDiagnosticCode Code,
			std::string Message,
			const CRenderCommandListSnapshot &CommandList,
			const CRenderCommandSnapshot &Command,
			std::size_t StableOrderOffset)
		{
			Diagnostics.emplace_back(
				ERenderDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				CommandList.SurfaceId(),
				CommandList.SceneId(),
				Command.ElementId(),
				Command.Id(),
				StableOrderOffset + Diagnostics.size());
		}

		void AddClipStackDiagnostic(
			std::vector<CRenderDiagnostic> &Diagnostics,
			std::string Message,
			const CRenderCommandListSnapshot &CommandList,
			std::optional<CRenderCommandId> CommandId,
			std::size_t StableOrderOffset)
		{
			Diagnostics.emplace_back(
				ERenderDiagnosticSeverity::Error,
				ERenderDiagnosticCode::InvalidClipStack,
				std::move(Message),
				CommandList.SurfaceId(),
				CommandList.SceneId(),
				std::nullopt,
				std::move(CommandId),
				StableOrderOffset + Diagnostics.size());
		}
	}

	CRenderDiagnosticSnapshot ValidateUiRenderCommandListSnapshot(
		const CRenderCommandListSnapshot &CommandList)
	{
		return ValidateUiRenderCommandListSnapshot(CommandList, 0);
	}

	CRenderDiagnosticSnapshot ValidateUiRenderCommandListSnapshot(
		const CRenderCommandListSnapshot &CommandList,
		std::size_t StableOrderOffset)
	{
		std::vector<CRenderDiagnostic> Diagnostics;
		std::size_t ClipDepth = 0;

		for(const auto &Command : CommandList.Commands())
		{
			if(Command.Id().IsEmpty())
			{
				AddDiagnostic(
					Diagnostics,
					ERenderDiagnosticCode::EmptyCommandId,
					"Render command ID must not be empty.",
					CommandList,
					Command,
					StableOrderOffset);
			}

			if(!IsSupportedRenderCommandKind(Command.Kind()))
			{
				AddDiagnostic(
					Diagnostics,
					ERenderDiagnosticCode::UnsupportedCommandKind,
					"Render command uses an unsupported command kind.",
					CommandList,
					Command,
					StableOrderOffset);
			}

			if(!IsFiniteBounds(Command.Bounds()))
			{
				AddDiagnostic(
					Diagnostics,
					ERenderDiagnosticCode::InvalidBounds,
					"Render command bounds must have finite coordinates and finite non-negative size.",
					CommandList,
					Command,
					StableOrderOffset);
			}

			if(!IsColorValid(Command.PrimaryColor()) || !IsColorValid(Command.SecondaryColor()))
			{
				AddDiagnostic(
					Diagnostics,
					ERenderDiagnosticCode::InvalidColor,
					"Render command colors must have finite channels in the inclusive range [0, 1].",
					CommandList,
					Command,
					StableOrderOffset);
			}

			if(Command.Kind() == ERenderCommandKind::PushClip)
			{
				++ClipDepth;
			}
			else if(Command.Kind() == ERenderCommandKind::PopClip)
			{
				if(ClipDepth == 0)
				{
					AddClipStackDiagnostic(
						Diagnostics,
						"Render command list attempts to pop an empty clip stack.",
						CommandList,
						Command.Id(),
						StableOrderOffset);
				}
				else
				{
					--ClipDepth;
				}
			}
		}

		if(ClipDepth != 0)
		{
			AddClipStackDiagnostic(
				Diagnostics,
				"Render command list leaves clip commands unbalanced.",
				CommandList,
				std::nullopt,
				StableOrderOffset);
		}

		return CRenderDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::render
