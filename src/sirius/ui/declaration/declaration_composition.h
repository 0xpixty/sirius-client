/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_DECLARATION_COMPOSITION_H
#define SIRIUS_UI_DECLARATION_DECLARATION_COMPOSITION_H

#include "declaration_registration_plan.h"
#include "declaration_snapshot.h"

namespace sirius::ui::declaration
{

	CUiDeclarationSnapshot ComposeUiDeclarationSnapshot(const CUiDeclarationRegistrationPlan &RegistrationPlan);

} // namespace sirius::ui::declaration

#endif
