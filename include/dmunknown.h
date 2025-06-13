#ifndef __DMUNKNOWN_H_INCLUDE__
#define __DMUNKNOWN_H_INCLUDE__

#include "dmos.h"
#include "dmguid.h"
#include "dmmoduleptr.h"

class IdmUnknown {
public:
    virtual ~IdmUnknown() {}
    virtual void DMAPI Release() = 0;
    virtual long DMAPI AddRef() = 0;
    virtual long DMAPI QueryInterface(const DmGuid& riid, void** ppvObject) = 0;
};

typedef DmModulePtr<IdmUnknown> dmUnknownPtr;

#endif // __DMUNKNOWN_H_INCLUDE__