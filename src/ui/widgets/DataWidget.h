#pragma once

#include <string>

#include "../AWidget.h"
#include "../DataDispatcher.h"

namespace TARDIS::UI
{
    template <typename T>
    class DataWidget : public AWidget
    {
    public:
        DataWidget(T &p_dataHolder) : m_data(p_dataHolder){};

        void draw()
        {
            if (enabled)
            {
                TRY_GATHER(T, m_data);
                AWidget::draw();
                TRY_PROVIDE(T, m_data);
            }
        }

        void notifyChange()
        {
            TRY_NOTIFY_CHANGE(T);
        }

    private:
        T &m_data;
    };
}
