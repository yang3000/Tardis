#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
    class GroupTable : public AWidget, public WidgetContainer
    {
    public:
        GroupTable(unsigned int columns = 1);

    protected:
        virtual void drawImpl() override;

    private:
        unsigned int m_columns;
    };
}