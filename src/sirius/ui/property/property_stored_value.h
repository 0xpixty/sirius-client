/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_STORED_VALUE_H
#define SIRIUS_UI_PROPERTY_PROPERTY_STORED_VALUE_H

#include "property_type_descriptor.h"

#include <string>

namespace sirius::ui::property
{

	class CPropertyStoredValue final
	{
	public:
		CPropertyStoredValue(CPropertyTypeDescriptor Type, std::string StablePayload);
		~CPropertyStoredValue() noexcept;

		const CPropertyTypeDescriptor &Type() const noexcept;
		const std::string &StablePayload() const noexcept;
		bool IsEmptyPayload() const noexcept;

	private:
		CPropertyTypeDescriptor m_Type;
		std::string m_StablePayload;
	};

} // namespace sirius::ui::property

#endif
