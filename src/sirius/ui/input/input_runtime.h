/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_INPUT_INPUT_RUNTIME_H
#define SIRIUS_UI_INPUT_INPUT_RUNTIME_H

#include "input_diagnostic.h"

namespace sirius::ui::input
{

	class CUiInputRuntimeSnapshot final
	{
	public:
		CUiInputRuntimeSnapshot(
			CUiInputSnapshot Input,
			CUiInputDiagnosticSnapshot Diagnostics);
		~CUiInputRuntimeSnapshot() noexcept;

		const CUiInputSnapshot &Input() const noexcept;
		const CUiInputDiagnosticSnapshot &Diagnostics() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CUiInputSnapshot m_Input;
		CUiInputDiagnosticSnapshot m_Diagnostics;
	};

	CUiInputRuntimeSnapshot ProjectUiInputRuntimeSnapshot(const CUiInputSnapshot &Input);

} // namespace sirius::ui::input

#endif
