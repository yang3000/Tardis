#pragma once

#include <string>

#include "../AWidget.h"

namespace TARDIS::UI
{
    class HelperMarker : public AWidget
    {
    public:
        HelperMarker(std::string marker, bool isSameline = false);

        void drawImpl() override;

    private:
        std::string m_marker;
        bool        m_sameline;
    };
}
