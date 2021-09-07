#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ChangeRelativePath(const CString& wstrFilePath);
};

