#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
  class GroupChild : public AWidget, public WidgetContainer
  {
  public:
    GroupChild(float padding_h = 0.0f, float padding_v = 0.0f);

  protected:
    virtual void drawImpl() override;

  
  private:
    float m_padding_h  = 0.0f;
    float m_padding_v = 0.0f;
  };
}