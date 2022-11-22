#pragma once

#include <memory>
#include <functional>
#include "JsonParser.h"
namespace TARDIS::CORE
{
	class JsonHandler
	{
	public:
		JsonHandler(std::shared_ptr<JsonParser>& jsonParser) :
			m_jsonParser(jsonParser)
		{}

		virtual ~JsonHandler() {};

		virtual void parseConfig() = 0;

		virtual void serialize() {};

	protected:
		std::shared_ptr<JsonParser> m_jsonParser;
	};
}