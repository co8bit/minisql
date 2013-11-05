#ifndef _RECORD_H_
#define _RECORD_H_

#include "minisql.h"
#include "sqlcommand.h"
#include "BufferManager.h"
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

#endif
