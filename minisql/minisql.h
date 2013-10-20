#ifndef _MINISQL_H_
#define _MINISQL_H_
#include "catalog.h"
#include "interpreter.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define SQL_CREATE_DATABASE 10
#define SQL_CREATE_TABLE    11
#define SQL_CREATE_INDEX    12
#define SQL_CREATE_INDEX_ON 13
#define SQL_DROP_DATABASE   20
#define SQL_DROP_TABLE      21
#define SQL_DROP_INDEX      22
#define SQL_SELECT          30
#define SQL_INSERT_INTO     40
#define SQL_DELETE          50
#define SQL_USE             60
#define SQL_QUIT            70
#define SQL_ERROR           90
//catalog���ص���Ϣ
class catainfo{
public:
	bool succ;
	string message;
};

/**
 * class SqlCommand
 * @brief �ڲ���ʽsql����
 */
class SqlCommand {
public:
	//������������
	void setType(int t){
		type = t;
	}
	//�������ݿ���
	void setDatabaseName(string& str){
		databaseName = str;
	}
	//���ñ���
	void setTableName(string& str){
		tableName = str;
	}
	//����������
	void setIndexName(string& str){
		indexName = str;
	}
	//��������
	void setRowName(string& str){
		rowName = str;
	}

	//vector<int> attrListType;
	//vector<string> attrListName;
	//vector<string> attrListValue;
	//push��¼����
	void pushType(int t){
		attrListType.push_back(t);
	}
	//push��¼��
	void pushName(string& str){
		attrListName.push_back(str);
	}
	//push��¼ֵ
	void pushValue(string& str){
		attrListValue.push_back(str);
	}
	//���������Ϣ
	void print(){
		cout<<"type: "<<type<<endl;
		cout<<"tableName: "<<tableName<<endl;
		cout<<"databaseName: "<<databaseName<<endl;
		cout<<"indexName: "<<indexName<<endl;
		cout<<"rowName: "<<rowName<<endl;

		cout<<"attrListType:  ";
		for (int i=0; i<attrListType.size(); i++)
			cout<<attrListType[i]<<" ";
		cout<<endl;
		cout<<"attrListName:  ";
		for (int i=0; i<attrListName.size(); i++)
			cout<<attrListName[i]<<" ";
		cout<<endl;
		cout<<"attrListValue: ";
		for (int i=0; i<attrListValue.size(); i++)
			cout<<attrListValue[i]<<" ";
		cout<<endl;
	}
private:
	// ��������
	int type;

	// ��������
	string tableName;
	string databaseName;
	string indexName;
	string rowName;

	vector<int> attrListType;       // ����/ɾ�������б�� ����������
	vector<string> attrListName;    // ����/ɾ�������б�� ��������
	vector<string> attrListValue;  	// ����/ɾ�������б�� ������ֵ
};
//������Ϣ
class attribute{
	string attr;	//����
	int datatype;	//��������
	bool PK;		//����
	bool UNIQUE;	//Ψһ
	bool NN;		//�ǿ�
}
#endif