#include "sampleplugin.h"
#include <iostream>

SamplePlugin::SamplePlugin() : m_initialized(false) {
    std::cout << "SamplePlugin构造函数调用" << std::endl;
}

SamplePlugin::~SamplePlugin() {
    std::cout << "SamplePlugin析构函数调用" << std::endl;
}

long SamplePlugin::QueryInterface(const DmGuid& riid, void** ppvObject) {
    if (!ppvObject) {
        return -1;
    }

    if (riid == IID_IUNKNOWN) {
        *ppvObject = static_cast<IdmUnknown*>(this);
        AddRef();
        return 0;
    }

    if (riid == IID_IPLUGIN) {
        *ppvObject = static_cast<IdmPlugin*>(this);
        AddRef();
        return 0;
    }

    *ppvObject = nullptr;
    return -1;
}

bool SamplePlugin::Initialize() {
    if (m_initialized) {
        return true;
    }

    std::cout << "SamplePlugin初始化" << std::endl;
    m_initialized = true;
    return true;
}

void SamplePlugin::Shutdown() {
    if (!m_initialized) {
        return;
    }

    std::cout << "SamplePlugin关闭" << std::endl;
    m_initialized = false;
}

std::string SamplePlugin::GetPluginName() const {
    return "SamplePlugin";
}

std::string SamplePlugin::GetPluginVersion() const {
    return "1.0.0";
}

std::string SamplePlugin::GetPluginDescription() const {
    return "这是一个示例插件，用于演示插件系统的功能";
}

bool SamplePlugin::Execute(const std::string& command, const std::string& params) {
    std::cout << "SamplePlugin执行命令: " << command << ", 参数: " << params << std::endl;
    
    if (command == "hello") {
        std::cout << "Hello from SamplePlugin! 参数: " << params << std::endl;
        return true;
    }
    
    if (command == "test") {
        std::cout << "测试命令执行成功，参数: " << params << std::endl;
        return true;
    }
    
    std::cout << "未知命令: " << command << std::endl;
    return false;
}

extern "C" DMEXPORT_DLL IdmPlugin* DMAPI CreatePlugin() {
    return new SamplePlugin();
}
