#ifndef _LOG_H_
#define _LOG_H_

#include "stdio.h"

class Log
{
public:

	enum LOG_LEVEL
	{
		TRACE,
		DEBUG,
		INFO,
		WARNING,
		ERR
	};

	static LOG_LEVEL level() {
		return getInstance().m_level;
	}

	static void setLevel(LOG_LEVEL level) {
		getInstance().m_level = level;
	}

private:

	LOG_LEVEL m_level = TRACE;

	static Log& getInstance()
	{
		static Log instance;
		return instance;
	}

	Log() {}

public:
	Log(Log const&) = delete;
	void operator=(Log const&) = delete;
};

#define Log_msg(lev, fmt, ...) if(lev >= Log::level()){printf("%s: %s: line %d: " fmt "\n", __VA_ARGS__);}
#define Log_trace(fmt, ...)		Log_msg(Log::TRACE,		fmt, "trace",   __FUNCTION__, __LINE__, __VA_ARGS__);
#define Log_debug(fmt, ...)		Log_msg(Log::DEBUG,		fmt, "debug",   __FUNCTION__, __LINE__, __VA_ARGS__);
#define Log_info(fmt, ...)		Log_msg(Log::INFO,		fmt, "info",	__FUNCTION__, __LINE__, __VA_ARGS__);
#define Log_warning(fmt, ...)	Log_msg(Log::WARNING,	fmt, "warning", __FUNCTION__, __LINE__, __VA_ARGS__);
#define Log_error(fmt, ...)		Log_msg(Log::ERR,		fmt, "error",   __FUNCTION__, __LINE__, __VA_ARGS__);


#endif // _LOG_H_

