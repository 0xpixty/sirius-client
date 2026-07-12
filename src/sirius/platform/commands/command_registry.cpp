/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_registry.h"

#include <utility>

namespace sirius::platform::commands
{

	CCommandRegistry::~CCommandRegistry() noexcept = default;

	bool CCommandRegistry::Register(std::unique_ptr<ICommand> &pCommand)
	{
		if(m_Sealed)
		{
			return false;
		}

		if(!pCommand || pCommand->Id().IsEmpty())
		{
			return false;
		}

		const auto &Id = pCommand->Id().Value();
		if(m_Commands.find(Id) != m_Commands.end())
		{
			return false;
		}

		auto *pRegisteredCommand = pCommand.get();
		m_Commands.emplace(Id, std::move(pCommand));
		m_CommandsInRegistrationOrder.push_back(pRegisteredCommand);
		return true;
	}

	bool CCommandRegistry::Has(const CCommandId &Id) const
	{
		return m_Commands.find(Id.Value()) != m_Commands.end();
	}

	ICommand *CCommandRegistry::Get(const CCommandId &Id)
	{
		const auto Iter = m_Commands.find(Id.Value());
		if(Iter == m_Commands.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const ICommand *CCommandRegistry::Get(const CCommandId &Id) const
	{
		const auto Iter = m_Commands.find(Id.Value());
		if(Iter == m_Commands.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const std::vector<ICommand *> &CCommandRegistry::CommandsInRegistrationOrder() const noexcept
	{
		return m_CommandsInRegistrationOrder;
	}

	std::size_t CCommandRegistry::Count() const noexcept
	{
		return m_Commands.size();
	}

	void CCommandRegistry::Clear() noexcept
	{
		if(m_Sealed)
		{
			return;
		}

		m_CommandsInRegistrationOrder.clear();
		m_Commands.clear();
	}

	void CCommandRegistry::Seal() noexcept
	{
		m_Sealed = true;
	}

	void CCommandRegistry::Unseal() noexcept
	{
		m_Sealed = false;
	}

	bool CCommandRegistry::IsSealed() const noexcept
	{
		return m_Sealed;
	}

} // namespace sirius::platform::commands
