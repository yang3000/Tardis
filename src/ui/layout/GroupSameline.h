#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
  class GroupSameline : public AWidget, public WidgetContainer
  {
  protected:
    virtual void drawImpl() override;
  };
}