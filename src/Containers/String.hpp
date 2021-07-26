#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"

class String final: public IRef {
public:
    String();
    String(const char* cstring);
    String(u8* data, u64 length);
    String(const String& other);
    String(String&& other);
    ~String();
public:
    u8& operator[](u64 index);
    const u8& operator[](u64 index) const;
public: // TODO: Do I make this private?
    u8* Data   = nullptr;
    u64 Length = 0;
};
