/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_validation.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::layout
{
	namespace
	{
		bool IsNonNegativeFinite(const CLayoutScalar &Value) noexcept
		{
			const float RawValue = Value.Value();
			return RawValue == RawValue && RawValue >= 0.0f;
		}

		bool IsOrdered(const CLayoutScalar &Minimum, const CLayoutScalar &Preferred, const CLayoutScalar &Maximum) noexcept
		{
			return Minimum.Value() <= Preferred.Value() && Preferred.Value() <= Maximum.Value();
		}

		bool IsSupportedLayoutKind(ELayoutKind Kind) noexcept
		{
			switch(Kind)
			{
			case ELayoutKind::FixedRect:
			case ELayoutKind::Stack:
			case ELayoutKind::DockFill:
			case ELayoutKind::ProportionalSplit:
			case ELayoutKind::ScrollContentExtent:
				return true;
			}

			return false;
		}

		void AddDiagnostic(
			std::vector<CLayoutDiagnostic> &Diagnostics,
			ELayoutDiagnosticCode Code,
			std::string Message,
			const CLayoutSnapshot &Layout,
			const sirius::ui::scene::CUiElementId &ElementId,
			std::size_t StableOrderOffset)
		{
			Diagnostics.emplace_back(
				ELayoutDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				Layout.SurfaceId(),
				Layout.SceneId(),
				ElementId,
				StableOrderOffset + Diagnostics.size());
		}

		bool HasInvalidBounds(const CLayoutRect &Bounds) noexcept
		{
			return !IsNonNegativeFinite(Bounds.Width()) || !IsNonNegativeFinite(Bounds.Height());
		}

		bool HasInvalidSize(const CLayoutSize &Size) noexcept
		{
			return !IsNonNegativeFinite(Size.Width()) || !IsNonNegativeFinite(Size.Height());
		}

		bool HasInvalidSizeConstraints(const CLayoutSizeConstraints &Constraints) noexcept
		{
			return HasInvalidSize(Constraints.Minimum()) ||
				HasInvalidSize(Constraints.Preferred()) ||
				HasInvalidSize(Constraints.Maximum()) ||
				!IsOrdered(Constraints.Minimum().Width(), Constraints.Preferred().Width(), Constraints.Maximum().Width()) ||
				!IsOrdered(Constraints.Minimum().Height(), Constraints.Preferred().Height(), Constraints.Maximum().Height());
		}
	}

	CLayoutDiagnosticSnapshot ValidateUiLayoutSnapshot(const CLayoutSnapshot &Layout)
	{
		return ValidateUiLayoutSnapshot(Layout, 0);
	}

	CLayoutDiagnosticSnapshot ValidateUiLayoutSnapshot(const CLayoutSnapshot &Layout, std::size_t StableOrderOffset)
	{
		std::vector<CLayoutDiagnostic> Diagnostics;

		for(const auto &Element : Layout.Elements())
		{
			if(!IsSupportedLayoutKind(Element.Kind()))
			{
				AddDiagnostic(
					Diagnostics,
					ELayoutDiagnosticCode::UnsupportedLayoutKind,
					"Layout element uses an unsupported layout kind.",
					Layout,
					Element.ElementId(),
					StableOrderOffset);
			}

			if(HasInvalidBounds(Element.Bounds()))
			{
				AddDiagnostic(
					Diagnostics,
					ELayoutDiagnosticCode::InvalidBounds,
					"Layout element bounds must have finite non-negative width and height.",
					Layout,
					Element.ElementId(),
					StableOrderOffset);
			}

			if(HasInvalidSizeConstraints(Element.SizeConstraints()))
			{
				AddDiagnostic(
					Diagnostics,
					ELayoutDiagnosticCode::InvalidSizeConstraints,
					"Layout element size constraints must be finite, non-negative, and ordered minimum <= preferred <= maximum.",
					Layout,
					Element.ElementId(),
					StableOrderOffset);
			}
		}

		return CLayoutDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::layout
