#pragma once

#include "Plugin.h"

namespace TARDIS
{
	class DynamicModule;
    class IHonorCustomization;
}

class HonorCust4Dongle : public TARDIS::CORE::Plugin
{
public:
	HonorCust4Dongle(std::string name);
	
	~HonorCust4Dongle();

	virtual bool loadCallers() override;


    bool WriteImei(const char* imei, int len);
    bool WriteImeiEx(const char* imei, size_t len);
    bool WriteImeiEx1(const char* imei, size_t len);
    bool Test1(const char* imei);
    bool Test2();



	static void log(const char *msg);
	static HonorCust4Dongle* m_honorCust4Dongle;
	
private:
	TARDIS::DynamicModule *p_module_cust;
    TARDIS::IHonorCustomization* m_honor_cust;
};