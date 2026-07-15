/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_runtime_collection.h"

#include <utility>

namespace sirius::ui::theme
{

	CThemeRuntimeCollectionSnapshot::CThemeRuntimeCollectionSnapshot(std::vector<CThemeRuntimeSnapshot> Themes) :
		m_Themes(std::move(Themes))
	{
	}

	CThemeRuntimeCollectionSnapshot::~CThemeRuntimeCollectionSnapshot() noexcept = default;

	const std::vector<CThemeRuntimeSnapshot> &CThemeRuntimeCollectionSnapshot::Themes() const noexcept
	{
		return m_Themes;
	}

	std::size_t CThemeRuntimeCollectionSnapshot::ThemeCount() const noexcept
	{
		return m_Themes.size();
	}

	bool CThemeRuntimeCollectionSnapshot::IsEmpty() const noexcept
	{
		return m_Themes.empty();
	}

	bool CThemeRuntimeCollectionSnapshot::HasErrors() const noexcept
	{
		for(const auto &Theme : m_Themes)
		{
			if(Theme.HasErrors())
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::theme
