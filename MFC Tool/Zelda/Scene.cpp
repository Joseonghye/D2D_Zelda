#include "stdafx.h"
#include "Scene.h"
#include "HardHat.h"
#include "Weed.h"
#include "BlackStone.h"

CScene::CScene()
{
	if(m_mapObjOption.empty())
		LoadGameObjInfo(L"../Data/Obj/ObjInfo.dat");
}


CScene::~CScene()
{
	m_mapObjOption.clear();
}

void CScene::LoadGameObjInfo(const wstring & wstrFilePath)
{
	//오브젝트 리스트 데이터 불러오기 
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	DWORD dwStrByte = 0;
	TCHAR* pStr = nullptr;

	OBJINFO tInfo;
	while (true)
	{
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
		pStr = new TCHAR[dwStrByte];
		ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
	
		ReadFile(hFile, &tInfo.m_eID, sizeof(OBJID), &dwByte, nullptr);

		ReadFile(hFile, &tInfo.m_bMove, sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &tInfo.m_bDestroy, sizeof(bool), &dwByte, nullptr);
		
		if (0 == dwByte)
			break;

		int len = wcslen((wchar_t*)pStr);
		char* szName = new char[2 * len + 1];
		//	wcstombs(szName, (wchar_t*)pStr, 2 * len + 1);
		size_t tcnt;
		wcstombs_s(&tcnt, szName, 2 * len + 1 * sizeof(char), (wchar_t*)pStr, 100);

		string str = szName;

		delete[] szName;
		delete[] pStr;
		pStr = nullptr;

		m_mapObjOption.emplace(str,tInfo);
	}
	CloseHandle(hFile);
}

void CScene::CreateMonster(string strName,INFO* pInfo)
{
	CGameObject* pGameObj = nullptr;
	if ("HardHat" == strName) 
	{
		pGameObj = CHardHat::Create();
	}
	
	if (pGameObj != nullptr) 
	{
		pGameObj->SetInfo(*pInfo);
		GAMEOBJECTMGR->Add_GameObject(MONSTER, pGameObj);
	}
}

void CScene::CreateInteractionObj(string strName, INFO * pInfo, bool bMove)
{
	CGameObject* pGameObj = nullptr;
	if ("Weed" == strName)
	{
		pGameObj = CWeed::Create();
	}
	else if ("BlackStone" == strName)
	{
		pGameObj = CBlackStone::Create();
	}

	if (pGameObj != nullptr) 
	{
		pGameObj->SetInfo(*pInfo);
		GAMEOBJECTMGR->Add_GameObject(INTERACTION, pGameObj);
	}
}

void CScene::LoadGameObject(const wstring & wstrFilePath)
{
	// 오브젝트 설치 데이터 불러오기
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	DWORD dwStrByte = 0;

	TCHAR* pStr = nullptr;
	INFO* pInfo = nullptr;

	while (true)
	{
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
		pStr = new TCHAR[dwStrByte];
		ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);

		pInfo = new INFO;
		ReadFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pInfo);
			break;
		}

		int len = wcslen((wchar_t*)pStr);
		char* szName = new char[2 * len + 1];
	//	wcstombs(szName, (wchar_t*)pStr, 2 * len + 1);
		size_t tcnt;
		wcstombs_s(&tcnt, szName, 2 * len + 1 *sizeof(char), (wchar_t*)pStr, 100);

		string str = szName;
		auto& iter = m_mapObjOption.find(str);
		if (iter != m_mapObjOption.end()) {
			if (iter->second.m_eID == MONSTER)
			{
				CreateMonster(str, pInfo);
			}
			else
			{
				//몬스터가 아닌 오브젝트 
				CreateInteractionObj(str, pInfo,false);
			}
		}
		else
		{
			//오브젝트 인포가 없어!!
		}

		delete[] szName;
		delete[] pStr;
		pStr = nullptr;
	}
	CloseHandle(hFile);

}
