#pragma once

#include "Plugin.h"

class WriteImeiPlugin : public TARDIS::CORE::Plugin<WriteImeiPlugin>
{
public:
	WriteImeiPlugin(std::string name);

	bool Initialize(std::string userData);

	bool WriteImei(std::string imei, int len);

	bool WriteSn(std::string sn);

	~WriteImeiPlugin() {};
};
