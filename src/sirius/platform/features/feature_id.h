/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_ID_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_ID_H

#include <string>

namespace sirius::platform::features
{

	class CFeatureId final
	{
	public:
		explicit CFeatureId(std::string Value);
		~CFeatureId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CFeatureId &Other) const noexcept;
		bool operator!=(const CFeatureId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

} // namespace sirius::platform::features

#endif
