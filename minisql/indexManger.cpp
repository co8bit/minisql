#include"indexManager.h"

IndexManager::IndexManager(string DBName):buff(DBName)
{
}

//create tableʱ����
bool IndexManager::createIndex(string indexName)
{
	//buff.storeIndex(indexName,"");??
}





//create index onʱ����
/*bool IndexManager::createIndexOn(SqlCommand sql,table tableInstance,string indexName,int type)
{
	if (tableInstance.recNum == 0)
	{
		this->createIndex(indexName);
		return;
	}
	BPTree tree(buff,type);
	tree.createBPTree(sql,tableInstance,indexName);
}
*/




//drop indexʱ����
bool IndexManager::dropIndex(SqlCommand sql,table tableInstance)
{
}





//drop tableʱ����
bool IndexManager::dropIndexAll(SqlCommand sql,table tableInstance)
{
}





//select recʱ����
vector<int> IndexManager::selectRec(SqlCommand sql,table tableInstance,vector<string> indexList,string key)
{
	vector<int> result;
	for (int j = 0; j < indexList.size(); j++)//ά��ÿһ������
	{
		int attrType = 0;
		for(int i = 0; i < tableInstance.attrList.size(); i++)
			if (tableInstance.attrList[i].name == indexList[j])
			{
				switch(tableInstance.attrList[i].datatype)
				{
				case -1:attrType = _TYPE_FLOAT;break;
				case 0:attrType = _TYPE_INT;break;
				case 1:attrType = _TYPE_STRING;break;
				}
				break;
			}
		BPTree tree(buff,attrType);
		tree.loadBPTree(sql.getTableName()+"."+indexList[j]);
		Value temp(attrType,key);
		result.push_back(tree.find(temp));
	}
	return result;
}




//insert recʱ����
vector<int> IndexManager::insertRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key, int blockPtr, int inBlockPtr)
{
	for (int j = 0; j < indexList.size(); j++)//ά��ÿһ������
	{
		int attrType = 0;
		for(int i = 0; i < tableInstance.attrList.size(); i++)
			if (tableInstance.attrList[i].name == indexList[j])
			{
				switch(tableInstance.attrList[i].datatype)
				{
				case -1:attrType = _TYPE_FLOAT;break;
				case 0:attrType = _TYPE_INT;break;
				case 1:attrType = _TYPE_STRING;break;
				}
				break;
			}
		BPTree tree(buff,attrType);
		tree.loadBPTree(sql.getTableName()+"."+indexList[j]);
		Value temp(attrType,key);
		int recordCount = 4096 / (tableInstance.recLength + 1);//���ؼ�¼�Ŀ������
		tree.insert(temp,blockPtr*recordCount + inBlockPtr);
	}
}




//delete recʱ����
vector<int> IndexManager::deleteRec(SqlCommand sql, table tableInstance, vector<string> indexList, string key)
{
	vector<int> result;
	for (int j = 0; j < indexList.size(); j++)//ά��ÿһ������
	{
		int attrType = 0;
		for(int i = 0; i < tableInstance.attrList.size(); i++)
			if (tableInstance.attrList[i].name == indexList[j])
			{
				switch(tableInstance.attrList[i].datatype)
				{
				case -1:attrType = _TYPE_FLOAT;break;
				case 0:attrType = _TYPE_INT;break;
				case 1:attrType = _TYPE_STRING;break;
				}
				break;
			}
		BPTree tree(buff,attrType);
		tree.loadBPTree(sql.getTableName()+"."+indexList[j]);
		Value temp(attrType,key);
		result.push_back(tree.deleteNode(temp));
	}
	return result;
}
