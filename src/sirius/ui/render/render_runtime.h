/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_RUNTIME_H
#define SIRIUS_UI_RENDER_RENDER_RUNTIME_H

#include "render_command_snapshot.h"
#include "render_diagnostic.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::render
{

	class CRenderCommandListCollectionSnapshot final
	{
	public:
		explicit CRenderCommandListCollectionSnapshot(std::vector<CRenderCommandListSnapshot> CommandLists);
		~CRenderCommandListCollectionSnapshot() noexcept;

		const std::vector<CRenderCommandListSnapshot> &CommandLists() const noexcept;
		std::size_t CommandListCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CRenderCommandListSnapshot> m_CommandLists;
	};

	class CRenderRuntimeSnapshot final
	{
	public:
		CRenderRuntimeSnapshot(
			CRenderCommandListCollectionSnapshot CommandLists,
			CRenderDiagnosticSnapshot Diagnostics);
		~CRenderRuntimeSnapshot() noexcept;

		const CRenderCommandListCollectionSnapshot &CommandLists() const noexcept;
		const CRenderDiagnosticSnapshot &Diagnostics() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CRenderCommandListCollectionSnapshot m_CommandLists;
		CRenderDiagnosticSnapshot m_Diagnostics;
	};

} // namespace sirius::ui::render

#endif
