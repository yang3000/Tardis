#include "Runner.h"

#include "ValueHelper.h"
#include "PluginManager.h"
#include "SpdLog.h"
#include "ICaller.h"
#include "Engine.h"
//#include "Helper.h"

namespace TARDIS::CORE
{
    uint64_t Runner::ID_INCREMENT = 0;

	Runner::Runner(const std::string& name, bool lock, bool skip, bool pause, bool times) 
        : m_name(name)
        , m_id("##" + std::to_string(++ID_INCREMENT))
        , m_lock(lock)
        , m_skip(skip)
        , m_paused(pause)
        , m_times(times)
	{};

	Runner::Runner() 
        : m_name("")
        , m_id("##" + std::to_string(++ID_INCREMENT))
        , m_lock(false)
        , m_skip(false)
        , m_paused(false)
        , m_times(1)
	{};

    Runner::Runner(const Runner& runner)
    {
        m_name   = runner.m_name;
        m_id     = "##" + std::to_string(++ID_INCREMENT);
        m_lock   = runner.m_lock;
        m_skip   = runner.m_skip;
        m_paused = runner.m_paused;
        m_times  = runner.m_times;
        m_moduleId = runner.m_moduleId;
        m_caller = runner.m_caller;

        for(auto param : runner.m_params)
        {
            m_params.emplace_back(std::make_shared<Param>(
                param->m_name,
                param->m_value,
                param->m_get,
                param->m_desc,
                param->m_type,
                param->m_typeId
            ));
        }
    }

	bool Runner::exec(Engine* engine)
	{
        {
            LOG_INFO(engine->getEngineId(), "--------------------------------");
            LOG_INFO(engine->getEngineId(), "start run:{}", m_name);
        }

        // find plugin
        auto it = engine->m_plugins.find(m_moduleId);
        if (it == engine->m_plugins.end())
        {
            LOG_ERROR(engine->getEngineId(), "can not find module:{}[{}]", PluginManager::GetPluginName(m_moduleId), m_moduleId);
            return false;
        }

        {
            LOG_INFO(engine->getEngineId(), "find module:{}[{}]", PluginManager::GetPluginName(m_moduleId), m_moduleId);
        }

        // find caller
        ICaller *pCaller = it->second->getCaller(m_caller.c_str());
        if (!pCaller)
        {
            LOG_ERROR(engine->getEngineId(), "can not find caller:{}", m_caller);
            return false;
        }

        {
            LOG_INFO(engine->getEngineId(), "find caller:{}", m_caller);
        }

        // initialize params
        AssignParam params(m_params.size());
        for (int i = 0; i < params.n; ++i)
        {
            if (!m_params[i]->m_get.empty())
            {
                auto poolData = engine->getPoolData(m_params[i]->m_get);
                params.push(poolData.buf, poolData.len);
            }
            else
            {
                if(m_params[i]->m_typeId == TardisDataType_Communication)
                {
                    auto pluginId = ValueHelper<uint64_t>::from(m_params[i]->m_value);
                    auto plugin = engine->getPlugin(pluginId);
                    if(!plugin)
                    {
                        LOG_ERROR(engine->getEngineId(), "can not find communication plugin, id:{}", pluginId);
                        return false;
                    }
                    auto commu = dynamic_cast<Communication *>(plugin);
                    if(!commu)
                    {
                        LOG_ERROR(engine->getEngineId(), "can not turn plugin to communication");
                        return false;
                    }
                    params.push(commu, sizeof(void *));
                }
                else
                {
                    params.push(m_params[i]->m_value.c_str(), m_params[i]->m_value.size());
                }
            }
        }

        // execute caller
        for (uint32_t i = 0; i < m_times; ++i)
		{
			//std::lock_guard<std::mutex> locker(m_mutex);
			if (!(*pCaller)(params.args))
			{
				return false;
			}
		}
		return true;
	}

	void Runner::onDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
	{
		setName(json_node->get<std::string>("name"));
		setId(json_node->get<std::string>("id"));
		setLock(json_node->get<bool>("lock"));
		setSkip(json_node->get<bool>("skip"));
		setPaused(json_node->get<bool>("pause"));

        if (json_node->nodeBegin("runner"))
        {
            m_moduleId = json_node->get<uint64_t>("module_id");
            m_caller   = json_node->get<std::string>("method");
            if (json_node->nodeBegin("input"))
            {
                if (json_node->is<rapidjson::Value::Array>())
                {
                    for (int i = 0; i < json_node->size(); i++)
                    {
                        json_node->nodeBegin(std::to_string(i));
                        m_params.emplace_back(std::make_shared<Param>(
                            json_node->get<std::string>("param"),
                            json_node->get<std::string>("value"),
                            json_node->get<std::string>("get"),
                            json_node->get<std::string>("desc"),
                            json_node->get<std::string>("type"),
                            ValueHelper<UInt>::from(json_node->get<std::string>("type_id"))
                            ));
                        json_node->nodeEnd();
                    }
                }
                json_node->nodeEnd();
            }
            json_node->nodeEnd();
        }
    }

    bool Runner::OnSerialize(CORE::RapidJsonParser::Writer &json_writer)
    {
        json_writer.StartObject();

        json_writer.Key("name");        json_writer.String(m_name);
        json_writer.Key("lock");        json_writer.Bool(m_lock);
        json_writer.Key("skip");        json_writer.Bool(m_skip);
        json_writer.Key("pause");       json_writer.Bool(m_paused);

        json_writer.Key("runner");

        json_writer.StartObject();

        json_writer.Key("module_id");   json_writer.Int64(m_moduleId);
        json_writer.Key("method");      json_writer.String(m_caller);
        json_writer.Key("input");
        json_writer.StartArray();
        for (auto param : m_params)
        {
            json_writer.StartObject();
            json_writer.Key("param");   json_writer.String(param->m_name);
            json_writer.Key("type");    json_writer.String(param->m_type);
            json_writer.Key("type_id"); json_writer.String(ValueHelper<uint8_t>::toString(param->m_typeId));
            json_writer.Key("value");   json_writer.String(param->m_value);
            json_writer.Key("get");     json_writer.String(param->m_get);
            json_writer.Key("desc");    json_writer.String(param->m_get);
            json_writer.EndObject();
        }
        json_writer.EndArray();

        json_writer.EndObject();

        json_writer.EndObject();
        return true;
    }

	Runner::~Runner()
	{}
}