#include <stdlib.h>
#include "DynamicModule.h"
#include <direct.h>

namespace TARDIS
{
	static std::string getFailureString()
	{
		std::string retMsg;
		LPVOID msgBuffer;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			GetLastError(),
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			reinterpret_cast<LPTSTR>(&msgBuffer),
			0,
			0))
		{
			retMsg = reinterpret_cast<LPTSTR>(msgBuffer);
			LocalFree(msgBuffer);
		}
		else
		{
			retMsg = "Unknown Error";
		}
		return retMsg;
	}

	static HMODULE DynLibLoad(const std::string& name)
	{
		HMODULE handle = 0;
		if (!handle)
			handle = DYNLIB_LOAD(name);
		auto err = GetLastError();
#if defined(TARDIS_MODULE_DIR)
		if (!handle)
			handle = DYNLIB_LOAD(TARDIS_MODULE_DIR + name);
#endif
		return handle;
	}

	struct DynamicModule::Impl
	{
		Impl(const std::string& name) :
			d_moduleName(name),
			d_handle(nullptr)
		{}

		~Impl()
		{
			FreeLibrary(d_handle);
		}

		std::string d_moduleName;
		HMODULE d_handle;
	};

	DynamicModule::DynamicModule(const std::string& name) :
		d_pimpl(new Impl(name))
	{
		char* path = _getcwd(NULL, 0);
		assert(!name.empty());
		d_pimpl->d_handle = DynLibLoad(d_pimpl->d_moduleName);
		assert(d_pimpl->d_handle);
	}

	DynamicModule::~DynamicModule()
	{
		delete d_pimpl;
	}

	const std::string& DynamicModule::getModuleName() const
	{
		return d_pimpl->d_moduleName;
	}

	void* DynamicModule::getSymbolAddress(const std::string& symbol) const
	{
		return (void*)DYNLIB_GETSYM(d_pimpl->d_handle, symbol);
	}
}
