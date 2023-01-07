#pragma once

#include "Plugin.h"
#include "Communication.h"

namespace TARDIS
{
	class DynamicModule;
	class Communication;
    class IHonorCustomization;
}

class HonorCust4Dongle : public TARDIS::CORE::Plugin<HonorCust4Dongle>
{
public:
	HonorCust4Dongle(std::string name);
	
	~HonorCust4Dongle();

	virtual bool loadCallers() override;

    bool WriteImei(const char* imei, int len);

    void TestCommunication(uint64_t id, std::string cmd);

    void TestCommunicationEx(TARDIS::Communication* commu, std::string cmd);


    bool Test1(const char* imei);
    bool Test2();

	static void log(const char *msg);
	static HonorCust4Dongle* m_honorCust4Dongle;
	
private:
	TARDIS::DynamicModule *p_module_cust;
    TARDIS::IHonorCustomization* m_honor_cust;
};
