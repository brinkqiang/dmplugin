#ifndef __SAMPLEPLUGIN_H_INCLUDE__
#define __SAMPLEPLUGIN_H_INCLUDE__

#include "dmplugin.h"
#include "dmbaseunknown.h"

class SamplePlugin : virtual public DmBaseUnknown, virtual public IdmPlugin {
private:
    bool m_initialized;

public:
    SamplePlugin();
    virtual ~SamplePlugin();

    // IdmUnknown
    virtual long DMAPI QueryInterface(const DmGuid& riid, void** ppvObject) override;

    // IdmPlugin
    virtual bool DMAPI Initialize() override;
    virtual void DMAPI Shutdown() override;
    virtual std::string DMAPI GetPluginName() const override;
    virtual std::string DMAPI GetPluginVersion() const override;
    virtual std::string DMAPI GetPluginDescription() const override;
    virtual bool DMAPI Execute(const std::string& command, const std::string& params) override;
};

#endif // __SAMPLEPLUGIN_H_INCLUDE__