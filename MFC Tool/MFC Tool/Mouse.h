#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__

class Mouse : public CSingleTon<Mouse>
{
	friend CSingleTon;
private:
	Mouse();
public:
	~Mouse();

	inline void SetChkMouse(bool _b) { chkMouse = _b; };
	inline void SetRenderObj(CString _wstrObjKey) { m_wstrObjKey = _wstrObjKey; SetChkMouse(true); };
	void RenderMouse(HWND _pHWnd);
	void ReleaseMouse();
	void RenderObj(HWND _pHWnd,OBJINFO* _obj);

private:
	bool chkMouse;
	CString m_wstrObjKey;
};


#endif // !__MOUSE_H__