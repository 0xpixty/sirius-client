/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_RUNTIME_H
#define SIRIUS_UI_LAYOUT_LAYOUT_RUNTIME_H

#include "layout_diagnostic.h"
#include "layout_snapshot.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::layout
{

	class CLayoutSnapshotList final
	{
	public:
		explicit CLayoutSnapshotList(std::vector<CLayoutSnapshot> Layouts);
		~CLayoutSnapshotList() noexcept;

		const std::vector<CLayoutSnapshot> &Layouts() const noexcept;
		std::size_t LayoutCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CLayoutSnapshot> m_Layouts;
	};

	class CLayoutRuntimeSnapshot final
	{
	public:
		CLayoutRuntimeSnapshot(
			CLayoutSnapshotList Layouts,
			CLayoutDiagnosticSnapshot Diagnostics);
		~CLayoutRuntimeSnapshot() noexcept;

		const CLayoutSnapshotList &Layouts() const noexcept;
		const CLayoutDiagnosticSnapshot &Diagnostics() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CLayoutSnapshotList m_Layouts;
		CLayoutDiagnosticSnapshot m_Diagnostics;
	};

} // namespace sirius::ui::layout

#endif
