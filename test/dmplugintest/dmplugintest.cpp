#include "gtest.h"
#include "dmpluginmanager.h" // 插件管理器接口
#include "dmplugin.h"       // 插件接口
#include "dmguid.h"          // GUID定义
#include "dmfix_win_utf8.h"
// 定义测试固件 (Test Fixture)
class SamplePluginTest : public ::testing::Test {
protected:
    dmPluginManagerPtr manager;
    IdmPlugin* samplePlugin = nullptr;

    // SetUp 会在每个 TEST_F 测试用例开始前执行
    void SetUp() override {
        // 1. 获取插件管理器模块
        manager = dmPluginManagerPtr(dmpluginmanagerGetModule());
        ASSERT_TRUE(manager != nullptr) << "获取插件管理器失败";

        // 2. 加载示例插件
        // 假设 sampleplugin.dll/.so 在可执行文件目录或者系统路径中
#ifdef _WIN32
        const char* pluginPath = "sampleplugin.dll";
#else
        const char* pluginPath = "./libsampleplugin.so";
#endif
        bool loaded = manager->LoadPlugin(pluginPath);
        ASSERT_TRUE(loaded) << "加载插件 " << pluginPath << " 失败";

        // 3. 获取插件实例
        samplePlugin = manager->GetPlugin("SamplePlugin");
        ASSERT_TRUE(samplePlugin != nullptr) << "获取 'SamplePlugin' 实例失败";
    }

    // TearDown 会在每个 TEST_F 测试用例结束后执行
    void TearDown() override {
        // manager 是一个 unique_ptr，它会在作用域结束时自动调用 Release()
        // Release() 中会调用 UnloadAllPlugins()，所以这里不需要手动清理
    }
};

// 测试用例 1: 验证插件基本信息
TEST_F(SamplePluginTest, GetPluginInfo) {
    ASSERT_EQ(samplePlugin->GetPluginName(), "SamplePlugin");
    ASSERT_EQ(samplePlugin->GetPluginVersion(), "1.0.0");
    ASSERT_EQ(samplePlugin->GetPluginDescription(), "这是一个示例插件，用于演示插件系统的功能");
}

// 测试用例 2: 测试执行命令
TEST_F(SamplePluginTest, ExecuteCommands) {
    // 测试已知命令
    EXPECT_TRUE(samplePlugin->Execute("hello", "world"));
    EXPECT_TRUE(samplePlugin->Execute("test", "with params"));

    // 测试未知命令
    EXPECT_FALSE(samplePlugin->Execute("unknown_command", ""));
}

// 测试用例 3: 测试 QueryInterface
// 这个测试非常重要，它验证了虚继承是否正确解决了菱形继承问题
TEST_F(SamplePluginTest, QueryInterface) {
    IdmUnknown* unknown_from_plugin = nullptr;
    IdmPlugin* plugin_from_unknown = nullptr;
    long result;

    // 3.1 从 IdmPlugin 接口查询 IdmUnknown 接口
    result = samplePlugin->QueryInterface(IID_IUNKNOWN, (void**)&unknown_from_plugin);
    
    ASSERT_EQ(result, 0) << "从 IdmPlugin 查询 IID_IUNKNOWN 失败";
    ASSERT_TRUE(unknown_from_plugin != nullptr) << "查询到的 IID_IUNKNOWN 接口为空指针";
    
    // 3.2 从获取到的 IdmUnknown 接口查询回 IdmPlugin 接口
    result = unknown_from_plugin->QueryInterface(IID_IPLUGIN, (void**)&plugin_from_unknown);

    ASSERT_EQ(result, 0) << "从 IdmUnknown 查询 IID_IPLUGIN 失败";
    ASSERT_TRUE(plugin_from_unknown != nullptr) << "查询到的 IID_IPLUGIN 接口为空指针";

    // 3.3 验证查询回来的指针和原始指针是同一个对象
    ASSERT_EQ(plugin_from_unknown, samplePlugin);

    // 3.4 释放通过 QueryInterface 获取的接口指针
    // QueryInterface 内部调用了 AddRef，所以我们必须调用 Release 来平衡引用计数
    plugin_from_unknown->Release();
    unknown_from_plugin->Release();
}


// 测试用例 4: 测试插件卸载
TEST_F(SamplePluginTest, UnloadPlugin) {
    // 4.1 卸载插件
    bool unloaded = manager->UnloadPlugin("SamplePlugin");
    ASSERT_TRUE(unloaded) << "卸载插件 'SamplePlugin' 失败";

    // 4.2 确认插件已被卸载
    IdmPlugin* plugin_after_unload = manager->GetPlugin("SamplePlugin");
    ASSERT_TRUE(plugin_after_unload == nullptr) << "插件卸载后，GetPlugin 应该返回空指针";
}


// 测试程序的 main 函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}