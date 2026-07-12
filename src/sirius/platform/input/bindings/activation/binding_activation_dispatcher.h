/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_DISPATCHER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_DISPATCHER_H

namespace sirius::platform::input
{

	class CBindingActivationRegistry;
	class CBindingMatcher;
	class CBindingRegistry;
	class CInputEvent;
	class IBindingActivationHandler;

	class CBindingActivationDispatcher final
	{
	public:
		explicit CBindingActivationDispatcher(
			const CBindingMatcher &Matcher,
			const CBindingRegistry &Bindings,
			const CBindingActivationRegistry &Activations,
			IBindingActivationHandler &Handler) noexcept;
		~CBindingActivationDispatcher() noexcept;

		CBindingActivationDispatcher(const CBindingActivationDispatcher &Other) = delete;
		CBindingActivationDispatcher &operator=(const CBindingActivationDispatcher &Other) = delete;
		CBindingActivationDispatcher(CBindingActivationDispatcher &&Other) = delete;
		CBindingActivationDispatcher &operator=(CBindingActivationDispatcher &&Other) = delete;

		void Dispatch(const CInputEvent &Event) const;

	private:
		const CBindingMatcher &m_Matcher;
		const CBindingRegistry &m_Bindings;
		const CBindingActivationRegistry &m_Activations;
		IBindingActivationHandler &m_Handler;
	};

} // namespace sirius::platform::input

#endif
