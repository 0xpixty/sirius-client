/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_runtime.h"

#include "theme_validation.h"

#include <utility>

namespace sirius::ui::theme
{

	CThemeRuntimeSnapshot::CThemeRuntimeSnapshot(
		CThemeSnapshot Theme,
		CThemeDiagnosticSnapshot Diagnostics) :
		m_Theme(std::move(Theme)),
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CThemeRuntimeSnapshot::~CThemeRuntimeSnapshot() noexcept = default;

	const CThemeSnapshot &CThemeRuntimeSnapshot::Theme() const noexcept
	{
		return m_Theme;
	}

	const CThemeDiagnosticSnapshot &CThemeRuntimeSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	bool CThemeRuntimeSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CThemeRuntimeSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

	CThemeRuntimeSnapshot ProjectUiThemeRuntimeSnapshot(const CThemeSnapshot &Theme)
	{
		return CThemeRuntimeSnapshot(
			Theme,
			ValidateUiThemeSnapshot(Theme));
	}

} // namespace sirius::ui::theme
