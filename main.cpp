#include "stdafx.h"
#include "INILoader.h"
#include "ItemLoader.h"

int main()
{
	system("title 장비 사전");

	char szPath[MAX_PATH * 2];
	INILoader kLoader("config/Itembook.ini");
	kLoader.SetTitle("resource");
	kLoader.LoadString("path", "", szPath, sizeof(szPath));
	if (strcmp(szPath, "") == 0)
	{
		cout << "폴더 경로를 제대로 적어주세요." << endl;
		system("pause");
		return 0;
	}

	cout << "아이템 읽는중..." << endl;
	CItemLoader* loader = new CItemLoader(szPath);
	loader->LoadItem();
	loader->LoadExtraItem();
	cout << "아이템 읽기 성공!" << endl << endl;
	string szItemName = "";
	while (true)
	{
		cout << "찾을 아이템명을 입력하세요 : ";
		cin >> szItemName;
		loader->FindItemUseName(szItemName.c_str());
		system("pause");
		system("cls");
	}
	delete loader;
	return 0;
}