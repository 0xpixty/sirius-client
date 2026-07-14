/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_declaration_contribution.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiModuleDeclarationContribution::CUiModuleDeclarationContribution(
		sirius::platform::modules::CModuleId ModuleId,
		CUiDeclarationSnapshot Declarations,
		std::size_t ModuleRuntimeOrderIndex) :
		m_ModuleId(std::move(ModuleId)),
		m_Declarations(std::move(Declarations)),
		m_ModuleRuntimeOrderIndex(ModuleRuntimeOrderIndex)
	{
	}

	CUiModuleDeclarationContribution::~CUiModuleDeclarationContribution() noexcept = default;

	const sirius::platform::modules::CModuleId &CUiModuleDeclarationContribution::ModuleId() const noexcept
	{
		return m_ModuleId;
	}

	const CUiDeclarationSnapshot &CUiModuleDeclarationContribution::Declarations() const noexcept
	{
		return m_Declarations;
	}

	std::size_t CUiModuleDeclarationContribution::ModuleRuntimeOrderIndex() const noexcept
	{
		return m_ModuleRuntimeOrderIndex;
	}

	bool CUiModuleDeclarationContribution::IsEmpty() const noexcept
	{
		return m_Declarations.IsEmpty();
	}

	CUiModuleDeclarationContributionSnapshot::CUiModuleDeclarationContributionSnapshot(std::vector<CUiModuleDeclarationContribution> Contributions) :
		m_Contributions(std::move(Contributions))
	{
	}

	CUiModuleDeclarationContributionSnapshot::~CUiModuleDeclarationContributionSnapshot() noexcept = default;

	const std::vector<CUiModuleDeclarationContribution> &CUiModuleDeclarationContributionSnapshot::Contributions() const noexcept
	{
		return m_Contributions;
	}

	std::size_t CUiModuleDeclarationContributionSnapshot::ContributionCount() const noexcept
	{
		return m_Contributions.size();
	}

	bool CUiModuleDeclarationContributionSnapshot::IsEmpty() const noexcept
	{
		return m_Contributions.empty();
	}

} // namespace sirius::ui::declaration
