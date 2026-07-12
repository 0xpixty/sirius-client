/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_SOURCE_BUFFERED_INPUT_SOURCE_H
#define SIRIUS_PLATFORM_INPUT_SOURCE_BUFFERED_INPUT_SOURCE_H

#include "input_source.h"

#include <cstddef>
#include <vector>

namespace sirius::platform::input
{

	class CBufferedInputSource final : public IInputSource
	{
	public:
		CBufferedInputSource() = default;
		~CBufferedInputSource() noexcept override;

		CBufferedInputSource(const CBufferedInputSource &Other);
		CBufferedInputSource &operator=(const CBufferedInputSource &Other);
		CBufferedInputSource(CBufferedInputSource &&Other) noexcept;
		CBufferedInputSource &operator=(CBufferedInputSource &&Other) noexcept;

		void Push(CInputEvent Event);

		std::span<const CInputEvent> Events() const noexcept override;
		void ClearEvents() noexcept override;

		bool IsEmpty() const noexcept;
		std::size_t Size() const noexcept;

	private:
		std::vector<CInputEvent> m_Events;
	};

} // namespace sirius::platform::input

#endif
