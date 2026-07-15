/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_stored_value.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyStoredValue::CPropertyStoredValue(CPropertyTypeDescriptor Type, std::string StablePayload) :
		m_Type(Type),
		m_StablePayload(std::move(StablePayload))
	{
	}

	CPropertyStoredValue::~CPropertyStoredValue() noexcept = default;

	const CPropertyTypeDescriptor &CPropertyStoredValue::Type() const noexcept
	{
		return m_Type;
	}

	const std::string &CPropertyStoredValue::StablePayload() const noexcept
	{
		return m_StablePayload;
	}

	bool CPropertyStoredValue::IsEmptyPayload() const noexcept
	{
		return m_StablePayload.empty();
	}

} // namespace sirius::ui::property
