/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "logger.h"

#include <utility>

namespace sirius::core::logging
{

	CLogMessage::CLogMessage(ELogLevel Level, std::string Text) :
		m_Level(Level),
		m_Text(std::move(Text))
	{
	}

	CLogMessage::~CLogMessage() noexcept = default;

	ELogLevel CLogMessage::Level() const noexcept
	{
		return m_Level;
	}

	const std::string &CLogMessage::Text() const noexcept
	{
		return m_Text;
	}

	CLogMessageEvent::CLogMessageEvent(CLogMessage Message) :
		m_Message(std::move(Message))
	{
	}

	CLogMessageEvent::~CLogMessageEvent() noexcept = default;

	const CLogMessage &CLogMessageEvent::Message() const noexcept
	{
		return m_Message;
	}

	CLogger::CLogger(events::CEventDispatcher &Events) noexcept :
		m_Events(Events)
	{
	}

	CLogger::~CLogger() noexcept = default;

	void CLogger::Log(ELogLevel Level, std::string Message)
	{
		const CLogMessageEvent Event(CLogMessage(Level, std::move(Message)));
		m_Events.Dispatch(Event);
	}

	void CLogger::Trace(std::string Message)
	{
		Log(ELogLevel::Trace, std::move(Message));
	}

	void CLogger::Debug(std::string Message)
	{
		Log(ELogLevel::Debug, std::move(Message));
	}

	void CLogger::Info(std::string Message)
	{
		Log(ELogLevel::Info, std::move(Message));
	}

	void CLogger::Warning(std::string Message)
	{
		Log(ELogLevel::Warning, std::move(Message));
	}

	void CLogger::Error(std::string Message)
	{
		Log(ELogLevel::Error, std::move(Message));
	}

	void CLogger::Fatal(std::string Message)
	{
		Log(ELogLevel::Fatal, std::move(Message));
	}

} // namespace sirius::core::logging

