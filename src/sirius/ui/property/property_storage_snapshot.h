/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_STORAGE_SNAPSHOT_H
#define SIRIUS_UI_PROPERTY_PROPERTY_STORAGE_SNAPSHOT_H

#include "property_id.h"
#include "property_stored_value.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::property
{

	class CPropertyStorageRecord final
	{
	public:
		CPropertyStorageRecord(CPropertyId Id, CPropertyStoredValue Value);
		~CPropertyStorageRecord() noexcept;

		const CPropertyId &Id() const noexcept;
		const CPropertyStoredValue &Value() const noexcept;

	private:
		CPropertyId m_Id;
		CPropertyStoredValue m_Value;
	};

	class CPropertyStorageSnapshot final
	{
	public:
		explicit CPropertyStorageSnapshot(std::vector<CPropertyStorageRecord> Records);
		~CPropertyStorageSnapshot() noexcept;

		const std::vector<CPropertyStorageRecord> &Records() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyStorageRecord> m_Records;
	};

} // namespace sirius::ui::property

#endif
