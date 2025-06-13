#ifndef __DMGUID_H_INCLUDE__
#define __DMGUID_H_INCLUDE__

#include <string>
#include <cstring>

struct DmGuid {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
    
    DmGuid() : Data1(0), Data2(0), Data3(0) {
        std::memset(Data4, 0, sizeof(Data4));
    }
    
    DmGuid(unsigned long d1, unsigned short d2, unsigned short d3,
           unsigned char d4_0, unsigned char d4_1, unsigned char d4_2, unsigned char d4_3,
           unsigned char d4_4, unsigned char d4_5, unsigned char d4_6, unsigned char d4_7)
        : Data1(d1), Data2(d2), Data3(d3) {
        Data4[0] = d4_0; Data4[1] = d4_1; Data4[2] = d4_2; Data4[3] = d4_3;
        Data4[4] = d4_4; Data4[5] = d4_5; Data4[6] = d4_6; Data4[7] = d4_7;
    }
    
    bool operator==(const DmGuid& other) const {
        return Data1 == other.Data1 && Data2 == other.Data2 && 
               Data3 == other.Data3 && std::memcmp(Data4, other.Data4, 8) == 0;
    }
    
    bool operator!=(const DmGuid& other) const {
        return !(*this == other);
    }
    
    std::string ToString() const;
};

// 定义一些常用的GUID
static const DmGuid IID_IUNKNOWN = {0x00000000, 0x0000, 0x0000, 
    0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46};

static const DmGuid IID_IPLUGIN = {0x12345678, 0x1234, 0x1234,
    0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

#endif // __DMGUID_H_INCLUDE__