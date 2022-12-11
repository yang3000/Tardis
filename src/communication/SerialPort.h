#pragma once

#include "Communication.h"
#include "../core/Plugin.h"

namespace TARDIS
{
    class SerialPort : public CORE::Plugin<SerialPort>, public Communication
    {
    public:
    	SerialPort(std::string name);
	
	    ~SerialPort();

        virtual bool loadCallers() override;

        virtual bool sendCommand(const char *command, int length) override;

        virtual bool readCommand(char *buffer, int &length, const char *regex = nullptr) override;

        virtual bool queryCommand(const char *command, int command_length, char *buffer, int &buffer_length, const char *regex = nullptr) override;

        bool initialize(const PChar port, UInt baud, UInt parity , UInt databits, UInt stopbits);
    };
}