/**
 * @file  buffermanager.h
 * @brief ����������ͷ�ļ�
 * @author tgmerge
 * ����������������黺�������Ƿ���Ҫ��Ŀ飬�����򷵻أ�����Ӵ��̶�ȡ��
 * ΪIndex��Record�ṩ����Ŀ�
 *
 * ÿ��BufferManager����ֻ��һ�����ݿ⣨�ļ������ļ�����"���ݿ���.db"��
 * ���췽����Ҫ�������ݿ�����
 * ʹ��BufferManagerʱ����Ҫ����д�鵽�ļ���ֻ��Ҫ�ڿ鷢���ı�ʱ���ÿ��dirty()�����������ó����
 * BufferManager������鱻�滻�����棬����������֮ǰ������д���ļ���
 */

/**
��Ŀ�����dbName.blk
��¼ÿ��table��һ�����ƫ����
�Ƕ������ļ�
tableName[MAX_TABLE_NAME]  offset[4]
tableName[MAX_TABLE_NAME]  offset[4]
...
*/


#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "block.h"

#include <string>
#include <iostream>
#include <list>
#include <hash_map>
#include <fstream>

using namespace std;

// ��������������
#define MAX_BLOCK_ACTIVE 40
#define MAX_TABLE_NAME   32

class BufferManager {

private:
	string dbName;
	string dbFileName;
	string infoFileName;
	fstream dbFile;
	fstream infoFile;
private:
	// �����һ���ƫ��string:tableName, int:offset
	hash_map<char[MAX_TABLE_NAME], int> firstBlock;

public:
	// �ڴ��еĻ�����
	list<Block> buffer;

public:							// ���죬����
	// �����ݿ�����ʼ��buffermanager
	BufferManager(string name);
	// д��������飬����buffermanager
	~BufferManager();

private:						// ���÷�������д
	// ��ĳ�ļ���һ��block
	Block readBlock(int offset);
	// ��blockд���ļ������Ǹɾ��ľͲ�д�ˣ�
	void writeBlock(Block &block);
	// д�����л������е���block���ļ�
	void writeAllBlocks();

private:						// ���÷��������ҿ���أ�LRU
	// ��offset�ڻ�����ļ��в��ҿ飬�����뻺��
	Block findBlock(int offset);

private:						// ���ã����±�����.blk
	// ��ȡdbFile�ı�������ļ�, ��ʧ�����½�һ��
	void readDbInfo();
	// д�����ļ�
	void writeDbInfo();

public:							// RecordManagerʹ��
	// ����tableName�����п�
	static vector<Block> getTableBlocks(string tableName);
	// ����tableName��ĳ���飨offset��IndexManagerȡ�ã���
	// static Block getTableBlock(string tableName, int offset);
	// ��tableName���һ���¿�
	static Block newBlock(string tableName);

public:							// IndexManagerʹ��
	// ����indexName�����п�
	vector<Block> getIndexBlocks(string IndexName);

};

#endif