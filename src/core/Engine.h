#pragma once

#include <vector>
#include <mutex>
//#include "EventSet.h"
#include "Helper.h"
//#include "Db.h"
#include "Log.h"
#include "Runner.h"
#include "IPlugin.h"
#include "JsonParser.h"
#include "RapidJsonParser.h"
//#include "FunctorContainer.h"
//#include "RunnerHandle.h"


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

		static inline bool onDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
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

		~Engine() { m_plugins.clear(); };

		void runTask();

		//bool onCreateModule(const EventArgs& args);

		//static bool isNodePresent(const std::string& name);
		//static void removeNode(const std::string& name);

		//unsigned long getEngineId() { return m_engineId; };

		//std::string getName() { return m_name; };

		//Db* getDb() { return &m_db; };

		//FunctorContainer::FunctorData* getFunctor(const std::string moduleId, const std::string fnName);

  

		//void setPluginThreadLogger(spdlog::logger* logger);

		bool isRunning() { return m_running; }

        Str getPoolData(const std::string& key) const;

        void addPlugin(const std::string& moduleId, IPlugin* plugin);

        void loadPlugins();

	public:
		static RunnerList   runnerList;
	private:
		void run();
		void onStart();
		void onStop();
		void onFinish();

		unsigned long       m_engineId;
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

        CallBackImpl(Engine* engine) : m_engine(engine) {}

        void addPoolData(const char* key, const char* value)
        {
            printf( "add pool data->key:%s, value:%s", key, value);
            printf( m_engine->m_curRunner->getName().c_str());
            m_engine->m_poolData.emplace(key, value);
        }

        void addOutput(const char* key, const char* value)
        {
            m_engine->m_curRunner->addOutput(key, value);
        }

    private:
        Engine* m_engine;
    };
}
