/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_contract_resolution.h"

#include "module_definition.h"
#include "module_registration_plan.h"

#include <utility>

namespace sirius::platform::modules
{
namespace
{

	class CExportCandidate final
	{
	public:
		CExportCandidate(CModuleId ModuleId, CModuleContractExport Export) :
			m_ModuleId(std::move(ModuleId)),
			m_Export(std::move(Export))
		{
		}

		const CModuleId &ModuleId() const noexcept
		{
			return m_ModuleId;
		}

		const CModuleContractExport &Export() const noexcept
		{
			return m_Export;
		}

	private:
		CModuleId m_ModuleId;
		CModuleContractExport m_Export;
	};

	bool SameContract(const CModuleContractExport &Export, const CModuleContractImport &Import) noexcept
	{
		return Export.Id() == Import.Id() && Export.Version() == Import.Version();
	}

	bool SameContract(const CModuleContractExport &Left, const CModuleContractExport &Right) noexcept
	{
		return Left.Id() == Right.Id() && Left.Version() == Right.Version();
	}

	bool HasDuplicateExport(const std::vector<CExportCandidate> &Exports, const CModuleContractExport &Export) noexcept
	{
		for(const auto &Candidate : Exports)
		{
			if(SameContract(Candidate.Export(), Export))
			{
				return true;
			}
		}

		return false;
	}

	const CExportCandidate *FindExport(const std::vector<CExportCandidate> &Exports, const CModuleContractImport &Import) noexcept
	{
		for(const auto &Candidate : Exports)
		{
			if(SameContract(Candidate.Export(), Import))
			{
				return &Candidate;
			}
		}

		return nullptr;
	}

} // namespace

	CModuleContractBinding::CModuleContractBinding(CModuleId ImportingModuleId, CModuleId ExportingModuleId, CModuleContractId ContractId, CModuleContractVersion Version) :
		m_ImportingModuleId(std::move(ImportingModuleId)),
		m_ExportingModuleId(std::move(ExportingModuleId)),
		m_ContractId(std::move(ContractId)),
		m_Version(Version)
	{
	}

	CModuleContractBinding::~CModuleContractBinding() noexcept = default;

	const CModuleId &CModuleContractBinding::ImportingModuleId() const noexcept
	{
		return m_ImportingModuleId;
	}

	const CModuleId &CModuleContractBinding::ExportingModuleId() const noexcept
	{
		return m_ExportingModuleId;
	}

	const CModuleContractId &CModuleContractBinding::ContractId() const noexcept
	{
		return m_ContractId;
	}

	const CModuleContractVersion &CModuleContractBinding::Version() const noexcept
	{
		return m_Version;
	}

	CModuleContractResolution::CModuleContractResolution(std::vector<CModuleContractBinding> Bindings) :
		m_Bindings(std::move(Bindings))
	{
	}

	CModuleContractResolution::~CModuleContractResolution() noexcept = default;

	const std::vector<CModuleContractBinding> &CModuleContractResolution::Bindings() const noexcept
	{
		return m_Bindings;
	}

	std::optional<CModuleContractResolution> ResolveModuleContractImports(const CModuleRegistrationPlan &Plan)
	{
		std::vector<CExportCandidate> Exports;
		for(const auto &Definition : Plan.DefinitionsInRegistrationOrder())
		{
			for(const auto &Export : Definition.Descriptor().ContractExports())
			{
				if(Export.Id().IsEmpty() || HasDuplicateExport(Exports, Export))
				{
					return std::nullopt;
				}

				Exports.emplace_back(CModuleId(Definition.Descriptor().Id().Value()), Export);
			}
		}

		std::vector<CModuleContractBinding> Bindings;
		for(const auto &Definition : Plan.DefinitionsInRegistrationOrder())
		{
			for(const auto &Import : Definition.Descriptor().ContractImports())
			{
				if(Import.Id().IsEmpty())
				{
					return std::nullopt;
				}

				const auto *pExport = FindExport(Exports, Import);
				if(!pExport)
				{
					if(Import.Requirement() == EModuleContractImportRequirement::Required)
					{
						return std::nullopt;
					}

					continue;
				}

				Bindings.emplace_back(
					CModuleId(Definition.Descriptor().Id().Value()),
					CModuleId(pExport->ModuleId().Value()),
					CModuleContractId(Import.Id().Value()),
					Import.Version());
			}
		}

		return CModuleContractResolution(std::move(Bindings));
	}

} // namespace sirius::platform::modules
