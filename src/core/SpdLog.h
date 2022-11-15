#pragma once

#include "Log.h"
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
        SpdLog(const std::string& id);

        ~SpdLog();

        static std::shared_ptr<spdlog::logger> Logger(const std::string id = "");

		static std::shared_ptr<spdlog::logger> AddLogger(const std::string id, const std::string file = "");

		static std::shared_ptr<spdlog::logger> DefaultLogger();

        virtual void log(LogType type,const char *msg) override;

        

    private:
		SpdLog(const SpdLog&) = delete;
		SpdLog& operator=(const SpdLog&) = delete;

        std::string m_logId;
    };

}

#define TDS_CREATE_LOG(...) ::TARDIS::CORE::Log::AddLogger(__VA_ARGS__)

//#define TDS_TRACE(...)      ::TARDIS::CORE::Log::Logger(std::to_string(Helper::getThreadId()))->trace(__VA_ARGS__)
//#define TDS_INFO(...)       ::TARDIS::CORE::Log::Logger()->info(__VA_ARGS__)
//#define TDS_WARN(...)       ::TARDIS::CORE::Log::Logger()->warn(__VA_ARGS__)
//#define TDS_ERROR(...)      ::TARDIS::CORE::Log::Logger()->error(__VA_ARGS__)
//#define TDS_CRITICAL(...)   ::TARDIS::CORE::Log::Logger()->critical(__VA_ARGS__)

#define TDS_G_TRACE(...)     spdlog::trace(__VA_ARGS__)
#define TDS_G_INFO(...)      spdlog::info(__VA_ARGS__)
#define TDS_G_WARN(...)      spdlog::warn(__VA_ARGS__)
#define TDS_G_ERROR(...)     spdlog::error(__VA_ARGS__)
#define TDS_G_CRITICAL(...)  spdlog::critical(__VA_ARGS__)