#pragma once
#include "SingletonBase.h"
class TxtData : public SingletonBase<TxtData>
{
public:
	HRESULT init();
	void release();

	// ���̺�
	void txtSave(const char * fileName, vector<string> vStr);
	char * vectorArrayCombine(vector<string> vArray);

	// �ε�
	vector<string> txtLoad(const char * fileName);
	vector<string> charArraySeparation(char charArray[]);

	TxtData() {}
	~TxtData() {}
};

