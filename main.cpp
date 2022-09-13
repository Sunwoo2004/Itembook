#include "stdafx.h"
#include "INILoader.h"
#include "ItemLoader.h"

int main()
{
	system("title ��� ����");

	char szPath[MAX_PATH * 2];
	INILoader kLoader("config/Itembook.ini");
	kLoader.SetTitle("resource");
	kLoader.LoadString("path", "", szPath, sizeof(szPath));
	if (strcmp(szPath, "") == 0)
	{
		cout << "���� ��θ� ����� �����ּ���." << endl;
		system("pause");
		return 0;
	}

	cout << "������ �д���..." << endl;
	CItemLoader* loader = new CItemLoader(szPath);
	loader->LoadItem();
	loader->LoadExtraItem();
	cout << "������ �б� ����!" << endl << endl;
	string szItemName = "";
	while (true)
	{
		cout << "ã�� �����۸��� �Է��ϼ��� : ";
		cin >> szItemName;
		loader->FindItemUseName(szItemName.c_str());
		system("pause");
		system("cls");
	}
	delete loader;
	return 0;
}