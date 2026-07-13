/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_TEST_ACTIVATION_BEHAVIOR_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_TEST_ACTIVATION_BEHAVIOR_H

#include "feature_activation_behavior.h"

#include <cstddef>

namespace sirius::platform::features
{

	class CTestActivationBehavior final : public IFeatureActivationBehavior
	{
	public:
		CTestActivationBehavior() = default;
		~CTestActivationBehavior() noexcept override;

		void Activate() override;
		void Deactivate() override;

		bool IsActive() const noexcept;
		std::size_t ActivationCount() const noexcept;
		std::size_t DeactivationCount() const noexcept;

	private:
		bool m_Active = false;
		std::size_t m_ActivationCount = 0;
		std::size_t m_DeactivationCount = 0;
	};

} // namespace sirius::platform::features

#endif
