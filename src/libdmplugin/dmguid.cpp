#include "dmguid.h"
#include <sstream>
#include <iomanip>

std::string DmGuid::ToString() const {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    ss << "{" << std::setw(8) << Data1 << "-";
    ss << std::setw(4) << Data2 << "-";
    ss << std::setw(4) << Data3 << "-";
    ss << std::setw(2) << static_cast<int>(Data4[0]) << std::setw(2) << static_cast<int>(Data4[1]) << "-";
    for (int i = 2; i < 8; ++i) {
        ss << std::setw(2) << static_cast<int>(Data4[i]);
    }
    ss << "}";
    return ss.str();
}