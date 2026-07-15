#include <gtest/gtest.h>
#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>
#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_context.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_lifecycle.h>
#include <sirius/platform/modules/module_lifecycle_graph.h>
#include <sirius/platform/modules/module_registry.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sirius::platform::modules
{
	namespace
	{

		class CRecordingModule final : public IModule
		{
		public:
			CRecordingModule(CModuleId Id, std::vector<std::string> &Events) :
				m_Descriptor(std::move(Id)),
				m_Events(Events)
			{
			}

			const CModuleDescriptor &Descriptor() const noexcept override
			{
				return m_Descriptor;
			}

			const CModuleId &Id() const noexcept override
			{
				return m_Descriptor.Id();
			}

			features::CFeatureRegistry &Features() noexcept override
			{
				return m_Features;
			}

			const features::CFeatureRegistry &Features() const noexcept override
			{
				return m_Features;
			}

			commands::CCommandRegistry &Commands() noexcept override
			{
				return m_Commands;
			}

			const commands::CCommandRegistry &Commands() const noexcept override
			{
				return m_Commands;
			}

			services::CModuleServiceRegistry &ModuleServices() noexcept override
			{
				return m_ModuleServices;
			}

			const services::CModuleServiceRegistry &ModuleServices() const noexcept override
			{
				return m_ModuleServices;
			}

			bool Initialize(CModuleContext &Context) override
			{
				(void)Context;
				m_Events.push_back("init:" + Id().Value());
				return true;
			}

			void Shutdown(CModuleContext &Context) noexcept override
			{
				(void)Context;
				m_Events.push_back("shutdown:" + Id().Value());
			}

		private:
			CModuleDescriptor m_Descriptor;
			features::CFeatureRegistry m_Features;
			commands::CCommandRegistry m_Commands;
			services::CModuleServiceRegistry m_ModuleServices;
			std::vector<std::string> &m_Events;
		};

		void RegisterRecordingModule(CModuleRegistry &Registry, const CModuleId &Id, std::vector<std::string> &Events)
		{
			std::unique_ptr<IModule> pModule = std::make_unique<CRecordingModule>(CModuleId(Id.Value()), Events);
			ASSERT_TRUE(Registry.Register(pModule));
		}

		CModuleContext MakeContext(core::runtime::CCoreRuntime &Runtime)
		{
			return CModuleContext(Runtime, Runtime.Events(), Runtime.Config(), Runtime.Logger(), Runtime.Tasks());
		}

		TEST(SiriusModuleLifecycleOrder, InitializesByLifecycleGraphAndShutsDownInReverseInitializedOrder)
		{
			std::vector<std::string> Events;
			CModuleRegistry Registry;
			RegisterRecordingModule(Registry, CModuleId("module.sirius.lifecycle.consumer"), Events);
			RegisterRecordingModule(Registry, CModuleId("module.sirius.lifecycle.core"), Events);
			CModuleLifecycleGraph LifecycleGraph(
				{CModuleId("module.sirius.lifecycle.core"), CModuleId("module.sirius.lifecycle.consumer")},
				{CModuleId("module.sirius.lifecycle.consumer"), CModuleId("module.sirius.lifecycle.core")});
			core::runtime::CCoreRuntime Runtime{core::runtime::CCoreRuntimeConfiguration()};
			auto Context = MakeContext(Runtime);
			CModuleLifecycle Lifecycle;

			ASSERT_TRUE(Lifecycle.Initialize(Registry, Context, LifecycleGraph));
			Lifecycle.Shutdown(Registry, Context);

			const std::vector<std::string> ExpectedEvents{
				"init:module.sirius.lifecycle.core",
				"init:module.sirius.lifecycle.consumer",
				"shutdown:module.sirius.lifecycle.consumer",
				"shutdown:module.sirius.lifecycle.core",
			};
			EXPECT_EQ(Events, ExpectedEvents);
		}

		TEST(SiriusModuleLifecycleOrder, RejectsLifecycleGraphMissingRegisteredModules)
		{
			std::vector<std::string> Events;
			CModuleRegistry Registry;
			RegisterRecordingModule(Registry, CModuleId("module.sirius.lifecycle.registered"), Events);
			CModuleLifecycleGraph LifecycleGraph(
				{CModuleId("module.sirius.lifecycle.unknown")},
				{CModuleId("module.sirius.lifecycle.unknown")});
			core::runtime::CCoreRuntime Runtime{core::runtime::CCoreRuntimeConfiguration()};
			auto Context = MakeContext(Runtime);
			CModuleLifecycle Lifecycle;

			EXPECT_FALSE(Lifecycle.Initialize(Registry, Context, LifecycleGraph));
			EXPECT_FALSE(Registry.IsSealed());
			EXPECT_TRUE(Events.empty());
		}

	} // namespace
} // namespace sirius::platform::modules
