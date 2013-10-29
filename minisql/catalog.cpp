#include "catalog.h"

bool catalog::check(int t, string& str){
	bool isint = true;
	bool isfloat = true;
	if (!(str.find('.') < str.length() && str.find_first_of('.') == str.find_last_of('.')))
		isfloat = false;
	for (int i=0; i<str.length(); i++)
		if (str[i] < '0' && str[i] > '9'){
			isint = false;
			if (str[i] != '.')
				isfloat = false;
		}
	if (t == 0 && isint)
		return true;
	if (t == -1 && isfloat)
		return true;
	if (t >= 1)
		return true;
	return false;
}

catalog::catalog(void)
{
}

catalog::~catalog(void)
{
}

void catalog::init(string& dbname){
	fstream fout;
	fout.open(dbname + ".list",ios::out | ios::binary);

	tableNum t(0);
	writeHead(fout, t);
}

void catalog::writeHead(fstream& f, tableNum& t)
{
	f.write((char *)(t.num), sizeof(int));
    f.flush();
}

void catalog::readHead(fstream& f, tableNum& t){
	f.read((char *)&(t.num), sizeof(int));
}

void catalog::readTable(fstream& f, table& t){
	char buf[MAX_CHAR_LENGTH];
	f.read((char *)buf, MAX_CHAR_LENGTH);
	f.read((char *)&(t.attrNum), sizeof(int));
	f.read((char *)&(t.recLength), sizeof(int));
	t.name = buf;
	for (int i = 0; i < t.attrNum; i++)
		readAttr(f, t.attrList[i]);
}

void catalog::writeTable(fstream& f, table& t){
	f.write((char *)t.name.c_str(), MAX_CHAR_LENGTH);
	f.write((char *)&(t.attrNum), sizeof(int));
	f.write((char *)&(t.recLength), sizeof(int));
	for (int i = 0; i < t.attrNum; i++)
		writeAttr(f, t.attrList[i]);
	f.flush();
}

void catalog::readAttr(fstream& f, attribute& attr){
	char buf[MAX_CHAR_LENGTH];
	f.read((char *)buf, MAX_CHAR_LENGTH);
	f.read((char *)&(attr.datatype), sizeof(int));
	f.read((char *)&(attr.length), sizeof(int));
	f.read((char *)&(attr.PK), sizeof(bool));
	f.read((char *)&(attr.UN), sizeof(bool));
	f.read((char *)&(attr.NN), sizeof(bool));
	attr.name = buf;
}

void catalog::writeAttr(fstream& f, attribute& attr){
	f.write((char *)attr.name.c_str(), MAX_CHAR_LENGTH);
	f.write((char *)&(attr.datatype), sizeof(int));
	f.write((char *)&(attr.length), sizeof(int));
	f.write((char *)&(attr.PK), sizeof(bool));
	f.write((char *)&(attr.UN), sizeof(bool));
	f.write((char *)&(attr.NN), sizeof(bool));
	f.flush();
}

catainfo catalog::creat_Table(SqlCommand& cmd){
	string dbname = cmd.getDatabaseName();
	table tmptable;
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);

	string tname = cmd.getTableName();
	bool existt = exist_Table(dbname, tname);
	if (existt)
		return catainfo(false, "Table " + tname + " Has Already Exist!", tmptable);

	

	fstream f;
	f.open(dbname + ".list", ios::in | ios::out | ios::beg);
	tableNum tnum;
	f.seekg(0, ios::beg);
	readHead(f, tnum);
	tnum.num++;
	f.seekp(0, ios::beg);
	writeHead(f, tnum);
	f.seekp(0, ios::end);
	writeTable(f, tmptable);
	f.close();
	return catainfo(true, "", tmptable);
}

catainfo catalog::drop_Table(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);

	string tname = cmd.getTableName();
	bool existt = exist_Table(dbname, tname);
	if (!existt)
		return catainfo(false, "Table " + tname + " Do Not Exist!", tmptable);
	
	fstream f;
	f.open(dbname + ".list", ios::in | ios::out | ios::binary);
	tableNum tnum;
	//������ͷ����
	f.seekg(0, ios::beg);
	readHead(f, tnum);

	int readPos = f.tellg();
	int TN = tnum.num;
	tnum.num--;
	f.seekp(0, ios::beg);
	writeHead(f, tnum);
	// �������б����ҵ�Ҫɾ���ı��λ��
	int n = 0;      //��n��������Ҫɾ���ı���
	int pos = 0;    //ɾ���ı������ʼ��ַ

	f.seekg(readPos);
	// ���ٿռ������б���
	vector <table> tables;
	for (int i = 0; i < TN; i++){
        readTable(f, tmptable);
		tables.push_back(tmptable);
		if (tmptable.name == tname){
            n = i;
            pos = (int)f.tellg() - (int)TABLENODE_SIZE_IN_FILE;
        }
    }
	
    // �ӵ�ַ pos ����ʼд��� n + 1 �������ı���Ϣ��
    f.seekp(pos);
    for (int i = n + 1; i < TN; i++)
        writeTable(f, tables[i]);

    f.close();
    return catainfo(true, "", tmptable);
}

catainfo catalog::creat_Database(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (existdb){
		return catainfo(false, "Database " + dbname + " Has Already Exist!", tmptable);
	}else{
		init(dbname);
		return catainfo(true, "", tmptable);
	}
}

catainfo catalog::drop_Database(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);
	string del = dbname + ".list";

	if (!DeleteFile(del.c_str()))
		return catainfo(false, "Can't Delete File " + dbname + ".list!", tmptable);
	return catainfo(true, "", tmptable);
}

catainfo catalog::insert_Rec(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);

	string tname = cmd.getTableName();
	bool existt = exist_Table(dbname, tname);
	if (!existt)
		return catainfo(false, "Table " + tname + " Do Not Exist!", tmptable);
	tableNum tnum;
	fstream f;
	f.open(dbname + ".list", ios::in | ios::out | ios::binary);
	//������ͷ����
	f.seekg(0, ios::beg);
	readHead(f, tnum);
	int TN = tnum.num;

	for (int i = 0; i < TN; i++){
        readTable(f, tmptable);
		if (tmptable.name == tname)
			break;
    }
	//vector<string> tmpCNV = cmd.getcolNameVector();
	vector<string> tmpCVV = cmd.getcolValueVector();
	if (tmptable.attrNum != tmpCVV.size())
		return catainfo(false, "The number of Attribute is Wrong!", tmptable);

	for (int i=0; i<tmptable.attrNum; i++){
		if (!check(tmptable.attrList[i].datatype, tmpCVV[i]))
			return catainfo(false, "The Type of Arrtibute " + tmptable.attrList[i].name + 
			" Should Be" + tmptable.attrList[i].typeName() + "!", tmptable);
	}
	f.close();
	return catainfo(true, "", tmptable);
}

catainfo catalog::select_Rec(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);

	string tname = cmd.getTableName();
	bool existt = exist_Table(dbname, tname);
	if (!existt)
		return catainfo(false, "Table " + tname + " Do Not Exist!", tmptable);
	
	fstream f;
	f.open(dbname + ".list", ios::in | ios::out | ios::binary);
	tableNum tnum;
	//������ͷ����
	f.seekg(0, ios::beg);
	readHead(f, tnum);
	int TN = tnum.num;
	
	for (int i = 0; i < TN; i++){
        readTable(f, tmptable);
		if (tmptable.name == tname)
			break;
    }
	vector<string> CLV = cmd.getCondLeftVector();
	vector<string> COV = cmd.getCondOpVector();
	vector<string> CRV = cmd.getCondRightVevtor();

	bool flag;
	for (int j=0; j<CLV.size(); j++){
		flag = false;
		for(int i=0; i<tmptable.attrNum; i++){
			if (tmptable.attrList[i].name == CLV[j]){
				flag = true;
				if (!check(tmptable.attrList[i].datatype, CRV[j]))
					return catainfo(false, "The Type of Arrtibute " + tmptable.attrList[i].name + 
					" Should Be" + tmptable.attrList[i].typeName() + "!", tmptable);
			}
		}
		if (!flag) 
			return catainfo(false, "Don't Have Attribute " + CLV[j], tmptable);
	}
	return catainfo(true, "", tmptable);
}

catainfo catalog::delete_Rec(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);

	string tname = cmd.getTableName();
	bool existt = exist_Table(dbname, tname);
	if (!existt)
		return catainfo(false, "Table " + tname + " Do Not Exist!", tmptable);
	
	fstream f;
	f.open(dbname + ".list", ios::in | ios::out | ios::binary);
	tableNum tnum;
	//������ͷ����
	f.seekg(0, ios::beg);
	readHead(f, tnum);
	int TN = tnum.num;

	for (int i = 0; i < TN; i++){
        readTable(f, tmptable);
		if (tmptable.name == tname)
			break;
    }
	vector<string> CLV = cmd.getCondLeftVector();
	vector<string> COV = cmd.getCondOpVector();
	vector<string> CRV = cmd.getCondRightVevtor();

	bool flag;
	for (int j=0; j<CLV.size(); j++){
		flag = false;
		for(int i=0; i<tmptable.attrNum; i++){
			if (tmptable.attrList[i].name == CLV[j]){
				flag = true;
				if (!check(tmptable.attrList[i].datatype, CRV[j]))
					return catainfo(false, "The Type of Arrtibute " + tmptable.attrList[i].name + 
					" Should Be" + tmptable.attrList[i].typeName() + "!", tmptable);
			}
		}
		if (!flag) 
			return catainfo(false, "Don't Have Attribute " + CLV[j], tmptable);
	}
	return catainfo(true, "", tmptable);
}

catainfo catalog::use_Database(SqlCommand& cmd){
	table tmptable;
	string dbname = cmd.getDatabaseName();
	bool existdb = exist_Database(dbname);
	if (!existdb)
		return catainfo(false, "Database " + dbname + " Do Not Exist!", tmptable);
	else
		return catainfo(true, "", tmptable);
}

bool catalog::exist_Table(string& dbname, string& tname){
	bool flag = false;
	fstream f;
	f.open(dbname + ".list", ios::in | ios::binary);

	tableNum tnum;
	table t;
	readHead(f, tnum);
	int Maxn = tnum.num;

	for (int i=0; i<Maxn; i++){
		readTable(f, t);
		if (t.name == tname){
			flag = true;
			break;
		}
	}
	f.close();
	return flag;
}

bool catalog::exist_Database(string& dbname){
	fstream f;
	f.open(dbname+".list",ios::in);
	if(!f)
		return false;
	else{
		f.close();
		return true;
	}
}