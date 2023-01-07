#include "SpdLog.h"
#include "stdio.h"
#include "ICaller.h"
#include "IPlugin.h"
#include "DynamicModule.h"
#include "JsonHandler.h"
#include "RapidJsonParser.h"
#include "Communication.h"
#include "PluginManager.h"

#include "Engine.h"
#include "ValueHelper.h"


using namespace TARDIS::CORE;
typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

void testValueHelper()
{
    // from std::string
    TDS_LOG_INFO("char* : \"tardis\"->{}",            TARDIS::CORE::ValueHelper<char*>::from("tardis"));
    TDS_LOG_INFO("string: \"tardis\"->{}",            TARDIS::CORE::ValueHelper<std::string>::from("tardis"));
    TDS_LOG_INFO("float : \"3.1415926\"->{}",         TARDIS::CORE::ValueHelper<float>::from("3.1415921"));
    TDS_LOG_INFO("float : \"0.31415926\"->{}",        TARDIS::CORE::ValueHelper<float>::from("0.31415926"));
    TDS_LOG_INFO("double: \"3.1415926535758\"->{}",   TARDIS::CORE::ValueHelper<double>::from("3.1415926535758"));
    TDS_LOG_INFO("double: \"314159265.35758\"->{}",   TARDIS::CORE::ValueHelper<double>::from("314159265.35758"));
    TDS_LOG_INFO("char  : \"12\" ->{:b}",             TARDIS::CORE::ValueHelper<char>::from("12") == 12);
    TDS_LOG_INFO("char  : \"127\"->{:b}",             TARDIS::CORE::ValueHelper<char>::from("127") == 127);
    TDS_LOG_INFO("char  : \"128\"->{:b}",             TARDIS::CORE::ValueHelper<char>::from("128") == -128);
    TDS_LOG_INFO("unsigned char:   \"255\"->{}",      TARDIS::CORE::ValueHelper<unsigned char>::from("255"));
    TDS_LOG_INFO("unsigned char:   \"256\"->{}",      TARDIS::CORE::ValueHelper<unsigned char>::from("256"));

    TDS_LOG_INFO("int:   \"2147483647\"->{}",         TARDIS::CORE::ValueHelper<int>::from("2147483647"));
    TDS_LOG_INFO("int:   \"111\"->{}",                TARDIS::CORE::ValueHelper<int>::from("111"));
    TDS_LOG_INFO("int:   \"-2147483648\"->{}",        TARDIS::CORE::ValueHelper<int>::from("-2147483648"));

    TDS_LOG_INFO("uint:   \"4294967295\"->{}",        TARDIS::CORE::ValueHelper<unsigned int>::from("4294967295"));
    TDS_LOG_INFO("uint:   \"4294967296\"->{}",        TARDIS::CORE::ValueHelper<unsigned int>::from("4294967296"));
    TDS_LOG_INFO("uint:   \"4294967297\"->{}",        TARDIS::CORE::ValueHelper<unsigned int>::from("4294967297"));

    TDS_LOG_INFO("long:   \"2147483647\"->{}",        TARDIS::CORE::ValueHelper<long>::from("2147483647"));
    TDS_LOG_INFO("long:   \"-2147483648\"->{}",       TARDIS::CORE::ValueHelper<long>::from("-2147483648"));
    TDS_LOG_INFO("ulong:   \"1234567890221\"->{}",    TARDIS::CORE::ValueHelper<unsigned long>::from("1234567890221"));
    
    TDS_LOG_INFO("llong:   \"9223372036854774807\"->{}",  TARDIS::CORE::ValueHelper<long long>::from("9223372036854774807"));
    TDS_LOG_INFO("llong:   \"-9223372036854774808\"->{}", TARDIS::CORE::ValueHelper<long long>::from("-9223372036854774808"));
    TDS_LOG_INFO("ullong:   \"1234567890221\"->{}",   TARDIS::CORE::ValueHelper<unsigned long long>::from("1234567890221"));
    TDS_LOG_INFO("bool:   \"True\"->{:d}",            TARDIS::CORE::ValueHelper<bool>::from("True"));
    TDS_LOG_INFO("bool:   \"False\"->{:d}",           TARDIS::CORE::ValueHelper<bool>::from("False"));
}

int main()
{

    SpdLog::DefaultLogger();

    testValueHelper();

    PluginManager::LoadPlugin("honor_cust_lib",  "honor_cust_lib.dll",  123456789);
    PluginManager::LoadPlugin("serial_port_lib", "serial_port_lib.dll", 12);

    // MemoryBuffer buffer;
    // std::string test("test str...");
    // buffer.buf = test.c_str();
    // buffer.len = sizeof("test str...");
    // auto aa = TARDIS::CORE::ValueHelper<char*>::fromMemory(buffer);

    // float _float = 3.1415926;
    // MemoryBuffer mem_float;
    // mem_float.buf = &_float;
    // mem_float.len = sizeof(float);

    // auto o_float = TARDIS::CORE::ValueHelper<float>::fromMemory(mem_float);

    // auto _plugin = PluginManager::CreatePlugin(1);


    // MemoryBuffer mem_plugin;
    // mem_plugin.buf = _plugin;
    // mem_plugin.len = sizeof(_plugin);
    // auto o_plugin = TARDIS::CORE::ValueHelper<IPlugin*>::fromMemory(mem_plugin);

    auto engine1 = std::make_shared<Engine>("testEngine_1");
    auto engine2 = std::make_shared<Engine>("testEngine_2");

    auto log1 = new SpdLog(engine1->getEngineId(), "thread1.log");
    auto log2 = new SpdLog(engine2->getEngineId(), "thread2.log");
    log1->log(LogType::Info, "testEngine_1 task");
    log2->log(LogType::Info, "testEngine_2 task");

    std::shared_ptr<RapidJsonParser> jsonParser = std::make_shared<RapidJsonParser>();
    jsonParser->parseJsonFile("sequence.json");
    TDS_LOG_INFO(jsonParser->get("version"));

    Engine::OnDeserialize(jsonParser);

    auto pCallback1 = std::make_shared<CallBackImpl>(engine1);
    auto pCallback2 = std::make_shared<CallBackImpl>(engine2);

    //engine1->addPlugin(123456789);
    //engine2->addPlugin(123456789);

    //TARDIS::DynamicModule* p_dyModule = new TARDIS::DynamicModule("honor_cust_lib.dll");
    auto pPlugin1 = engine1->addPlugin(123456789);// PluginManager::CreatePlugin(123456789);
    //auto pPlugin1 = p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin1->setLogger(log1);
    pPlugin1->loadCallers();
    pPlugin1->setCallback(pCallback1.get());

    auto pPlugin_serial_port = engine1->addPlugin(12);
    pPlugin_serial_port->setLogger(log1);
    pPlugin_serial_port->loadCallers();
    pPlugin_serial_port->setCallback(pCallback1.get());


    auto pPlugin2 = engine2->addPlugin(123456789);// PluginManager::CreatePlugin(123456789);//pPlugin1->clone(); //p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin2->setLogger(log2);
    pPlugin2->loadCallers();
    pPlugin2->setCallback(pCallback2.get());

    auto pPlugin_serial_port_2 = engine2->addPlugin(12);
    pPlugin_serial_port_2->setLogger(log2);
    pPlugin_serial_port_2->loadCallers();
    pPlugin_serial_port_2->setCallback(pCallback2.get());
    // pPlugin1->parseCallerInfo([](const char *name, Param *params, unsigned count)
    // { 
    //     TDS_LOG_INFO("Method:{}", name);
    //     for (int i = 0; i < count; ++i)
    //     {
    //         TDS_LOG_INFO("Param{}:{}[{}]:{}", i, params[i].name.buf, params[i].type.buf, params[i].desc.buf);
    //     }
    //     TDS_LOG_INFO("--------------------------------");
    // });
    // TDS_LOG_INFO("Call WriteImeiEx directly...");
    // Str param[2];
    // param[0].buf = "111111123456";
    // param[0].len = strlen(param[0].buf);
    // param[1].buf = "021";
    // param[1].len = strlen(param[1].buf);
    // auto fn11 = pPlugin->getCaller("WriteImei");
    // auto fnEx = pPlugin->getCaller("WriteImeiEx");
    // //auto fn11 = pPlugin->getCaller("WriteImei");
    // (*fnEx)(param);
    // TDS_LOG_INFO("--------------------------------");
    //===================================================
    // TARDIS::DynamicModule* p_SerialPortDyModule = new TARDIS::DynamicModule("serial_port_lib.dll");
    // auto pSerialPortPlugin = p_SerialPortDyModule->Call<CreatePlugin>("CreatePlugin");
    // pSerialPortPlugin->setLogger(log);
    // pSerialPortPlugin->loadCallers();
    // pSerialPortPlugin->setCallback(pCallback.get());
    // pSerialPortPlugin->parseCallerInfo([](const char *name, Param *params, unsigned count)
    // { 
    //     TDS_LOG_INFO("Method:{}", name);
    //     for (UInt i = 0; i < count; ++i)
    //     {
    //         TDS_LOG_INFO("Param{}:{}[{}]:{}", i, params[i].name.buf, params[i].type.buf, params[i].desc.buf);
    //     }
    //     TDS_LOG_INFO("--------------------------------");
    // });
    // TARDIS::Communication *pCommunication = dynamic_cast<TARDIS::Communication *>(pSerialPortPlugin);
    // if (pCommunication)
    // {
    //     pCommunication->sendCommand("4353445", 7);
    // }
    //===================================================


    //engine1.addPlugin("SerialPortPlugin", pSerialPortPlugin);

    TDS_LOG_INFO("Run Task1...");
    engine1->runTask();
    TDS_LOG_INFO("--------------------------------");
    TDS_LOG_INFO("Run Task2...");
    engine2->runTask();
    TDS_LOG_INFO("--------------------------------");


    while(engine1->isRunning())
    {
        TDS_LOG_INFO("engine1 is running, waitting...");
        Sleep(100);
    }

    while(engine2->isRunning())
    {
        TDS_LOG_INFO("engine2 is running, waitting...");
        Sleep(100);
    }

    TDS_LOG_INFO("--------------------------------");

    // TDS_LOG_INFO("Print engine pool data...");
    // for(auto it : engine.m_poolData)
    // {
    //     TDS_LOG_INFO("{}->{}", it.first, it.second);
    // }
    // TDS_LOG_INFO("--------------------------------");
    pCallback1.reset();
    pCallback2.reset();
    PluginManager::DestroyAllPlugins();
    //delete p_dyModule;
    //delete p_SerialPortDyModule;

    return 1;
}