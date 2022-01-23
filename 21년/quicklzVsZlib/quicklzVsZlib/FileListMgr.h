#pragma once
class CFileListMgr
{
public:
	CFileListMgr();
	~CFileListMgr();

	void GetAllFileNames(std::string folderName, std::vector<std::string>& fileList);
};

