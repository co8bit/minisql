/**
 * @file interpreter.h
 * @brief ������ģ��ͷ�ļ�
 * @author tgmerge
 * ����������ȡ�����SQL��䣬����������ȷ�ԣ�ת���������Ϊ�ڲ���ʽ��
 * �Ժ��д������䣬��ʾ������Ϣ��
 */

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "sqlcommand.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/**
 * classs Interpreter
 * @brief ������
 */
class Interpreter {

public: // �����
	string readInput();                     // ��ȡ����
	SqlCommand getExpression(string input); // ��ȡ�ڲ���ʽ����

public: // �ַ�������
	string firstWord(string& str, string split);    // ��ȡ�ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string delFirstWord(string& str, string split); // ɾ���ַ����ĵ�һ�����ʣ��ָ����Զ��壩
	string preProcess(string& str); // Ԥ����ȥ������ո��
	string& Interpreter::replaceAll(string& str,const string& old_value,const string& new_value); // �ַ����滻

public: // ������
	SqlCommand createDatabase(string& str);  // ���CREATE DATABASE databaseName
	SqlCommand showDatabase(string& str);
	// TODO: createTableδ���
	SqlCommand createTable(string& str);     // ���CREATE TABLE tableName(colName type, ..., PRIMARY KEY(primarycolName))
	SqlCommand createIndex(string& str);     // ���CREATE INDEX indexName ON tableName(colName)
										     
	SqlCommand dropDatabase(string& str);    // ���DROP DATABASE databaseName
	SqlCommand dropTable(string& str);       // ���DROP TABLE tableName
	SqlCommand dropIndex(string& str);       // ���DROP INDEX indexName
										     
	SqlCommand selectClause(string& str);    // ���SELECT colName FROM tableName WHERE condcol condOp condValue

	SqlCommand insertIntoValues(string& str);// ���INSERT INTO tableName VALUES(insertValueList)

	SqlCommand deleteFromWhere(string& str); // ���DELETE FROM tableName WHERE condcol condOp condValue

	SqlCommand useClause(string& str);       // ���USE databaseName

	SqlCommand quitClause();                 // ���QUIT
};

#endif