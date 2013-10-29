#ifndef _MINISQL_H_
#define _MINISQL_H_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

#define MAX_FILENAME_LENGTH 256     /* ��ļ������� */
#define MAX_CMD_LENGTH      256     /* ������ */
#define MAX_ATTRNAME_LENGTH 256     /* ��ֶγ��� */
#define MAX_RECORD_LENGTH   256     /* ���¼���� */
#define MAX_ATTR_NUM        32      /* һ�������ֶ���Ŀ */
#define MAX_CHAR_LENGTH 32
#define FILE_PAGESIZE 4096          /* ����ҳ��С */
#define MEM_MAXPAGE 1000            /* �ڴ�ҳ�����Ŀ */
#define FILENAME_MAXLEN 256         /* �ļ�����󳤶� */
#define MAX_CHAR_LENGTH     32      /* ��� CHAR �����ֶγ��� */
#define IDXHEAD_SIZE_IN_FILE (ATTR_SIZE_IN_FILE + sizeof(int))/* һ������ͷ���ļ�����ռ�Ĵ�С */
#define IDXNODE_SIZE_IN_FILE (sizeof(unsigned) + MAX_CHAR_LENGTH * sizeof(char)) /* һ�������ڵ����ļ�����ռ�Ĵ�С */
#define ATTR_SIZE_IN_FILE (sizeof(bool) + sizeof(int) + sizeof(int) + MAX_CHAR_LENGTH * sizeof(char))/* һ���ֶ����ļ�����ռ�Ĵ�С */
#define TABLEHEAD_SIZE_IN_FILE (sizeof(int))/* һ������Ϣͷ���ļ�����ռ�Ĵ�С */
#define TABLENODE_SIZE_IN_FILE (2 * sizeof(int) + MAX_CHAR_LENGTH * sizeof(char) + MAX_ATTR_NUM * ATTR_SIZE_IN_FILE)/* һ������Ϣ�����ļ�����ռ�Ĵ�С */
//catalog���ص���Ϣ
//������Ϣ
class attribute{
public:
	string name;	//����
	int datatype;	//��������
	int length;		//���ݳ���
	bool PK;		//����
	bool UN;		//Ψһ
	bool NN;		//�ǿ�
	string typeName(){
		if (datatype == 0)
			return "Integer";
		if (datatype == -1)
			return "Float";
		stringstream ss;
		ss<<datatype;
		return "Char(" + ss.str() + ")";
	}
};
class table{
public:
	table (const table& T){
		name = T.name;
		attrNum = T.attrNum;
		recLength = T.recLength;
		attrList = T.attrList;
	}
	table (){}
	string name;					//����
	int attrNum;					//������
	int recLength;					//��¼����
	vector<attribute> attrList;		//�����б�
};
class catainfo{
public:
	//Ctor
	catainfo(bool f, string mes, table tab){
		succ = f;
		message = mes;
		T = tab;
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
	table T;

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