/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_REGISTRY_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_REGISTRY_H

#include "command.h"
#include "command_id.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::commands
{

	class CCommandRegistry final
	{
	public:
		CCommandRegistry() = default;
		~CCommandRegistry() noexcept;

		CCommandRegistry(const CCommandRegistry &Other) = delete;
		CCommandRegistry &operator=(const CCommandRegistry &Other) = delete;
		CCommandRegistry(CCommandRegistry &&Other) = delete;
		CCommandRegistry &operator=(CCommandRegistry &&Other) = delete;

		bool Register(std::unique_ptr<ICommand> &pCommand);
		bool Has(const CCommandId &Id) const;
		ICommand *Get(const CCommandId &Id);
		const ICommand *Get(const CCommandId &Id) const;
		const std::vector<ICommand *> &CommandsInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;
		void Clear() noexcept;
		bool IsSealed() const noexcept;

	private:
		friend class CCommandLifecycle;
		friend class CCommandDispatcher;

		void Seal() noexcept;
		void Unseal() noexcept;

		std::unordered_map<std::string, std::unique_ptr<ICommand>> m_Commands;
		std::vector<ICommand *> m_CommandsInRegistrationOrder;
		bool m_Sealed = false;
	};

} // namespace sirius::platform::commands

#endif
