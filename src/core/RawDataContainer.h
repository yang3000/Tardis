#pragma once
#include <string.h>

namespace TARDIS::CORE
{
	class RawDataContainer
	{
	public:
		RawDataContainer() :
			d_data(nullptr),
			d_size(0)
		{}

		~RawDataContainer()
		{
			release();
		}

		void setData(unsigned char* data)
		{
			d_data = data;
		}

		void copyData(const char* data, size_t len)
		{
			d_data = new unsigned char[len];
			d_size = len;
			memcpy_s(d_data, len, data, len);
		}

		const unsigned char* getDataPtr()
		{
			return d_data;
		}

		const unsigned char* getDataPtr() const
		{
			return d_data;
		}

		void setSize(size_t size)
		{
			d_size = size;
		}

		size_t getSize() const
		{
			return d_size;
		}

		void release();

	private:
		unsigned char* d_data;
		size_t d_size;
	};
}