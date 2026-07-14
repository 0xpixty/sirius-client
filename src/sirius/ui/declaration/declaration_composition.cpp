/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "declaration_composition.h"

#include <vector>

namespace sirius::ui::declaration
{

	CUiDeclarationSnapshot ComposeUiDeclarationSnapshot(const CUiDeclarationRegistrationPlan &RegistrationPlan)
	{
		std::vector<CUiSurfaceDeclarationSnapshot> Surfaces;

		for(const auto &Contribution : RegistrationPlan.ContributionsInRegistrationOrder())
		{
			for(const auto &Surface : Contribution.Declarations().Surfaces())
			{
				Surfaces.emplace_back(Surface.Surface(), Surface.Elements(), Surface.Properties());
			}
		}

		return CUiDeclarationSnapshot(std::move(Surfaces));
	}

} // namespace sirius::ui::declaration
