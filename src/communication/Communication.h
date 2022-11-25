#pragma once

namespace TARDIS
{
    class Communication
    {
    public:
        virtual bool sendCommand(const char* command, int length) = 0;

        virtual bool readCommand(char* buffer, int& length, const char* regex = nullptr) = 0;

        virtual bool queryCommand(const char* command, int command_length, char* buffer, int& buffer_length, const char* regex = nullptr) = 0;
    };
}
