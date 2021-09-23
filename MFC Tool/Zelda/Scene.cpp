#include "stdafx.h"
#include "Scene.h"
#include "HardHat.h"
#include "Weed.h"
#include "BlackStone.h"
#include "Enter.h"
#include "GameButton.h"
#include "Check.h"

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
	
		size_t tcnt;
		wcstombs_s(&tcnt, szName, 2 * len + 1 * sizeof(char), (wchar_t*)pStr, 100);
		string str = szName;

		delete[] pStr;
		pStr = nullptr;
		delete[] szName;
		szName = nullptr;

		m_mapObjOption.emplace(str,tInfo);
	}

	delete[] pStr;
	pStr = nullptr;

	CloseHandle(hFile);
}

void CScene::CreateMonster(string strName,int index, INFO* pInfo)
{
	CGameObject* pGameObj = nullptr;
	if ("HardHat" == strName) 
	{
		pGameObj = CHardHat::Create();
	}
	
	if (pGameObj != nullptr) 
	{
		pGameObj->SetRoomIndex(index);
		pGameObj->SetInfo(*pInfo);
		pGameObj->SetTransMat();
		pGameObj->SetWorldMat();
		GAMEOBJECTMGR->Add_GameObject(MONSTER, pGameObj);
	}
}

void CScene::CreateInteractionObj(string strName,int index, INFO * pInfo)
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
		pGameObj->SetRoomIndex(index);
		pGameObj->SetInfo(*pInfo);
		pGameObj->SetTransMat();
		pGameObj->SetWorldMat();
		GAMEOBJECTMGR->Add_GameObject(INTERACTION, pGameObj);
	}
}

void CScene::CreateEnter(string strName, int index, INFO * pInfo)
{
	CGameObject* pGameObj = CEnter::Create();

	if ("Up" == strName) {
		pInfo->eDir = DIR::BACK;
		pInfo->vPos.y -= 8.f;
	}
	else if ("Down" == strName) {
		pInfo->eDir = DIR::FRONT;
		pInfo->vPos.y += 8.f;
	}else if ("Left" == strName){
		pInfo->eDir = DIR::LEFT;
		pInfo->vPos.x -= 8.f;
	}else if ("Right" == strName) {
		pInfo->eDir = DIR::RIGHT;
		pInfo->vPos.x += 8.f;
	}
	pGameObj->SetRoomIndex(index);
	pGameObj->SetInfo(*pInfo);
	pGameObj->SetTransMat();
	pGameObj->SetWorldMat();

	GAMEOBJECTMGR->Add_GameObject(ENTER, pGameObj);
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
	int index = 0;
	while (true)
	{
		ReadFile(hFile, &index, sizeof(int), &dwByte, nullptr);

		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
		pStr = new TCHAR[dwStrByte];
		ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);

		pInfo = new INFO;
		ReadFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pInfo);

			delete[] pStr;
			pStr = nullptr;

			break;
		}

		int len = wcslen((wchar_t*)pStr);
		char* szName = new char[2 * len + 1];

		size_t tcnt;
		wcstombs_s(&tcnt, szName, 2 * len + 1 *sizeof(char), (wchar_t*)pStr, 100);

		int iRoomIndex = -1;
		if (index != -1)
		{
			int y = index / (TOTAL_TILEX*ROOM_TILEX);
			int x = index - ((TOTAL_TILEX*ROOM_TILEX)*y);

			int totalY = y / ROOM_TILEY;
			int totalX = x / ROOM_TILEX;
			iRoomIndex = totalX + (TOTAL_TILEX *totalY);
		}

		string str = szName;
		auto& iter = m_mapObjOption.find(str);
		if (iter != m_mapObjOption.end()) {
			switch (iter->second.m_eID)
			{
			case MONSTER:
				CreateMonster(str, iRoomIndex, pInfo);
				break;
			case INTERACTION:
				CreateInteractionObj(str, iRoomIndex, pInfo);
				break;
			case ENTER:
				CreateEnter(str, iRoomIndex, pInfo);
				break;
			}
		}
		else
		{
			MessageBox(NULL, L"ERR:: Scene::NO OBJ INFO", L"System message", MB_OK);
			//오브젝트 인포가 없어!!
		}

		delete[] szName;
		delete[] pStr;
		pStr = nullptr;
		szName = nullptr;
		Safe_Delete(pInfo);
	}

	CloseHandle(hFile);

}

void CScene::LoadEvent(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	DWORD dwStrByte = 0;

	char* pStr = nullptr;
	int index = 0;

	while (true)
	{
		ReadFile(hFile, &index, sizeof(int), &dwByte, nullptr);

		int iEventID = -1;
		ReadFile(hFile, &iEventID, sizeof(int), &dwByte, nullptr);

		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
		pStr = new char[dwStrByte];
		ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);

		D3DXVECTOR3 vPos;
		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
	
		if (0 == dwByte)
		{
			delete[] pStr;
			pStr = nullptr;
			break;
		}

		int iRoomIndex = -1;
		if (index != -1)
		{
			int y = index / (TOTAL_TILEX*ROOM_TILEX);
			int x = index - ((TOTAL_TILEX*ROOM_TILEX)*y);

			int totalY = y / ROOM_TILEY;
			int totalX = x / ROOM_TILEX;
			iRoomIndex = totalX + (TOTAL_TILEX *totalY);
		}

		CGameObject* pGameObj = nullptr;
		
		//EVENTID로 어떤 오브젝트인지 
		switch (iEventID)
		{
		case EVENT::BUTTON:
			pGameObj = CGameButton::Create(pStr);
			pGameObj->SetRoomIndex(iRoomIndex);

			pGameObj->SetPos(vPos);
			pGameObj->SetTransMat();
			pGameObj->SetWorldMat();
			break;
		case EVENT::CHECK:
			pGameObj = CCheck::Create(pStr);
			pGameObj->SetRoomIndex(iRoomIndex);
			static_cast<CCheck*>(pGameObj)->SetMonsterCount();
			pGameObj->SetPos(vPos);
			break;
	
		case EVENT::OPEN:
			break;
		case EVENT::CLOSE:
			break;
		}

		GAMEOBJECTMGR->Add_GameObject(EVENT, pGameObj);

		delete[] pStr;
		pStr = nullptr;
	}
	CloseHandle(hFile);

}
