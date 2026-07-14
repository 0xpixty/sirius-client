/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_AGGREGATE_SURFACE_VALIDATION_H
#define SIRIUS_UI_SCENE_AGGREGATE_SURFACE_VALIDATION_H

#include "surface_runtime_diagnostic.h"

#include <sirius/ui/declaration/declaration_snapshot.h>

namespace sirius::ui::scene
{

	CSurfaceRuntimeDiagnosticSnapshot ValidateAggregateSurfaceDeclarations(
		const sirius::ui::declaration::CUiDeclarationSnapshot &Declarations);

} // namespace sirius::ui::scene

#endif
