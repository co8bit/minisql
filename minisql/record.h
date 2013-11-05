#ifndef _RECORD_H_
#define _RECORD_H_

#include "minisql.h"
#include "sqlcommand.h"
//#include "BufferManager.h"
#include "block.h"
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <strstream>
#include <sstream>
#include "minisql.h"
using namespace std;

#define BLOCK_LEN        4096
#define Used 0x01
#define Unused 0x00
///////////////////////////////////////////////////
class record
{
public:
	record(void){}
	virtual ~record(void){}
	//���Ҳ���
	recoinfo Select_Rec(SqlCommand& sql,table &Table);
	//ɾ������
	recoinfo Delete_Rec(SqlCommand& sql,table &Table);
	//�������
	recoinfo Insert_Rec(SqlCommand& sql,table &Table);
private:
    //����������ÿ��record
    Row parser(istrstream& inp,vector<attribute>& attrList);
    //��Ҫ����з��ؽ��
    void push(Row& oneTuple,Results& results,vector<int> colNamePosVector);
    //�ж��Ƿ�����Լ������
    bool checkConstraints(Row& oneTuple,vector<attribute>& attrList,vector<string>& condLeftVector,vector<string>& condOpVector,vector<string>& condRightVector);
	recoinfo writeblock(Block& blocks,int j,int tupleLen,vector<attribute>& attrList,vector<string>& colValueVector);//д��һ����¼
	Row getOneTuple(Block& blocks,int j,int tupleLen,vector<attribute>& attrList);
};
class BufferManager {
/*public:
        // �ڴ��еĻ�����
        Block buffer[MAX_BLOCK_ACTIVE];*/

public:                                                        // ���죬����
        // �����ݿ�����ʼ��buffermanager
        //BufferManager(string dbName);
	BufferManager(){}
        // д��������飬����buffermanager
	~BufferManager(){}

/*private:                                                // ���÷�������д
        // ��ĳ�ļ���һ��block
        Block readBlock(string fileName, int offset);
        // ��ĳ�ļ���n��������ŵ�block
        vector<Block> readBlocks(string fileName, int offset, int n);
        // ��blockд���ļ�
        bool writeBlock();
        // д�����л������е�block���ļ�
        bool writeAllBlocks();

private:                                                // ���÷�����LRU���
        // ����ĳ���LRU
        void updateLru(Block& b);
        // ���»��������п��LRU
        void updateAllLru();
*/
public:                                                        // RecordManagerʹ��
        // ����tableName�����п�
        static vector<Block> getTableBlocks(string tableName){
			Block block;
			vector<Block> blockVector;
			
			for (int i=0;i<2;i++){
			if (i>=1){
				block.fileName="student.table";                        // �ļ���(���ݿ���)
				block.tableName="student";                        // ����
				//block.offset=i*4096;
				// block���ļ��е�ƫ����
				block.content[0]=1;block.content[1]='2';block.content[2]='3';block.content[3]='4';
				block.content[4]='5';block.content[5]='6';block.content[6]='\0';block.content[7]='W';
				block.content[8]='D';block.content[9]='\0' ;block.content[10]=22;block.content[11]=0;
				block.content[12]=0;block.content[13]=0;block.content[14]='M';block.content[15]='\0';

				block.content[16]=1;block.content[17]='2';block.content[18]='2';block.content[19]='2';
				block.content[20]='2';block.content[21]='2';block.content[22]='\0';block.content[23]='Y';
				block.content[24]='S';block.content[25]='\0' ;block.content[26]=20;block.content[27]=0;
				block.content[28]=0;block.content[29]=0;block.content[30]='M';block.content[31]='\0';

				block.content[32]=1;block.content[33]='3';block.content[34]='3';block.content[35]='3';
				block.content[36]='3';block.content[37]='3';block.content[38]='\0';block.content[39]='S';
				block.content[40]='F';block.content[41]='\0' ;block.content[42]=16;block.content[43]=0;
				block.content[44]=0;block.content[45]=0;block.content[46]='F';block.content[47]='\0';

				block.content[48]=1;block.content[49]='4';block.content[50]='4';block.content[51]='4';
				block.content[52]='4';block.content[53]='4';block.content[54]='\0';block.content[55]='Z';
				block.content[56]='H';block.content[57]='\0' ;block.content[58]=22;block.content[59]=0;
				block.content[60]=0;block.content[61]=0;block.content[62]='F';block.content[63]='\0';

				/*for (int j=0;j<BLOCK_LEN;j++){
					if ((j%16)==0) block.content[j]=0x00;
					else
					block.content[j]=0x01;       // ����
				}*/
				block.contentSize=BLOCK_LEN;                        // ���ݳ���
			    block.dirty=false;                                        // �Ƿ���Ҫд���ļ�
				//bool active;                                // for lru
				//int value;                                        // for lru
			}
			else {
				block.fileName="student.table";                        // �ļ���(���ݿ���)
				block.tableName="student";                        // ����
				//block.offset=i*4096;                                        // block���ļ��е�ƫ����
				for (int j=0;j<BLOCK_LEN;j++){
					if ((j>=0)&&(j<=31)) block.content[j]=0x00;
					else block.content[j]=0x00;       // ����
				}
				block.contentSize=BLOCK_LEN;                        // ���ݳ���
				block.dirty=false;                                        // �Ƿ���Ҫд���ļ�
				//bool active;                                // for lru
				//int value;							// for lru
			}
			blockVector.push_back(block);
			}
			return blockVector;
		}

		static Block newBlock(string tableName){
			Block block;
			block.fileName="student.table";                        // �ļ���(���ݿ���)
				block.tableName="student";                        // ����
				//block.offset=i*4096;                                        // block���ļ��е�ƫ����
				//block.content[BLOCK_LEN];        // ����
				for (int j=0;j<BLOCK_LEN;j++){
					block.content[j]=0x00;;        // ����
				}
				block.contentSize=BLOCK_LEN;                        // ���ݳ���
			    block.dirty=true;                                        // �Ƿ���Ҫд���ļ�
				//bool active;                                // for lru
				//int value;                                        // for lru
				return block;
		}
        // ����tableName��ĳ���飨offset��IndexManagerȡ�ã���
        //static Block getTableBlock(string tableName, int offset);

//public:                                                        // IndexManagerʹ��
        // ����indexName�����п�
        //vector<Block> getIndexBlocks(string IndexName);
};
#endif
