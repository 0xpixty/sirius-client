#include <sirius/platform/commands/command.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_descriptor_validation.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/services/module_service.h>
#include <sirius/platform/modules/services/module_service_id.h>

#include <gtest/gtest.h>

#include <memory>
#include <utility>

namespace sirius::platform::modules
{
namespace
{

	class CDescriptorValidationFeature final : public features::IFeature
	{
	public:
		explicit CDescriptorValidationFeature(features::CFeatureId Id) :
			m_Id(std::move(Id))
		{
		}

		const features::CFeatureId &Id() const noexcept override { return m_Id; }
		bool Initialize(features::CFeatureContext &Context) override
		{
			(void)Context;
			return true;
		}
		void Shutdown(features::CFeatureContext &Context) noexcept override { (void)Context; }

	private:
		features::CFeatureId m_Id;
	};

	class CDescriptorValidationCommand final : public commands::ICommand
	{
	public:
		explicit CDescriptorValidationCommand(commands::CCommandId Id) :
			m_Id(std::move(Id))
		{
		}

		const commands::CCommandId &Id() const noexcept override { return m_Id; }
		bool Initialize(commands::CCommandContext &Context) override
		{
			(void)Context;
			return true;
		}
		void Shutdown(commands::CCommandContext &Context) noexcept override { (void)Context; }
		bool Execute(commands::CCommandContext &Context) override
		{
			(void)Context;
			return true;
		}

	private:
		commands::CCommandId m_Id;
	};

	class CDescriptorValidationService final : public services::IModuleService
	{
	public:
		explicit CDescriptorValidationService(services::CModuleServiceId Id) :
			m_Id(std::move(Id))
		{
		}

		const services::CModuleServiceId &Id() const noexcept override { return m_Id; }
		bool Initialize(services::CModuleServiceContext &Context) override
		{
			(void)Context;
			return true;
		}
		void Shutdown(services::CModuleServiceContext &Context) noexcept override { (void)Context; }

	private:
		services::CModuleServiceId m_Id;
	};

	TEST(SiriusModuleDescriptorValidation, MatchingDeclaredOwnershipPasses)
	{
		CModule Module(CModuleDescriptor(
			CModuleId("module.sirius.validation.matching"),
			{features::CFeatureId("feature.sirius.validation.matching")},
			{commands::CCommandId("command.sirius.validation.matching")},
			{services::CModuleServiceId("service.sirius.validation.matching")}));

		std::unique_ptr<features::IFeature> pFeature = std::make_unique<CDescriptorValidationFeature>(features::CFeatureId("feature.sirius.validation.matching"));
		std::unique_ptr<commands::ICommand> pCommand = std::make_unique<CDescriptorValidationCommand>(commands::CCommandId("command.sirius.validation.matching"));
		std::unique_ptr<services::IModuleService> pService = std::make_unique<CDescriptorValidationService>(services::CModuleServiceId("service.sirius.validation.matching"));
		ASSERT_TRUE(Module.Features().Register(pFeature));
		ASSERT_TRUE(Module.Commands().Register(pCommand));
		ASSERT_TRUE(Module.ModuleServices().Register(pService));

		EXPECT_TRUE(IsModuleDescriptorOwnershipValid(Module));
	}

	TEST(SiriusModuleDescriptorValidation, MissingDeclaredOwnershipFails)
	{
		CModule Module(CModuleDescriptor(
			CModuleId("module.sirius.validation.missing"),
			{features::CFeatureId("feature.sirius.validation.missing")},
			{},
			{}));

		EXPECT_FALSE(IsModuleDescriptorOwnershipValid(Module));
	}

	TEST(SiriusModuleDescriptorValidation, UndeclaredActualOwnershipFails)
	{
		CModule Module(CModuleDescriptor(CModuleId("module.sirius.validation.undeclared")));
		std::unique_ptr<features::IFeature> pFeature = std::make_unique<CDescriptorValidationFeature>(features::CFeatureId("feature.sirius.validation.undeclared"));
		ASSERT_TRUE(Module.Features().Register(pFeature));

		EXPECT_FALSE(IsModuleDescriptorOwnershipValid(Module));
	}

	TEST(SiriusModuleDescriptorValidation, DuplicateDeclarationsFail)
	{
		CModule Module(CModuleDescriptor(
			CModuleId("module.sirius.validation.duplicate"),
			{features::CFeatureId("feature.sirius.validation.duplicate"), features::CFeatureId("feature.sirius.validation.duplicate")},
			{},
			{}));

		EXPECT_FALSE(IsModuleDescriptorOwnershipValid(Module));
	}

} // namespace
} // namespace sirius::platform::modules
