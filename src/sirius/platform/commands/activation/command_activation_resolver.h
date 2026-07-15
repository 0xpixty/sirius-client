/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_ACTIVATION_COMMAND_ACTIVATION_RESOLVER_H
#define SIRIUS_PLATFORM_COMMANDS_ACTIVATION_COMMAND_ACTIVATION_RESOLVER_H

#include <sirius/platform/activation/activation_id.h>
#include <sirius/platform/commands/command_id.h>

#include <cstddef>
#include <string>
#include <unordered_map>

namespace sirius::platform::commands
{

	class CCommandActivationResolver final
	{
	public:
		CCommandActivationResolver() = default;
		~CCommandActivationResolver() noexcept;

		CCommandActivationResolver(const CCommandActivationResolver &Other);
		CCommandActivationResolver &operator=(const CCommandActivationResolver &Other);
		CCommandActivationResolver(CCommandActivationResolver &&Other) noexcept;
		CCommandActivationResolver &operator=(CCommandActivationResolver &&Other) noexcept;

		bool Register(activation::CActivationId ActivationId, CCommandId CommandId);
		bool Has(const activation::CActivationId &ActivationId) const noexcept;
		const CCommandId *Resolve(const activation::CActivationId &ActivationId) const;
		bool Remove(const activation::CActivationId &ActivationId);
		void Clear() noexcept;
		std::size_t Count() const noexcept;

	private:
		struct CMapping final
		{
			activation::CActivationId m_ActivationId;
			CCommandId m_CommandId;
		};

		std::unordered_map<std::string, CMapping> m_Mappings;
	};

} // namespace sirius::platform::commands

#endif
