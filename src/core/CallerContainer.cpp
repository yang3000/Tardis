#include "CallerContainer.h"

namespace TARDIS::CORE
{
    void CallerContainer::addFunctor(const std::string& callerName, CallerInfo* callerInfo)
    {
        printf("add functor[%s] to container.\r\n", callerName.c_str());
		m_slots.emplace(callerName, callerInfo);
    }

    CallerContainer::~CallerContainer()
    {
        while (!m_slots.empty())
		{
			auto it = m_slots.begin();
			delete it->second;
			m_slots.erase(it);
		}
    }

    CallerInfo* CallerContainer::get(const std::string& name)
    {
        return m_slots.find(name)->second;
    }
}