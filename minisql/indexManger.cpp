#include"indexManager.h"

IndexManager::IndexManager(string DBName):buff(DBName)
{
}

//create tableʱ����
bool IndexManager::createIndex(string indexName)
{
	buff.storeIndex(indexName,"");
}





//create index onʱ����
bool IndexManager::createIndexOn(SqlCommand sql,table tableInstance,string indexName)
{
	if (tableInstance.recNum == 0)
	{
		this->createIndex(indexName);
		return;
	}
	BPTree tree;
	tree.createBPTree(sql,tableInstance,BufferManager buff);
}





//drop indexʱ����
bool IndexManager::dropIndex(SqlCommand sql,table tableInstance)
{
}





//drop tableʱ����
bool IndexManager::dropIndexAll(SqlCommand sql,table tableInstance)
{
}





//select recʱ����
indexInfo IndexManager::selectRec(SqlCommand sql,table tableInstance,vector<string> indexList)
{
}




//insert recʱ����
indexInfo IndexManager::insertRec(SqlCommand sql,table tableInstance,vector<string> indexList)
{
}




//delete recʱ����
indexInfo IndexManager::deleteRec(SqlCommand sql,table tableInstance,vector<string> indexList)
{
}