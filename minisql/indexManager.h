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
public:
	//create tableʱ����
	bool createIndex(SqlCommand sql,table tableInstance);
	//create index onʱ����
	bool createIndexOn(SqlCommand sql,table tableInstance);
	//drop indexʱ����
	bool dropIndex(SqlCommand sql,table tableInstance);
	//drop tableʱ����
	bool dropIndexAll(SqlCommand sql,table tableInstance);
	//select recʱ����
	indexInfo selectRec(SqlCommand sql,table tableInstance,vector<string> indexList);
	//insert recʱ����
	indexInfo insertRec(SqlCommand sql,table tableInstance,vector<string> indexList);
	//delete recʱ����
	indexInfo deleteRec(SqlCommand sql,table tableInstance,vector<string> indexList);
};

#endif