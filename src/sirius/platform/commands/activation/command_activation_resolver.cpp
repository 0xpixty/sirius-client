/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_activation_resolver.h"

#include <utility>

namespace sirius::platform::commands
{

	CCommandActivationResolver::~CCommandActivationResolver() noexcept = default;

	CCommandActivationResolver::CCommandActivationResolver(const CCommandActivationResolver &Other) = default;

	CCommandActivationResolver &CCommandActivationResolver::operator=(const CCommandActivationResolver &Other)
	{
		if(this != &Other)
		{
			CCommandActivationResolver Copy(Other);
			m_Mappings.swap(Copy.m_Mappings);
		}

		return *this;
	}

	CCommandActivationResolver::CCommandActivationResolver(CCommandActivationResolver &&Other) noexcept = default;

	CCommandActivationResolver &CCommandActivationResolver::operator=(CCommandActivationResolver &&Other) noexcept
	{
		if(this != &Other)
		{
			m_Mappings.swap(Other.m_Mappings);
		}

		return *this;
	}

	bool CCommandActivationResolver::Register(activation::CActivationId ActivationId, CCommandId CommandId)
	{
		if(ActivationId.IsEmpty() || CommandId.IsEmpty())
		{
			return false;
		}

		const std::string ActivationKey = ActivationId.Value();
		if(m_Mappings.find(ActivationKey) != m_Mappings.end())
		{
			return false;
		}

		m_Mappings.emplace(
			ActivationKey,
			CMapping{
				std::move(ActivationId),
				std::move(CommandId),
			});
		return true;
	}

	bool CCommandActivationResolver::Has(const activation::CActivationId &ActivationId) const noexcept
	{
		return m_Mappings.find(ActivationId.Value()) != m_Mappings.end();
	}

	const CCommandId *CCommandActivationResolver::Resolve(const activation::CActivationId &ActivationId) const
	{
		const auto Iter = m_Mappings.find(ActivationId.Value());
		if(Iter == m_Mappings.end())
		{
			return nullptr;
		}

		return &Iter->second.m_CommandId;
	}

	bool CCommandActivationResolver::Remove(const activation::CActivationId &ActivationId)
	{
		const auto Iter = m_Mappings.find(ActivationId.Value());
		if(Iter == m_Mappings.end())
		{
			return false;
		}

		m_Mappings.erase(Iter);
		return true;
	}

	void CCommandActivationResolver::Clear() noexcept
	{
		m_Mappings.clear();
	}

	std::size_t CCommandActivationResolver::Count() const noexcept
	{
		return m_Mappings.size();
	}

} // namespace sirius::platform::commands
