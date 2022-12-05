#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include "Base.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4996)
#endif

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

		static inline return_type fromString(const std::string& str)
		{
			return ValueHelper<T>::fromString(str);
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

		static inline return_type fromString(const std::string& str)
		{
			return ValueHelper<T>::fromString(str);
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

		static inline return_type fromString(const std::string& str)
		{
			return ValueHelper<T*>::fromString(str);
		}

		static inline std::string toString(pass_type val)
		{
			return ValueHelper<T*>::toString(val);
		}
	};

	class IPlugin;
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

		static return_type fromString(const std::string& str);
		static std::string toString(pass_type val);
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

		static inline return_type fromString(const std::string& str)
		{
			return str.c_str();
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

		static inline return_type fromString(const std::string& str)
		{
			return str.c_str();
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

		static inline return_type fromString(const std::string& str)
		{
			float val = 0;
			sscanf(str.c_str(), "%g", &val);
			return val;
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%g", val);
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

		static inline return_type fromString(const std::string& str)
		{
			double val = 0;
			sscanf(str.c_str(), " %lg", &val);
			return val;
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%g", val);
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

		static inline return_type fromString(const std::string& str)
		{
			char val = 0;
			sscanf(str.c_str(), "%d", &val);
			return val;
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

		static return_type fromString(const std::string& str)
		{
			unsigned char val = 0;
			sscanf(str.c_str(), "%u", &val);
			return val;
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

		static inline return_type fromString(const std::string& str)
		{
			int val = 0;
			sscanf(str.c_str(), " %d", &val);
			return val;
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

		static return_type fromString(const std::string& str)
		{
			unsigned int val = 0;
			sscanf(str.c_str(), "%u", &val);
			return val;
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

		static inline return_type fromString(const std::string& str)
		{
			long val = 0;
			sscanf(str.c_str(), "%l", &val);
			return val;
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%l", val);
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

		static return_type fromString(const std::string& str)
		{
			unsigned long val = 0;
			sscanf(str.c_str(), "%lu", &val);
			return val;
		}

		static string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%lu", val);

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

		static inline return_type fromString(const std::string& str)
		{
			long long val = 0;
			sscanf(str.c_str(), "%I64", &val);
			return val;
		}

		static inline string_return_type toString(pass_type val)
		{
			char buff[64];
			snprintf(buff, sizeof(buff), "%I64", val);
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

		static return_type fromString(const std::string& str)
		{
			unsigned long long val = 0;
			sscanf(str.c_str(), "%I64u", &val);
			return val;
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

		static return_type fromString(const std::string& str)
		{
			return (str == True || str == "True");
		}

		static string_return_type toString(pass_type val)
		{
			return val ? True : False;
		}

		static const std::string True;
		static const std::string False;
	};
}
#if defined(_MSC_VER)
#pragma warning(pop)
#endif