#pragma once

#include <vector>
#include <mutex>
#include <assert.h>
//#include "EventSet.h"
#include "Helper.h"
#include "SpdLog.h"
#include "Runner.h"

#include "JsonParser.h"
#include "RapidJsonParser.h"
#include <stdio.h>

#include "IPlugin.h"
#include "Communication.h"

extern int main();

namespace TARDIS::CORE
{
	// class CreateModuleEventArgs : public EventArgs
	// {
	// public:
	// 	CreateModuleEventArgs(const std::string& moduleId) :
	// 		m_moduleId(moduleId)
	// 	{}
	// 	std::string m_moduleId;
	// };

	// class RunnerParseEventArgs : public EventArgs
	// {
	// public:
	// 	RunnerParseEventArgs(std::shared_ptr<JsonParser> jsonParser) :
	// 		m_jsonParser(jsonParser)
	// 	{}
	// 	std::shared_ptr<JsonParser> m_jsonParser;
	// };
    
	class Engine /* : public EventSet */
	{
	public:
		friend class Runner;

		friend class CallBackImpl;

        friend int ::main();

		static const std::string EventEngineRun;
		static const std::string EventEngineStop;
		static const std::string EventRunnerStart;
		static const std::string EventRunnerEnd;
		static const std::string EventRunnerError;
		static const std::string EventRunnerWarn;
		static const std::string EventLog;

		using RunnerList = std::vector<std::shared_ptr<Runner>>;

		using Plugins    = std::unordered_map<std::string, IPlugin*>;

		using PoolData   = std::unordered_map<std::string, std::string>;

		static inline bool registerRunner(std::shared_ptr<Runner> runner)
		{
			runnerList.emplace_back(runner);
			return true;
		}

		// static inline bool onAddRunner(const EventArgs& args)
		// {
		// 	RunnerHandle(static_cast<const RunnerParseEventArgs&>(args).m_jsonParser).parseConfig();
		// 	return true;
		// }

		static inline bool OnDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
		{
			//CORE::ValueHelper<size_t>::fromString(json_node->get<std::string>("id"));
			//json_node->get<std::string>("name");
			if (json_node->nodeBegin("nodes"))
			{
				if (json_node->is<rapidjson::Value::Array>())
				{
					for (int i = 0; i < json_node->size(); i++)
					{
						if (json_node->nodeBegin(std::to_string(i)))
                        {
                            auto runner = std::make_shared<CORE::Runner>();
                            runner->onDeserialize(json_node);

                            CORE::Engine::registerRunner(runner);

                            json_node->nodeEnd();
                        };
					}
				}
				json_node->nodeEnd();
			}
			return true;
		}

		static bool RemoveAllRunner();

		Engine(std::string name);

        ~Engine()
        {
            for (auto it : m_plugins)
            {
                it.second->destroy();
            }
            m_plugins.clear();
        };

        void runTask();

		//bool onCreateModule(const EventArgs& args);

		//static bool isNodePresent(const std::string& name);
		//static void removeNode(const std::string& name);

		const std::string& getEngineId() const { return m_engineId; };

		const std::string& getName() const { return m_name; };

		//Db* getDb() { return &m_db; };

		//FunctorContainer::FunctorData* getFunctor(const std::string moduleId, const std::string fnName);

  

		//void setPluginThreadLogger(spdlog::logger* logger);

		bool isRunning() { return m_running; }

        Str getPoolData(const std::string& key) const;

        void addPlugin(const std::string& moduleId, IPlugin* plugin);

		IPlugin* getPlugin(const std::string &moduleId);

        void loadPlugins();

	public:
		static RunnerList   runnerList;

	private:
		void run();
		void onStart();
		void onStop();
		void onFinish();

        std::string         m_engineId;
		std::string         m_name;
		PoolData            m_poolData;
		//std::shared_ptr<spdlog::logger> m_thread_logger;
		bool                m_stop;
		bool                m_running;
		Plugins             m_plugins;

		
        std::shared_ptr<Runner> m_curRunner;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

        
	};

    class CallBackImpl : public VCallBack
    {
    public:

        CallBackImpl(Engine* engine) : m_engine(engine) 
		{
			assert(m_engine);
		}

		~CallBackImpl() 
		{
			printf("CallBackImpl is destroyed\r\n");
		}

        void addPoolData(const char* key, const char* value)
        {
			TDS_LOG_INFO("add pool data->key:{}, value:{}",  key, value);
           // printf( m_engine->m_curRunner->getName().c_str());
            m_engine->m_poolData.emplace(key, value);
        }

        void addOutput(const char* key, const char* value)
        {
			TDS_LOG_INFO("add output->key:{}, value:{}",  key, value);
			if(m_engine->m_curRunner)
			{
				m_engine->m_curRunner->addOutput(key, value);
			}
        }

		Communication* getCommunication(const char* moduleId)
		{
			IPlugin* plugin = m_engine->getPlugin(moduleId);
			if(!plugin)
			{
				TDS_LOG_ERROR("can not find plugin:{}",  moduleId);
				return nullptr;
			}

			Communication* pCommu = dynamic_cast<Communication*>(plugin);
			if(!pCommu)
			{
				TDS_LOG_ERROR("can not from plugin[{}] to communication",  moduleId);
				return nullptr;
			}

			return pCommu;
		}

    private:
        Engine* m_engine;
    };
}
