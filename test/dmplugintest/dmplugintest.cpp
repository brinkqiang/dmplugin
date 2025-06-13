
#include "dmplugin.h"
#include "gtest.h"

class env_dmplugin
{
public:
    void init(){}
    void uninit(){}
};

class frame_dmplugin : public testing::Test
{
public:
    virtual void SetUp()
    {
        env.init();
    }
    virtual void TearDown()
    {
        env.uninit();
    }
protected:
    env_dmplugin env;
};

TEST_F(frame_dmplugin, init)
{
    Idmplugin* module = dmpluginGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
}
