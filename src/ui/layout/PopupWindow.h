#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
    class PopupWindow : public AWidget, public WidgetContainer
    {
    public:
        PopupWindow(const std::string &popupId);
        
    protected:
        virtual void drawImpl() override;

    private:
        std::string m_popupId;
    };
}