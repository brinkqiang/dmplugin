# dmplugin 🔌

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmplugin](https://img.shields.io/badge/brinkqiang-dmplugin-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmplugin)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmplugin/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmplugin.svg?label=Stars)](https://github.com/brinkqiang/dmplugin) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmplugin.svg?label=Fork)](https://github.com/brinkqiang/dmplugin)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmplugin/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmplugin/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmplugin/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmplugin/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmplugin/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmplugin/actions/workflows/win.yml "win build status"

## Introduction 🚀

dmplugin is a C++ plugin system that allows for dynamic loading and execution of plugins. It provides a simple interface for creating and managing plugins in C++ applications.

## Features ✨

- Cross-platform support (Windows, Linux, macOS)
- Simple plugin interface
- Dynamic loading of plugins
- C++11/14/17 support
- CMake build system

## Requirements 📋

- CMake 3.21+
- C++11 compatible compiler

## Building 🔨

### Windows
```bash
git clone https://github.com/brinkqiang/dmplugin.git
cd dmplugin
build.bat
```

### Linux/macOS
```bash
git clone https://github.com/brinkqiang/dmplugin.git
cd dmplugin
./build.sh
```

## Usage 📝

### Creating a Plugin

```cpp
#include "dmplugin.h"

class MyPlugin : public IdmPlugin {
public:
    MyPlugin() {}
    virtual ~MyPlugin() {}

    virtual bool Execute(const std::string& command, const std::string& params) {
        // Implement your plugin logic here
        return true;
    }
};

extern "C" DMEXPORT_DLL IdmPlugin* DMAPI CreatePlugin() {
    return new MyPlugin();
}
```

### Loading and Using Plugins

```cpp
// Example code for loading and using plugins
// See loader implementation for details
```

## Dependencies 🔗

- [dmtest](https://github.com/brinkqiang/dmtest) - Testing framework
- [dmformat](https://github.com/brinkqiang/dmformat) - String formatting library

## License 📄

This project is licensed under the [MIT License](LICENSE).

## Contacts 📧

- [brinkqiang](https://github.com/brinkqiang)
- Email: brink.qiang@gmail.com

## Thanks 🙏
