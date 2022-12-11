#include <stdio.h> 
#include "Base.h"
#include "WriteImeiPlugin.h"

WriteImeiPlugin::WriteImeiPlugin(std::string name) : TARDIS::CORE::Plugin(std::move(name))
{
	m_callerContainer->registerFunctor("Initialize", &WriteImeiPlugin::Initialize, this, 
	{
		{"Engine", "Engine"}
	});

	m_callerContainer->registerFunctor("WriteImei", &WriteImeiPlugin::WriteImei, this, 
	{
		{"Imei", "this string will be written for imei"}, 
		{"Length", "the length of imei"}
	});

	m_callerContainer->registerFunctor("WriteSn", &WriteImeiPlugin::WriteSn, this, 
	{
		{"Sn", "jdfhsjd3re红豆沙合法的"}
	});
};

bool WriteImeiPlugin::Initialize(std::string userData)
{
	return true;
}

bool WriteImeiPlugin::WriteImei(std::string imei, int len)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	printf("write imei->%s, %d", imei.c_str(), len);
	
	return true;
}

bool WriteImeiPlugin::WriteSn(std::string sn)
{
	return true;
}

extern "C" TARDIS_EXPORT TARDIS::CORE::IPlugin* CreatePlugin()
{
	auto plugin = WriteImeiPlugin::CreateInstance("WriteImei");
    return plugin;
}