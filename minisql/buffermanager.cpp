#include "buffermanager.h"

/**
 * @brief  �����ݿ����½�buffer��
 */
BufferManager::BufferManager(string name) {
  // �����ļ���Ϊ"���ݿ���.db"
  dbName = name;
  dbFileName = name + ".db";
  // TODO �����ݿ���ת��Ϊ
  dbFile.open(dbFileName, std::fstream::out | std::fstream::in );
  // �����������½��ļ�
  if( !dbFile ) {
	  // TODO: �����������½��ļ�
  }
}

/**
 * @brief  �ر�buffer֮ǰ����bufferд���������
 */
BufferManager::~BufferManager() {
	writeAllBlocks();
}

/**
 * @brief  �����ݿ��ļ���ȡһ��block��ָ��ƫ����
 */
BufferManager::readBlock(string fileName, int offset) {
	// TODO ˵��fileName�Ѿ�������
	