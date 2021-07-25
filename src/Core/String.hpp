#pragma once

#include "Defines.hpp"
#include "Ref.hpp"

class String: public IRef {
public:
    String();
    String(const char *cstring);
    String(u8 *data, u64 length);
    String(const String &other);
    String(String &&other);
    ~String();

public: // TODO: Do I have this public?
    u8 *Data   = nullptr;
    u64 Length = 0;
};
