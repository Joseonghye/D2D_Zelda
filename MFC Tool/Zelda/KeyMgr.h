#pragma once
#ifndef __KEYMGR_H__
#define __KEYMGR_H__
#include "SingleTon.h"

//					0000 0001
#define KEY_LBUTTON 0x00000001
//					0000 0010
#define KEY_RBUTTON 0x00000002
//					0000 0100
#define KEY_SPACE	0x00000004
#define KEY_LEFT	0x00000008
#define KEY_RIGHT	0x00000010
#define KEY_UP		0x00000020
#define KEY_DOWN	0x00000040

#define KEY_CTRL	0x00000080
#define KEY_Z		0x00000100
#define KEY_X		0x00000200
#define KEY_Q		0x00000400

class CKeyMgr: public CSingleTon<CKeyMgr>
{
	friend CSingleTon;
private:
	CKeyMgr();
	~CKeyMgr();

public:
	void Update_KeyMgr();
	bool Key_Up(DWORD dwKey);
	bool Key_Down(DWORD dwKey);
	bool Key_Pressing(DWORD dwKey);

private:
	DWORD m_dwKey;
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUp;
};

#endif // !__KEYMGR_H__