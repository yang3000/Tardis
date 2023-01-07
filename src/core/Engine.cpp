#include "Engine.h"

#include <iostream>
#include "Helper.h"
//#include "RunnerEventArgs.h"
//#include "Event.h"
//#include "RunnerArgs.h"
//#include "Node.h"

#include "PluginManager.h"

//#include "CommunicationManager.h"
//#include "Printer.h"


namespace TARDIS::CORE
{
	const std::string Engine::EventEngineRun("EngineRun");
	const std::string Engine::EventEngineStop("EngineStop");
	const std::string Engine::EventRunnerStart("RunnerStart");
	const std::string Engine::EventRunnerEnd("RunnerEnd");
	const std::string Engine::EventRunnerError("RunnerError");
	const std::string Engine::EventRunnerWarn("RunnerWarn");
	const std::string Engine::EventLog("PrintLog");

	Engine::RunnerList Engine::runnerList;
	Engine::RunnerList Engine::Setup;
	Engine::RunnerList Engine::Cleanup;

	Engine::Engine(std::string name) :
		m_name(name),
		m_engineId(std::to_string(Helper::getHash(name))),
		m_stop(false),
		m_running(false)
	{};

	void Engine::onStart()
	{
		m_running = true;

		// std::string logFile = m_db.getValue<std::string>("logfile");
		// logFile = logFile.empty() ? std::to_string(m_engineId) + "_log.txt" : logFile;

		// m_thread_logger = Log::AddLogger(std::to_string(m_engineId), logFile);
		// setPluginThreadLogger(m_thread_logger.get());

		// m_thread_logger->info("{} start running...", m_name);
	}

	void Engine::onStop()
	{
		m_running = false;
	}

	void Engine::onFinish()
	{
		// m_thread_logger->info("{} is finished.", m_name);
		// Log::DropLogger(std::to_string(m_engineId));
		// m_thread_logger.reset();
		m_running = false;
	}

	void Engine::runTask()
	{
        m_running = true;
		// if (m_running)
		// {
		// 	m_thread_logger->warn("{} is running, please waitting...", m_name);
		// 	return;
		// }
		std::thread thread(&Engine::run, this);
		thread.detach();
	}

	void Engine::run()
	{
		if (runnerList.size() == 0) {
			// RunnerEventArgs event_warn("no node");
			// fireEvent(EventRunnerWarn, event_warn);
			onFinish();
			return;
		}

        onStart();

		for (int i = 0; i < runnerList.size(); i++)
		{
			if (m_stop)
			{
				break;
			}
			if(runnerList[i]->getSkip())
			{
				continue;
			}

            m_curRunner = runnerList[i];

			// node start. fire!
			// RunnerEventArgs event_start(m_curRunner);
			// fireEvent(EventRunnerStart, event_start);

			// if (m_curRunner->m_paused)
			// {

			// }

			// call it.
			bool res = runnerList[i]->exec(this);
			if (!res) {
				// RunnerEventArgs event_error(m_curRunner, std::string("execute node[") + m_curRunner->m_name + "] fail");
				// fireEvent(EventRunnerError, event_error);
				break;
			}
			// RunnerEventArgs event_end(m_curRunner);
			// fireEvent(EventRunnerEnd, event_end);
		}

		// RunnerEventArgs event_stop;
		// fireEvent(EventEngineStop, event_stop);

		onFinish();
		return;
	}

    Str Engine::getPoolData(const std::string &key) const
    {
        Str str;
        str.buf = nullptr;
        str.len = 0;
        auto it = m_poolData.find(key);
        if (it == m_poolData.cend())
        {
			TDS_LOG_WARN("can not find data from pool by key[{}]", key);
        	return str;
        }
		str.buf = it->second.c_str();
        str.len = it->second.size();
        return str;
    }

    IPlugin* Engine::addPlugin(uint64_t moduleId, IPlugin* plugin)
    {
		if(plugin)
		{
			m_plugins.emplace(moduleId, plugin);
			return plugin;
		}

		if(!m_plugins.count(moduleId))
		{
			auto plugin = PluginManager::CreatePlugin(moduleId);
			m_plugins.emplace(moduleId, plugin);
			return plugin;
		}
		return nullptr;
    }

    void Engine::loadPlugins()
    {

    }
    
    IPlugin* Engine::getPlugin(uint64_t moduleId)
	{
		auto it = m_plugins.find(moduleId);
		if(it != m_plugins.end())
		{
			return it->second;
		}
		return nullptr;
	}

	bool Engine::RemoveAllRunner()
	{
		//Nodes.clear();
		//if (Nodes.empty())
		//{
		//	return true;
		//}
		//std::vector<std::unique_ptr<Node>>::const_iterator pos = Nodes.begin();
		//for (; pos != Nodes.end(); ++pos)
		//	delete *pos;

		//d_nodes.clear();
		return true;
	}

}