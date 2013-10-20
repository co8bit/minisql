/**
 * @file interpreter.h
 * @brief ������ģ��ͷ�ļ�
 * @author tgmerge
 * ����������ȡ�����SQL��䣬����������ȷ�ԣ�ת���������Ϊ�ڲ���ʽ��
 * �Ժ��д������䣬��ʾ������Ϣ��
 */

#if !defined(_INTERPRETER_H_)
#define _INTERPRETER_H_

#define SQL_CREATE_DATABASE 10
#define SQL_CREATE_TABLE    11
#define SQL_CREATE_INDEX    12
#define SQL_DROP_DATABASE   20
#define SQL_DROP_TABLE      21
#define SQL_DROP_INDEX      22
#define SQL_SELECT          30
#define SQL_INSERT_INTO     40
#define SQL_DELETE          50
#define SQL_USE             60
#define SQL_QUIT            70
#define SQL_ERROR           90

//#include "Minisql.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

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

/**
 * classs Interpreter
 * @brief ������
 */
class Interpreter {

public:

public: // �����
	string readInput();                     // ��ȡ����
	SqlCommand getExpression(string input); // ��ȡ�ڲ���ʽ����

public: // �ַ�������
	string firstWord(string& str, string split);    // ��ȡ�ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string delFirstWord(string& str, string split); // ɾ���ַ����ĵ�һ�����ʣ��ָ����Զ��壩

public: // ������
	SqlCommand createDatabase(string& str);// ���CREATE DATABASE databaseName
	SqlCommand createTable(string& str);   // ���CREATE TABLE tableName(rowName type, ..., PRIMARY KEY(primaryRowName))
	SqlCommand createIndex(string& str);   // ���CREATE INDEX indexName ON tableName(rowName)

	SqlCommand dropDatabase(string& str);  // ���DROP DATABASE databaseName
	SqlCommand dropTable(string& str);     // ���DROP TABLE tableName
	SqlCommand dropIndex(string& str);     // ���DROP INDEX indexName

	SqlCommand selectClause();             // ���SELECT rowName FROM tableName WHERE condRow condOp condValue

	SqlCommand insertIntoValues();         // ���INSERT INTO tableName VALUES(insertValueList)

	SqlCommand deleteFromWhere();          // ���DELETE FROM tableName WHERE condRow condOp condValue

	SqlCommand useClause(string& str);     // ���USE databaseName

	SqlCommand quitClause();               // ���QUIT
};

#endif