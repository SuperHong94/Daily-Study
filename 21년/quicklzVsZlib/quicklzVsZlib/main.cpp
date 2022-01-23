#include <iostream>
#include <vector>
#include "FileListMgr.h"
#include "CompressMgr.h"

int main()
{
	CFileListMgr fileListMgr;

	std::string folderName = "C:\\Users\\SuperHong\\Documents\\GitHub\\Daily-Study\\21년\\Zlib\\zlib1211";
	std::vector<std::string> filelist;

	fileListMgr.GetAllFileNames(folderName, filelist);

	for (const auto& name : filelist)
	{
		std::cout << name << '\n';
	}

	std::cout << "총 파일의 개수 :" << filelist.size() << '\n';

	CCompressMgr CCompressMgr;
	CCompressMgr.Compress('z', filelist[0].c_str());
}