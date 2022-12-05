#pragma once

#include <functional>

namespace TARDIS::CORE
{

    using ListenerID = uint64_t;

    template <class... ArgTypes>
    class Event
    {
    public:
        using Callback = std::function<void(ArgTypes...)>;

        ListenerID addListener(Callback p_callback)
        {
            ListenerID listenerID = m_availableListenerID++;
            m_callbacks.emplace(listenerID, p_callback);
            return listenerID;
        }

        bool removeListener(ListenerID p_listenerID)
        {
            return m_callbacks.erase(p_listenerID) != 0;
        }

        void removeAllListeners()
        {
            m_callbacks.clear();
        }

        uint64_t getListenerCount()
        {
            return m_callbacks.size();
        }

        void invoke(ArgTypes... p_args)
        {
            for (auto const &[key, fn] : m_callbacks)
            {
                fn(p_args...);
            }
        }

    private:
        std::unordered_map<ListenerID, Callback> m_callbacks;
        ListenerID m_availableListenerID = 0;
    };
}