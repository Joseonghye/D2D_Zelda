#include "stdafx.h"
#include "KeyMgr.h"


CKeyMgr::CKeyMgr()
	:m_dwKey(0), m_dwKeyDown(0), m_dwKeyUp(0) {}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Update_KeyMgr()
{
	m_dwKey = 0;
	//0000 0001
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;

	//0000 0011
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_dwKey |= KEY_CTRL;

	if (GetAsyncKeyState(VK_MENU) & 0x8000)
		m_dwKey |= KEY_ALT;
}

bool CKeyMgr::Key_Up(DWORD dwKey)
{
	//0000 0011 m_dwKey
	//0000 0001 dwKey

	if (dwKey & m_dwKey)
	{
		m_dwKeyUp |= dwKey;
		return FALSE;
	}
	else if (m_dwKeyUp & dwKey)
	{
		// 0000 0011
		// 0000 0001
		// 0000 0010
		m_dwKeyUp ^= dwKey;
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Down(DWORD dwKey)
{
	if (m_dwKey & dwKey && !(m_dwKeyDown & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	else if (!(m_dwKey & dwKey) && (m_dwKeyDown & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}
	return false;
}

bool CKeyMgr::Key_Pressing(DWORD dwKey)
{
	if (m_dwKey & dwKey)
		return true;

	return false;
}
