/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_DIAGNOSTIC_H
#define SIRIUS_UI_THEME_THEME_DIAGNOSTIC_H

#include "theme_snapshot.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::theme
{

	enum class EThemeDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class EThemeDiagnosticCode
	{
		Unknown,
		EmptyThemeId,
		EmptyTokenId,
		UnsupportedTokenCategory,
		UnsupportedStateDimension,
		DuplicateToken,
		MissingRequiredToken,
		MissingFallbackTheme,
		CircularFallback,
		TypeMismatch,
		CircularAlias,
	};

	class CThemeDiagnostic final
	{
	public:
		CThemeDiagnostic(
			EThemeDiagnosticSeverity Severity,
			EThemeDiagnosticCode Code,
			std::string Message,
			std::optional<CThemeId> ThemeId,
			std::optional<CThemeTokenId> TokenId,
			std::size_t StableOrderIndex);
		~CThemeDiagnostic() noexcept;

		EThemeDiagnosticSeverity Severity() const noexcept;
		EThemeDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<CThemeId> &ThemeId() const noexcept;
		const std::optional<CThemeTokenId> &TokenId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		EThemeDiagnosticSeverity m_Severity = EThemeDiagnosticSeverity::Info;
		EThemeDiagnosticCode m_Code = EThemeDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<CThemeId> m_ThemeId;
		std::optional<CThemeTokenId> m_TokenId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CThemeDiagnosticSnapshot final
	{
	public:
		explicit CThemeDiagnosticSnapshot(std::vector<CThemeDiagnostic> Diagnostics);
		~CThemeDiagnosticSnapshot() noexcept;

		const std::vector<CThemeDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CThemeDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::theme

#endif
