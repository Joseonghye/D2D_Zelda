#pragma once

typedef struct obj
{
	OBJID m_eID;
	bool m_bMove;
	bool m_bDestroy;
}OBJINFO;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Initialized_Scene() PURE;
	virtual void Update_Scene() PURE;
	virtual void LateUpdate_Scene() PURE;
	virtual void Render_Scene() PURE;
	virtual void Release_Scene() PURE;

private:
	void LoadGameObjInfo(const wstring & wstrFilePath);
	void CreateMonster(string strName, int index, INFO* pInfo);
	void CreateInteractionObj(string strName, int index, INFO* pInfo, OBJINFO& ObjInfo);

protected:
	void LoadGameObject(const wstring & wstrFilePath);
	void LoadEvent(const wstring & wstrFilePath);

private:
	map<string,OBJINFO> m_mapObjOption;
};