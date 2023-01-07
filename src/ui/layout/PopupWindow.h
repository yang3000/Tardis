#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
  class PopupWindow : public AWidget, public WidgetContainer
  {
  protected:
    virtual void drawImpl() override;

  private:
   // std::string 
  };
}