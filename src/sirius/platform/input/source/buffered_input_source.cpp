/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "buffered_input_source.h"

#include <utility>

namespace sirius::platform::input
{

	CBufferedInputSource::~CBufferedInputSource() noexcept = default;

	CBufferedInputSource::CBufferedInputSource(const CBufferedInputSource &Other) = default;

	CBufferedInputSource &CBufferedInputSource::operator=(const CBufferedInputSource &Other)
	{
		if(this == &Other)
		{
			return *this;
		}

		std::vector<CInputEvent> Events(Other.m_Events);
		m_Events.swap(Events);
		return *this;
	}

	CBufferedInputSource::CBufferedInputSource(CBufferedInputSource &&Other) noexcept = default;

	CBufferedInputSource &CBufferedInputSource::operator=(CBufferedInputSource &&Other) noexcept = default;

	void CBufferedInputSource::Push(CInputEvent Event)
	{
		m_Events.push_back(std::move(Event));
	}

	std::span<const CInputEvent> CBufferedInputSource::Events() const noexcept
	{
		return {m_Events.data(), m_Events.size()};
	}

	void CBufferedInputSource::ClearEvents() noexcept
	{
		m_Events.clear();
	}

	bool CBufferedInputSource::IsEmpty() const noexcept
	{
		return m_Events.empty();
	}

	std::size_t CBufferedInputSource::Size() const noexcept
	{
		return m_Events.size();
	}

} // namespace sirius::platform::input
