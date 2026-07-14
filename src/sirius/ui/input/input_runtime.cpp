/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_runtime.h"

#include "input_validation.h"

#include <utility>

namespace sirius::ui::input
{

	CUiInputRuntimeSnapshot::CUiInputRuntimeSnapshot(
		CUiInputSnapshot Input,
		CUiInputDiagnosticSnapshot Diagnostics) :
		m_Input(std::move(Input)),
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CUiInputRuntimeSnapshot::~CUiInputRuntimeSnapshot() noexcept = default;

	const CUiInputSnapshot &CUiInputRuntimeSnapshot::Input() const noexcept
	{
		return m_Input;
	}

	const CUiInputDiagnosticSnapshot &CUiInputRuntimeSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	bool CUiInputRuntimeSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CUiInputRuntimeSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

	CUiInputRuntimeSnapshot ProjectUiInputRuntimeSnapshot(const CUiInputSnapshot &Input)
	{
		return CUiInputRuntimeSnapshot(
			Input,
			ValidateUiInputSnapshot(Input));
	}

} // namespace sirius::ui::input
