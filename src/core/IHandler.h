#pragma once

#include <iostream>

using namespace std;

namespace TARDIS::CORE
{
	class IHandler {
	public:
		virtual bool Null() { cout << "Null()" << endl; return true; }
		virtual bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
		virtual bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
		virtual bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
		virtual bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
		virtual bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
		virtual bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
		virtual bool RawNumber(const char* str, unsigned length, bool copy) { cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl; return true; }
		virtual bool String(const char *str, unsigned length, bool copy) { cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl; return true; }
		virtual bool StartObject() { cout << "StartObject()" << endl; return true; }
		virtual bool Key(const char* str, unsigned length, bool copy) { cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl; return true; }
		virtual bool EndObject(unsigned memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
		virtual bool StartArray() { cout << "StartArray()" << endl; return true; }
		virtual bool EndArray(unsigned elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
	};
}