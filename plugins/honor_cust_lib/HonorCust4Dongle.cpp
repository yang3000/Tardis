#include <stdio.h> 
#include "Base.h"
#include "HonorCust4Dongle.h"
#include "DynamicModule.h"
#include "IHonorCustomizationForDongle.h"

typedef TARDIS::IHonorCustomization* (*ImportModule)();

bool test()
{
	printf("test");
	return true;
}


HonorCust4Dongle* HonorCust4Dongle::m_honorCust4Dongle = nullptr;

void HonorCust4Dongle::log(const char *msg)
{
	m_honorCust4Dongle->m_logger->log(TARDIS::CORE::LogType::Trace, msg);
}

HonorCust4Dongle::HonorCust4Dongle(std::string name) : TARDIS::CORE::Plugin(std::move(name))
{};

HonorCust4Dongle::~HonorCust4Dongle()
{
	if (p_module_cust)
	{
		delete p_module_cust;
	}
	p_module_cust = nullptr;
};

bool HonorCust4Dongle::initialize()
{
	LOG_INFO("load file:{}", "HonorCustomization.dll");
	// p_module_cust = new TARDIS::DynamicModule("HonorCustomization.dll");
	// LOG_INFO("load file:{} success", "HonorCustomization.dll");

    // addPoolData("foo", "bar");

	// LOG_WARN("initialize obj:{}", "HonorCustomization");
    // m_honor_cust = p_module_cust->Call<ImportModule>("CreateInstance");
	// m_honor_cust->SetupCallback(HonorCust4Dongle::log, true);
	// LOG_INFO("initialize obj:{} success", "HonorCustomization");

	// m_callerContainer->registerFunctor("EnumDonglePorts", &TARDIS::IHonorCustomization::EnumDonglePorts, m_honor_cust, {});

	// // registerFunctor("EnumDonglePorts",
	// // 				{},
	// // 				&TARDIS::IHonorCustomization::EnumDonglePorts,
	// // 				m_honor_cust);

	// registerFunctor("InitializeConnection",
	// 				{
	// 					{"Mac", "Mac address"}, 
	// 					{"Index", "slot"}
	// 				},
	// 				&TARDIS::IHonorCustomization::InitializeConnection,
	// 				m_honor_cust);

	// registerFunctor("TestFreeFn", {}, test);

	m_callerContainer->registerFunctor("WriteImei", &HonorCust4Dongle::WriteImei, this, {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

    m_callerContainer->registerFunctor("WriteImeiEx", &HonorCust4Dongle::WriteImeiEx, this, {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

        m_callerContainer->registerFunctor("WriteImeiEx1", &HonorCust4Dongle::WriteImeiEx1, this, {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

    m_callerContainer->registerFunctor("Test1", &HonorCust4Dongle::Test1, this, {{"Imei", "imei..."}});

    m_callerContainer->registerFunctor("Test2", &HonorCust4Dongle::Test2, this, {});

    return true;
}

bool HonorCust4Dongle::WriteImei(const char* imei, int len)
{
    printf("running Write Imei...\r\n");
    printf("imei:%s, len:%d\r\n", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}

bool HonorCust4Dongle::WriteImeiEx(const char* imei, size_t len)
{
    printf("running Write Imei ex...\r\n");
    printf("imei:%s, len:%d\r\n", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}


bool HonorCust4Dongle::WriteImeiEx1(const char* imei, size_t len)
{
    printf("running Write Imei ex1...\r\n");
    printf("imei:%s, len:%d\r\n", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}

bool HonorCust4Dongle::Test1(const char *imei)
{
    printf("running Test1...\r\n");
    return true;

}
bool HonorCust4Dongle::Test2()
{
    printf("running Test2...\r\n");
    return true;

}

extern "C" TARDIS_EXPORT  TARDIS::CORE::IPlugin* CreatePlugin()
{
	HonorCust4Dongle::m_honorCust4Dongle = TARDIS::CORE::Plugin::CreateInstance<HonorCust4Dongle>("HonorCust4Dongle");
    return HonorCust4Dongle::m_honorCust4Dongle;
}