#ifndef __DMIPLUGIN_H_INCLUDE__
#define __DMIPLUGIN_H_INCLUDE__

#include "dmiunknown.h"
#include <string>

class IdmPlugin : virtual public IdmUnknown {
public:
    virtual ~IdmPlugin() {}
    virtual bool DMAPI Initialize() = 0;
    virtual void DMAPI Shutdown() = 0;
    virtual std::string DMAPI GetPluginName() const = 0;
    virtual std::string DMAPI GetPluginVersion() const = 0;
    virtual std::string DMAPI GetPluginDescription() const = 0;
    virtual bool DMAPI Execute(const std::string& command, const std::string& params) = 0;
};

typedef DmModulePtr<IdmPlugin> dmPluginPtr;

#endif // __DMIPLUGIN_H_INCLUDE__