#include "SpdLog.h"
#include "Helper.h"

namespace TARDIS::CORE
{

	void SpdLog::log(LogType type,const char *msg)
	{
		switch (type)
		{
		case LogType::Trace:    SpdLog::Logger(m_logId)->trace   (msg); break;
		case LogType::Info:     SpdLog::Logger(m_logId)->info    (msg); break;
		case LogType::Warn:     SpdLog::Logger(m_logId)->warn    (msg); break;
		case LogType::Error:    SpdLog::Logger(m_logId)->error   (msg); break; 
		case LogType::Critical: SpdLog::Logger(m_logId)->critical(msg); break;
		default:
			break;
		}
	}

    SpdLog::SpdLog(const std::string& id, const std::string& file) : m_logId(id)
    {
        AddLogger(m_logId, file);
    }


	SpdLog::~SpdLog()
	{
		spdlog::drop(m_logId);
	}

	std::shared_ptr<spdlog::logger> SpdLog::Logger(const std::string& id)
	{
		// if(!id.empty())
		// {
		// 	auto logger = spdlog::get(id);
		// 	return logger ? logger : spdlog::default_logger();
		// }
		return spdlog::default_logger();
	}

	std::shared_ptr<spdlog::logger> SpdLog::AddLogger(const std::string& id, const std::string& fileName)
	{
		if(!id.empty())
		{
			auto logger = spdlog::get(id);
			if(logger)
			{
				return logger;
			}
			
			spdlog::sink_ptr t_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, true);
			t_sink->set_pattern("%^[%T] %t %n: %v%$");
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

	std::shared_ptr<spdlog::logger> SpdLog::DefaultLogger()
	{
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_pattern("[Tardis][%t][%^%l%$] %v");
		auto logger = std::make_shared<spdlog::logger>("Default", console_sink);
		logger->set_level(spdlog::level::trace);
		spdlog::set_default_logger(logger);
		return logger;
	}
}