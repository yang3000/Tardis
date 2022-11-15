#include "SpdLog.h"

namespace TARDIS::CORE
{

	void SpdLog::log(LogType type,const char *msg)
	{
        printf(msg);
		switch (type)
		{
		case LogType::TRACE:    SpdLog::Logger(m_logId)->trace(msg);    break;
		case LogType::INFO:     SpdLog::Logger(m_logId)->info("45645645");     break;
		case LogType::WARN:     SpdLog::Logger(m_logId)->warn(msg);     break;
		//case TARDIS::CORE::ERROR:    SpdLog::Logger(m_logId)->error(msg);    break;
		case LogType::CRITICAL: SpdLog::Logger(m_logId)->critical(msg); break;
		default:
			break;
		}
	}

    SpdLog::SpdLog(const std::string& id) : m_logId(id)
    {
        AddLogger(m_logId, "demo");
    }


	SpdLog::~SpdLog()
	{
		spdlog::drop(m_logId);
	}

	std::shared_ptr<spdlog::logger> SpdLog::Logger(const std::string id)
	{
		if(!id.empty())
		{
			auto logger = spdlog::get(id);
			return logger ? logger : spdlog::default_logger();
		}
		return spdlog::default_logger();
	}

	std::shared_ptr<spdlog::logger> SpdLog::AddLogger(const std::string id, std::string fileName)
	{
		if(!id.empty())
		{
			auto logger = spdlog::get(id);
			if(logger)
			{
				return logger;
			}
			
			spdlog::sink_ptr t_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, true);
			t_sink->set_pattern("%^[%T] %n: %v%$");
			auto t_logger = std::make_shared<spdlog::logger>(id, t_sink);
			spdlog::register_logger(t_logger);
			t_logger->set_level(spdlog::level::trace);
			t_logger->flush_on(spdlog::level::trace);
			return t_logger;

            // spdlog::sink_ptr t_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, true);
            // t_sink->set_pattern("%^[%T] %n: %v%$");

            // auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            // console_sink->set_level(spdlog::level::trace);

            // std::string pattern = "[" + id + "] [%^%l%$] %v";
            // console_sink->set_pattern(pattern.c_str());

            // // spdlog::logger logger("multi_sink", { console_sink, t_sink });
            // // std::make_shared<spdlog::logger>(id,)
            // spdlog::sinks_init_list sinks = {t_sink, console_sink};
            // auto t_logger = std::make_shared<spdlog::logger>(id, sinks);
            // spdlog::register_logger(t_logger);
            // t_logger->set_level(spdlog::level::trace);
            // t_logger->flush_on(spdlog::level::trace);
        }

		return spdlog::default_logger();
	}
}