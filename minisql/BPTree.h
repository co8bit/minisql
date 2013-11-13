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

#define _LEAFNODE 1
#define _NONLEAFNODE 0

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
	Value(int type):type(type){}
	Value(int type,string key):type(type),charKey(key){}
	Value(int type,int key):type(type),intKey(key){}
	Value(int type,float key):type(type),floatKey(key){}
	//�õ�key��ͳһ���ַ�������
	string getKey();
	int getType(){return type;}
	int getIntKey(){return intKey;}
	float getFloatKey(){return floatKey;}
	string getCharKey(){return charKey;}
	void setKey(int key){intKey = key;}
	void setKey(string key){charKey = key;}
	void setKey(float key){floatKey = key;}
};
/*
class  KeyAndPtr
{
private:
	int type;
	Value value;
	PtrType ptr;

public:
	KeyAndPtr(int type,Value value,PtrType ptr):type(type),value(value),ptr(ptr){}
};
*/
class Node
{
private:
	vector<Value> info;
	//��ǰָ���λ�ã���δ����
	int now;
	string indexName;
	//��ǰ�ڵ���ӵ�е�ָ����
	int count;
	//�ڵ����ͣ�0�Ƿ�Ҷ�ڵ㣬1��Ҷ�ڵ�
	int nodeType;
	//�ڵ�Ӧӵ�е�ָ����
	int ptrN;
	//indexName ����Ӧ��key����
	int attrType;
	//��ż�ƫ����
	int offset;
	
	BufferManager indexBuff;
	Block block;
	table tableInstance;
	TYPE_SIZE;

	//�ѿ�����ݶ�����
	string read();

public:
	//����һ���ڵ�ʱ���õĹ��캯��
	Node(BufferManager indexBuff,string indexName,table tableInstance,int n):indexBuff(indexBuff){}
	//�õ�һ���ڵ�ʱ���õĹ��캯��
	Node(BufferManager indexBuff,PtrType ptr,string indexName,table tableInstance,int n);
	//�������������������д����̣�������
	~Node();

	//�õ��ڵ��ƫ����
	PtrType getNodePtr();

	void set(vector<Value> temp){info.clear();info = temp;updateCount();}
	void updateCount();//���¸ýڵ㵱ǰָ����
	void setLastPtr(Value ptr);
	void setLastPtr(PtrType ptr);
	Value getLastPtr(){return info[info.size() - 1];}
	vector<Value> getInfo(){return info;}
	int getCount(){return count;} 
	int getNodeType(){return nodeType;}

};


class BPTree{
public:
	//��������buff���������ֵ����
	BPTree(BufferManager indexBuff,int type);
	bool createBPTree(SqlCommand sql,table tableInstance,string indexName);
	bool loadBPTree(string indexName);//TODO:�ĳɹ��캯��
	void insert(Value key,PtrType pointer);

private:
	BufferManager indexBuff;//��ô��ʼ������
	int n;//�ڵ�ָ����
	int type;//��ֵ����
	string indexName;
	table tableInstance;
	PtrType root;
	class ParentMap
	{
	public:
		PtrType nodePtr;
		PtrType parentPtr;
	};
	vector<ParentMap> parentMap;//�����б�

	
	void insertLeaf(Node node,Value key,PtrType pointer);
	void insertNonleaf(Node node,Value key,PtrType pointer);
	//û�ҵ�����-1���ҵ�����ƫ����
	PtrType find(Value key);
	PtrType findLeafNode(Value key);
	PtrType findParentNode(PtrType ptr);//����parentMap����ptr�ڵ�ĸ��ڵ�
	//�����ʹ�С
	TYPE_SIZE;
};
//TODO�� �ȽϺ���
#endif