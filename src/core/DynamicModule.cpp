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

    static HMODULE DynLibLoad(const std::string &name)
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
        Impl(const std::string &path)
            : m_modulePath(path)
            , m_handle(nullptr)
        { }

        ~Impl()
        {
            FreeLibrary(m_handle);
        }

        std::string m_modulePath;
        HMODULE     m_handle;
    };

    DynamicModule::DynamicModule(const std::string &path) : m_pimpl(new Impl(path))
    {
        //char *path = _getcwd(NULL, 0);
        assert(!path.empty());
        m_pimpl->m_handle = DynLibLoad(m_pimpl->m_modulePath);
        assert(m_pimpl->m_handle);
    }

    DynamicModule::~DynamicModule()
    {
        delete m_pimpl;
    }

    const std::string &DynamicModule::getModulePath() const
    {
        return m_pimpl->m_modulePath;
    }

    void *DynamicModule::getSymbolAddress(const std::string &symbol) const
    {
        return (void *)DYNLIB_GETSYM(m_pimpl->m_handle, symbol);
    }
}
