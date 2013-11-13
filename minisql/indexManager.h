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
public:
	//�����ݿ����Ƴ�ʼ��
	IndexManager(string DBName);
	//create tableʱ����
	bool createIndex(string indexName);
	//create index onʱ����
	bool createIndexOn(SqlCommand sql,table tableInstance,string indexName);
	//drop indexʱ����
	bool dropIndex(SqlCommand sql,table tableInstance);
	//drop tableʱ����
	bool dropIndexAll(SqlCommand sql,table tableInstance);
	//select recʱ����
	vector<int> IndexManager::selectRec(SqlCommand sql,table tableInstance,vector<string> indexList,string key);
	//insert recʱ����
	indexInfo insertRec(SqlCommand sql,table tableInstance,vector<string> indexList,string key,int blockPtr,int inBlockPtr);
	//delete recʱ����
	indexInfo deleteRec(SqlCommand sql,table tableInstance,vector<string> indexList,string key)
};

#endif