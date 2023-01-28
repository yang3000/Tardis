#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include "Base.h"
#include "Event.h"
#include "../communication/Communication.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4996)
#endif

namespace TARDIS
{
	class Communication;
	namespace CORE
	{
		class IPlugin;
	}
}


namespace TARDIS::CORE
{
	template<typename T>
	class ValueHelper;

	template<typename T>
	class ValueHelper<const T>
	{
	public:
		typedef typename ValueHelper<T>::return_type return_type;
		typedef typename ValueHelper<T>::safe_method_return_type safe_method_return_type;
		typedef typename ValueHelper<T>::pass_type pass_type;
		typedef typename ValueHelper<T>::string_return_type string_return_type;

		static const TardisDataType Type = ValueHelper<T>::Type;


		static inline const std::string& getDataTypeName()
		{
			return ValueHelper<T>::getDataTypeName();
		}

		static inline return_type from(const std::string& str)
		{
			return ValueHelper<T>::from(str);
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return ValueHelper<T>::from(memory);
		}

		static inline std::string toString(pass_type val)
		{
			return ValueHelper<T>::toString(val);
		}
	};

	template<typename T>
	class ValueHelper<const T&>
	{
	public:
		typedef typename ValueHelper<T>::return_type return_type;
		typedef typename ValueHelper<T>::safe_method_return_type safe_method_return_type;
		typedef typename ValueHelper<T>::pass_type pass_type;
		typedef typename ValueHelper<T>::string_return_type string_return_type;

		static const TardisDataType Type = ValueHelper<T>::Type;

		static inline const std::string& getDataTypeName()
		{
			return ValueHelper<T>::getDataTypeName();
		}

		static inline return_type from(const std::string& str)
		{
			return ValueHelper<T>::from(str);
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return ValueHelper<T>::from(memory);
		}

		static inline std::string toString(pass_type val)
		{
			return ValueHelper<T>::toString(val);
		}
	};

	template<typename T>
	class ValueHelper<const T*>
	{
	public:
		typedef typename ValueHelper<T*>::return_type return_type;
		typedef typename ValueHelper<T*>::safe_method_return_type safe_method_return_type;
		typedef typename ValueHelper<T*>::pass_type pass_type;
		typedef typename ValueHelper<T*>::string_return_type string_return_type;

		static const TardisDataType Type = ValueHelper<T*>::Type;


		static inline const std::string& getDataTypeName()
		{
			return ValueHelper<T*>::getDataTypeName();
		}

		static inline return_type from(const std::string& str)
		{
			return ValueHelper<T*>::from(str);
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return ValueHelper<T*>::from(memory);
		}

		static inline std::string toString(pass_type val)
		{
			return ValueHelper<T*>::toString(val);
		}
	};

	template<>
	class ValueHelper<IPlugin*>
	{
	public:
		typedef IPlugin* return_type;
		typedef IPlugin* safe_method_return_type;
		typedef const IPlugin* pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_S8;

		static const std::string& getDataTypeName()
		{
			static const std::string type("plugin");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			return nullptr;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return const_cast<IPlugin*>(reinterpret_cast<const IPlugin*>(memory.buf));
		}

		static std::string toString(pass_type val) {return "";};
	};
	
	template<>
	class ValueHelper<Communication*>
	{
	public:
		typedef Communication* return_type;
		typedef Communication* safe_method_return_type;
		typedef const Communication* pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_Communication;

		static const std::string& getDataTypeName()
		{
			static const std::string type("communication");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			return nullptr;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return const_cast<Communication*>(reinterpret_cast<const Communication*>(memory.buf));
		}

		static std::string toString(pass_type val) {return "";};
	};

	template<>
	class ValueHelper<char*>
	{
	public:
		typedef const char* return_type;
		typedef std::string safe_method_return_type;
		typedef const std::string& pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_String;

		static const std::string& getDataTypeName()
		{
			static std::string type("string");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			return str.c_str();
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return reinterpret_cast<return_type>(memory.buf);
		}

		static inline string_return_type toString(pass_type val)
		{
			return val;
		}
	};

	template<>
	class ValueHelper<std::string>
	{
	public:
		typedef std::string return_type;
		typedef return_type safe_method_return_type;
		typedef const std::string& pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_String;

		static const std::string& getDataTypeName()
		{
			static std::string type("string");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			return str;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return reinterpret_cast<return_type>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			return val;
		}
	};

	template<>
	class ValueHelper<float>
	{
	public:
		typedef float return_type;
		typedef return_type safe_method_return_type;
		typedef const float pass_type;
		typedef std::string string_return_type;
		
		static const TardisDataType Type = TardisDataType_Float;

		static const std::string& getDataTypeName()
		{
			static std::string type("float");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			float val = 0;
			sscanf(str.c_str(), "%f", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%.3f", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<double>
	{
	public:
		typedef double return_type;
		typedef return_type safe_method_return_type;
		typedef const double pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_Double;

		static const std::string& getDataTypeName()
		{
			static std::string type("double");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			double val = 0;
			sscanf(str.c_str(), " %lf", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%.5f", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<char>
	{
	public:
		typedef char return_type;
		typedef return_type safe_method_return_type;
		typedef const char pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_S8;

		static const std::string& getDataTypeName()
		{
			static std::string type("char");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			uint32_t val = 0;
			sscanf(str.c_str(), "%d", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%d", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<unsigned char>
	{
	public:
		typedef unsigned char return_type;
		typedef return_type safe_method_return_type;
		typedef const unsigned char pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_U8;

		static const std::string& getDataTypeName()
		{
			static std::string type("uchar");
			return type;
		}

		static return_type from(const std::string& str)
		{
			uint32_t val = 0;
			sscanf(str.c_str(), "%u", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			///return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%u", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<int>
	{
	public:
		typedef int return_type;
		typedef return_type safe_method_return_type;
		typedef const int pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_S32;

		static const std::string& getDataTypeName()
		{
			static std::string type("int");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			int val = 0;
			sscanf(str.c_str(), "%d", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
			//return *reinterpret_cast<pass_type*>(memory.buf);
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%d", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<unsigned int>
	{
	public:
		typedef unsigned int return_type;
		typedef return_type safe_method_return_type;
		typedef const unsigned int pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_U32;

		static const std::string& getDataTypeName()
		{
			static std::string type("uint");
			return type;
		}

		static return_type from(const std::string& str)
		{
			unsigned int val = 0;
			sscanf(str.c_str(), "%u", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%u", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<long>
	{
	public:
		typedef long return_type;
		typedef return_type safe_method_return_type;
		typedef const long pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_S64;

		static const std::string& getDataTypeName()
		{
			static std::string type("long");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			uint64_t val = 0;
			sscanf(str.c_str(), "%I64d", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%I64d", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<unsigned long>
	{
	public:
		typedef unsigned long return_type;
		typedef return_type safe_method_return_type;
		typedef const unsigned long pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_U64;

		static const std::string& getDataTypeName()
		{
			static std::string type("ulong");
			return type;
		}

		static return_type from(const std::string& str)
		{
			uint64_t val = 0;
			sscanf(str.c_str(), "%I64u", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%I64u", val);

			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<long long>
	{
	public:
		typedef long long return_type;
		typedef return_type safe_method_return_type;
		typedef const long long pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_S64;

		static const std::string& getDataTypeName()
		{
			static std::string type("llong");
			return type;
		}

		static inline return_type from(const std::string& str)
		{
			uint64_t val = 0;
			sscanf(str.c_str(), "%I64d", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%I64d", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<unsigned long long>
	{
	public:
		typedef unsigned long long return_type;
		typedef return_type safe_method_return_type;
		typedef const unsigned long long pass_type;
		typedef std::string string_return_type;

		static const TardisDataType Type = TardisDataType_U64;

		static const std::string& getDataTypeName()
		{
			static std::string type("ullong");
			return type;
		}

		static return_type from(const std::string& str)
		{
			uint64_t val = 0;
			sscanf(str.c_str(), "%I64u", &val);
			return val;
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%I64u", val);
			return std::string(buff);
		}
	};

	template<>
	class ValueHelper<bool>
	{
	public:
		typedef bool return_type;
		typedef return_type safe_method_return_type;
		typedef const bool pass_type;
		typedef const std::string string_return_type;

		static const TardisDataType Type = TardisDataType_Bool;

		static const std::string& getDataTypeName()
		{
			static std::string type("bool");
			return type;
		}

		static return_type from(const std::string& str)
		{
			return str == "True";
		}

		static inline return_type from(MemoryBuffer memory)
		{
			//return *reinterpret_cast<pass_type*>(memory.buf);
			return from(std::string(static_cast<const char*>(memory.buf), memory.len));
		}

		static string_return_type toString(pass_type val)
		{
			return val ? "True" : "False";
		}
	};
}

//#include "ValueHelper.inl"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif