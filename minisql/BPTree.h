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

extern BufferManager *bfm;
typedef int PtrType;

class Value//���ֵ����
{
private:
	int type;//�洢��Ӧ��ֵ
	string charKey;
	int intKey;
	float floatKey;

public:
	//��ֵ���ͺ�key��ʼ�������
	//_TYPE_STRING 0; _TYPE_INT 1; _TYPE_FLOAT 2;
	Value(int type):type(type){}
	Value(int type,string key):type(type),charKey(key){}
	Value(int type,int key):type(type),intKey(key){}
	Value(int type,float key):type(type),floatKey(key){}
	
	//�õ�key��ͳһ���ַ�������
	string getKey();
	
	//���ֵ����
	int getType(){return type;}
	
	//��ö�Ӧ�����͵�ֵ
	int getIntKey(){return intKey;}
	float getFloatKey(){return floatKey;}
	string getCharKey(){return charKey;}
	
	//����ֵ
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
class Node//B+���ڵ���
{
private:
	//B+���Ľڵ����ݣ���ȥ���ӵĽڵ�ͷ��
	vector<Value> info;

	//��������
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

	//���ݿ�����
	string dbName;

	//��
	Block block;

	//����Ϣ
	table tableInstance;

	//������ʹ�С�ĺ���
	TYPE_SIZE;

	//�ѿ�����ݶ�����
	void read();

public:
	//����һ���ڵ�ʱ���õĹ��캯��
	Node(string dbName, string indexName, table tableInstance, int n);

	//�õ�һ���ڵ�ʱ���õĹ��캯��
	Node(string dbName,PtrType ptr,string indexName,table tableInstance,int n);

	Node(string dbName,PtrType ptr,string indexName,table tableInstance,int n,int tag);//��read���캯��
	//�������������������д����̣�������
	~Node();

	//�õ��ڵ��ƫ����
	PtrType getNodePtr();

	//����B+���Ľڵ����ݣ���ȥ���ӵĽڵ�ͷ��
	void set(vector<Value> temp){info.clear();info = temp;updateCount();}

	//���¸ýڵ㵱ǰָ����
	void updateCount();

	//��������ָ���ַ
	void setLastPtr(Value ptr);
	void setLastPtr(PtrType ptr);

	//���ýڵ�ļ�ֵ����
	void setType(int type){nodeType = type;}

	//���ýڵ�Ӧӵ�е�ָ����
	void setCount(int t){count = t;}

	//�õ�����ָ��
	Value getLastPtr(){return info[info.size() - 1];}

	//�õ��ڵ���Ϣ����ȥ��ͷ��
	vector<Value> getInfo(){return info;}

	//�õ��ڵ�Ӧӵ�е�ָ����
	int getCount(){return count;} 

	//�õ��ڵ�����
	int getNodeType(){return nodeType;}
};


class BPTree{
public:
	//����������buff���������ֵ���͹���
	BPTree(string dbName,int type);

	//����һ���յ�B+��
	void createBPTree(SqlCommand sql,table tableInstance,string indexName,int type);

	//��ȡB+��
	void loadBPTree(string indexName);//TODO:�ĳɹ��캯��

	//����ڵ�
	void insert(Value key,PtrType pointer);

	//��B+�����ҵ�keyֵ��λ�ã���������keyֵ�󶨵�ƫ���������ü�¼�����ļ��е�ƫ������
	PtrType find(Value key);

	//ɾ��keyֵ��Ӧ�ļ�ֵ����ַ��
	PtrType deleteNode(Value key);

	//�ӿ�ʼ��ֱ�����ȥȡֵ�����ڴ��ڵ���
	vector<int> findToBehind(Value key);

	//�ӿ�ʼ��ֱ������������ȥȡֵ������С�ڵ���
	vector<int> findToBehindIF(Value key);

private:
	//�ڵ�ָ����
	int n;

	//��ֵ����
	int type;

	//��������
	string indexName;

	//����Ϣ
	table tableInstance;

	//���ڵ�
	PtrType root;

	//���ݿ�����
	string dbName;

	//��ǰ�ڵ��븸�׽ڵ��ӳ����
	class ParentMap
	{
	public:
		//��ǰ�ڵ�
		PtrType nodePtr;
		//��Ӧ�ĸ��׽ڵ�
		PtrType parentPtr;
	};

	//�����б�
	vector<ParentMap> parentMap;

	//Value��ıȽϺ��� if key1 < key2 then true
	bool isLess(Value& key1,Value& key2);

	//Value��ıȽϺ��� if key1 <= key2 then true
	bool isLessEqual(Value& key1,Value& key2);

	//Value��ıȽϺ��� if key1 == key2 then true
	bool isEqual(Value& key1,Value& key2);
	
	//����ڵ㵽Ҷ�ڵ�
	void insertLeaf(Node node,Value key,PtrType pointer);

	//����ڵ㵽��Ҷ�ڵ㣨����node��Ҫ���µĸ��ڵ���ӽڵ㣩
	void insertNonleaf(Node node,Value key,PtrType pointer);
	
	//����Ҷ�ӽڵ㣬û�ҵ�����-1���ҵ�����Ҷ�ӽڵ��ƫ��������Ҷ�ӽڵ������ڵ�ģ�
	PtrType findLeafNode(Value key);

	//����parentMap����ptr�ڵ�ĸ��ڵ�
	PtrType findParentNode(PtrType ptr);

	//�����ʹ�С
	TYPE_SIZE;
};

#endif