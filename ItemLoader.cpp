#include "stdafx.h"
#include "ItemLoader.h"
#include "INILoader.h"

typedef std::vector< ioItem > ItemList;
ItemList vItemlist;
ItemList vExtraItemlist;

CItemLoader::CItemLoader(string szPath)
{
	Init();
	szAbsolutePath = szPath;
}

CItemLoader::CItemLoader()
{
	Init();
}

CItemLoader::~CItemLoader()
{

}

void CItemLoader::Init()
{
	strcpy(szItemGroupNum, "");
	strcpy(szItemPath, "");
	strcpy(szItemTitle, "");
	strcpy(szItemName, "");
	szAbsolutePath = "";

	vItemlist.clear();
	vExtraItemlist.clear();
}

void CItemLoader::LoadItem()
{
	string szINIPath = szAbsolutePath + "config/sp2_item.ini";
	INILoader kLoader(szINIPath.c_str());
	kLoader.SetTitle("common_info");
	int iCnt = kLoader.LoadInt("item_group_cnt", 0);

	vItemlist.reserve(iCnt);

	for (int i = 0; i < iCnt; i++)
	{
		wsprintf(szItemGroupNum, "item_group%d", i);
		kLoader.LoadString(szItemGroupNum, "", szItemPath, sizeof(szItemPath));

		string szPath = szAbsolutePath + "config/" + (string)szItemPath;

		INILoader kLoader2(szPath.c_str());
		kLoader2.SetTitle("common");
		int item_cnt = kLoader2.LoadInt("item_cnt", 0);
		for (int j = 0; j < item_cnt; j++)
		{
			ioItem item;
			wsprintf(szItemTitle, "item%d", j + 1);
			kLoader2.SetTitle(szItemTitle);
			kLoader2.LoadString("name", "", szItemName, sizeof(szItemName));
			item.m_szName = szItemName;
			item.m_iCode = kLoader2.LoadInt("code", 0);
			vItemlist.push_back(item);
		}
	}
}

void CItemLoader::LoadExtraItem()
{
	string szINIPath = szAbsolutePath + "config/sp2_extraitem.ini";
	INILoader kLoader(szINIPath.c_str());
	kLoader.SetTitle("common_info");
	int iCnt = kLoader.LoadInt("item_group_cnt", 0);

	vExtraItemlist.reserve(iCnt);

	for (int i = 0; i < iCnt; i++)
	{
		wsprintf(szItemGroupNum, "item_group%d", i);
		kLoader.LoadString(szItemGroupNum, "", szItemPath, sizeof(szItemPath));

		string szPath = szAbsolutePath + "config/" + (string)szItemPath;

		INILoader kLoader2(szPath.c_str());
		kLoader2.SetTitle("common");
		int item_cnt = kLoader2.LoadInt("item_cnt", 0);
		for (int j = 0; j < item_cnt; j++)
		{
			ioItem item = { "",0 };
			wsprintf(szItemTitle, "item%d", j + 1);
			kLoader2.SetTitle(szItemTitle);
			kLoader2.LoadString("name", "", szItemName, sizeof(szItemName));
			item.m_szName = szItemName;
			item.m_iCode = kLoader2.LoadInt("code", 0);
			vExtraItemlist.push_back(item);
		}
	}
}

void CItemLoader::FindItemUseName(const char* szName)
{
	int iCount = 0;

	int iCnt = vItemlist.size();
	for (int i = 0; i < iCnt; i++)
	{
		const ioItem& rkItem = vItemlist[i];
		if (rkItem.m_szName.find(szName) != string::npos)
		{
			cout << "Name : " << rkItem.m_szName << ", Code : " << rkItem.m_iCode << endl;
			iCount++;
		}
	}

	int iCnt2 = vExtraItemlist.size();
	for (int i = 0; i < iCnt2; i++)
	{
		const ioItem& rkItem = vExtraItemlist[i];
		if (rkItem.m_szName.find(szName) != string::npos)
		{
			cout << "Name : " << rkItem.m_szName << ", Code : " << rkItem.m_iCode << endl;
			iCount++;
		}
	}

	if (iCount == 0)
	{
		cout << "아이템이 존재하지 않습니다." << endl;
	}
	else
	{
		cout << "아이템 " << iCount << "개 찾음." << endl;
	}
}