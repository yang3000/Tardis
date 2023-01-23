#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
  class GroupSamelineEx : public AWidget, public WidgetContainer
  {
  public:
    GroupSamelineEx(const std::string& label, bool autoColumnWidth = true);

  protected:
    virtual void drawImpl() override;

  private:
    std::string m_label;
    bool        m_autoColumnWidth;
  };
}