/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_type_descriptor.h"

namespace sirius::ui::property
{

	CPropertyTypeDescriptor::CPropertyTypeDescriptor(EPropertyValueKind ValueKind) noexcept :
		m_ValueKind(ValueKind)
	{
	}

	CPropertyTypeDescriptor::CPropertyTypeDescriptor(EPropertyValueKind ValueKind, EPropertySemanticKind SemanticKind) noexcept :
		m_ValueKind(ValueKind),
		m_SemanticKind(SemanticKind)
	{
	}

	CPropertyTypeDescriptor::~CPropertyTypeDescriptor() noexcept = default;

	EPropertyValueKind CPropertyTypeDescriptor::ValueKind() const noexcept
	{
		return m_ValueKind;
	}

	EPropertySemanticKind CPropertyTypeDescriptor::SemanticKind() const noexcept
	{
		return m_SemanticKind;
	}

	bool CPropertyTypeDescriptor::operator==(const CPropertyTypeDescriptor &Other) const noexcept
	{
		return m_ValueKind == Other.m_ValueKind && m_SemanticKind == Other.m_SemanticKind;
	}

	bool CPropertyTypeDescriptor::operator!=(const CPropertyTypeDescriptor &Other) const noexcept
	{
		return !(*this == Other);
	}

} // namespace sirius::ui::property
