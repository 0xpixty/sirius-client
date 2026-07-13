/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "sirius_status_feature.h"

#include <sirius/platform/features/feature_context.h>

namespace sirius::platform::features
{

	CSiriusStatusFeature::CSiriusStatusFeature() :
		m_Id("feature.sirius.status")
	{
	}

	CSiriusStatusFeature::~CSiriusStatusFeature() noexcept = default;

	const CFeatureId &CSiriusStatusFeature::Id() const noexcept
	{
		return m_Id;
	}

	bool CSiriusStatusFeature::Initialize(CFeatureContext &Context)
	{
		(void)Context;
		m_Initialized = true;
		return true;
	}

	void CSiriusStatusFeature::Shutdown(CFeatureContext &Context) noexcept
	{
		(void)Context;
		m_Open = false;
		m_Initialized = false;
	}

	bool CSiriusStatusFeature::Open() noexcept
	{
		if(!m_Initialized)
		{
			return false;
		}

		if(!m_Open)
		{
			m_Open = true;
			++m_OpenCount;
		}

		return true;
	}

	bool CSiriusStatusFeature::Close() noexcept
	{
		if(!m_Initialized)
		{
			return false;
		}

		if(m_Open)
		{
			m_Open = false;
			++m_CloseCount;
		}

		return true;
	}

	bool CSiriusStatusFeature::Toggle() noexcept
	{
		if(!m_Initialized)
		{
			return false;
		}

		if(m_Open)
		{
			return Close();
		}

		return Open();
	}

	bool CSiriusStatusFeature::IsInitialized() const noexcept
	{
		return m_Initialized;
	}

	bool CSiriusStatusFeature::IsOpen() const noexcept
	{
		return m_Open;
	}

	std::size_t CSiriusStatusFeature::OpenCount() const noexcept
	{
		return m_OpenCount;
	}

	std::size_t CSiriusStatusFeature::CloseCount() const noexcept
	{
		return m_CloseCount;
	}

	CSiriusStatusSnapshot CSiriusStatusFeature::Snapshot() const noexcept
	{
		return CSiriusStatusSnapshot(m_Initialized, m_Open, m_OpenCount, m_CloseCount);
	}

} // namespace sirius::platform::features
