/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_storage_snapshot.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyStorageRecord::CPropertyStorageRecord(CPropertyId Id, CPropertyStoredValue Value) :
		m_Id(std::move(Id)),
		m_Value(std::move(Value))
	{
	}

	CPropertyStorageRecord::~CPropertyStorageRecord() noexcept = default;

	const CPropertyId &CPropertyStorageRecord::Id() const noexcept
	{
		return m_Id;
	}

	const CPropertyStoredValue &CPropertyStorageRecord::Value() const noexcept
	{
		return m_Value;
	}

	CPropertyStorageSnapshot::CPropertyStorageSnapshot(std::vector<CPropertyStorageRecord> Records) :
		m_Records(std::move(Records))
	{
	}

	CPropertyStorageSnapshot::~CPropertyStorageSnapshot() noexcept = default;

	const std::vector<CPropertyStorageRecord> &CPropertyStorageSnapshot::Records() const noexcept
	{
		return m_Records;
	}

	std::size_t CPropertyStorageSnapshot::Size() const noexcept
	{
		return m_Records.size();
	}

	bool CPropertyStorageSnapshot::IsEmpty() const noexcept
	{
		return m_Records.empty();
	}

} // namespace sirius::ui::property
