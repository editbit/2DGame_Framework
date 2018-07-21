#include "stdafx.h"
#include "TxtData.h"

HRESULT TxtData::init()
{
	return S_OK;
}

void TxtData::release()
{
}

// 세이브
void TxtData::txtSave(const char * fileName, vector<string> vStr)
{
	HANDLE hFile;
	DWORD write;
	char str[128];
	ZeroMemory(str, sizeof(str));

	strcpy(str, vectorArrayCombine(vStr));

	hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, str, sizeof(str), &write, NULL);

	CloseHandle(hFile);
}

char * TxtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(128));

	for (int i = 0; i < vArray.size(); ++i)
	{
		strcat(str, vArray[i].c_str());
		if (i + 1 < vArray.size())
		{
			strcat(str, ",");
		}
	}

	return str;
}

// 로드
vector<string> TxtData::txtLoad(const char * fileName)
{
	HANDLE hFile;
	DWORD read;
	char str[128];
	ZeroMemory(str, sizeof(str));


	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, str, sizeof(str), &read, NULL);

	CloseHandle(hFile);
	return charArraySeparation(str);
}

vector<string> TxtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	const char * separation = ",";
	char * token;

	token = strtok(charArray, separation);
	while (NULL != token)
	{
		vArray.push_back(token);
		token = strtok(charArray, separation);
	}

	return vArray;
}
