/**
 * @file  buffer.h
 * @brief ����������ͷ�ļ�
 * @author tgmerge
 * ����������������黺�������Ƿ���Ҫ��Ŀ飬�����򷵻أ�����Ӵ��̶�ȡ��
 */

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// ���ݿ�ߴ�
#define BLOCK_LEN        4096
// ������������ļ�����
#define MAX_FILE_ACTIVE  5
// ��������������
#define MAX_BLOCK_ACTIVE 40



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
};


// ����Ϣ�ṹ
struct blockInfo {
	// ����
	int blockNum;
	// ��
	bool dirty;
	// ��һ��ָ��
	blockInfo *next;
	// �����ļ�
	fileInfo *file;
	// �������ݳ���
	int charNum;
	// ����ָ��
	char *cBlock;
	// ���뻺������ʱ��
	int iTime;
	// ��
	int lock;
};

class Buffer {

public:
	// �������ܺ��ĵ�����һģһ��w
	blockInfo *findBlock(string dbName);

	void replace(fileInfo *m_fileInfo, blockInfo *m_blockInfo);

	blockInfo *get_file_block(string dbName, string tableName, int fileType, int blockNum);

	void closeDataBase(string dbName, bool mFlag);

	void closeFile(string dbName, string m_fileName, int m_fileType, bool mFlag);

	void writeBlock(string dbName, blockInfo *block);

	fileInfo *get_file_info(string dbName, string fileName, int m_fileType);

	blockInfo* readBlock(string dbName,Cstring m_fileName, int m_blockNum, int m_fileType);

	void quitProg(string dbName);

	void Get_Table_Info(string dbName, string tableName, int recordCount, int recordLen, int free);

	void Get_Index_Info(string dbName, string indexName, int recordCount, int recordLen, int free);

	void Write_Table_Info(Cstring dbName,Cstring tableName,int recordCount,int recordLen,int free);

	void Write_ Index_Info(Cstring dbName,Cstring indexName,int recordCount,int recordLen,int free);
}
#endif