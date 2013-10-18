/**
 * @file interpreter.h
 * @brief ������ģ��ͷ�ļ�
 * @author tgmerge
 * ����������ȡ�����SQL��䣬����������ȷ�ԣ�ת���������Ϊ�ڲ���ʽ��
 * �Ժ��д������䣬��ʾ������Ϣ��
 */

#if !defined(_INTERPRETER_H_)
#define _INTERPRETER_H_

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

	// ����/ɾ�������б�� ����������
	vector<int> attrListType;
	// ����/ɾ�������б�� ��������
	vector<string> attrListName;
	// ����/ɾ�������б�� ������ֵ
	vector<string> attrListValue;
};

/**
 * classs Interpreter
 * @brief ������
 */
class Interpreter {

public:
	// ����
	Interpreter();
	// ��ȡ����
	string readInput();
	// ��ȡ�ڲ���ʽ����
	SqlCommand getExpression(string input);
	// ��ȡ�ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string firstWord(string& str, string split);
	// ɾ���ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string delFirstWord(string& str, string split);



public:
	// ��ȡ�ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string firstWord(string& str, string& split);
	// ɾ���ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string delFirstWord(string& str, string& split);

	// ���CREATE	type = 1
	SqlCommand createClause();
	// ���CREATE DATABASE databaseName	type = 2
	SqlCommand createDatabase();
	// ���CREATE TABLE tableName(rowName type, ..., PRIMARY KEY(primaryRowName))	type = 3
	SqlCommand createTable();
	// ���CREATE INDEX indexName	type = 4
	SqlCommand createIndex();
	// ���CREATE INDEX indexName ON tableName(rowName)	type = 5
	SqlCommand createIndexOn();
	
	// ���DROP	type = 6
	SqlCommand dropClause();
	// ���DROP DATABASE databaseName	type = 7
	SqlCommand dropDatabase(string& str);
	// ���DROP TABLE tableName	type = 8
	SqlCommand dropTable(string& str);
	// ���DROP INDEX indexName	type = 9
	SqlCommand dropIndex();

	// ���SELECT rowName FROM tableName WHERE condRow condOp condValue	type = 10
	SqlCommand selectClause();

	// ���INSERT INTO tableName VALUES(insertValueList)
	SqlCommand insertClause();
	SqlCommand insertIntoValues();
	
	// ���DELETE
	SqlCommand deleteClause();
	// ���DELETE FROM tableName WHERE condRow condOp condValue
	SqlCommand deleteFromWhere();

	// ���USE databaseName
	SqlCommand useClause();
	//
	SqlCommand execfileClause();

	// ���QUIT
	SqlCommand quitClause();
};

#endif