#ifndef _CATALOG_H_
#define _CATALOG_H_
#include"minisql.h"

class catalog
{
public:
	catalog(void);
	virtual ~catalog(void);
	//�������ݿ�
	catainfo creat_Database(SqlCommand& sqlcmd);
	//������
	catainfo creat_Table(SqlCommand& sqlcmd);
	//��������
	catainfo creat_Index(SqlCommand& sqlcmd);
	//ѡ��
	catainfo select_Rec(SqlCommand& sqlcmd);
	//�����¼
	catainfo insert_Rec(SqlCommand& sqlcmd);
	//ɾ����¼
	catainfo delete_Rec(SqlCommand& sqlcmd);
	//ɾ������
	catainfo drop_Index(SqlCommand& sqlcmd);
	//ɾ����
	catainfo drop_Table(SqlCommand& sqlcmd);
	//ɾ�����ݿ�
	catainfo drop_Database(SqlCommand& sqlcmd);
	//ʹ�����ݿ�
	catainfo use_Database(SqlCommand& sqlcmd);
private:
	//�ж����ݿ��Ƿ����
	bool exist_Database(string dbname);
	//�жϱ��Ƿ����
	bool exist_Table(string dbname, string tbname);
	//�ж������Ƿ����
	bool exist_Index(string dbname, string tbname, string indname);
	//��ȡ������Ϣ
	attribute get_Attr(string dbname, string tbname, string attrname);

};
#endif
