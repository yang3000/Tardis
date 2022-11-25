#pragma once
#include <string>
#include <assert.h>
#include <windows.h>

#define DYNLIB_LOAD( a ) LoadLibraryA( (a).c_str() )
#define DYNLIB_GETSYM( a, b ) GetProcAddress( a, (b).c_str() )

#define TARDIS_MODULE_DIR "./bin/"

namespace TARDIS
{
	class DynamicModule
	{
	public:
		DynamicModule(const std::string& name);

		~DynamicModule();

		const std::string& getModuleName() const;

		template <typename Fn, typename... Args>
		inline auto Call(const char* fnName, Args&&... args) -> typename std::result_of<Fn(Args...)>::type
		{
			Fn fn = (Fn)getSymbolAddress(fnName);
			assert(fn);
			return fn(std::forward<Args>(args)...);
		}

	
		void* getSymbolAddress(const std::string& symbol) const;
	private:
		struct Impl;
		Impl* d_pimpl;
	};
}
