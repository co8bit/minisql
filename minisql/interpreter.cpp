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
#include <vector>

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
SqlCommand Interpreter::dropIndex(string& str){
	// ���ڵ�strʾ��  drop index indexA ;
	SqlCommand sql;
	string name;

	// ɾ��"drop index"
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");

	// ȡ������
	name = firstWord(str, " ");

	// TODO: ��������������

	sql.setType(SQL_USE);
	sql.setIndexName(name);

	return sql;
}

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

/**
 * @brief  ����create database���Ϸ���
 * @author tgmerge
 */
SqlCommand Interpreter::createDatabase(string& str) {
	// ���ڵ�str: create database database1 ;
	SqlCommand sql;
	string name;

	// ɾ��"create database"
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");

	// ȡ���ݿ�����
	name = firstWord(str, " ");

	sql.setType(SQL_CREATE_DATABASE);
	sql.setDatabaseName(name);

	return sql;
}

/**
 * @brief  ����create table���Ϸ���
 * @author tgmerge
 */
SqlCommand Interpreter::createTable(string& str) {
	// ���ڵ�str: create table table1 ;
	SqlCommand sql;
	string name;

	// ɾ��"create table"
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");

	// ȡ����
	name = firstWord(str, " ");

	sql.setType(SQL_CREATE_TABLE);
	sql.setTableName(name);

	return sql;
}

/**
 * @brief  ����create index���Ϸ���
 * @author tgmerge
 */
SqlCommand Interpreter::createIndex(string& str) {
	SqlCommand sql;
	string indexName;
	string tableName;
	string colName;

	// ɾ��"create index"
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");

	// ȡ������
	indexName = firstWord(str, " ");

	// ɾ��"������ on"
	// TODO: �ж��Ƿ���ON
	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");
	tableName = firstWord(str, " ()");
	str = delFirstWord(str, " ()");
	colName = firstWord(str, " ()");

	sql.setType(SQL_CREATE_INDEX);
	sql.setIndexName(indexName);
	sql.setTableName(tableName);
	sql.setcolName(colName);

	return sql;
}

/**
 * @brief  ����������ø���ⷽ��������һ��SqlCommand����APIʹ��
 * @author tgmerge
 * @param  string     Ҫ�������ַ���
 * @return SqlCommand ������ɵ��������
 * TODO: δ���
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
		else if( secondStr == "index" ) {
			sql = dropIndex(input);
		}
		// �޷�ƥ��
		else {
			sql.setType(SQL_ERROR);
		}
	}
	// ��һ����create
	else if( firstStr == "create" ) {
		// ���ݵڶ��������ж�
		string secondStr = delFirstWord(input, " ");
			   secondStr = firstWord(secondStr, " ");
		if( secondStr == "database" ) {
			sql = createDatabase(input);
		}
		else if( secondStr == "table" ) {
			sql = createTable(input);
		}
		else if( secondStr == "index" ) {
			sql = createIndex(input);
		}
		// �޷�ƥ��
		else {
			sql.setType(SQL_ERROR);
		}
	}
	// ��һ����select
	else if( firstStr == "select" ) {
		sql = selectClause(input);
	}
	// ��һ����delete
	else if( firstStr == "delete" ) {
		sql = deleteFromWhere(input);
	}
	// ��һ����insert
	else if( firstStr == "insert" ) {
		sql = insertIntoValues(input);
	}
	// �޷�ƥ��
	else {
		sql.setType(SQL_ERROR);
	}

	return sql;
}

/**
 * @brief  ����select���
 * @author tgmerge
 * Ҫ֧�ֵ����
 * select a from xxx
 * select a, b from xxx
 * select * from xxx
 * where a > 10 and b < 10 ;
 */
SqlCommand Interpreter::selectClause(string& str) {
	// ���ڵ����ʾ�� select colName, colName from tableName where condcol condOp condValue and condcol condop condvalue, etc
	SqlCommand sql;
	string tableName;
	string temp;

	str = delFirstWord(str, " ");	// ɾ��"select"

	// ����colName
	for( temp = firstWord(str, " ,"); !(temp == "from"); temp = firstWord(str, " ,") ) {
		// TODO: ��֤col�Ĵ����ԣ�
		sql.pushColNameVector( temp );
		str = delFirstWord(str, " ,");
	}

	// ����tableName
	str = delFirstWord(str, " ");	// ɾ��from
	tableName = firstWord(str, " ");
	str = delFirstWord(str, " ");   // ɾ��tablename

	// ��������, �����where...
	if( firstWord(str, " ") == "where" ) {
		str = delFirstWord(str, " "); // ɾ��where
		for( temp = firstWord(str, " "); !(temp == ";"); temp = firstWord(str, " ") ) {
			if(temp == "and") {
				str = delFirstWord(str, " ");
			}
			sql.pushCondLeftVector(firstWord(str, " ")); // �Ƚϵ�������
			str = delFirstWord(str, " ");
			sql.pushCondOpVector(firstWord(str, " "));   // �ȽϵĲ�����
			str = delFirstWord(str, " ");
			sql.pushCondRightVector(firstWord(str, " "));// �Ƚϵ���ֵ
			str = delFirstWord(str, " ");
		}
	}

	sql.setType(SQL_SELECT);
	sql.setTableName(tableName);

	return sql;
}

/**
 * @brief  ����delete from���
 * @author tgmerge
 * Ҫ֧�ֵ����
 * delete from tableX
 * delete from tableX where a > 10 and b < 10 ;
 * TODO: ��֤tableX������
 */
SqlCommand Interpreter::deleteFromWhere(string& str) {
	// ���ڵ����ʾ�� delete from X where a > 10 and b < 10 ;
	SqlCommand sql;
	string tableName;
	string temp;

	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");	// ɾ��"delete from"
	// TODO: delete���治��from�����

	// ����tableName
	tableName = firstWord(str, " ");
	str = delFirstWord(str, " ");
	// TODO: ��֤tableName�Ĵ�����

	// ���������where
	if( firstWord(str, " ") == "where" ) {
		str = delFirstWord(str, " "); // ɾ��where
		for( temp = firstWord(str, " "); !(temp == ";"); temp = firstWord(str, " ") ) {
			if(temp == "and") {
				str = delFirstWord(str, " ");
			}
			sql.pushCondLeftVector(firstWord(str, " ")); // �Ƚϵ�������
			str = delFirstWord(str, " ");
			sql.pushCondOpVector(firstWord(str, " "));   // �ȽϵĲ�����
			str = delFirstWord(str, " ");
			sql.pushCondRightVector(firstWord(str, " "));// �Ƚϵ���ֵ
			str = delFirstWord(str, " ");
		}
	}

	sql.setType(SQL_DELETE);
	sql.setTableName(tableName);

	return sql;
}

/**
 * @brief  ����insert���
 * @author tgmerge
 * Ҫ֧�ֵ����
 * insert into tableA values( 10, '100' );
 * TODO: ��֤tableX������, ��֤��������
 */
SqlCommand Interpreter::insertIntoValues(string& str) {
	SqlCommand sql;
	string tableName;
	string temp;

	str = delFirstWord(str, " ");
	str = delFirstWord(str, " ");	// ɾ��"insert into"
	// TODO: insert���治��into

	// ����tableName;
	tableName = firstWord(str, " ");
	str = delFirstWord(str, " ");

	str = delFirstWord(str, " (");	// ɾ��"values ("

	// ����ֵ
	while( !(firstWord(str, " )") == ";") ) {
		sql.pushColValueVector( firstWord(str, " ),") );
		str = delFirstWord(str, " ),");
	}

	sql.setType(SQL_INSERT_INTO);
	sql.setTableName(tableName);

	return sql;
}