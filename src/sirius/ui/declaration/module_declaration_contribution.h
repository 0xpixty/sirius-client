/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_MODULE_DECLARATION_CONTRIBUTION_H
#define SIRIUS_UI_DECLARATION_MODULE_DECLARATION_CONTRIBUTION_H

#include "declaration_snapshot.h"

#include <sirius/platform/modules/module_id.h>

#include <cstddef>
#include <vector>

namespace sirius::ui::declaration
{

	class CUiModuleDeclarationContribution final
	{
	public:
		CUiModuleDeclarationContribution(
			sirius::platform::modules::CModuleId ModuleId,
			CUiDeclarationSnapshot Declarations,
			std::size_t ModuleRuntimeOrderIndex);
		~CUiModuleDeclarationContribution() noexcept;

		const sirius::platform::modules::CModuleId &ModuleId() const noexcept;
		const CUiDeclarationSnapshot &Declarations() const noexcept;
		std::size_t ModuleRuntimeOrderIndex() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		sirius::platform::modules::CModuleId m_ModuleId;
		CUiDeclarationSnapshot m_Declarations;
		std::size_t m_ModuleRuntimeOrderIndex = 0;
	};

	class CUiModuleDeclarationContributionSnapshot final
	{
	public:
		explicit CUiModuleDeclarationContributionSnapshot(std::vector<CUiModuleDeclarationContribution> Contributions);
		~CUiModuleDeclarationContributionSnapshot() noexcept;

		const std::vector<CUiModuleDeclarationContribution> &Contributions() const noexcept;
		std::size_t ContributionCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiModuleDeclarationContribution> m_Contributions;
	};

} // namespace sirius::ui::declaration

#endif
