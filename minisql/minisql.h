#ifndef _MINISQL_H_
#define _MINISQL_H_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include"sqlcommand.h"

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
#define ATTR_SIZE_IN_FILE (sizeof(bool)*4 + sizeof(int)*2 + MAX_CHAR_LENGTH * sizeof(char))/* һ���ֶ����ļ�����ռ�Ĵ�С */
#define TABLEHEAD_SIZE_IN_FILE (sizeof(int))/* һ������Ϣͷ���ļ�����ռ�Ĵ�С */
#define TABLENODE_SIZE_IN_FILE (2 * sizeof(int) + MAX_CHAR_LENGTH * sizeof(char)*2 + MAX_ATTR_NUM * ATTR_SIZE_IN_FILE)/* һ����
��Ϣ�����ļ�����ռ�Ĵ�С */
#define _TYPE_STRING 1
#define _TYPE_INT 0
#define _TYPE_FLOAT -1
//�����ʹ�С
#define TYPE_SIZE \
int typeSize(int type)\
{\
	switch(type) \
	{\
	case _TYPE_FLOAT:return sizeof(float);break;\
	case _TYPE_INT:return sizeof(int);break;\
	case _TYPE_STRING:return sizeof(char[255]);break;\
	}\
}//TODO:��255ô��

//catalog���ص���Ϣ
//������Ϣ
class attribute{
public:
	attribute():PK(false), UN(false), NN(false), ID(false){
	}
	string name;	//����
	int datatype;	//��������
	int length;		//���ݳ���
	bool PK;		//����
	bool UN;		//Ψһ
	bool NN;		//�ǿ�
	bool ID;		//�Ƿ�������
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
		dbname = T.dbname;
		attrNum = T.attrNum;
		recLength = T.recLength;
		attrList = T.attrList;
		recNum = T.recNum;
	}
	table (){}
	string name;					//����
	string dbname;					//�����ĸ����ݿ�
	int attrNum;					//������
	int recLength;					//��¼����
	int recNum;						//��¼����
	int size;						//����
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
	catainfo(){}
	//��ȡָ���Ƿ�ɹ�
	bool getsucc(){
		return succ;	
	}
	//���������Ϣ
	void print(){
		cout<<message<<endl;
	}
	table gettable(){
		return T;
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
//record������Ϣ
//�����Ϣ����������ɣ�ÿһ���ɶ���vector<string> col���
class Row
{
public:
	vector<string> col;//clolumns
};
class Results
{
public:
	vector<Row> row;//rows
};
//record���ص���Ϣ
class recoinfo
{
public:
	recoinfo(bool f, string mes,Results res,long num ){
		succ = f;
		message = mes;
		results=res;
		number=num;
	}
	recoinfo(){};
	//is execution succeed
	bool getsucc(){
		return succ;
	}
	//get the error message
	string errormes(){
		return message;
	}
	//get the reusult
	Results resultsmes(){
		return results;

	}
	//gei the number info of records
	long nummes(){
		return number;
	}
	void print (){
		cout<<message<<endl;
	}
private:
	bool succ;
	string message;
	Results results;
	long number;
};
class indexInfo{
	vector<int> result;
};
#endif