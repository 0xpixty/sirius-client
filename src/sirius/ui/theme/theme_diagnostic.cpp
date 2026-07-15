/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_diagnostic.h"

#include <utility>

namespace sirius::ui::theme
{

	CThemeDiagnostic::CThemeDiagnostic(
		EThemeDiagnosticSeverity Severity,
		EThemeDiagnosticCode Code,
		std::string Message,
		std::optional<CThemeId> ThemeId,
		std::optional<CThemeTokenId> TokenId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_ThemeId(std::move(ThemeId)),
		m_TokenId(std::move(TokenId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CThemeDiagnostic::~CThemeDiagnostic() noexcept = default;

	EThemeDiagnosticSeverity CThemeDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	EThemeDiagnosticCode CThemeDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CThemeDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<CThemeId> &CThemeDiagnostic::ThemeId() const noexcept
	{
		return m_ThemeId;
	}

	const std::optional<CThemeTokenId> &CThemeDiagnostic::TokenId() const noexcept
	{
		return m_TokenId;
	}

	std::size_t CThemeDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CThemeDiagnosticSnapshot::CThemeDiagnosticSnapshot(std::vector<CThemeDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CThemeDiagnosticSnapshot::~CThemeDiagnosticSnapshot() noexcept = default;

	const std::vector<CThemeDiagnostic> &CThemeDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CThemeDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CThemeDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CThemeDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const auto &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == EThemeDiagnosticSeverity::Error ||
				Diagnostic.Severity() == EThemeDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::theme
