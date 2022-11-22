#include "SpdLog.h"
#include "stdio.h"
#include "ICaller.h"
#include "IPlugin.h"
#include "DynamicModule.h"
#include "JsonHandler.h"
#include "RapidJsonParser.h"

#include "Engine.h"


using namespace TARDIS::CORE;
typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

int main()
{
    auto log = new SpdLog("demo");
    log->log(LogType::Info, "3232");

    TDS_LOG_INFO("{}", 2131);


    // const char json[] = " { \"Callers\" : [{\"name\":\"writeImei\",\"id\":\"21323\"}, {\"name\":\"writeSn\",\"id\":\"222222\"}], \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    // MyHandler handler;
    // Reader reader;
    // StringStream ss(json);
    // reader.Parse(ss, handler);

    std::shared_ptr<RapidJsonParser> jsonParser = std::make_shared<RapidJsonParser>();
    jsonParser->parseJsonFile("C:\\Users\\yangh\\Desktop\\Tardis\\bin\\Debug\\sequence.json");
    TDS_LOG_INFO(jsonParser->get("version"));

    Engine engine("testEngine");

    if(jsonParser->nodeBegin("sequences"))
    {
        engine.onDeserialize(jsonParser);
        jsonParser->nodeEnd();
    }

    TARDIS::DynamicModule* p_dyModule = new TARDIS::DynamicModule("honor_cust_lib.dll");
    auto pPlugin = p_dyModule->Call<CreatePlugin>("CreatePlugin");
    pPlugin->setLogger(log);
    pPlugin->initialize();
    pPlugin->parseCallerInfo([](const char *name, Param *params, unsigned count)
    { 
        printf("Method:%s\r\n", name);
        for (int i = 0; i < count; ++i)
        {
            printf("%s[%s]:%s\r\n",params[i].name.buf,params[i].type.buf,params[i].desc.buf); 
        }
        printf("--------------------------------\r\n");
    });

    Str param[2];
    param[0].buf = "111111123456";
    param[0].len = strlen(param[0].buf);
    param[1].buf = "021";
    param[1].len = strlen(param[1].buf);
    auto fn11 = pPlugin->getCaller("WriteImei");
    auto fnEx = pPlugin->getCaller("WriteImeiEx");
    //auto fn11 = pPlugin->getCaller("WriteImei");
   (*fnEx)(param);
   

    auto pCallback = new CallBackImpl(&engine);
    pPlugin->setCallback(pCallback);
    engine.addPlugin("8708AB25-1C86-45bd-ADEF-06FD5BCA03DA", pPlugin);
    engine.runTask();

    while(engine.isRunning())
    {
        printf("engine is running, waitting...\r\n");
        Sleep(100);
    }

    return 1;

    TARDIS::DynamicModule* p_mod_honor = new TARDIS::DynamicModule("honor_cust_lib.dll");
    IPlugin* p_plugin_honor = p_mod_honor->Call<CreatePlugin>("CreatePlugin");
    p_plugin_honor->setLogger(log);
    p_plugin_honor->initialize();

    p_plugin_honor->parseCallerInfo([](const char *name, Param *params, unsigned count)
    { 
        printf("Method:%s\r\n", name);
        for (int i = 0; i < count; ++i)
        {
            printf("%s[%s]:%s\r\n",params[i].name.buf,params[i].type.buf,params[i].desc.buf); 
        }
        printf("--------------------------------\r\n");
    });

    auto fn = p_plugin_honor->getCaller("EnumDonglePorts");
    (*fn)(nullptr);

    auto fn_test = p_plugin_honor->getCaller("TestFreeFn");
    (*fn_test)(nullptr);

    TARDIS::CORE::ICaller *caller = p_plugin_honor->getCaller("InitializeConnection");
    Str params[2];
    params[0].buf = "111111123456";
    params[0].len = strlen(params[0].buf);
    params[1].buf = "0";
    params[1].len = strlen(params[1].buf);
    (*caller)(params);

    // TARDIS::DynamicModule* p_mod = new TARDIS::DynamicModule("write_imei_dll.dll");
    // IPlugin* p_plugin = p_mod->Call<CreatePlugin>("CreatePlugin");

    // p_plugin->parseCallerInfo([](const char *name, Param *params, unsigned count)
    // { 
    //     printf("Method:%s\r\n", name);
    //     for (int i = 0; i < count; ++i)
    //     {
    //         printf("%s[%s]:%s\r\n",params[i].name.buf,params[i].type.buf,params[i].desc.buf); 
    //     }
    //     printf("--------------------------------\r\n");
    // });

    // //p_plugin->setLogger(log);

    // TARDIS::CORE::ICaller *caller = p_plugin->getCaller("WriteImei");
    // Str params[2];
    // params[0].buf = "111111123456";
    // params[0].len = strlen(params[0].buf);
    // params[1].buf = "12";
    // params[1].len = strlen(params[1].buf);
    // (*caller)(params);

    // auto fn = p_plugin->getCaller("EnumDonglePorts");
    // (*fn)(nullptr);

    // auto fn_test = p_plugin->getCaller("TestFreeFn");
    // (*fn_test)(nullptr);

    // TARDIS::CORE::ICaller* caller = p_plugin->getCaller("InitializeConnection");
	// Str params[2];
	// params[0].buf = "111111123456";
	// params[0].len = strlen(params[0].buf);
	// params[1].buf = "0";
	// params[1].len = strlen(params[1].buf);
    // (*caller)(params);
    return 1;
}