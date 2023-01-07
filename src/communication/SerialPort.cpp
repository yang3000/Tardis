#include "SerialPort.h"

namespace TARDIS
{
    SerialPort::SerialPort(std::string name) : CORE::Plugin<SerialPort>(std::move(name))
    {
    }

    SerialPort::~SerialPort()
    {
    }

    bool SerialPort::loadCallers()
    {

        RegisterFunctor("Initialize", &SerialPort::sendCommand, this, 
        {
            {"Command", "command"}, 
			{"Length", "length"}
        });

        RegisterFunctor("SendCommand", &SerialPort::sendCommand, this, 
        {
            {"Command", "command"}, 
			{"Length", "length"}
        });

        RegisterFunctor("ReadCommand", [this](std::string regex) -> bool 
        {
            char buf[1024] = {0};
            int len = sizeof(buf);
            readCommand(buf, len, regex.c_str());
            addPoolData("Buf", regex.c_str());
            return true;
        }, 
        {
            {"Regex", "command"}
        });

        // RegisterFunctor"queryCommand", &SerialPort::queryCommand, this, 
        // {
        //     {"Command", "command"}, 
		// 	{"Length", "length"}
        // });
        return true;
    }

    bool SerialPort::sendCommand(const char *command, int length)
    {
        LOG_INFO("sendCommand:{},len:{}", command, length);
        return true;
    }

    bool SerialPort::readCommand(char *buffer, int &length, const char *regex)
    {
        LOG_INFO("readCommand->regex:{}", regex);

        strcpy_s(buffer, length -1 , "I was read..");
        length = 23;
        return true;

    }

    bool SerialPort::queryCommand(const char *command, int command_length, char *buffer, int &buffer_length, const char *regex)
    {

        LOG_INFO("queryCommand:{},len:{}, regex:", command, command_length, regex);
        return true;

    }

    bool SerialPort::initialize(const PChar port, UInt baud, UInt parity, UInt databits, UInt stopbits)
    {
        return true;

    }
}

extern "C" TARDIS_EXPORT  TARDIS::CORE::IPlugin* CreatePlugin()
{
	auto pPlugin = TARDIS::SerialPort::CreateInstance("SerialPort");
    return pPlugin;
}