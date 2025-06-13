
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMPLUGIN_H_INCLUDE__
#define __DMPLUGIN_H_INCLUDE__

#include "dmos.h" // dmos.h已经处理平台头文件, 以及相关宏定义
#include "dmfix_win_utf8.h" // 处理 win平台utf8问题
#include "dmmoduleptr.h"

class Idmplugin;

typedef DmModulePtr<Idmplugin> dmpluginPtr;

class Idmplugin
{
public:
    virtual ~Idmplugin(){}
    virtual void DMAPI Release(void) = 0;
	
    virtual void DMAPI Test(void) = 0;
};

extern "C" DMEXPORT_DLL Idmplugin* DMAPI dmpluginGetModule();

typedef Idmplugin* (DMAPI* PFN_dmpluginGetModule)();
#endif // __DMPLUGIN_H_INCLUDE__