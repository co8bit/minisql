#include "record.h"
using namespace std;

void record::push(Row& oneTuple,Results& results,vector<int> colNamePosVector){
    Row row;
    int i;

    for (i=0;i<colNamePosVector.size();i++)
    {
        row.col.push_back(oneTuple.col[colNamePosVector[i]]);
    }
    results.row.push_back(row);
}


bool record::checkConstraints(Row& oneTuple,vector<attribute>& attrList,vector<string>& condLeftVector,vector<string>& condOpVector,vector<string>& condRightVector){

    string condLeft;
    int pos;
    int type,condtype;

    for ( int i = 0 ; i < condLeftVector.size(); i ++ )
    {
        condLeft=condLeftVector[i];
        for (int j=0;j<attrList.size();j++){
            if (!condLeft.compare(attrList[j].name)){
                pos=j;
                break;
            }
        }
        if (attrList[pos].datatype==0){type=0;}
        else if (attrList[pos].datatype==-1){type=-1;}
        else type=1;
        if (!condOpVector[i].compare("<")) condtype=1;
        if (!condOpVector[i].compare("<=")) condtype=2;
        if (!condOpVector[i].compare("==")) condtype=3;
        if (!condOpVector[i].compare("!=")) condtype=4;
        if (!condOpVector[i].compare(">=")) condtype=5;
        if (!condOpVector[i].compare(">")) condtype=6;
        switch ( type )
        {

            case 0:
            {
				int value2 = atoi( condRightVector[i].c_str() );
                int value1 = atoi( oneTuple.col[pos].c_str());
                switch ( condtype) {
                    case 1:
                        if ( value1 >= value2 ) //<
                            return false ;
                        break ;
                    case 2:
                        if ( value1 > value2 ) //<=
                            return false;
                        break ;
                    case 3:
                        if ( value1 != value2 ) //==
                            return false ;
                        break ;
                    case 4:
                        if ( value1 == value2 ) //!=
                            return false ;
                        break ;
                    case 5:
                        if ( value1 < value2  ) //>=
                            return false ;
                        break ;
                    case 6:
                        if ( value1 <= value2 ) //>
                            return false ;
                        break ;
                }
            }
                break ;
            case -1:
            {
                float value2 = atof( condRightVector[i].c_str());
				float value1 = atof( oneTuple.col[pos].c_str());
                switch ( condtype) {
                    case 1:
                        if ( value1 >= value2 ) //<
                            return false ;
                        break ;
                    case 2:
                        if ( value1 > value2 ) //<=
                            return false;
                        break ;
                    case 3:
                        if ( value1 != value2 ) //==
                            return false ;
                        break ;
                    case 4:
                        if ( value1 == value2 ) //!=
                            return false ;
                        break ;
                    case 5:
                        if ( value1 < value2  ) //>=
                            return false ;
                        break ;
                    case 6:
                        if ( value1 <= value2 ) //>
                            return false ;
                        break ;
                }
            }
                break ;
            case 1:
            {
                string value2 = condRightVector[i];
                string value1 =  oneTuple.col[pos] ;
                switch ( condtype) {
                    case 1:
                        if ( value1 >= value2 ) //<
                            return false ;
                        break ;
                    case 2:
                        if ( value1 > value2 ) //<=
                            return false;
                        break ;
                    case 3:
                        if ( value1 != value2 ) //==
                            return false ;
                        break ;
                    case 4:
                        if ( value1 == value2 ) //!=
                            return false ;
                        break ;
                    case 5:
                        if ( value1 < value2  ) //>=
                            return false ;
                        break ;
                    case 6:
                        if ( value1 <= value2 ) //>
                            return false ;
                        break ;
                }

            }
                break ;
        }
    }
    return true ;
}

recoinfo record::writeblock(Block& blocks,int j,int tupleLen,vector<attribute>& attrList,vector<string>& colValueVector){
	int i,k,p=1;
	float floatNum;
	int intNum;
	string str;
	bool succ=false;
	Results results;
	int num=0;
	string message="";

	for (k=0;k<attrList.size();k++){
		//float
        if (attrList[k].datatype==-1){
			floatNum=atof(colValueVector[k].c_str());
            memcpy(blocks.content+j*tupleLen+p,&floatNum,sizeof(float));
			p+=sizeof(float);
			//д��ȥ
        }
		//int
        else if(attrList[k].datatype==0) {
			intNum=atof(colValueVector[k].c_str());
			memcpy(blocks.content+j*tupleLen+p,&intNum,sizeof(int));
			p+=sizeof(int);
        }
		//string
        else {
            str=colValueVector[k];
			//���ȱ�datatype�������ش�����Ϣ
			if ((str.length()+1)>attrList[k].datatype){
				succ=false;
				message="Insertion failed. Format inconsistency in "+attrList[k].name;
				return recoinfo(succ,message,results,num);
			}
			//���ȱ�datatype�̣�������Ҫ���ɶ���
			else if ((str.length()+1)<attrList[k].datatype){
				int diff=attrList[k].datatype-str.length();
				for (i=0;i<diff;i++){ str.insert(0," ");}
			}
			memcpy(blocks.content+j*tupleLen+p,str.c_str(),attrList[k].datatype);
			p+=attrList[k].datatype;
		}
    }
	blocks.content[j*tupleLen]=Used;
	blocks.dirty=true;
	succ=true;
	message="Insertion suceeded";
	num=num+1;
	return recoinfo(succ,message,results,num);
}

Row record::getOneTuple(Block& blocks,int j,int tupleLen,vector<attribute>& attrList){
	int i,k,p=1;
	float floatNum;
	int intNum;
	string str;
	char ch[255];
	bool succ=false;
	int num=0;
	Row oneTuple;
	stringstream ss;

	for (k=0;k<attrList.size();k++){
		//float
        if (attrList[k].datatype==-1){
            memcpy(&floatNum,blocks.content+j*tupleLen+p,sizeof(float));
			p+=sizeof(float);
			ss<<floatNum;
            oneTuple.col.push_back(ss.str());	
        }
		//int
        else if(attrList[k].datatype==0) {
			memcpy(&intNum,blocks.content+j*tupleLen+p,sizeof(int));
			p+=sizeof(int);
			ss<<intNum;
			oneTuple.col.push_back(ss.str());
        }
		//string
        else {
			memcpy(ch,blocks.content+j*tupleLen+p,attrList[k].datatype);
			p+=attrList[k].datatype;
			str=ch;//???
			oneTuple.col.push_back(str);
		}
    }
	return oneTuple;
}

recoinfo record::Select_Rec(SqlCommand& sql,table &Table)
{
	int i,j;
	long num=0;//���ҵ��ļ�¼��
	Row row;//ÿ��
	Results results;//�ܽ��
	BufferManager BM;
	bool succ=false;//�����Ƿ�ɹ�
	string message="";//����ʧ�ܵ���Ϣ
    string databaseName=Table.dbname;
	string tableName=Table.name;//��صı�����
	vector<attribute> attrList=Table.attrList;//������������б�
	vector<string> colNameVector=sql.getcolNameVector();//��Ҫ���ҵ�����
	vector<int> colNamePosVector;
	vector<string> condLeftVector=sql.getCondLeftVector();//������ֵ
	vector<string> condOpVector=sql.getCondOpVector();//����������
	vector<string> condRightVector=sql.getCondRightVevtor();//������ֵ
    vector<Block> blockVector=BM.getTableBlocks(tableName);//����buffer���õ�block
    bool whereFlag=false;//�ж�sql����ľ��where
    int blockLen;//��ǰblock���м�����¼
    int tupleLen=Table.recLength+1;//������ÿ��rec�ĳ���
    Block blocks;
    Row oneTuple;

	//���colname=��*��,��attrList������colname��
	if (!colNameVector.at(0).compare("*"))
	{
		colNameVector.clear();
		for (i=0;i<attrList.size();i++)
			colNameVector.push_back(attrList.at(i).name);
	}
	//��¼��ѯ�������ڱ����Ե�λ�ã�����֮��Ĳ�����
	string colName;
	colNamePosVector.clear();
	for (i=0;i<colNameVector.size();i++){
        colName=colNameVector[i];
        for (j=0;j<attrList.size();j++){
            if (!colName.compare(attrList[j].name)) colNamePosVector.push_back(j);
        }
	}
	//��ѯ�����һ�д�����������������
	row.col=colNameVector;
	results.row.push_back(row);

	if (condLeftVector.size()) whereFlag=true;//�ж��ǲ��Ǻ�where����
    for (i=0;i<blockVector.size();i++){
        blocks=blockVector[i];
        blockLen=blocks.getSize()/tupleLen;
        for (j=0;j<blockLen;j++){
            //����ɾ�����ݣ���������ݲ�����
            if (blocks.content[j*tupleLen]==Used){
				oneTuple=getOneTuple(blocks,j,tupleLen,attrList);
                //�����where������������Ƚϲ���
                //���ľ��where�����ñȽ�
                if (!whereFlag)
                    { push(oneTuple,results,colNamePosVector); num++;succ=true;}
                else
                    if (checkConstraints(oneTuple,attrList,condLeftVector,condOpVector,condRightVector))
                        { push(oneTuple,results,colNamePosVector);num++;succ=true;}
            }
        }
    }

//������Ϣ
if (num==0) {succ=false; message="The results is null.";}
return recoinfo(succ,message,results,num);
}


recoinfo record::Delete_Rec(SqlCommand& sql,table &Table)
{
	int i,j;
	long num=0;//���ҵ��ļ�¼��
	Row row;//ÿ��
	Results results;//�ܽ��
	bool succ=false;//�����Ƿ�ɹ�
	string message="";//����ʧ�ܵ���Ϣ
    string databaseName=Table.dbname;
	string tableName=Table.name;//��صı�����
	vector<attribute> attrList=Table.attrList;//������������б�
	vector<string> condLeftVector=sql.getCondLeftVector();//������ֵ
	vector<string> condOpVector=sql.getCondOpVector();//����������
	vector<string> condRightVector=sql.getCondRightVevtor();//������ֵ
    vector<Block> blockVector=BufferManager::getTableBlocks(tableName);//����buffer���õ�block
    bool whereFlag=false;//�ж�sql����ľ��where
    int blockLen;//��ǰblock���м�����¼
    int tupleLen=Table.recLength+1;//������ÿ��rec�ĳ���
    Block blocks;
    Row oneTuple;

	if (condLeftVector.size()) whereFlag=true;//�ж��ǲ��Ǻ�where����
    for (i=0;i<blockVector.size();i++){
        blocks=blockVector[i];
        blockLen=blocks.getSize()/tupleLen;
        for (j=0;j<blockLen;j++){
            //����ɾ�����ݣ���������ݲ�����
            if (blocks.content[j*tupleLen]==Used){
				oneTuple=getOneTuple(blocks,j,tupleLen,attrList);
                //�����where������������Ƚϲ���
                //���ľ��where�����ñȽ�
                if (!whereFlag)
                    { blocks.content[j*tupleLen]=Unused;num++;blocks.dirty=true; succ=true;}
                else
                    if (checkConstraints(oneTuple,attrList,condLeftVector,condOpVector,condRightVector))
                        { blocks.content[j*tupleLen]=Unused;num++;blocks.dirty=true; succ=true;}
            }
        }
		blockVector[i]=blocks;
    }

//������Ϣ
stringstream ss;
ss<<num;
message="Total "+ss.str()+" record(s) in deletion";
return recoinfo(succ,message,results,num);
}


recoinfo record::Insert_Rec(SqlCommand& sql,table &Table)
{
	int i,j,k;
	long num=0;//���ҵ��ļ�¼��
	Row row;//ÿ��
	Results results;//�ܽ��
	recoinfo recoInfo;
	bool succ=false;//�����Ƿ�ɹ�
	string message="";//����ʧ�ܵ���Ϣ
    string databaseName=Table.dbname;
	string tableName=Table.name;//��صı�����
	vector<attribute> attrList=Table.attrList;//������������б�
    vector<string> colValueVector=sql.getcolValueVector();//��Ҫ�����rec��ֵ
    vector<Block> blockVector=BufferManager::getTableBlocks(tableName);//����buffer���õ�block
    bool whereFlag=false;//�ж�sql����ľ��where
    int blockLen;//��ǰblock���м�����¼
    int tupleLen=Table.recLength+1;//������ÿ��rec�ĳ���
    Block blocks;
    Row oneTuple;
	int p;

    //������catalog���Ѿ��ж�insert��ֵ��������������һ��
    int intNum;
    float floatNum;
    string str;

    for (i=0;i<blockVector.size();i++){
        blocks=blockVector[i];
        blockLen=blocks.getSize()/tupleLen;
		p=1;
        for (j=0;j<blockLen;j++){
            //����ɾ�����ݣ���ɾ�������滻��������
            if (blocks.content[j*tupleLen]==Unused){
				recoInfo=writeblock(blocks,j,tupleLen,attrList,colValueVector);//д��һ����¼
				if (recoInfo.getsucc()) {blockVector[i]=blocks;return recoInfo;}
				else  return recoInfo;

			}
        }
    }

	//д�������
	{
		//���һ��block��д����
		if (blockLen<(BLOCK_LEN/tupleLen)){
			i=blockVector.size()-1;
			recoInfo=writeblock(blocks,j,tupleLen,attrList,colValueVector);//д��һ����¼
			if (recoInfo.getsucc()) {blocks.contentSize+=tupleLen; blockVector[i]=blocks; return recoInfo;}
		}
		//�½���һ��block
		else {
			blocks=BufferManager::newBlock(tableName);
			recoInfo=writeblock(blocks,0,tupleLen,attrList,colValueVector);//д��һ����¼
			if (recoInfo.getsucc()) {blocks.contentSize+=tupleLen;return recoInfo;}
		}
	}
//������Ϣ
if (num==0) {succ=false; message="The results is null.";}
return recoinfo(succ,message,results,num);
}

