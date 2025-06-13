#include <iostream>
#include <string>
#include <vector>

#include "dmpluginmanager.h" // 插件管理器接口
#include "dmiplugin.h"       // 插件接口
#include "dmguid.h"          // GUID定义
#include "dmfix_win_utf8.h"

void print_header(const std::string& title) {
    std::cout << "\n==================================================\n";
    std::cout << ">> " << title << "\n";
    std::cout << "==================================================\n";
}

int main(int argc, char* argv[]) {
    print_header("1. 获取插件管理器");

    // 使用我们定义的智能指针 DmModulePtr 来自动管理模块的生命周期
    dmPluginManagerPtr manager(dmpluginmanagerGetModule());

    if (!manager) {
        std::cerr << "错误: 获取插件管理器模块失败！" << std::endl;
        return -1;
    }
    std::cout << "成功获取插件管理器。\n";

    // --- 加载插件 ---
    print_header("2. 加载插件 (sampleplugin)");
#ifdef _WIN32
    const char* pluginPath = "sampleplugin.dll";
#else
    const char* pluginPath = "./libsampleplugin.so";
#endif

    if (!manager->LoadPlugin(pluginPath)) {
        std::cerr << "错误: 加载插件 '" << pluginPath << "' 失败！" << std::endl;
        return -1;
    }
    std::cout << "成功加载插件: " << pluginPath << "\n";
    
    // --- 获取插件实例 ---
    print_header("3. 从管理器获取插件实例");
    IdmPlugin* samplePlugin = manager->GetPlugin("SamplePlugin");
    if (!samplePlugin) {
        std::cerr << "错误: 获取 'SamplePlugin' 实例失败！" << std::endl;
        return -1;
    }
    std::cout << "成功获取 'SamplePlugin' 实例。\n";

    // --- 测试插件功能 ---
    print_header("4. 测试插件基本接口 (IdmPlugin)");
    std::cout << "  插件名称: " << samplePlugin->GetPluginName() << std::endl;
    std::cout << "  插件版本: " << samplePlugin->GetPluginVersion() << std::endl;
    std::cout << "  插件描述: " << samplePlugin->GetPluginDescription() << std::endl;
    
    std::cout << "\n  执行已知命令 'hello'..." << std::endl;
    samplePlugin->Execute("hello", "main_test");

    std::cout << "\n  执行未知命令 'unknown'..." << std::endl;
    samplePlugin->Execute("unknown", "params");


    // --- 测试 QueryInterface ---
    print_header("5. 测试接口查询 (QueryInterface)");
    IdmUnknown* unknownInterface = nullptr;
    long result = samplePlugin->QueryInterface(IID_IUNKNOWN, (void**)&unknownInterface);
    
    if (result == 0 && unknownInterface) {
        std::cout << "成功从 IdmPlugin 查询到 IdmUnknown 接口。\n";
        
        // 从 IdmUnknown 接口查询回 IdmPlugin 接口
        IdmPlugin* pluginAgain = nullptr;
        result = unknownInterface->QueryInterface(IID_IPLUGIN, (void**)&pluginAgain);

        if (result == 0 && pluginAgain) {
            std::cout << "成功从 IdmUnknown 查询回 IdmPlugin 接口。\n";
            std::cout << "  查询回的插件名称: " << pluginAgain->GetPluginName() << std::endl;

            // 重要：QueryInterface 会增加引用计数，所以必须调用 Release 来释放
            pluginAgain->Release();
        } else {
            std::cerr << "错误: 从 IdmUnknown 查询 IdmPlugin 接口失败！\n";
        }
        
        // 重要：释放第一次查询得到的接口
        unknownInterface->Release();
    } else {
        std::cerr << "错误: 从 IdmPlugin 查询 IdmUnknown 接口失败！\n";
    }

    // --- 卸载插件 ---
    print_header("6. 卸载插件");
    if (manager->UnloadPlugin("SamplePlugin")) {
        std::cout << "成功卸载插件 'SamplePlugin'。\n";
        
        // 验证插件是否真的被卸载
        IdmPlugin* pluginAfterUnload = manager->GetPlugin("SamplePlugin");
        if (pluginAfterUnload == nullptr) {
            std::cout << "验证成功：GetPlugin(\"SamplePlugin\") 返回空指针。\n";
        } else {
            std::cerr << "错误: 插件卸载后，GetPlugin 仍然能获取到实例！\n";
        }
    } else {
        std::cerr << "错误: 卸载插件 'SamplePlugin' 失败！\n";
    }

    print_header("测试结束");
    // main 函数结束，manager (dmPluginManagerPtr) 会自动调用其 Deleter
    // Deleter 会调用 manager->Release()，从而释放管理器资源
    return 0;
}