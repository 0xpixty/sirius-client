/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_ADAPTERS_DDNET_INPUT_DDNET_INPUT_COLLECTOR_H
#define SIRIUS_ADAPTERS_DDNET_INPUT_DDNET_INPUT_COLLECTOR_H

class IInput;

namespace sirius::platform::input
{
	class CBufferedInputSource;
} // namespace sirius::platform::input

namespace sirius::adapters::ddnet::input
{

	class CDdnetInputEventAdapter;

	class CDdnetInputCollector final
	{
	public:
		explicit CDdnetInputCollector(const CDdnetInputEventAdapter &Adapter) noexcept;
		~CDdnetInputCollector() noexcept;

		CDdnetInputCollector(const CDdnetInputCollector &Other) = delete;
		CDdnetInputCollector &operator=(const CDdnetInputCollector &Other) = delete;
		CDdnetInputCollector(CDdnetInputCollector &&Other) = delete;
		CDdnetInputCollector &operator=(CDdnetInputCollector &&Other) = delete;

		void Collect(IInput &Input, platform::input::CBufferedInputSource &Destination) const;

	private:
		const CDdnetInputEventAdapter &m_Adapter;
	};

} // namespace sirius::adapters::ddnet::input

#endif
