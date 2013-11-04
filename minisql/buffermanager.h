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
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "block.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// ������������ļ�����
#define MAX_FILE_ACTIVE  5
// ��������������
#define MAX_BLOCK_ACTIVE 40

/* ����
// �ļ�ͷ�ṹ
struct fileInfo {
	// 0=���ݣ�1=����
	int type;
	// �ļ���
	string fileName;
	// ��¼��Ŀ
	int recordAmount;
	// ���ÿ���
	int freeNum;
	// ��¼����
	int recordLength;
	// ��һ���ļ���ָ��
	fileInfo *next;
	// ��һ����ָ��
	blockInfo *firstBlock;
};*/

class BufferManager {

private:
	// ���ݿ���
	string dbName;
	// ���ݿ��ļ���
	string dbFileName;
	// ���ݿ��ļ�
	fstream dbFile;

public:
	// �ڴ��еĻ�����
	Block buffer[MAX_BLOCK_ACTIVE];

public:							// ���죬����
	// �����ݿ�����ʼ��buffermanager
	BufferManager(string name);
	// д��������飬����buffermanager
	~BufferManager();

private:						// ���÷�������д
	// ��ĳ�ļ���һ��block
	Block readBlock(int offset);
	// ��ĳ�ļ���n��������ŵ�block
	vector<Block> readBlocks(string fileName, int offset, int n);
	// ��blockд���ļ������Ǹɾ��ľͲ�д�ˣ�
	bool writeBlock();
	// д�����л������е���block���ļ�
	bool writeAllBlocks();

private:						// ���÷�����LRU���
	// ����ĳ���LRU
	void updateLru(Block& b);
	// ���»��������п��LRU
	void updateAllLru();

public:							// RecordManagerʹ��
	// ����tableName�����п�
	static vector<Block> getTableBlocks(string tableName);
	// ����tableName��ĳ���飨offset��IndexManagerȡ�ã���
	static Block getTableBlock(string tableName, int offset);
	// ��tableName���һ���¿�
	static Block newBlock(string tableName);
	// Ҫ��д�鵽Ӳ��

public:							// IndexManagerʹ��
	// ����indexName�����п�
	vector<Block> getIndexBlocks(string IndexName);

};

#endif