#include "interpreter.h"

using namespace std;

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
SqlCommand Interpreter::getExpression() {
	// Ҫ���ص��ڲ��������
	SqlCommand command();


}