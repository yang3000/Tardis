#include <iostream>
#include "JsonHandler.h"
#include "RapidJsonParser.h"

namespace TARDIS::CORE
{
	rapidjson::Document RapidJsonParser::m_doc;

	RapidJsonParser::RapidJsonParser()
	{}

	// RapidJsonParser::RapidJsonParser(std::shared_ptr<Node> node)
	// {
	// 	m_node_stack.emplace_back(node->m_name, node->m_node);
	// }

	// RapidJsonParser::RapidJsonParser(rapidjson::Value* node)
	// {
	// 	m_node_stack.emplace_back("root", node);
	// }



	RapidJsonParser::~RapidJsonParser()
	{
		//saveJsonToFile("C:\\Users\\yangh\\Desktop\\Tardis\\bin\\Debug\\sequence.json");
	}

	void RapidJsonParser::parseJson(const RawDataContainer& source)
	{
		if (m_doc.Parse(reinterpret_cast<const char*>(source.getDataPtr()), source.getSize()).HasParseError())
		{
			std::cout << "" << std::endl;
		}
		m_node_stack.emplace_back("root", rapidjson::Pointer("").Get(m_doc));
	}

	void RapidJsonParser::toJsonString(RawDataContainer& source)
	{
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		m_doc.Accept(writer);
		source.copyData(buffer.GetString(), buffer.GetSize());
	}

	bool RapidJsonParser::nodeBegin(const std::string& key)
	{
        printf("Begine Key:%s\r\n", key.c_str());
		rapidjson::Value* value = rapidjson::Pointer(std::string(std::string("/") + key).c_str()).Get(*(m_node_stack.back().second));
		if (value)
		{
			m_node_stack.emplace_back(key, value);
			return true;
		}
		return false;
	}

	bool RapidJsonParser::nodeEnd()
	{
		if (!m_node_stack.empty())
		{
			m_node_stack.pop_back();
		}
		return true;
	}

}