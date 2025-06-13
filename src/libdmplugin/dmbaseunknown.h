#ifndef __DMBASEUNKNOWN_H_INCLUDE__
#define __DMBASEUNKNOWN_H_INCLUDE__

#include "dmunknown.h"
#include <atomic>

class DmBaseUnknown : virtual public IdmUnknown {
private:
    std::atomic<long> m_refCount;

public:
    DmBaseUnknown() : m_refCount(1) {}
    virtual ~DmBaseUnknown() {}

    virtual void DMAPI Release() {
        long refCount = m_refCount.fetch_sub(1) - 1;
        if (refCount == 0) {
            delete this;
        }
    }

    virtual long DMAPI AddRef() {
        return m_refCount.fetch_add(1) + 1;
    }

    virtual long DMAPI QueryInterface(const DmGuid& riid, void** ppvObject) {
        if (!ppvObject) {
            return -1;
        }

        if (riid == IID_IUNKNOWN) {
            *ppvObject = static_cast<IdmUnknown*>(this);
            AddRef();
            return 0;
        }

        *ppvObject = nullptr;
        return -1;
    }

protected:
    long GetRefCount() const {
        return m_refCount.load();
    }
};

#endif // __DMBASEUNKNOWN_H_INCLUDE__