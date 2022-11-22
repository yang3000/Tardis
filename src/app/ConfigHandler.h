#param once

#include "IHandler.h"

#include "rapidjson/reader.h"
#include <string>


class ConfigHandler : public IHandler
{
public:

    ConfigHandler() : is_found(false) {}

    bool String(const char *str, SizeType length, bool copy)
    {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;

        if(is_found == false && std::string_view(str) == "Callers")
        {
            is_found = true;
            key = "Callers";
            return true;
        }

        if(is_found)
        {
            
        }

        if(!is_found)
        {
            return false;
        }
    }
    bool StartObject()
    {
        cout << "StartObject()" << endl;
        return true;
    }
    bool Key(const char *str, SizeType length, bool copy)
    {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        if(is_found == false && std::string_view(str) == "Callers")
        {
            is_found = true;
            key = "Callers";
            return true;
        }

        if(!is_found)
        {
            return false;
        }
        return true;
    }
    bool EndObject(SizeType memberCount)
    {
        cout << "EndObject(" << memberCount << ")" << endl;
        return true;
    }
    bool StartArray()
    {
        cout << "StartArray()" << endl;
        return true;
    }
    bool EndArray(SizeType elementCount)
    {
        cout << "EndArray(" << elementCount << ")" << endl;
        return true;
    }

private:
    bool is_found;
    std::string key;
}