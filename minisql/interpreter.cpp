/**
 * @file  interpreter.cpp
 * @brief ��������ʵ��
 *
   �������
   cin:    "drop table    tableA;"
   |  readInput();  ���ʵȸ�ʽ����
   v
   string: "drop table tableA ;"
   |  getExpression();  ��ȡSqlCommand���м�����dropTable();
   v
   SqlCommand ����������Ϣ������API
   
 */
#include "interpreter.h"
#include <cstring>
using namespace std;

string delFirstWord(string& str, string split) {
	int start   = str.find_first_not_of(split);
	    start   = str.find_first_of(split, start);
		start   = str.find_first_not_of(split, start);
	return str.substr(start);
}
string firstWord(string& str, string split) {
	int start   = str.find_first_not_of(split);
	int end     = str.find_first_of(split, start);
	return str.substr(start, end-start);
}

/**
 * @brief  ȡ�ַ����ĵ�һ������
 * @author tgmerge
 * @param  string& Ҫ����Ĵ�
 *         string  �ָ���
 * @return string  ��һ������
 */
string Interpreter::firstWord(string& str, string split) {
	int start   = str.find_first_not_of(split);
	int end     = str.find_first_of(split, start);
	return str.substr(start, end-start);
}

/**
 * @brief  ɾ���ַ����ĵ�һ������
 * @author tgmerge
 * @param  string& Ҫ����Ĵ�
 *         string  �ָ���
 * @return string  ʣ�µ��ַ���
 */
string Interpreter::delFirstWord(string& str, string split) {
	int start   = str.find_first_not_of(split);
	    start   = str.find_first_of(split, start);
		start   = str.find_first_not_of(split, start);
	return str.substr(start);
}

/**
 * @brief  ���û���ȡ���룬ɾ������ո�
 * @author tgmerge
 * @return �������ַ���
 */
string Interpreter::readInput() {
	string sql("");
	string temp("");
	bool fin = false;

	while( !fin ) {
		cin >> temp;
		sql += temp + " ";
		if( sql.at(sql.length()-2) == ';' ) {
			sql = sql.substr(0, sql.length()-2);
			sql += " ;";
			fin = true;
		}
	}

	return sql;
}

SqlCommand Interpreter::dropDatabase(string& str) {
	SqlCommand sql;
	string name;
	sql.setType(SQL_DROP_DATABASE);
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");
	name = firstWord(str, " ;");
	sql.setDatabaseName(name);
	return sql;
}

SqlCommand Interpreter::dropTable(string& str) {
	SqlCommand sql;
	string name;
	sql.setType(SQL_DROP_TABLE);
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");
	name = firstWord(str, " ;"); // ��readInput()����Ӧ���Ѿ������";"�������" ;"�� by tgmerge
	sql.setTableName(name);
	return sql;
}

/**
 * @brief  ����drop index���Ϸ���
 * @author tgmerge
 * @param  string&    SQLָ��
 * @return SqlCommand ����ΪSQL_DROP_INDEX���ڲ�����
 */
SqlCommand Interpreter::dropIndex(string& str)

/**
 * @brief  ����use���Ϸ���
 * @author tgmerge
 * @param  string&    SQLָ��
 * @return SqlCommand ����ΪSQL_USE���ڲ�����
 */
SqlCommand Interpreter::useClause(string& str){
	// ���ڵ�strʾ��  use database1 ;
	SqlCommand sql;
	string name;

	//ɾ��"use"
	str = delFirstWord(str, " ");
	
	//ȡ���ݿ�����
	name = firstWord(str, " ");

	// TODO: �������ݿ����ƴ�����
	sql.setType(SQL_USE);
	sql.setDatabaseName(name);

	return sql;
}

SqlCommand Interpreter::

/**
 * @brief  ����������ø���ⷽ��������һ��SqlCommand����APIʹ��
 * @author tgmerge
 * @param  string     Ҫ�������ַ���
 * @return SqlCommand ������ɵ��������
 */
SqlCommand Interpreter::getExpression(string input) {

	// Ҫ���صĶ���
	SqlCommand sql;
	
	// ȡ���ĵ�һ������
	string firstStr = firstWord(input, " ");
	
	// ���ݵ�һ�������ж�
	// ��һ����use
	if( firstStr == "use" ) {
		sql = useClause(input);
	}
	// ��һ����drop
	else if( firstStr == "drop" ) {
		// ���ݵڶ��������ж�
		string secondStr = delFirstWord(input, " ");
		       secondStr = firstWord(secondStr, " ");
		if( secondStr == "database" ) {
			sql = dropDatabase(input);
		}
		else if( secondStr == "table" ) {
			sql = dropTable(input);
		}
		// �޷�ƥ��
		else {
			sql.setType(SQL_ERROR);
		}
	}
	else {
		sql.setType(SQL_ERROR);
	}

	return sql;
}

