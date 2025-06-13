#ifndef __DMPLUGINMANAGER_H_INCLUDE__
#define __DMPLUGINMANAGER_H_INCLUDE__

#include "dmiplugin.h"
#include <string>
#include <vector>
#include <map>

struct DmPluginInfo {
    std::string name;
    std::string version;
    std::string description;
    std::string filePath;
    void* handle;
    dmPluginPtr plugin;
    
    DmPluginInfo() : handle(nullptr) {}
};

class IdmPluginManager : virtual public IdmUnknown {
public:
    virtual ~IdmPluginManager() {}
    virtual bool DMAPI LoadPlugin(const std::string& pluginPath) = 0;
    virtual bool DMAPI UnloadPlugin(const std::string& pluginName) = 0;
    virtual void DMAPI UnloadAllPlugins() = 0;
    virtual IdmPlugin* DMAPI GetPlugin(const std::string& pluginName) = 0;
    virtual std::vector<std::string> DMAPI GetLoadedPlugins() const = 0;
    virtual bool DMAPI ExecutePlugin(const std::string& pluginName, 
                                   const std::string& command, 
                                   const std::string& params) = 0;
    virtual void DMAPI ScanPluginDirectory(const std::string& directory) = 0;
};

typedef DmModulePtr<IdmPluginManager> dmPluginManagerPtr;

extern "C" DMEXPORT_DLL IdmPluginManager* DMAPI dmpluginmanagerGetModule();
typedef IdmPluginManager* (DMAPI* PFN_dmpluginmanagerGetModule)();

#endif // __DMPLUGINMANAGER_H_INCLUDE__