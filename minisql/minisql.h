#ifndef _MINISQL_H_
#define _MINISQL_H_

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
	void setcolName(string& str){
		colName = str;
	}

	//push����(selectʹ��)
	void pushColNameVector(string& t){
		colNameVector.push_back(t);
	}
	//push��ֵ(insertʹ��)
	void pushColValueVector(string& str){
		colValueVector.push_back(str);
	}
	//push������ֵ(select,delete)
	void pushCondLeftVector(string& str){
		condLeftVector.push_back(str);
	}
	//push����������(select,delete)
	void pushCondOpVector(string& str){
		condOpVector.push_back(str);
	}
	//push������ֵ(select,delete)
	void pushCondRightVector(string& str){
		condRightVector.push_back(str);
	}
	//���������Ϣ
	void print(){

		cout<<"type: "<<type<<endl;
		cout<<"tableName: "<<tableName<<endl;
		cout<<"databaseName: "<<databaseName<<endl;
		cout<<"indexName: "<<indexName<<endl;
		cout<<"colName: "<<colName<<endl;

		cout<<"colNameVector:  ";
		for (int i=0; i<colNameVector.size(); i++)
			cout<<colNameVector[i]<<" ";
		cout<<endl;
		cout<<"colValueVector:  ";
		for (int i=0; i<colValueVector.size(); i++)
			cout<<colValueVector[i]<<" ";
		cout<<endl;
		cout<<"condLeftVector: ";
		for (int i=0; i<condLeftVector.size(); i++)
			cout<<condLeftVector[i]<<" ";
		cout<<endl;
		cout<<"condOpVector: ";
		for (int i=0; i<condOpVector.size(); i++)
			cout<<condOpVector[i]<<" ";
		cout<<endl;
		cout<<"condRightVector: ";
		for (int i=0; i<condRightVector.size(); i++)
			cout<<condRightVector[i]<<" ";
		cout<<endl;
	}
private:
	// ��������
	int type;

	// ��������
	string tableName;
	string databaseName;
	string indexName;
	string colName;

	vector<string> colNameVector;	// where/insert�����е�������
	vector<string> colValueVector;  // where/insert�����е�����ֵ
	vector<string> condLeftVector;	// where�����е������� e.g. colA
	vector<string> condOpVector;	// where�����еķ���   e.g. >=
	vector<string> condRightVector;	// where�����е�ֵ     e.g. 10

};
//������Ϣ
class attribute{
	string attr;	//����
	int datatype;	//��������
	bool PK;		//����
	bool UNIQUE;	//Ψһ
	bool NN;		//�ǿ�
};
#endif