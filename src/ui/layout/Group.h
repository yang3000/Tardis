#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
  class Group : public AWidget, public WidgetContainer
  {
  protected:
    virtual void drawImpl() override;
  };
}