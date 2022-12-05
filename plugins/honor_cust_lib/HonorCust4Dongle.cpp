#include <stdio.h> 
#include "Base.h"
#include "HonorCust4Dongle.h"
#include "DynamicModule.h"
#include "IHonorCustomizationForDongle.h"
#include "Helper.h"

typedef TARDIS::IHonorCustomization* (*ImportModule)();

void test()
{
    HonorCust4Dongle::m_honorCust4Dongle->log("test");
	return;
}

void test_free(int a)
{
    HonorCust4Dongle::m_honorCust4Dongle->log("test free->");
	return;
}


HonorCust4Dongle* HonorCust4Dongle::m_honorCust4Dongle = nullptr;

void HonorCust4Dongle::log(const char *msg)
{
	m_honorCust4Dongle->m_logger->log(TARDIS::CORE::LogType::Info, msg);
}

HonorCust4Dongle::HonorCust4Dongle(std::string name) : 
    TARDIS::CORE::Plugin(std::move(name)),
    p_module_cust(nullptr),
    m_honor_cust(nullptr)
{};

HonorCust4Dongle::~HonorCust4Dongle()
{
	if (p_module_cust)
	{
		delete p_module_cust;
	}
	p_module_cust = nullptr;
};

bool HonorCust4Dongle::loadCallers()
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

	RegisterFunctor("WriteImei", &HonorCust4Dongle::WriteImei, this, 
    {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

    RegisterFunctor("WriteImeiEx", &HonorCust4Dongle::WriteImeiEx, this, 
    {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

    RegisterFunctor("WriteImeiEx1", &HonorCust4Dongle::WriteImeiEx1, this, 
    {
                    {"Imei", "imei..."}, 
					{"Len", "length..."}
    });

    RegisterFunctor("Test1", &HonorCust4Dongle::Test1, this, {{"Imei", "imei..."}});

    RegisterFunctor("Test2", &HonorCust4Dongle::Test2, this, {});

    RegisterFunctor("TestFreeCaller", test, {});
    
    RegisterFunctor("Test", [this](const char* msg) -> bool {
        LOG_INFO("running Lamda Test...");
        return true;
    }, {{"Imei", "imei..."}});

    RegisterFunctor("TestLamdaCaller", [this](const char* msg) {
        Sleep(1000);
        LOG_INFO("running  test lamda caller...(msg:{})", msg);
    }, {{"Str", "str..."}});

    std::function<void(int)> funcCaller = test_free;
    RegisterFunctor("TestFunctionalCaller", funcCaller, {{"Number", "num..."}});

    return true;
}

bool HonorCust4Dongle::WriteImei(const char* imei, int len)
{
    auto commu = getCommunication("SerialPortPlugin");
    if (commu)
    {
        commu->sendCommand("AT^WriteImei=43534", len);
    }
    else
    {
        LOG_ERROR("can not find SerialPortPlugin plugin...");

    }

    LOG_INFO("running Write Imei...");
    LOG_INFO("imei:{}, len:{}", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}

bool HonorCust4Dongle::WriteImeiEx(const char* imei, size_t len)
{
    LOG_INFO("running Write Imei Ex...");
    LOG_INFO("imei:{}, len:{}", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}


bool HonorCust4Dongle::WriteImeiEx1(const char* imei, size_t len)
{
    LOG_INFO("running Write Imei Ex1...");
    LOG_INFO("imei:{}, len:{}", imei, len);
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}

bool HonorCust4Dongle::Test1(const char *imei)
{
    LOG_INFO("running Test1...");
    return true;
}
bool HonorCust4Dongle::Test2()
{
    LOG_INFO("running Test2...");
    return true;

}

extern "C" TARDIS_EXPORT  TARDIS::CORE::IPlugin* CreatePlugin()
{
	HonorCust4Dongle::m_honorCust4Dongle = TARDIS::CORE::Plugin::CreateInstance<HonorCust4Dongle>("HonorCust4Dongle");
    return HonorCust4Dongle::m_honorCust4Dongle;
}