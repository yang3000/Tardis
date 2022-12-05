#include "Plugin.h"
#include "CallerContainer.h"

namespace TARDIS::CORE
{
    Plugin::Plugin(std::string name) :
        m_name(std::move(name)),
        m_self(this),
        m_callerContainer(new CallerContainer()),
        m_pFn(nullptr)

    {};

    void Plugin::parseCallerInfo(ParseCallBack cb)
    {
        for( auto it : m_callerContainer->m_slots)
        {   
            auto callerParams = it.second->params;

            Param* param = new Param[callerParams.size()];

            for(int i = 0; i < callerParams.size(); ++i)
            {
                param[i].name = {callerParams[i].m_name.c_str(), (unsigned)callerParams[i].m_name.size()};
                param[i].type = {callerParams[i].m_type.c_str(), (unsigned)callerParams[i].m_type.size()};
                param[i].abbr = {callerParams[i].m_abbr.c_str(), (unsigned)callerParams[i].m_abbr.size()};
                param[i].desc = {callerParams[i].m_desc.c_str(), (unsigned)callerParams[i].m_desc.size()};
            }

            cb(it.second->name.c_str(), param, callerParams.size());

            delete[] param;
        }
    }

}