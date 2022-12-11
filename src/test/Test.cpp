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


using namespace TARDIS::CORE;
typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

int main()
{

    SpdLog::DefaultLogger();
    Engine engine1{"testEngine_1"};
    Engine engine2{"testEngine_2"};

    auto log1 = new SpdLog(engine1.getEngineId(), "thread1.log");
    auto log2 = new SpdLog(engine2.getEngineId(), "thread2.log");
    log1->log(LogType::Info, "testEngine_1 task");
    log2->log(LogType::Info, "testEngine_2 task");

    std::shared_ptr<RapidJsonParser> jsonParser = std::make_shared<RapidJsonParser>();
    jsonParser->parseJsonFile("sequence.json");
    TDS_LOG_INFO(jsonParser->get("version"));

    if(jsonParser->nodeBegin("sequences"))
    {
        Engine::OnDeserialize(jsonParser);
        jsonParser->nodeEnd();
    }

    auto pCallback1 = std::make_shared<CallBackImpl>(&engine1);
    auto pCallback2 = std::make_shared<CallBackImpl>(&engine2);

    PluginManager::LoadPlugin("honor_cust_lib","honor_cust_lib.dll");

    //TARDIS::DynamicModule* p_dyModule = new TARDIS::DynamicModule("honor_cust_lib.dll");
    auto pPlugin1 = PluginManager::CreatePlugin(1);
    //auto pPlugin1 = p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin1->setLogger(log1);
    pPlugin1->loadCallers();
    pPlugin1->setCallback(pCallback1.get());

    auto pPlugin2 = PluginManager::CreatePlugin(1);//pPlugin1->clone(); //p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin2->setLogger(log2);
    pPlugin2->loadCallers();
    pPlugin2->setCallback(pCallback2.get());
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

    engine1.addPlugin("WriteImeiPlugin", pPlugin1);
    engine2.addPlugin("WriteImeiPlugin", pPlugin2);
    //engine1.addPlugin("SerialPortPlugin", pSerialPortPlugin);

    TDS_LOG_INFO("Run Task1...");
    engine1.runTask();
    TDS_LOG_INFO("--------------------------------");
    TDS_LOG_INFO("Run Task2...");
    engine2.runTask();
    TDS_LOG_INFO("--------------------------------");


    while(engine1.isRunning())
    {
        TDS_LOG_INFO("engine1 is running, waitting...");
        Sleep(100);
    }

    while(engine2.isRunning())
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