#include "String.hpp"

#include <cstring>

String::String() : Data(nullptr), Length(0) {}

String::String(const char* cstring) : Data(nullptr), Length(strlen(cstring)) {
    this->Data = new u8[this->Length];
    memcpy(this->Data, cstring, this->Length);
}

String::String(u8* data, u64 length) : Data(data), Length(length) {}

String::String(const String& other) : Data(nullptr), Length(other.Length) {
    this->Data = new u8[this->Length];
    memcpy(this->Data, other.Data, this->Length);
}

String::String(String&& other) : Data(other.Data), Length(other.Length) {
    if (this != &other) {
        other.Data   = nullptr;
        other.Length = 0;
    }
}

String::~String() {
    delete[] this->Data;
}

u8& String::operator[](u64 index) {
    return this->Data[index];
}

const u8& String::operator[](u64 index) const {
    return this->Data[index];
}
