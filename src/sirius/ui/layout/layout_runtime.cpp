/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_runtime.h"

#include <utility>

namespace sirius::ui::layout
{

	CLayoutSnapshotList::CLayoutSnapshotList(std::vector<CLayoutSnapshot> Layouts) :
		m_Layouts(std::move(Layouts))
	{
	}

	CLayoutSnapshotList::~CLayoutSnapshotList() noexcept = default;

	const std::vector<CLayoutSnapshot> &CLayoutSnapshotList::Layouts() const noexcept
	{
		return m_Layouts;
	}

	std::size_t CLayoutSnapshotList::LayoutCount() const noexcept
	{
		return m_Layouts.size();
	}

	bool CLayoutSnapshotList::IsEmpty() const noexcept
	{
		return m_Layouts.empty();
	}

	CLayoutRuntimeSnapshot::CLayoutRuntimeSnapshot(
		CLayoutSnapshotList Layouts,
		CLayoutDiagnosticSnapshot Diagnostics) :
		m_Layouts(std::move(Layouts)),
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CLayoutRuntimeSnapshot::~CLayoutRuntimeSnapshot() noexcept = default;

	const CLayoutSnapshotList &CLayoutRuntimeSnapshot::Layouts() const noexcept
	{
		return m_Layouts;
	}

	const CLayoutDiagnosticSnapshot &CLayoutRuntimeSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	bool CLayoutRuntimeSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CLayoutRuntimeSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

} // namespace sirius::ui::layout
