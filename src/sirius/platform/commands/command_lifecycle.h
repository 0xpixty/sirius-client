/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_LIFECYCLE_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_LIFECYCLE_H

#include <cstddef>

namespace sirius::platform::commands
{

	class CCommandContext;
	class CCommandRegistry;

	class CCommandLifecycle final
	{
	public:
		CCommandLifecycle() = default;
		~CCommandLifecycle() noexcept;

		CCommandLifecycle(const CCommandLifecycle &Other) = delete;
		CCommandLifecycle &operator=(const CCommandLifecycle &Other) = delete;
		CCommandLifecycle(CCommandLifecycle &&Other) = delete;
		CCommandLifecycle &operator=(CCommandLifecycle &&Other) = delete;

		bool Initialize(CCommandRegistry &Registry, CCommandContext &Context);
		void Shutdown(CCommandRegistry &Registry, CCommandContext &Context) noexcept;

	private:
		void ShutdownInitializedCommands(CCommandRegistry &Registry, CCommandContext &Context) noexcept;

		bool m_Initialized = false;
		std::size_t m_InitializedCommandCount = 0;
	};

} // namespace sirius::platform::commands

#endif
