/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_LOGGING_LOG_MESSAGE_H
#define SIRIUS_CORE_LOGGING_LOG_MESSAGE_H

#include "log_level.h"

#include <string>

namespace sirius::core::logging
{

	class CLogMessage final
	{
	public:
		CLogMessage(ELogLevel Level, std::string Text);
		~CLogMessage() noexcept;

		ELogLevel Level() const noexcept;
		const std::string &Text() const noexcept;

	private:
		const ELogLevel m_Level;
		const std::string m_Text;
	};

} // namespace sirius::core::logging

#endif
