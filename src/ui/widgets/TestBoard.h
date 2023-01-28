#pragma once

#include "../AWidget.h"

#include <string>
#include <memory>

namespace TARDIS::CORE
{
    class Engine;
}

namespace TARDIS::UI
{
	class TestBoard : public AWidget
	{
	public:
		TestBoard();

	protected:
		void drawImpl() override;


	protected:
		std::string m_content;

	private:
        std::shared_ptr<CORE::Engine> m_engine;

	};
}
