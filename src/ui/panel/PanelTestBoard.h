#pragma once

#include "APanel.h"

#include <memory>
#include <vector>

namespace TARDIS::UI
{
    class PanelTestBoard : public APanel
    {
    public:
        PanelTestBoard();
        
    protected:
        void drawImpl() override;

    };
}