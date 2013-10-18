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



private:
	// ��ȡ�ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string firstWord(string& str, string& split);
	// ɾ���ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string delFirstWord(string& str, string& split);

	// ���CREATE
	SqlCommand createClause();
	// ���CREATE DATABASE databaseName
	SqlCommand createDatabase();
	// ���CREATE TABLE tableName(rowName type, ..., PRIMARY KEY(primaryRowName))
	SqlCommand createTable();
	// ���CREATE INDEX indexName
	SqlCommand createIndex();
	// ���CREATE INDEX indexName ON tableName(rowName)
	SqlCommand createIndexOn();
	
	// ���DROP
	SqlCommand dropClause();
	// ���DROP DATABASE databaseName
	SqlCommand dropDatabase();
	// ���DROP TABLE tableName
	SqlCommand dropTable();
	// ���DROP INDEX indexName
	SqlCommand dropIndex();

	// ���SELECT rowName FROM tableName WHERE condRow condOp condValue
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