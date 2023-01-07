#pragma once

#include "../AWidget.h"

namespace TARDIS::UI
{
    class Caller : public AWidget
    {
    public:
        Caller(std::string content) 
            : m_selected(false)
            , m_content(content)
        {}

        void selected(bool selected) { m_selected = selected; }

    protected:
        virtual void drawImpl() override;
    
    private:
        std::string m_content;
        bool        m_selected;
    };
}