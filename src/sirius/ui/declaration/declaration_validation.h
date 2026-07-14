/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_DECLARATION_VALIDATION_H
#define SIRIUS_UI_DECLARATION_DECLARATION_VALIDATION_H

#include "declaration_diagnostic.h"
#include "declaration_snapshot.h"

namespace sirius::ui::declaration
{

	CDeclarationDiagnosticSnapshot ValidateUiDeclarationSnapshot(const CUiDeclarationSnapshot &Declarations);

} // namespace sirius::ui::declaration

#endif
