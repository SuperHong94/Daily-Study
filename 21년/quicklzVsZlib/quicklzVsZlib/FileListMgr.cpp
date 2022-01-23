#include <Windows.h>
#include <vector>
#include <string>
#include "FileListMgr.h"

CFileListMgr::CFileListMgr()
{
}

CFileListMgr::~CFileListMgr()
{
}

void CFileListMgr::GetAllFileNames(std::string folderName, std::vector<std::string>& fileList)
{
	std::string searchFolder = folderName + "\\*.*";
	WIN32_FIND_DATAA findData;

	HANDLE hFind = FindFirstFileA(searchFolder.c_str(), &findData); //(ã�� ����, �Լ��� ���)
	if (INVALID_HANDLE_VALUE == hFind) return; //�ƹ��͵� ��ã��
	
	std::string filePath;
	do {
		if (0 == strcmpi(findData.cFileName, ".") || 0 == strcmpi(findData.cFileName, "..")) 
			continue;
		filePath = folderName + '\\' + findData.cFileName;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {//ã�������� �����̸�
			GetAllFileNames(filePath, fileList);
			continue;
		}
		fileList.emplace_back(filePath);

	} while (FindNextFileA(hFind, &findData));
}
