#include <cassert>
#include "JsonParser.h"
#include "RawDataContainer.h"

namespace TARDIS::CORE
{

	JsonParser::JsonParser()
	{}

	JsonParser::~JsonParser()
	{}

	void JsonParser::cleanup()
	{

	}

	void JsonParser::parseJsonFile(const std::string& filename)
	{
		RawDataContainer rawJsonData;
		loadRawData(filename, rawJsonData);
		parseJson(rawJsonData);
		unloadRawData(rawJsonData);
	}

	void JsonParser::saveJsonToFile(const std::string& filename)
	{
		assert(!filename.empty());

		FILE* file;
		fopen_s(&file, filename.c_str(), "w");

		assert(file != nullptr);

		RawDataContainer rawJsonData;
		toJsonString(rawJsonData);

		fwrite(rawJsonData.getDataPtr(), sizeof(char), rawJsonData.getSize(), file);
		fclose(file);

		unloadRawData(rawJsonData);
	}

	void JsonParser::loadRawData(const std::string& filename, RawDataContainer& output)
	{
		assert(!filename.empty());

		FILE* file;
		fopen_s(&file, filename.c_str(), "rb");

		assert(file != nullptr);

		fseek(file, 0, SEEK_END);
		const size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);

		unsigned char* buffer = new unsigned char[size];

		const size_t size_read = fread(buffer, sizeof(char), size, file);
		fclose(file);

		if (size_read != size)
		{
			delete[] buffer;
			assert(0);
		}

		output.setData(buffer);
		output.setSize(size);

	}
	void JsonParser::unloadRawData(RawDataContainer& data)
	{
		data.release();
	}

}