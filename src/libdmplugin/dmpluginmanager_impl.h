#ifndef __DMPLUGINMANAGER_IMPL_H_INCLUDE__
#define __DMPLUGINMANAGER_IMPL_H_INCLUDE__

#include "dmpluginmanager.h"
#include "dmbaseunknown.h"
#include <map>

class DmPluginManagerImpl :  virtual public DmBaseUnknown, virtual public IdmPluginManager {
private:
    std::map<std::string, DmPluginInfo> m_plugins;

public:
    virtual ~DmPluginManagerImpl();
    
    // IdmUnknown
    virtual long DMAPI QueryInterface(const DmGuid& riid, void** ppvObject) override;
    
    // IdmPluginManager
    virtual bool DMAPI LoadPlugin(const std::string& pluginPath) override;
    virtual bool DMAPI UnloadPlugin(const std::string& pluginName) override;
    virtual void DMAPI UnloadAllPlugins() override;
    virtual IdmPlugin* DMAPI GetPlugin(const std::string& pluginName) override;
    virtual std::vector<std::string> DMAPI GetLoadedPlugins() const override;
    virtual bool DMAPI ExecutePlugin(const std::string& pluginName, 
                                   const std::string& command, 
                                   const std::string& params) override;
    virtual void DMAPI ScanPluginDirectory(const std::string& directory) override;

private:
    void* LoadLibrary(const std::string& path);
    void UnloadLibrary(void* handle);
    void* GetProcAddress(void* handle, const char* procName);
    bool IsPluginFile(const std::string& filename);
    std::vector<std::string> ListFiles(const std::string& directory);
};

#endif // __DMPLUGINMANAGER_IMPL_H_INCLUDE__