#ifndef _INDEXMANAGER_H_
#define _INDEXMANAGER_H_
/**
 * @file   indexManager.h
 * @brief  ��������
 * @author co8bit
 */

#include "minisql.h"
#include"BPTree.h"

extern BufferManager *bfm;
class IndexManager{
private:
	string dbName;
public:
	//�����ݿ����Ƴ�ʼ��
	IndexManager(string DBName);

	//create tableʱ����
	void createIndex(string indexName);

	//create index onʱ����
	void createIndexOn(SqlCommand sql,table tableInstance,string indexName);

	//drop indexʱ����
	bool dropIndex(SqlCommand sql,table tableInstance);

	//drop tableʱ����
	bool dropIndexAll(SqlCommand sql,table tableInstance);

	//select recʱ����
	vector<int> selectOne(SqlCommand sql,table tableInstance,string indexName,string key);
	vector<int> selectMany_x(SqlCommand sql,table tableInstance,string indexName,string key);//С��
	vector<int> selectMany_d(SqlCommand sql,table tableInstance,string indexName,string key);//����
	vector<int> selectMany_xd(SqlCommand sql,table tableInstance,string indexName,string key);//С�ڵ���
	vector<int> selectMany_dd(SqlCommand sql,table tableInstance,string indexName,string key);//���ڵ���

	//insert recʱ����
	void insertRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key, int blockPtr, int inBlockPtr);

	//delete recʱ����
	vector<int> deleteRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key);
};

#endif