#include "Runner.h"

#include "ICaller.h"
#include "Engine.h"
#include "ValueHelper.h"
#include "SpdLog.h"
//#include "RunnerArgs.h"

namespace TARDIS::CORE
{

	Runner::Runner(const std::string& name, bool lock, bool skip, bool pause, bool times) :
		m_name(name),
		m_lock(lock),
		m_skip(skip),
		m_paused(pause),
		m_times(times)
	{};

	Runner::Runner() :
		m_name(""),
		m_lock(false),
		m_skip(false),
		m_paused(false),
		m_times(1)
	{};


	// bool Runner::exec(Engine* engine)
	// {
	// 	auto funcData = engine->getFunctor(m_moduleId, m_functor);
	// 	if (!funcData)
	// 	{
	// 		engine->m_thread_logger->error("can not find functor[{}] from module[{}]", m_functor, m_moduleId);
	// 		return false;
	// 	}

	// 	auto& functor = funcData->m_functorSlot;

	// 	RunnerArgs args(engine, this);

	// 	for (uint32_t i = 0; i < m_times; i++)
	// 	{
	// 		//std::lock_guard<std::mutex> locker(m_mutex);

	// 		if (!functor(args))
	// 		{
	// 			return false;
	// 		}
	// 	}
	// 	return true;
	// }

	bool Runner::exec(Engine* engine)
	{

		//RunnerArgs args(engine, this);
        LOG_INFO(engine->getEngineId(), "--------------------------------");
        printf("start run:%s\r\n", m_name.c_str());

        

        auto it = engine->m_plugins.find(m_moduleId);
        if (it == engine->m_plugins.end())
        {
            return false;
        }
        printf("find module:%s\r\n", m_moduleId.c_str());

        ICaller *pCaller = it->second->getCaller(m_caller.c_str());
        if (!pCaller)
        {
            return false;
        }
        printf("find caller:%s\r\n", m_caller.c_str());

        Str* params = nullptr;
        int param_count = m_params.size();
        if(param_count > 0)
        {
            params = new (std::nothrow) Str[param_count];
            if(!params)
            {
                return false;
            }
            for (int i = 0; i < param_count; ++i)
            {
                if (!m_params[i]->m_get.empty())
                {
                    params[i] = engine->getPoolData(m_params[i]->m_get);
                }
                else
                {
                    params[i].buf = m_params[i]->m_value.c_str();
                    params[i].len = m_params[i]->m_value.size();
                }
                //auto sss = TARDIS::CORE::ValueHelper<const char *>::fromString(std::string(params[i].buf, params[i].len));
            }
        }

       

        for (uint32_t i = 0; i < m_times; ++i)
		{
			//std::lock_guard<std::mutex> locker(m_mutex);
			if (!(*pCaller)(params))
			{
				return false;
			}
		}
        if(params)
        {
            delete[] params;
        }
       
		return true;
	}

	// void Runner::setFunctorData(std::string type, std::string moduleId, std::string functor)
	// {
	// 	//m_type     = std::move(type);
	// 	//m_moduleId = std::move(moduleId);
	// 	//m_functor  = std::move(functor);
	// }

	void Runner::onDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
	{
		setName(json_node->get<std::string>("name"));
		setId(json_node->get<std::string>("id"));
		setLock(json_node->get<bool>("lock"));
		setSkip(json_node->get<bool>("skip"));
		setPaused(json_node->get<bool>("pause"));

        if (json_node->nodeBegin("runner"))
        {
            m_moduleId = json_node->get<std::string>("module_id");
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
                            json_node->get<std::string>("type"),
                            json_node->get<std::string>("value"),
                            json_node->get<std::string>("get")));
                        json_node->nodeEnd();
                    }
                }
                json_node->nodeEnd();
            }
            json_node->nodeEnd();
        }
    }

	Runner::~Runner()
	{
		
	}
}