#include "RawDataContainer.h"

namespace TARDIS::CORE
{
	void RawDataContainer::release()
	{
		if (d_data)
		{
			delete[] d_data;
			d_data = nullptr;
			d_size = 0;
		}
	}

}