#include "dmplugin.h"

int main(int argc, char* argv[]) {
    Idmplugin* module = dmpluginGetModule();
    if (module) {
        module->Release();
    }
    return 0;
}