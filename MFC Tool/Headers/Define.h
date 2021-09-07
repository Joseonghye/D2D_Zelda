#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 1280
#define WINCY 720
#define PURE = 0
#define VIR_KEY 0xff
#define SAFE_DELETE(p) if(p) {delete p; p=nullptr;}

#define MSG_BOX(text) MessageBox(NULL, text, L"System message", MB_OK); return E_FAIL;
#endif