#pragma once

#include <vector>
#include <functional>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/pointer.h"
#include "JsonParser.h"
//#include "Exceptions.h"

#include "RawDataContainer.h"

namespace TARDIS::CORE
{
	class RapidJsonParser : public JsonParser
	{
	public:
		RapidJsonParser();

		~RapidJsonParser();

		void parseJson(const RawDataContainer& source) override;

		void toJsonString(RawDataContainer& source) override;

		bool nodeBegin(const std::string& key) override;

		bool nodeEnd() override;

		template<typename T>
		T get()
		{
			if (m_node_stack.empty())
			{
				//throw GenericException("node stack is empty");
			}

			if (!is<T>())
			{
				std::string err = std::string("the current value[") + m_node_stack.back().first + "] does not match type[" + typeid(T).name() + "].";
				//throw GenericException(err);
			}
			return m_node_stack.back().second->Get<T>();
		}

		template<typename T>
		T get(const std::string key)
		{
			T t;
			if (nodeBegin(key))
			{
				//try {
					t = get<T>();
				//}
				//catch (/*const Exception& err>*/)
				//{
					//nodeEnd();
					//throw err;
				//}
				nodeEnd();
			}
			return t;
		}

		std::string get(const std::string key)
		{
			std::string t;
			if (nodeBegin(key))
			{
				t = get<const char*>();
				nodeEnd();
			}
			return t;
		}

		template<typename T>
		bool is()
		{
			return m_node_stack.back().second->Is<T>();
		}

		size_t size()
		{
			return m_node_stack.back().second->Size();
		}


	private:

		static rapidjson::Document m_doc;

		std::vector<std::pair<std::string, rapidjson::Value*>> m_node_stack;
	};
}

