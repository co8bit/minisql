/**
 * @file interpreter.h
 * @brief ������ģ��
 * @author tgmerge
 * ����������ȡ�����SQL��䣬����������ȷ�ԣ�ת���������Ϊ�ڲ���ʽ��
 * �Ժ��д������䣬��ʾ������Ϣ��
 */

#if !defined(_INTERPRETER_H_)
#define _INTERPRETER_H_

#include "Minisql.h"
#include <string>

using std::string;

/**
 * classs Interpreter
 * @brief ������
 */
class Interpreter {

public:
	// ����
	Interpreter();
	// ��ȡ����
	read_input(string& input);

private:
	// ���CREATE
	CString create_clause();
	// ���CREATE DATABASE databaseName
	CString create_database();
	// ���CREATE TABLE tableName(rowName type, ..., PRIMARY KEY(primaryRowName))
	CString create_table();
	// ���CREATE INDEX indexName
	CString create_index();
	// ���CREATE INDEX indexName ON tableName(rowName)
	CString create_index_on();
	
	// ���DROP
	CString drop_clause();
	// ���DROP DATABASE databaseName
	CString drop_database();
	// ���DROP TABLE tableName
	CString drop_table();
	// ���DROP INDEX indexName
	CString drop_index();

	// ���SELECT rowName FROM tableName WHERE condRow condOp condValue
	CString select_clause();

	// ���INSERT INTO tableName VALUES(insertValueList)
	CString insert_clause();
	CString insert_into_values();
	
	// ���DELETE
	CString delete_clause();
	// ���DELETE FROM tableName WHERE condRow condOp condValue
	CString delete_from_where();


	CString use_clause();
	CString execfile_clause();
	CString quit_clause();

	CString get_expression();
	CString get_each();

	CString get_attribute();
	CString get_part();
}

/**
 * class SqlCommand
 * @brief �ڲ���ʽsql����
 */
class SqlCommand {
public:
	
private:
	// ��������
	enum type;
	string tableName;
	string databaseName;
	string indexName;
	string rowName;
	// SELECT����ʹ��
	enum condition;
	string 

#endif