/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_VALIDATION_H
#define SIRIUS_UI_RENDER_RENDER_VALIDATION_H

#include "render_diagnostic.h"

#include <cstddef>

namespace sirius::ui::render
{

	CRenderDiagnosticSnapshot ValidateUiRenderCommandListSnapshot(
		const CRenderCommandListSnapshot &CommandList);

	CRenderDiagnosticSnapshot ValidateUiRenderCommandListSnapshot(
		const CRenderCommandListSnapshot &CommandList,
		std::size_t StableOrderOffset);

} // namespace sirius::ui::render

#endif
