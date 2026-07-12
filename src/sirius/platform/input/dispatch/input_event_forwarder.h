/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_DISPATCH_INPUT_EVENT_FORWARDER_H
#define SIRIUS_PLATFORM_INPUT_DISPATCH_INPUT_EVENT_FORWARDER_H

namespace sirius::core::events
{
	class CEventDispatcher;
} // namespace sirius::core::events

namespace sirius::platform::input
{

	class IInputSource;

	class CInputEventForwarder final
	{
	public:
		explicit CInputEventForwarder(core::events::CEventDispatcher &Events) noexcept;
		~CInputEventForwarder() noexcept;

		CInputEventForwarder(const CInputEventForwarder &Other) = delete;
		CInputEventForwarder &operator=(const CInputEventForwarder &Other) = delete;
		CInputEventForwarder(CInputEventForwarder &&Other) = delete;
		CInputEventForwarder &operator=(CInputEventForwarder &&Other) = delete;

		void Forward(IInputSource &Source);

	private:
		core::events::CEventDispatcher &m_Events;
	};

} // namespace sirius::platform::input

#endif
