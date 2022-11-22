#pragma once
#include <string>
#include <memory>

namespace TARDIS::CORE
{
	class RawDataContainer;

	class JsonParser
	{
	public:

		JsonParser();
		virtual ~JsonParser();

		void cleanup();

		virtual void         parseJson(const RawDataContainer& source) = 0;
		virtual void         parseJsonFile(const std::string& filename);

		virtual void         toJsonString(RawDataContainer& source) = 0;
		virtual void         saveJsonToFile(const std::string& filename);

		virtual bool         nodeBegin(const std::string& key) = 0;
		virtual bool         nodeEnd() = 0;

	private:
		void loadRawData(const std::string& filename, RawDataContainer& output);
		void unloadRawData(RawDataContainer& data);

	};
}