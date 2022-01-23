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

	HANDLE hFind = FindFirstFileA(searchFolder.c_str(), &findData); //(찾을 파일, 함수의 결과)
	if (INVALID_HANDLE_VALUE == hFind) return; //아무것도 못찾음
	
	std::string filePath;
	do {
		if (0 == strcmpi(findData.cFileName, ".") || 0 == strcmpi(findData.cFileName, "..")) 
			continue;
		filePath = folderName + '\\' + findData.cFileName;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {//찾은파일이 폴더이면
			GetAllFileNames(filePath, fileList);
			continue;
		}
		fileList.emplace_back(filePath);

	} while (FindNextFileA(hFind, &findData));
}
