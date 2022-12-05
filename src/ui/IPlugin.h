#pragma once

namespace TARDIS::UI
{
    class IPlugin
    {
    public:
        virtual void execute() = 0;
        
        void *userData = nullptr;
    };
}