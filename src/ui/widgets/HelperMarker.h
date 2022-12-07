#pragma once

#include <string>

#include "../AWidget.h"

namespace TARDIS::UI
{
    class HelperMarker : public AWidget
    {
    public:
        HelperMarker(std::string marker);

        void drawImpl() override;

    private:
        std::string m_marker;
    };
}
