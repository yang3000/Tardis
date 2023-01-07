#include "Separator.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    void Separator::drawImpl()
    {
        ImGui::Separator();
    }
}