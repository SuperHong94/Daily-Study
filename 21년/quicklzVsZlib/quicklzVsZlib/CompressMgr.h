#pragma once

class CCommand 
{
public:
	virtual ~CCommand() {};
	virtual void Compress(const char* filename) = 0;
};

class CZlibCompress :public CCommand
{

public:
	virtual void Compress(const char* filename) override;
};

class CCompressMgr
{
private:
	CCommand* zlibCompress;
	CCommand* quickLZCompress;

public:
	CCompressMgr();
	~CCompressMgr();
	void Compress(char c,const char* filename);
};

