#pragma once

#include "Log.h"
#include "Helper.h"
//#include "Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace TARDIS::CORE
{
	class SpdLog : public Log
	{
	public:
        SpdLog(const std::string& id, const std::string& file = "undefine.log", bool followThread = false);

        ~SpdLog();

        static std::shared_ptr<spdlog::logger> Logger(const std::string& id = "");

		static std::shared_ptr<spdlog::logger> AddLogger(const std::string& id, const std::string& file = "");

		static std::shared_ptr<spdlog::logger> DefaultLogger();

        virtual void log(LogType type,const char *msg) override;

    private:
		SpdLog(const SpdLog&) = delete;
		SpdLog& operator=(const SpdLog&) = delete;

        std::string m_logId;

        bool m_followThread;
    };

}

#define TDS_CREATE_LOG(...) ::TARDIS::CORE::SpdLog::AddLogger(__VA_ARGS__)

//#define TDS_LOG_TRACE(...)      ::TARDIS::CORE::Log::Logger(std::to_string(Helper::getThreadId()))->trace(__VA_ARGS__)
#define TDS_LOG_TRACE(...)         ::TARDIS::CORE::SpdLog::Logger()->trace(__VA_ARGS__)
#define TDS_LOG_INFO(...)          ::TARDIS::CORE::SpdLog::Logger()->info(__VA_ARGS__)
#define TDS_LOG_WARN(...)          ::TARDIS::CORE::SpdLog::Logger()->warn(__VA_ARGS__)
#define TDS_LOG_ERROR(...)         ::TARDIS::CORE::SpdLog::Logger()->error(__VA_ARGS__)
#define TDS_LOG_CRITICAL(...)      ::TARDIS::CORE::SpdLog::Logger()->critical(__VA_ARGS__)

#define LOG_TRACE(LogId, ...)      ::TARDIS::CORE::SpdLog::Logger(LogId)->trace(__VA_ARGS__)
#define LOG_INFO(LogId, ...)       ::TARDIS::CORE::SpdLog::Logger(LogId)->info(__VA_ARGS__)
#define LOG_WARN(LogId, ...)       ::TARDIS::CORE::SpdLog::Logger(LogId)->warn(__VA_ARGS__)
#define LOG_ERROR(LogId, ...)      ::TARDIS::CORE::SpdLog::Logger(LogId)->error(__VA_ARGS__)
#define LOG_CRITICAL(LogId, ...)   ::TARDIS::CORE::SpdLog::Logger(LogId)->critical(__VA_ARGS__)

#define THREAD_LOG_TRACE(...)      ::TARDIS::CORE::SpdLog::Logger(Helper::getThreadIdStr())->trace(__VA_ARGS__)
#define THREAD_LOG_INFO(...)       ::TARDIS::CORE::SpdLog::Logger(Helper::getThreadIdStr())->info(__VA_ARGS__)
#define THREAD_LOG_WARN(...)       ::TARDIS::CORE::SpdLog::Logger(Helper::getThreadIdStr())->warn(__VA_ARGS__)
#define THREAD_LOG_ERROR(...)      ::TARDIS::CORE::SpdLog::Logger(Helper::getThreadIdStr())->error(__VA_ARGS__)
#define THREAD_LOG_CRITICAL(...)   ::TARDIS::CORE::SpdLog::Logger(Helper::getThreadIdStr())->critical(__VA_ARGS__)



// #define TDS_LOG_TRACE(...)     spdlog::trace(__VA_ARGS__)
// #define TDS_LOG_INFO(...)      spdlog::info(__VA_ARGS__)
// #define TDS_LOG_WARN(...)      spdlog::warn(__VA_ARGS__)
// #define TDS_LOG_ERROR(...)     spdlog::error(__VA_ARGS__)
// #define TDS_LOG_CRITICAL(...)  spdlog::critical(__VA_ARGS__)