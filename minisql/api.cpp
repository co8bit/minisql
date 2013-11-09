#include "api.h"
#include <iostream>
using namespace std;
#include "catalog.h"
#include "interpreter.h"
#include "minisql.h"
#include "sqlcommand.h"
#include "record.h"
api::api(void)
{
}

api::~api(void)
{
}

api::api(int t, SqlCommand& c){
	type =t;
	sql = c;
	
	string succ = "Operation Succeeds";
	extern string Wdbname;
	if (Wdbname == ""){
		if (type == SQL_CREATE_DATABASE || type == SQL_USE)
			Wdbname = c.getDatabaseName();
		else{
			cout<<"Please Use database"<<endl;
			return;
		}
	}else
		sql.setDatabaseName(Wdbname);
	c.writelog();
	catalog CL;
	record RE;
        switch (t){
                case ( SQL_CREATE_DATABASE ):{

					sql.setDatabaseName(Wdbname);
					cataInfo = CL.creat_Database(sql);//����catalog���creat_Database����
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                            break;
                        }
                        //�ɹ�������ɹ���ʾ
                        else cout<<succ<<endl;
                        break;
                }
                case ( SQL_CREATE_TABLE    ):{
                       cataInfo = CL.creat_Table(sql);//����catalog�����creat_table����
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                             break;
                        }
                        //�ɹ�
                        else{
                            Table=cataInfo.gettable();
                           // indexInfo=index::create_index(sql,Table);//����table��Ϣ���Ƿ�������������������Ͱ�create_index_on ����;
                            //����������������ʧ��
                            //if (!indexInfo.succ) {
                              //  indexInfo.print();//���ʧ��ԭ��
                                //SqlCommand sql1;//������ָ����ڳ����ոս�����table
                                //sql1.type=SQL_DROP_TABLE;
                                //sql1.tableName=sql.getTableName();
                                //sql1.databaseName=sql.getDatabaseName();
                                cataInfo = CL.drop_Table(sql);//rollback������table
                               // break;
                            //}
                            //else cout<<succ<<endl;//�ɹ�����ʾ�ɹ���Ϣ
                        }
                        break;
                }
                case ( SQL_CREATE_INDEX    ):{//???��ʲô������
                        break;
                }
                case ( SQL_CREATE_INDEX_ON ):{
                        //???����һ������Table��Ϣ�ĺ���,ȷ��table����������������index����û�У��������ɹ�����Ҫ��дTable��Ϣ������ײ��ļ����������ʧ��ԭ��
                        //cataInfo=find_Table(sql,Table,0);//0��ʾcreate index
						cataInfo = CL.creat_Index(sql);//����catalog���creat_Index�����������ж�table�Ƿ���ڣ������Ƿ���ڣ�����index������table��Ϣ��
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
                             cataInfo.print();
                             break;
                        }
                        //�ɹ�������index��create_index_on���������ڽ����������Ե�����
                        else{
							Table = cataInfo.gettable();
                            //indexInfo=index::create_index_on(sql,Table);
                            //ʧ��
                            //if (!indexInfo.succ){
                                //indexInfo.print();
                              //  break;
                            }
                            //�ɹ�
                            //else{
                                //����table��Ϣ
                                string attrname=sql.getcolName();
                                attrList=Table.attrList;
                                int size=attrList.size();
                                for (int i=0;i<size;i++){
                                    if (attrList.at(i).name.compare(attrname))
                                        { attrList.at(i).ID=true; break;}
                              //  }
                                Table.attrList=attrList;
                                CL.change_Table(Table);//����catalog���change_Tavble��������д�������
                                //indexInfo.print();
                            //}
                        }
                        break;
                }
                case ( SQL_DROP_DATABASE   ):{
                        cataInfo = CL.drop_Database(sql);//����catalog���drop_Database����
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc())
							cataInfo.print();
                        //�ɹ�������ɹ���Ϣ
                        else cout<<succ<<endl;
                        break;
                }
                case ( SQL_DROP_TABLE      ):{
                        cataInfo = CL.drop_Table(sql);//����catalog���drop_Table����
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()) 
						{ cataInfo.print();}
                        //�ɹ���ɾ����ص�index������ɹ���Ϣ
                        else{
                            Table=cataInfo.gettable();
                            //indexInfo=index::drop_index_all(sql,Table);//��table�йص�����index��ɾ��
                            //������ɾ��indexʧ�ܣ���û�����ô�죻
                            //if (!indexInfo.succ){
                            //    indexInfo.print();
                            //    break;
                            //}
                            //ɾ���ɹ�������ɹ���ʾ
                            //else cout<<succ<<endl;
                        }
                        break;
                }
               /* case ( SQL_DROP_INDEX      ):{
                        cataInfo=CL.drop_Index(sql);//����catalog���drop_Index���������table��Ϣ
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                            break;
                        }
                        //�ɹ�������ɹ���ʾ��ɾ��index
                        else{
                            Table=cataInfo.gettable();
                           // indexInfo=index::drop_index(sql,Table);//����ָ���index ɾ��index
                            //ʧ�ܣ����ʧ��ԭ��
                            //if (!indexInfo.succ){
                             //   indexInfo.print();
                                break;
                            }
                            //�ɹ�������table��Ϣ������ɹ���ʾ
                            //else{
                                //����table��Ϣ
                                string attrname=sql.getcolName();//����������sql���������������Ӧ�ô�indexInfo�л�ȡ
                                attrList=Table.attrList;
                                int size=attrList.size();
                                for (int i=0;i<size;i++){
                                    if (attrList.at(i).name.compare(attrname))
                                        { attrList.at(i).ID=false; break;}
                                ///}
                                Table.attrList=attrList;
                                CL.change_Table(Table);//����catalog���change_Tavble��������д�������
                                //indexInfo.print();
                            //}
                        }
                        break;
                }*/

                /*case ( SQL_SELECT          ):{
                        //ȷ��table������ȷ�������ǶԵ��
                        cataInfo = CL.select_Rec(sql);
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                            break;
                        }
                        //�ɹ�������������������where���ò�ͬ���selec_Rec����
                        else{
                            Table=cataInfo.gettable();
                            //��where����
                            if (sql.condLeftVector.size()==0){
                                recoInfo=RE.Select_Rec(sql,Table);
                                //ʧ�ܣ������ʧ����Ϣ���������Ϊ�յ���Ϣ��
								if (!recoInfo.getsucc()){
									recoInfo.print();
									break;
								}
                                //else RE.print_results(recoInfo.results,-1);//������
                            }
                            //��where����
                            else{
                                bool f=false;
                                attrList=Table.attrList;
                                int i;
                                int asize=attrList.size();
                                indexList.clear();
                                for (i=0;i<asize;i++){
                                    if (attrList.at(i).ID){indexList.push_back(attrList.at(i).name);f=true;}//???
                                }
                                //������
                                if (f){
                                    //indexInfo=index::Select_Rec(sql,Table,indexList);//��֪��indexList������ʽ�ǲ��ǻ᷽����ң��ɸ�
                                    //if (!indexInfo.succ){cout<<indexInfo.message<<endl;break;}
                                    //else print_results(indexInfo.results,-1);//???
                                }
                                //������
                                else {
                                    recoInfo=RE.Select_Rec(sql,Table);
                                    if (!recoInfo.getsucc()){
										recoInfo.print();
										break;
									}
                                    //else print_results(recoInfo.results,-1);//???
                                }
                            }
                        }
                        break;
                }*/
                /*case ( SQL_INSERT_INTO     ):{
                        //ȷ��table������ֵ�ĸ����Ƿ��ǶԵ�
                        cataInfo = CL.insert_Rec(sql);
                        //ʧ�ܣ����ʧ��ԭ��
                        if (!cataInfo.getsucc()){
                             cataInfo.print();
                             break;
                        }
                        //�ɹ�����������ò�ͬģ���insert_Rec����
                        else{
                            Table=cataInfo.gettable();
                            bool f=false;
                            attrList=Table.attrList;
                            int i;
                            int asize=attrList.size();
                            indexList.clear();
                            for (i=0;i<asize;i++){
                                if (attrList.at(i).ID){indexList.push_back(attrList.at(i).name);f=true;}//???
                            }
                            //������
                            if (f){
                                //indexInfo=index::Insert_Rec(sql,Table,indexList);//��֪��indexList������ʽ�ǲ��ǻ᷽����ң��ɸ�
                                //if (!indexInfo.succ){cout<<indexInfo.message<<endl;break;}
                                //else {
                                    //Table.attrNum+=indexInfo.number;//����Table��Ϣ
                                    CL.change_Table(Table); //��д
                                    //cout<<indexInfo.message<<endl;
                                //}
                            }
                            //������
                            else {
                                recoInfo=RE.Insert_Rec(sql,Table);
                                if (!recoInfo.getsucc()){
									recoInfo.print();
									break;
								}
                                else {
                                    Table.attrNum+=recoInfo.nummes();
                                    CL.change_Table(Table);
                                    recoInfo.print();
                                }
                            }
                        }
                        break;
                }*/
               /* case ( SQL_DELETE          ):{
                        //ȷ��table������ȷ�������ǶԵ��
                        cataInfo = CL.delete_Rec(sql);
                        //ʧ�ܣ������ʧ��ԭ��
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                             break;
                        }
                        //�ɹ������շ�����ò�ͬģ���Delete_Rec����
                        else{
                            Table=cataInfo.gettable();
                            //��where����
                            if (sql.condLeftVector.size()==0){
                                recoInfo=RE.Delete_Rec(sql,Table);
                                if (!recoInfo.getsucc()){
									recoInfo.print();
									break;
								}
                                else {
									Table.attrNum-=recoInfo.nummes();//����table��Ϣ
                                    CL.change_Table(Table);//��д
									recoInfo.print();
								}
                            }
                            //��where����
                            else{
                                bool f=false;
                                attrList=Table.attrList;
                                int i;
                                int asize=attrList.size();
                                indexList.clear();
                                for (i=0;i<asize;i++){
                                    if (attrList.at(i).ID){indexList.push_back(attrList.at(i).name);f=true;}
                                }
                                //������
                                if (f){
                                    //indexInfo=index::Delete_Rec(sql,Table,indexList);//��֪��indexList������ʽ�ǲ��ǻ᷽����ң��ɸ�
                                    //if (!indexInfo.succ){cout<<indexInfo.message<<endl;break;}
                                    //else {
                                        //Table.attrNum-=recoInfo.number;//����table��Ϣ
                                        CL.change_Table(Table);
                                        //cout<<indexInfo.message<<endl;
                                    //}
                                }
                                //������
                                else {
                                    recoInfo = RE.Select_Rec(sql,Table);
                                    if (!recoInfo.getsucc()){recoInfo.print(); break;}
                                    else {
                                        Table.attrNum-=recoInfo.nummes();//����table��Ϣ
                                        CL.change_Table(Table);
                                        recoInfo.print();
                                    }
                                }
                            }
                        }
                        break;
                }*/
                case ( SQL_USE             ):{
					cataInfo = CL.use_Database(sql);
					if (!cataInfo.getsucc())
						cataInfo.print();
					else{
						Wdbname = sql.getDatabaseName();
						cout<<succ<<endl;
					}
                        break;
                }
                case ( SQL_QUIT            ):{
					exit(0);
                        break;
                }
                case ( SQL_ERROR           ):{
					cout<<"Syntax Error"<<endl;
                        break;
                }
				case (SQL_SHOW_DATABASE):{
					cataInfo = CL.creat_Database(sql);
                        if (!cataInfo.getsucc()){
							cataInfo.print();
                            break;
                        }
				}

        }
}
