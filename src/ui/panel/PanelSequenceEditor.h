#pragma once

#include "APanel.h"

class ImVec4;

namespace TARDIS::UI
{
    class PanelSequenceEditor : public APanel
    {
    public:
        PanelSequenceEditor();
        
        static void TestStatusButton(const char *id, const ImVec4 &color, bool running);

    protected:
        void drawImpl() override;
    };
}