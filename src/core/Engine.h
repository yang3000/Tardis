#pragma once

#include <vector>
#include <mutex>
#include <assert.h>
#include <stdio.h>

#include "Helper.h"
#include "SpdLog.h"
#include "Runner.h"
#include "JsonParser.h"
#include "RapidJsonParser.h"
#include "IPlugin.h"
#include "Communication.h"
#include "Event.h"

extern int main();

namespace TARDIS::CORE
{
    struct TestItemResult
    {
        std::string name;
        std::string desc;
        std::string lower;
        std::string value;
        std::string upper;
        std::string result;
    };

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

        using Plugins    = std::unordered_map<uint64_t, IPlugin *>;

        using PoolData   = std::unordered_map<std::string, std::string>;

        using PoolData   = std::unordered_map<std::string, std::string>;

        static inline bool registerRunner(std::shared_ptr<Runner> runner)
        {
            runnerList.emplace_back(runner);
            return true;
        }

        static inline bool registerSetup(std::shared_ptr<Runner> runner)
        {
            Setup.emplace_back(runner);
            return true;
        }

        static inline bool registerCleanup(std::shared_ptr<Runner> runner)
        {
            Cleanup.emplace_back(runner);
            return true;
        }


        // static inline bool onAddRunner(const EventArgs& args)
        // {
        // 	RunnerHandle(static_cast<const RunnerParseEventArgs&>(args).m_jsonParser).parseConfig();
        // 	return true;
        // }

        static inline bool OnDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
        {
            if (json_node->nodeBegin("setup"))
            {
                if (json_node->is<rapidjson::Value::Array>())
                {
                    for (int i = 0; i < json_node->size(); i++)
                    {
                        if (json_node->nodeBegin(std::to_string(i)))
                        {
                            auto runner = std::make_shared<CORE::Runner>();
                            runner->onDeserialize(json_node);

                            CORE::Engine::registerSetup(runner);

                            json_node->nodeEnd();
                        };
                    }
                }
                json_node->nodeEnd();
            }

            if (json_node->nodeBegin("sequences"))
            {
                // CORE::ValueHelper<size_t>::fromString(json_node->get<std::string>("id"));
                // json_node->get<std::string>("name");
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
                json_node->nodeEnd();
            }
            return true;
        }

        static inline bool OnSerialize(CORE::RapidJsonParser::Writer &json_writer)
        {
            json_writer.Key("sequences");
            json_writer.StartObject();
            json_writer.Key("id");   json_writer.String("111111");
            json_writer.Key("name"); json_writer.String("test_sequences");

            json_writer.Key("nodes");
            json_writer.StartArray();
            for(auto runner : runnerList)
            {
                runner->OnSerialize(json_writer);
            }
            json_writer.EndArray();

            json_writer.EndObject();
            return true;
        }

        static bool RemoveAllRunner();

        Engine(std::string name);

        ~Engine()
        {
            // for (auto it : m_plugins)
            // {
            //     it.second->destroy();
            // }
            m_plugins.clear();
        };

        void runTask();

        // bool onCreateModule(const EventArgs& args);

        // static bool isNodePresent(const std::string& name);
        // static void removeNode(const std::string& name);

        const std::string &getEngineId() const { return m_engineId; };

        const std::string &getName() const { return m_name; };

        // Db* getDb() { return &m_db; };

        bool isRunning() { return m_running; }

        Str getPoolData(const std::string &key) const;

        IPlugin *addPlugin(uint64_t moduleId, IPlugin* plugin = nullptr);

        IPlugin *getPlugin(uint64_t moduleId);

        void loadPlugins();

    public:
        static RunnerList runnerList;

        static RunnerList Setup;

        static RunnerList Cleanup;

        Event<TestItemResult*>  RunnerFinishEvent;

        Event<>                 EngineBeginEvent;
        Event<>                 EngineEndEvent;

    private:
        void run();
        void onStart();
        void onStop();
        void onFinish();

        std::string m_engineId;
        std::string m_name;
        PoolData    m_poolData;
        
        bool        m_stop;
        bool        m_running;
        Plugins     m_plugins;

        std::weak_ptr<Runner> m_curRunner;



        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;
    };

    class CallBackImpl : public VCallBack
    {
    public:
        CallBackImpl(std::weak_ptr<Engine> engine) 
            : m_engine(engine)
        { }

        ~CallBackImpl()
        {
            printf("CallBackImpl is destroyed\r\n");
        }

        void addPoolData(const char *key, const char *value)
        {
            TDS_LOG_INFO("add pool data->key:{}, value:{}", key, value);
            // printf( m_engine->m_curRunner->getName().c_str());
            auto engine = m_engine.lock();
            if(engine)
            {
                engine->m_poolData.emplace(key, value);
            }
        }

        void output(const char *value)
        {
            TDS_LOG_INFO("add output value:{}",value);

            auto engine = m_engine.lock();
            if (!engine)
            {
                TDS_LOG_ERROR("the current engine was destroyed");
                return;
            }

            auto runner = engine->m_curRunner.lock();
            if (!runner)
            {
                TDS_LOG_ERROR("the current runner was destroyed");
                return;
            }

            runner->output(value);
        }

        void showTestItem(
            const char *name,
            bool res = true,
            const char *value = nullptr,
            const char *lower = nullptr,
            const char *upper = nullptr,
            const char *desc = nullptr)
        {
            THREAD_LOG_INFO("{}-{}-{}-{}-{}-{}", name, res, value ? value : "", lower ? lower : "", upper ? upper : "", desc ? desc : "");
        }

        Communication *getCommunication(uint64_t moduleId)
        {
            auto engine = m_engine.lock();
            if(!engine)
            {
                return nullptr;
            }

            IPlugin *plugin = engine->getPlugin(moduleId);
            if (!plugin)
            {
                THREAD_LOG_ERROR("can not find plugin:{}", moduleId);
                return nullptr;
            }

            Communication *pCommu = dynamic_cast<Communication *>(plugin);
            if (!pCommu)
            {
                THREAD_LOG_ERROR("can not from plugin[{}] to communication", moduleId);
                return nullptr;
            }

            return pCommu;
        }

    private:
        std::weak_ptr<Engine> m_engine;
    };
}
