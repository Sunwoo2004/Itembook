#pragma once

struct ioItem
{
	string m_szName;
	int m_iCode;
};

class CItemLoader
{
private:
	char szItemGroupNum[MAX_PATH];
	char szItemPath[MAX_PATH * 2];
	char szItemTitle[MAX_PATH];
	char szItemName[MAX_PATH * 2];
	string szAbsolutePath;

public:
	void FindItemUseName(const char* szName);

public:
	void LoadItem();
	void LoadExtraItem();
	void Init();

public:
	CItemLoader();
	CItemLoader(string szPath);
	virtual ~CItemLoader();
};