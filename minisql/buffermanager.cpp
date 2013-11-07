
#include "buffermanager.h"

/**
 * @brief  �����ݿ����½�buffer��
 */
BufferManager::BufferManager(string name) {
  dbName = name;
  dbFileName = name + ".db";
  infoFileName = name + ".blk";
  dbFile.open(dbFileName, std::fstream::out | std::fstream::in );
  infoFile.open(infoFileName, std::fstream::out | std::fstream::in );
  if( !dbFile ) {
	  // TODO: �����������½��ļ�
  }
  readDbInfo();
}

/**
 * @brief  �ر�buffer֮ǰ����bufferд���������
 */
BufferManager::~BufferManager() {
	writeAllBlocks();
	writeDbInfo();
}

/**
 * @brief  �����ݿ��ļ���ȡһ��block��ָ��ƫ����
 */
Block BufferManager::readBlock(int offset) {
	char temp[33];
	Block block;

	// ����ͷ
	dbFile.seekg(offset);
	dbFile.read(block.tableName, MAX_TABLE_NAME);
	dbFile.read((char *)&(block.nextOffset), sizeof(int));
	dbFile.read((char *)&(block.contentSize), sizeof(int));
	dbFile.read((char *)&(block.isAlive), sizeof(bool));
	dbFile.read((char *)&(block.isIndex), sizeof(bool));


	// ����
	dbFile.seekg(offset+HEAD_LEN);
	dbFile.read(block.content, BLOCK_LEN);
	
	block.isDirty = false;
	block.isActive = true;
	block.value = 0;

	return block;
}


void BufferManager::writeBlock(Block &block) {
	if( !block.isDirty ) {
		return;
	}

	// д��ͷ
	dbFile.seekp(block.offset);
	dbFile.write(block.tableName, MAX_TABLE_NAME);
	dbFile.write((char *)&(block.nextOffset), sizeof(int));
	dbFile.write((char *)&(block.contentSize), sizeof(int));
	dbFile.write((char *)&(block.isAlive), sizeof(bool));
	dbFile.write((char *)&(block.isIndex), sizeof(bool));

	// д��
	dbFile.seekp(block.offset+HEAD_LEN);
	dbFile.write(block.content, BLOCK_LEN);

	return;
}

void BufferManager::writeAllBlocks() {
	for(list<Block>::iterator i = buffer.begin(); i != buffer.end(); i ++ ) {
		writeBlock(*i);
	}
	return;
}


Block BufferManager::findBlock(int offset) {
	// ���ڻ����в��ң��ҵ�������ڻ�����ǰͷ
	for(list<Block>::iterator i = buffer.begin(); i != buffer.end(); i ++ ) {
		if( i->offset == offset ) {
			buffer.splice( buffer.begin(), buffer, i, std::next(i) );
			return *(buffer.begin());
		}
	}
	// �Ҳ�������������д��ɾ������ĩβ�飬���ļ������뻺��
	if(buffer.size() >= MAX_BLOCK_ACTIVE) {
		writeBlock(*(buffer.end()));
		buffer.pop_back();
	}
	buffer.push_front(readBlock(offset));
	return *(buffer.begin());
}


void BufferManager::readDbInfo() {
	char tableName[MAX_TABLE_NAME];
	int offset;
	infoFile.seekg(0);
	while( !infoFile.eof() ) {
		infoFile.read(tableName, MAX_TABLE_NAME);
		infoFile.read((char *)offset, sizeof(int));
		firstBlock.insert(pair<char[MAX_TABLE_NAME], int>(tableName, offset));
		infoFile.read((char *)offset, sizeof(int));
		lastBlock.insert(pair<char[MAX_TABLE_NAME], int>(tableName, offset));
	}
}


void BufferManager::writeDbInfo() {
	// ����ļ�
	infoFile.close();
	infoFile.open(infoFileName, std::fstream::out | std::fstream::in | std::fstream::trunc );
	for(
		hash_map<char[MAX_TABLE_NAME], int>::iterator i = firstBlock.begin(), j = lastBlock.begin();
		i != firstBlock.end();
		i ++, j++
	   ) {
		infoFile.write((char *)(i->first), MAX_TABLE_NAME);
		infoFile.write((char *)(i->second), sizeof(int));
		infoFile.write((char *)(j->second), sizeof(int));
	}
}


vector<Block> BufferManager::getTableBlocks(string tableName) {
	//ת��tableNameΪchar[]

	//��firstBlock���в���tableName�ĵ�һ���ַ

	//����vector�����Ҹ����в���index�Ŀ�
		//�ҵ���
			//����vector
			//vector<Block> a;
			//return a;
		//�Ҳ�����
			//����null
}


Block BufferManager::newBlock(string tableName) {
	//ת��tableNameΪchar[]

	//�½���Block��tableΪtableName, offsetΪdb�ļ�ĩβ����ֱ��д���ļ�ĩβ

	//����LastOffset�������һ�飬��������nextoffsetΪ�¿��offset������dirty

	//�����¿�
}
