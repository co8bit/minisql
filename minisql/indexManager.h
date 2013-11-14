#ifndef _INDEXMANAGER_H_
#define _INDEXMANAGER_H_
/**
 * @file   indexManager.h
 * @brief  ��������
 * @author co8bit
 */

#include "minisql.h"
#include"BPTree.h"

class IndexManager{
private:
	BufferManager buff;
	string dbName;
public:
	//�����ݿ����Ƴ�ʼ��
	IndexManager(string DBName);

	//create tableʱ����
	void createIndex(string indexName);

	//create index onʱ���ã�����һ�ÿ�����Ȼ��ȴ��ϲ���ò��������������������ϵ�����
	void createIndexOn(SqlCommand sql,table tableInstance,string indexName);

	//drop indexʱ����
	bool dropIndex(SqlCommand sql,table tableInstance);

	//drop tableʱ����
	bool dropIndexAll(SqlCommand sql,table tableInstance);

	//select recʱ����
	vector<int> selectOne(SqlCommand sql,table tableInstance,string indexName,string key);//ѡ��һ���Ĳ���
	vector<int> selectMany_x(SqlCommand sql,table tableInstance,string indexName,string key);//ѡ�����Ĳ�����С�ڣ�
	vector<int> selectMany_d(SqlCommand sql,table tableInstance,string indexName,string key);//ѡ�����Ĳ��������ڣ�
	vector<int> selectMany_xd(SqlCommand sql,table tableInstance,string indexName,string key);//ѡ�����Ĳ�����С�ڵ��ڣ�
	vector<int> selectMany_dd(SqlCommand sql,table tableInstance,string indexName,string key);//ѡ�����Ĳ��������ڵ��ڣ�

	//����Ӧ�����������¼������insert recʱ����
	void insertRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key, int blockPtr, int inBlockPtr);

	//����Ӧ��������ɾ����¼������delete recʱ����
	vector<int> deleteRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key);
};

#endif