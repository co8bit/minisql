#ifndef _MINISQL_H_
#define _MINISQL_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//catalog���ص���Ϣ
class catainfo{
public:
	bool succ;
	string message;
};

//������Ϣ
class attribute{
	string attr;	//����
	int datatype;	//��������
	bool PK;		//����
	bool UNIQUE;	//Ψһ
	bool NN;		//�ǿ�
};

#endif