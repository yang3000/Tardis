#pragma once

#include "Base.h"
#include <thread>
//#include <objbase.h>
#include <string>
#include <random>
#include <sstream>
#include <iostream>

namespace TARDIS::CORE
{
	class TARDIS_EXPORT Helper
	{
	public:
		static inline size_t getThreadId()
		{
			return std::hash<std::thread::id>()(std::this_thread::get_id());
		}

		static inline std::string getThreadIdStr()
		{
			return std::to_string(getThreadId());
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

		static inline std::string GenerateHex()
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

		template <typename T, size_t N>
		static bool SplitString(const char *src, const char *split, T(*des)[N])
		{
			size_t src_len = strlen(src) + 1;
			char *s = new char[src_len];
			memcpy_s(s, src_len, src, src_len);
			char *c = nullptr;
			char *p = strtok_s(s, split, &c);
			while (p != nullptr)
			{
				sprintf_s(reinterpret_cast<char *>(des++), strlen(p) + 1, "%s", p);
				p = strtok_s(nullptr, split, &c);
			}
			delete[] s;
			return true;
		}
		
		static inline bool MinValue(TardisDataType type, void* value)
		{
			switch (type)
			{
			case TardisDataType_S8:     *(signed char*)        value = (std::numeric_limits<signed char>::min)();        return true;
			case TardisDataType_U8:     *(unsigned char*)      value = (std::numeric_limits<unsigned char>::min)();      return true;
			case TardisDataType_S16:    *(signed short*)       value = (std::numeric_limits<signed short>::min)();       return true;
			case TardisDataType_U16:    *(unsigned short*)     value = (std::numeric_limits<unsigned short>::min)();     return true;
			case TardisDataType_S32:    *(signed int*)         value = (std::numeric_limits<signed int>::min)();         return true;
			case TardisDataType_U32:    *(unsigned int*)       value = (std::numeric_limits<unsigned int>::min)();       return true;
			case TardisDataType_S64:    *(signed long long*)   value = (std::numeric_limits<signed long long>::min)();   return true;
			case TardisDataType_U64:    *(unsigned long long*) value = (std::numeric_limits<unsigned long long>::min)(); return true;
			case TardisDataType_Float:  *(float*)              value = (std::numeric_limits<float>::lowest)();           return true;
			case TardisDataType_Double: *(double*)             value = (std::numeric_limits<double>::lowest)();          return true;
			default: break;
			}
			return false;
		}

		static inline bool MaxValue(TardisDataType type, void* value)
		{
			switch (type)
			{
			case TardisDataType_S8:     *(signed char*)        value = (std::numeric_limits<signed char>::max)();        return true;
			case TardisDataType_U8:     *(unsigned char*)      value = (std::numeric_limits<unsigned char>::max)();      return true;
			case TardisDataType_S16:    *(signed short*)       value = (std::numeric_limits<signed short>::max)();       return true;
			case TardisDataType_U16:    *(unsigned short*)     value = (std::numeric_limits<unsigned short>::max)();     return true;
			case TardisDataType_S32:    *(signed int*)         value = (std::numeric_limits<signed int>::max)();         return true;
			case TardisDataType_U32:    *(unsigned int*)       value = (std::numeric_limits<unsigned int>::max)();       return true;
			case TardisDataType_S64:    *(signed long long*)   value = (std::numeric_limits<signed long long>::max)();   return true;
			case TardisDataType_U64:    *(unsigned long long*) value = (std::numeric_limits<unsigned long long>::max)(); return true;
			case TardisDataType_Float:  *(float*)              value = (std::numeric_limits<float>::max)();              return true;
			case TardisDataType_Double: *(double*)             value = (std::numeric_limits<double>::max)();             return true;
			default: break;
			}
			return false;
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