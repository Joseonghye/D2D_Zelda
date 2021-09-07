#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ChangeRelativePath(const CString & wstrFilePath)
{
	TCHAR szCurrentPath[MAX_PATH] = {};
	GetCurrentDirectory(MAX_PATH, szCurrentPath);
	TCHAR szRelativePath[MAX_PATH] = {};

	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY, wstrFilePath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
