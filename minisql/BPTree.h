#ifndef _BPTREE_H_
#define _BPTREE_H_
/**
 * @file   BPTree.h
 * @brief   B+����ʵ��
 * @author co8bit
 */

#include "minisql.h"
#include"buffermanager.h"
#include"stdio.h";
typedef int PtrType;

class Value
{
private:
	int type;
	string charKey;
	int intKey;
	float floatKey;
public:
	//�����ͺ�key��ʼ�������
	//_TYPE_STRING 0; _TYPE_INT 1; _TYPE_FLOAT 2;
	Value(int type,string key):type(type),charKey(key){}
	Value(int type,int key):type(type),intKey(key){}
	Value(int type,float key):type(type),floatKey(key){}
	//�õ�key��ͳһ���ַ�������
	string getKey();
};

class Node
{
private:
	vector<string> nodeText;
	//��ǰָ���λ�ã���δ����
	int now;
public:
	//�õ�key
	int getIntKey();
	string getCharKey();
	float getFloatKey();
};

class LeafNode: public Node
{
	int getPtr();
	int getLastPtr();
};

class NonleafNode: public Node
{
	int getPtr();
	int getFirstPtr();
};

class BPTree{
public:
	//��������buff���������ֵ����
	BPTree(BufferManager indexBuff,int type);
	bool createBPTree(SqlCommand sql,table tableInstance,string indexName);
	bool loadBPTree(BufferManager buff,string indexName);//TODO:�ĳɹ��캯��

private:
	BufferManager indexBuff;//��ô��ʼ������
	int n;//�ڵ�ָ����
	int type;//��ֵ����

	void insert(Value key,PtrType pointer);
	void insertLeaf(LeafNode node,Value key,PtrType pointer);
	void insertNonleaf(NonleafNode node,Value key,PtrType pointer);
	PtrType find(Value key);
};

#endif