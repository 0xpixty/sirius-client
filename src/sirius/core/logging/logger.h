/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_LOGGING_LOGGER_H
#define SIRIUS_CORE_LOGGING_LOGGER_H

#include "log_level.h"
#include "log_message.h"

#include <sirius/core/events/event_dispatcher.h>

#include <string>

namespace sirius::core::logging
{

	class CLogMessageEvent final
	{
	public:
		explicit CLogMessageEvent(CLogMessage Message);
		~CLogMessageEvent() noexcept;

		const CLogMessage &Message() const noexcept;

	private:
		CLogMessage m_Message;
	};

	class CLogger final
	{
	public:
		explicit CLogger(events::CEventDispatcher &Events) noexcept;
		~CLogger() noexcept;

		CLogger(const CLogger &Other) = delete;
		CLogger &operator=(const CLogger &Other) = delete;
		CLogger(CLogger &&Other) = delete;
		CLogger &operator=(CLogger &&Other) = delete;

		void Log(ELogLevel Level, std::string Message);
		void Trace(std::string Message);
		void Debug(std::string Message);
		void Info(std::string Message);
		void Warning(std::string Message);
		void Error(std::string Message);
		void Fatal(std::string Message);

	private:
		events::CEventDispatcher &m_Events;
	};

} // namespace sirius::core::logging

#endif
