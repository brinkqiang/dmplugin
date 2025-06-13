#include "dmpluginmanager_impl.h"
#include <iostream>
#include <filesystem>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

DmPluginManagerImpl::~DmPluginManagerImpl() {
    UnloadAllPlugins();
}

long DmPluginManagerImpl::QueryInterface(const DmGuid& riid, void** ppvObject) {
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

bool DmPluginManagerImpl::LoadPlugin(const std::string& pluginPath) {
    void* handle = LoadLibrary(pluginPath);
    if (!handle) {
        std::cerr << "无法加载插件库: " << pluginPath << std::endl;
        return false;
    }

    typedef IdmPlugin* (DMAPI* PFN_CreatePlugin)();
    PFN_CreatePlugin createPlugin = (PFN_CreatePlugin)GetProcAddress(handle, "CreatePlugin");
    
    if (!createPlugin) {
        std::cerr << "无法找到CreatePlugin函数: " << pluginPath << std::endl;
        UnloadLibrary(handle);
        return false;
    }

    IdmPlugin* plugin = createPlugin();
    if (!plugin) {
        std::cerr << "创建插件实例失败: " << pluginPath << std::endl;
        UnloadLibrary(handle);
        return false;
    }

    dmPluginPtr pluginPtr(plugin);
    
    if (!pluginPtr->Initialize()) {
        std::cerr << "插件初始化失败: " << pluginPath << std::endl;
        UnloadLibrary(handle);
        return false;
    }

    std::string pluginName = pluginPtr->GetPluginName();
    
    // 检查是否已经加载了同名插件
    if (m_plugins.find(pluginName) != m_plugins.end()) {
        std::cerr << "插件已经加载: " << pluginName << std::endl;
        pluginPtr->Shutdown();
        UnloadLibrary(handle);
        return false;
    }

    DmPluginInfo info;
    info.name = pluginName;
    info.version = pluginPtr->GetPluginVersion();
    info.description = pluginPtr->GetPluginDescription();
    info.filePath = pluginPath;
    info.handle = handle;
    info.plugin = std::move(pluginPtr);

    m_plugins[pluginName] = std::move(info);
    
    std::cout << "成功加载插件: " << pluginName << " v" << info.version << std::endl;
    return true;
}

bool DmPluginManagerImpl::UnloadPlugin(const std::string& pluginName) {
    auto it = m_plugins.find(pluginName);
    if (it == m_plugins.end()) {
        return false;
    }

    DmPluginInfo& info = it->second;
    if (info.plugin) {
        info.plugin->Shutdown();
        info.plugin.reset();
    }

    if (info.handle) {
        UnloadLibrary(info.handle);
    }

    m_plugins.erase(it);
    std::cout << "成功卸载插件: " << pluginName << std::endl;
    return true;
}

void DmPluginManagerImpl::UnloadAllPlugins() {
    std::vector<std::string> pluginNames;
    for (const auto& pair : m_plugins) {
        pluginNames.push_back(pair.first);
    }

    for (const std::string& name : pluginNames) {
        UnloadPlugin(name);
    }
}

IdmPlugin* DmPluginManagerImpl::GetPlugin(const std::string& pluginName) {
    auto it = m_plugins.find(pluginName);
    if (it != m_plugins.end()) {
        return it->second.plugin.get();
    }
    return nullptr;
}

std::vector<std::string> DmPluginManagerImpl::GetLoadedPlugins() const {
    std::vector<std::string> result;
    for (const auto& pair : m_plugins) {
        result.push_back(pair.first);
    }
    return result;
}

bool DmPluginManagerImpl::ExecutePlugin(const std::string& pluginName, 
                                       const std::string& command, 
                                       const std::string& params) {
    IdmPlugin* plugin = GetPlugin(pluginName);
    if (!plugin) {
        return false;
    }
    
    return plugin->Execute(command, params);
}

void DmPluginManagerImpl::ScanPluginDirectory(const std::string& directory) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (IsPluginFile(filename)) {
                    std::string fullPath = entry.path().string();
                    std::cout << "发现插件文件: " << fullPath << std::endl;
                    
                    if (!LoadPlugin(fullPath)) {
                        std::cerr << "加载插件失败: " << fullPath << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "扫描插件目录失败: " << e.what() << std::endl;
    }
}

void* DmPluginManagerImpl::LoadLibrary(const std::string& path) {
#ifdef _WIN32
    return ::LoadLibraryA(path.c_str());
#else
    return dlopen(path.c_str(), RTLD_LAZY);
#endif
}

void DmPluginManagerImpl::UnloadLibrary(void* handle) {
    if (handle) {
#ifdef _WIN32
        ::FreeLibrary((HMODULE)handle);
#else
        dlclose(handle);
#endif
    }
}

void* DmPluginManagerImpl::GetProcAddress(void* handle, const char* procName) {
    if (!handle) {
        return nullptr;
    }
    
#ifdef _WIN32
    return ::GetProcAddress((HMODULE)handle, procName);
#else
    return dlsym(handle, procName);
#endif
}

bool DmPluginManagerImpl::IsPluginFile(const std::string& filename) {
#ifdef _WIN32
    return filename.find(".dll") != std::string::npos;
#else
    return filename.find(".so") != std::string::npos;
#endif
}

extern "C" DMEXPORT_DLL IdmPluginManager* DMAPI dmpluginmanagerGetModule() {
    return new DmPluginManagerImpl();
}