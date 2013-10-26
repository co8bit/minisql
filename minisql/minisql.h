#ifndef _MINISQL_H_
#define _MINISQL_H_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define MAX_CHAR_LENGTH 32
//catalog���ص���Ϣ
class catainfo{
public:
	//Ctor
	catainfo(bool f, string mes){
		succ = f;
		message = mes;
	}
	//��ȡָ���Ƿ�ɹ�
	bool getsucc(){
		return succ;	
	}
	//���������Ϣ
	void print(){
		cout<<message<<endl;
	}
private:
	bool succ;
	string message;

};

//������Ϣ
class attribute{
public:
	string name;	//����
	int datatype;	//��������
	int length;		//���ݳ���
	bool PK;		//����
	bool UN;		//Ψһ
	bool NN;		//�ǿ�
};

class table{
public:
	string name;					//����
	int attrNum;					//������
	int recLength;					//��¼����
	vector<attribute> attrList;		//�����б�
};

class tableNum{
public:
	tableNum(){}
	tableNum(int n){
		num = n;
	}
	int num;
};
#endif