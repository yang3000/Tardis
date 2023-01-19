#pragma once

#include "APanel.h"

namespace TARDIS::UI
{
    class MainMenuBar : public APanel
    {
    protected:
        void drawImpl() override;
    };
}