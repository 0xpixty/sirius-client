/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_INPUT_INPUT_VALIDATION_H
#define SIRIUS_UI_INPUT_INPUT_VALIDATION_H

#include "input_diagnostic.h"

#include <cstddef>

namespace sirius::ui::input
{

	CUiInputDiagnosticSnapshot ValidateUiInputSnapshot(
		const CUiInputSnapshot &Snapshot,
		std::size_t StableOrderOffset = 0);

} // namespace sirius::ui::input

#endif
