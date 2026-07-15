/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_INTERFACES_RUNTIME_COMPONENT_H
#define SIRIUS_CORE_INTERFACES_RUNTIME_COMPONENT_H

namespace sirius::core::interfaces
{

	class IRuntimeComponent
	{
	public:
		virtual ~IRuntimeComponent() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
	};

} // namespace sirius::core::interfaces

#endif
