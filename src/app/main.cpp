#include "SpdLog.h"
#include "stdio.h"
#include "ICaller.h"
#include "IPlugin.h"
#include "DynamicModule.h"
#include "JsonHandler.h"
#include "RapidJsonParser.h"
#include "Communication.h"

#include "Engine.h"


using namespace TARDIS::CORE;
typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

int main()
{

    Engine engine{"testEngine"};

    auto log = new SpdLog(engine.getEngineId());
    log->log(LogType::Info, "3232");

    TDS_LOG_INFO("{}", 2131);


    // const char json[] = " { \"Callers\" : [{\"name\":\"writeImei\",\"id\":\"21323\"}, {\"name\":\"writeSn\",\"id\":\"222222\"}], \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    // MyHandler handler;
    // Reader reader;
    // StringStream ss(json);
    // reader.Parse(ss, handler);

    std::shared_ptr<RapidJsonParser> jsonParser = std::make_shared<RapidJsonParser>();
    jsonParser->parseJsonFile("sequence.json");
    TDS_LOG_INFO(jsonParser->get("version"));

    if(jsonParser->nodeBegin("sequences"))
    {
        engine.onDeserialize(jsonParser);
        jsonParser->nodeEnd();
    }

    auto pCallback = std::make_shared<CallBackImpl>(&engine);

    TARDIS::DynamicModule* p_dyModule = new TARDIS::DynamicModule("honor_cust_lib.dll");
    auto pPlugin = p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin->setLogger(log);
    pPlugin->loadCallers();
    pPlugin->setCallback(pCallback.get());
    pPlugin->parseCallerInfo([](const char *name, Param *params, unsigned count)
    { 
        TDS_LOG_INFO("Method:{}", name);
        for (int i = 0; i < count; ++i)
        {
            TDS_LOG_INFO("Param{}:{}[{}]:{}", i, params[i].name.buf, params[i].type.buf, params[i].desc.buf);
        }
        TDS_LOG_INFO("--------------------------------");

    });

    TDS_LOG_INFO("Call WriteImeiEx directly...");
    Str param[2];
    param[0].buf = "111111123456";
    param[0].len = strlen(param[0].buf);
    param[1].buf = "021";
    param[1].len = strlen(param[1].buf);
    auto fn11 = pPlugin->getCaller("WriteImei");
    auto fnEx = pPlugin->getCaller("WriteImeiEx");
    //auto fn11 = pPlugin->getCaller("WriteImei");
    (*fnEx)(param);
    TDS_LOG_INFO("--------------------------------");

    //===================================================
    TARDIS::DynamicModule* p_SerialPortDyModule = new TARDIS::DynamicModule("serial_port_lib.dll");
    auto pSerialPortPlugin = p_SerialPortDyModule->Call<CreatePlugin>("CreatePlugin");
    pSerialPortPlugin->setLogger(log);
    pSerialPortPlugin->loadCallers();
    pSerialPortPlugin->setCallback(pCallback.get());
    pSerialPortPlugin->parseCallerInfo([](const char *name, Param *params, unsigned count)
    { 
        TDS_LOG_INFO("Method:{}", name);
        for (UInt i = 0; i < count; ++i)
        {
            TDS_LOG_INFO("Param{}:{}[{}]:{}", i, params[i].name.buf, params[i].type.buf, params[i].desc.buf);
        }
        TDS_LOG_INFO("--------------------------------");
    });

    TARDIS::Communication *pCommunication = dynamic_cast<TARDIS::Communication *>(pSerialPortPlugin);
    if (pCommunication)
    {
        pCommunication->sendCommand("4353445", 7);
    }
    //===================================================


    engine.addPlugin("WriteImeiPlugin", pPlugin);
    engine.addPlugin("SerialPortPlugin", pSerialPortPlugin);

    TDS_LOG_INFO("Run Task...");
    engine.runTask();
    TDS_LOG_INFO("--------------------------------");

    while(engine.isRunning())
    {
        TDS_LOG_INFO("engine is running, waitting...");
        Sleep(100);
    }

    TDS_LOG_INFO("--------------------------------");

    TDS_LOG_INFO("Print engine pool data...");
    for(auto it : engine.m_poolData)
    {
        TDS_LOG_INFO("{}->{}", it.first, it.second);
    }
    TDS_LOG_INFO("--------------------------------");
    pCallback.reset();
    //delete p_dyModule;
    //delete p_SerialPortDyModule;

    return 1;
}