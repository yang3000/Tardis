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
    char log[128] = {0};
    sprintf_s(log, 128, "test free function,input a number:%d\r\n", a);
    HonorCust4Dongle::m_honorCust4Dongle->log(log);
	return;
}


HonorCust4Dongle* HonorCust4Dongle::m_honorCust4Dongle = nullptr;

void HonorCust4Dongle::log(const char *msg)
{
	m_honorCust4Dongle->m_logger->log(TARDIS::CORE::LogType::Info, msg);
}

HonorCust4Dongle::HonorCust4Dongle(std::string name) : 
    TARDIS::CORE::Plugin<HonorCust4Dongle>(std::move(name)),
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
	// LOG_WARN("initialize obj:{}", "HonorCustomization");
    // m_honor_cust = p_module_cust->Call<ImportModule>("CreateInstance");
	// m_honor_cust->SetupCallback(HonorCust4Dongle::log, true);
	// LOG_INFO("initialize obj:{} success", "HonorCustomization");

    // test member function
	RegisterFunctor("WriteImei", &HonorCust4Dongle::WriteImei, this, 
    {
        {"Imei", "imei..."}, 
		{"Len", "length..."}
    });

    // test ommunication
	RegisterFunctor("TestCommunication", &HonorCust4Dongle::TestCommunication, this, 
    {
        {"PluginId", "id"},
        {"Cmd", "command"}
    });

    // test member function
    RegisterFunctor("Test1", &HonorCust4Dongle::Test1, this, 
    {
        {"Imei", "imei..."}
    });

    // test member function
    RegisterFunctor("Test2", &HonorCust4Dongle::Test2, this, {});

    // test free function
    RegisterFunctor("TestFreeCaller", test, {});
    
    // test lamda expression
    RegisterFunctor("Test", [this](const char* msg) -> bool {
        LOG_INFO("running Lamda Test...");
        LOG_INFO("input param:{}", msg);
        return true;
    }, {{"Imei", "imei..."}});

    // test lamda expression
    RegisterFunctor("TestLamdaCaller", [this](const char* msg) 
    {
        Sleep(1000);
        LOG_INFO("running  test lamda caller...(msg:{})", msg);
    }, 
    {
        {"Str", "str..."}
    });

    // test param long
    RegisterFunctor("TestParam_Long", [this](long num) 
    {
        LOG_INFO("run TestParam_Long, param:{}", num);
    }, 
    {
        {"Number", "is a long number..."}
    });

    // test param unsigned long
    RegisterFunctor("TestParam_UnsignedLong", [this](unsigned long num) 
    {
        LOG_INFO("run TestParam_UnsignedLong, param:{}", num);
    }, 
    {
        {"Number", "is a unsigned long number..."}
    });

    // test param long long
    RegisterFunctor("TestParam_LongLong", [this](long long num) 
    {
        LOG_INFO("run TestParam_LongLong, param:{}", num);
    }, 
    {
        {"Number", "is a long long number..."}
    });

    // test param unsigned long long
    RegisterFunctor("TestParam_UnsignedLongLong", [this](unsigned long long  num) 
    {
        LOG_INFO("run TestParam_UnsignedLongLong, param:{}", num);
    }, 
    {
        {"Number", "is a unsigned long long number..."}
    });

    // test param float
    RegisterFunctor("TestParam_Float", [this](float  num) 
    {
        LOG_INFO("run TestParam_Float, param:{}", num);
    }, 
    {
        {"Number", "is a float number..."}
    });


    // test functional object
    std::function<void(int)> funcCaller = test_free;
    RegisterFunctor("TestFunctionalCaller", funcCaller, {{"Number", "num..."}});

    return true;
}

void HonorCust4Dongle::TestCommunication(uint64_t id, std::string cmd)
{
    LOG_ERROR("communication test, input id:{}", id);
    LOG_ERROR("communication test, input cmd:{}", cmd);
    auto commu = getCommunication(id);
    if (commu)
    {
        commu->sendCommand(cmd.c_str(), cmd.size());
    }
    else
    {
        LOG_ERROR("can not find SerialPortPlugin plugin...");
    }
}

bool HonorCust4Dongle::WriteImei(const char* imei, int len)
{
    LOG_INFO("running Write Imei...");
    LOG_INFO("imei:{}, len:{}", imei, len);
    
    showTestItem("writeImei");
    showTestItem("writeImei", false);
    showTestItem("writeImei", 56, 12, 88);
    showTestItem("writeImei", 56, 66, 88);
    showTestItem("writeImei", 0.69909875, 66, 88);
    showTestItem("writeImei", (unsigned long  long)1234567898745, 66, 88);
    showTestItem("writeImei", 1234567898745, 66, 88);
    showTestItem("writeImei", 222222.22222, 66, 88);
    
    addPoolData("imei", imei);
    addPoolData("imei_len", TARDIS::CORE::ValueHelper<int>::toString(len).c_str());
    //m_honor_cust->WriteImei(imei);
    return true;
}

bool HonorCust4Dongle::Test1(const char *imei)
{
    LOG_INFO("running Test1...->{}", imei);
    return true;
}

bool HonorCust4Dongle::Test2()
{
    LOG_INFO("running Test2...");
    return true;

}

extern "C" TARDIS_EXPORT  TARDIS::CORE::IPlugin* CreatePlugin()
{
	HonorCust4Dongle::m_honorCust4Dongle = HonorCust4Dongle::CreateInstance("HonorCust4Dongle");
    return HonorCust4Dongle::m_honorCust4Dongle;
}