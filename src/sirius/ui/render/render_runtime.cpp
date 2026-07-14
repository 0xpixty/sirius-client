/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_runtime.h"

#include <utility>

namespace sirius::ui::render
{

	CRenderCommandListCollectionSnapshot::CRenderCommandListCollectionSnapshot(std::vector<CRenderCommandListSnapshot> CommandLists) :
		m_CommandLists(std::move(CommandLists))
	{
	}

	CRenderCommandListCollectionSnapshot::~CRenderCommandListCollectionSnapshot() noexcept = default;

	const std::vector<CRenderCommandListSnapshot> &CRenderCommandListCollectionSnapshot::CommandLists() const noexcept
	{
		return m_CommandLists;
	}

	std::size_t CRenderCommandListCollectionSnapshot::CommandListCount() const noexcept
	{
		return m_CommandLists.size();
	}

	bool CRenderCommandListCollectionSnapshot::IsEmpty() const noexcept
	{
		return m_CommandLists.empty();
	}

	CRenderRuntimeSnapshot::CRenderRuntimeSnapshot(
		CRenderCommandListCollectionSnapshot CommandLists,
		CRenderDiagnosticSnapshot Diagnostics) :
		m_CommandLists(std::move(CommandLists)),
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CRenderRuntimeSnapshot::~CRenderRuntimeSnapshot() noexcept = default;

	const CRenderCommandListCollectionSnapshot &CRenderRuntimeSnapshot::CommandLists() const noexcept
	{
		return m_CommandLists;
	}

	const CRenderDiagnosticSnapshot &CRenderRuntimeSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	bool CRenderRuntimeSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CRenderRuntimeSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

} // namespace sirius::ui::render
