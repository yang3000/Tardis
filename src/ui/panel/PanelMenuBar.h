#pragma once

#include "APanel.h"

namespace TARDIS::UI
{
    class PanelMenuBar : public APanel
    {
    protected:
        void drawImpl() override;
    };
}