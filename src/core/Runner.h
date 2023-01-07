#pragma once

#include <mutex>
#include <string>
#include <unordered_map>
//#include "SubscriberSlot.h"
#include "Helper.h"
#include "RapidJsonParser.h"


//#include "Helper.h"
//#include "TypedValue.h"

namespace TARDIS::CORE
{
	//class EventArgs;
	//class Value;
	//class Db;
	class Engine;
	class ICaller;

	class Runner
	{
	public:
		//friend class Engine;

		//using Functor = bool(*)(const EventArgs& args);

		//using Getter = std::function<std::string(Db*)>;

        using Output   = std::unordered_map<std::string, std::string>;

		struct Param
		{
            Param(const std::string &name,
                  const std::string &value,
                  const std::string &get,
                  const std::string &desc,
                  const std::string &type,
                  UInt              typeId) 
                : m_name(name)
                , m_value(value)
                , m_get(get)
                , m_desc(desc)
                , m_type(type)
                , m_typeId(typeId)
            {}

			std::string m_name;
            std::string m_value;
            std::string m_get;
            std::string m_desc;
            std::string m_type;
            UInt        m_typeId;
		};

		//static std::shared_ptr<Runner> CreateRunner

		Runner(const std::string& nodeName,
			bool lock = false,
			bool skip = false,
			bool pause = false,
			bool times = 1);

		Runner();

		Runner(const Runner& runner);
		
		~Runner();

		void onDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node);

		bool OnSerialize(CORE::RapidJsonParser::Writer &json_writer);


		bool exec(Engine* engine);

		// const Getter& getValue(const int index) const
		// {
		// 	return m_inputs[index];
		// };

		// void addParam(Getter getter)
		// {
		// 	m_inputs.emplace_back(getter);
		// }

		// void setFunctorData(std::string type, std::string moduleId, std::string functor);


		void setTimes(unsigned int times) { m_times = times; }
		void setSkip(bool skip) { m_skip = skip; };
		void setPaused(bool paused) { m_paused = paused; }
		void setLock(bool lock) { m_lock = lock; }
		void setName(std::string name) { m_name = name; }
		void setId(std::string id) { m_id = id.empty() ? Helper::GenerateHex() : id; }
		void setModuleId(uint64_t id) { m_moduleId = id; };
		void setCallerName(std::string name) {m_caller = name; };

		bool getSkip() const { return m_skip; }
		bool getPaused() const { return m_paused; }
		bool getLock() const { return m_lock; }
		const std::string& getId()  const { return m_id; }
		const std::string& getName() const { return m_name; }
		const uint64_t& getModuleId() const { return m_moduleId; }
		const std::string& getCallerName() const { return m_caller; }

        void addOutput(const std::string& k, const std::string& v) { m_output.emplace(k, v); }
		
        std::string getOutput(const std::string& k) const 
		{ 
            auto it = m_output.find(k);
            return (it == m_output.cend()) ? it->second : "";
           
           // (it == m_output.cend()) ? it->second : "";
            //return (auto it = m_output.find(k)) != m_output.cend() ? it->second : "";
        } 
		
		void addParam(std::shared_ptr<Param> param) { m_params.emplace_back(param); }
		void addParam(const std::string &name,
					  const std::string &value,
					  const std::string &get,
					  const std::string &desc,
					  const std::string &type,
					  UInt typeId)
		{
			addParam(std::make_shared<Param>(name, value, get, desc, type, typeId));
		}

		auto& getParams() { return m_params; }
		

	private:
		static uint64_t ID_INCREMENT;
        //ICaller *m_caller;

        unsigned m_times;
		bool     m_skip;
		bool     m_paused;
		bool     m_lock;   

        bool     m_isActived;

		std::string  m_name;
		std::string  m_id;

		// functor data
		//std::string  m_type;
		uint64_t     m_moduleId;

		std::string  m_caller;

		std::mutex   m_mutex;

		//std::vector<Getter> m_inputs;
		std::vector<std::shared_ptr<Param>>  m_params;

        Output m_output;
		//std::vector<Value>  m_params;
	};
}