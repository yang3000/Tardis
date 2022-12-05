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
                  const std::string &type,
                  const std::string &value,
                  const std::string &get) : 
                  m_name(name),
                  m_type(type),
                  m_value(value),
                  m_get(get)
            {}

			std::string m_name;
            std::string m_type;
            std::string m_value;
            std::string m_get;
		};

		//static std::shared_ptr<Runner> CreateRunner

		Runner(const std::string& nodeName,
			bool lock = false,
			bool skip = false,
			bool pause = false,
			bool times = 1);

		Runner();

		~Runner();

		void onDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node);


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

		bool getSkip() const { return m_skip; }
		bool getPaused() const { return m_paused; }
		bool getLock() const { return m_lock; }
		const std::string& getId()  const { return m_id; }
		const std::string& getName() const { return m_name; }

        void addOutput(const std::string& k, const std::string& v) { m_output.emplace(k, v); }
        std::string getOutput(const std::string& k) const { 
            auto it = m_output.find(k);
            return (it == m_output.cend()) ? it->second : "";
           
           // (it == m_output.cend()) ? it->second : "";
            //return (auto it = m_output.find(k)) != m_output.cend() ? it->second : "";
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
		std::string  m_moduleId;
		std::string  m_caller;

		std::mutex   m_mutex;

		//std::vector<Getter> m_inputs;
		std::vector<std::shared_ptr<Param>>  m_params;

        Output m_output;
		//std::vector<Value>  m_params;
	};
}