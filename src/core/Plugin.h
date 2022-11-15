#pragma once

#include <string>
#include "CallerContainer.h"
#include "IPlugin.h"

namespace TARDIS::CORE
{
    class Plugin : public IPlugin
    {
    public:
        Plugin(std::string name);

        ~Plugin()
        {
            printf("plugin[%s] is destroyed.\r\n", m_name.c_str());
            delete m_callerContainer;
        };

        template <typename T>
        static T *CreateInstance(const std::string& name) { return new T(name); }

        virtual ICaller* getCaller(const char* fnName) override;

        virtual void parseCallerInfo(ParseCallBack cb) override;

        virtual const char *getName() override;

        void destroy() { delete m_self; }

    protected:
        CallerContainer *m_callerContainer;
        

    private:
        IPlugin *m_self;
        std::string m_name;
    };
}

