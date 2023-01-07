#pragma once

#include "Base.h"
#include <thread>
//#include <objbase.h>
#include <string>
#include <random>
#include <sstream>

namespace TARDIS::CORE
{
	class TARDIS_EXPORT Helper
	{
	public:
		// static size_t getThreadId()
		// {
		// 	return std::hash<std::thread::id>()(std::this_thread::get_id());
		// }

		static std::thread::id getThreadId()
		{
			return std::this_thread::get_id();
		}

		template <typename T>
		static size_t getHash(T t)
		{
			return std::hash<T>()(std::move(t));
		}

		static unsigned int RandomChar()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 255);
			return dis(gen);
		}

		static std::string GenerateHex()
		{
			std::stringstream ss;
			for (auto i = 0; i < 16; i++)
			{
				const auto rc = RandomChar();
				std::stringstream hexstream;
				hexstream << std::hex << rc;
				auto hex = hexstream.str();
				ss << (hex.length() < 2 ? '0' + hex : hex);
			}
			return ss.str();
		}

		static void memory_dump(void *ptr, int len)
		{
			int i;

			for (i = 0; i < len; i++)
			{
				if (i % 8 == 0 && i != 0)
					printf(" ");
				if (i % 16 == 0 && i != 0)
					printf("\n");
				printf("%02x ", *((uint8_t *)ptr + i));
			}
			printf("\n");
		}

		// static std::string GenerateGuid()
		// {
		// 	char buf[64] = { 0 };
		// 	GUID guid;

		// 	if (S_OK != CoCreateGuid(&guid))
		// 	{
		// 		return std::move(std::string(""));
		// 	}

		// 	sprintf_s(buf, sizeof(buf),
		// 		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		// 		guid.Data1, guid.Data2, guid.Data3,
		// 		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		// 		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		// 	return std::string(buf);
		// }
	};

	// auto ConvertToNative(std::string type, std::string value)
	//  {
	// 	if(type == "string")
	// 	ValueHelper<std::string>::fromString(value)
	//  }

}

template<typename T>
struct remove_grammar;

template<typename T>
struct remove_grammar
{
	remove_grammar()
	{
		int a = 0;
	}
	using type = std::remove_reference_t<T>;
};

template<typename T>
struct remove_grammar<const T>
{
	remove_grammar()
	{
		int a = 0;
	}
	using type = std::remove_reference_t<T>;
};

template<>
struct remove_grammar<const std::string>
{
	using type = char*;
};

template<>
struct remove_grammar<std::string>
{
	using type = char*;
};

template<>
struct remove_grammar<const char*>
{
	using type = char*;
};