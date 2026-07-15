/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_RUNTIME_COLLECTION_H
#define SIRIUS_UI_THEME_THEME_RUNTIME_COLLECTION_H

#include "theme_runtime.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::theme
{

	class CThemeRuntimeCollectionSnapshot final
	{
	public:
		explicit CThemeRuntimeCollectionSnapshot(std::vector<CThemeRuntimeSnapshot> Themes);
		~CThemeRuntimeCollectionSnapshot() noexcept;

		const std::vector<CThemeRuntimeSnapshot> &Themes() const noexcept;
		std::size_t ThemeCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CThemeRuntimeSnapshot> m_Themes;
	};

} // namespace sirius::ui::theme

#endif
