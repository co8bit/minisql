#include "interpreter.h"

using namespace std;

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

Interpreter::Interpreter() {
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

/**
 * @brief  �����������һ��SqlCommand����APIʹ��
 * @author tgmerge
 * @param  string     Ҫ�������ַ���
 * @return SqlCommand ������ɵ��������
 */
SqlCommand Interpreter::getExpression(string input) {
	// Ҫ���ص��ڲ��������
	SqlCommand command;

	return command;
}