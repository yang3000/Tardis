#pragma once

namespace TARDIS::UI
{
	class IDrawable
	{
	public:
		virtual void draw() = 0;

	protected:
		virtual ~IDrawable() {};
	};
}