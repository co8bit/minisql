#include"BPTree.h"

Node::Node(BufferManager indexBuff,PtrType ptr,string indexName,table tableInstance,int n):indexBuff(indexBuff),indexName(indexName),tableInstance(tableInstance),ptrN(n),offset(ptr),block(indexBuff.getIndexOneBlock(indexName,ptr))
{
	read();
}

Node::Node(BufferManager indexBuff,string indexName,table tableInstance,int n):indexBuff(indexBuff),indexName(indexName),tableInstance(tableInstance),ptrN(n)
{
	//�����飬����offset
	block = indexBuff.newIndexBlock(indexName);
	offset = block.offset;
	read();
}

PtrType Node::getNodePtr()
{
	return offset;
}

Node::~Node()
{
	char coutStream[5000];
	
	char tempNodeType;
	if (nodeType == _LEAFNODE)
		tempNodeType = '1';
	else
		tempNodeType = '0';
	memcpy(coutStream,&tempNodeType,sizeof(char));
	memcpy(coutStream + 1,&count,sizeof(int));
	int j = 0;
	for (int i = 0; i < info.size(); i++)
	{
		switch (info[i].getType())
		{
		case _TYPE_INT:int temp = info[i].getIntKey();memcpy(coutStream + 1 + 4 + j,&temp,typeSize(_TYPE_INT));j+=typeSize(_TYPE_INT);break;
		case _TYPE_FLOAT:float temp = info[i].getFloatKey();memcpy(coutStream + 1 + 4 + j,&temp,typeSize(_TYPE_FLOAT));j+=typeSize(_TYPE_FLOAT);break;
		case _TYPE_STRING:string temp = info[i].getCharKey();memcpy(coutStream + 1 + 4 + j,&temp,typeSize(_TYPE_STRING));j+=typeSize(_TYPE_STRING);break;//��������д��
		}
	}
	
	indexBuff.writeIndexData(indexName, coutStream, j+5);
}

string Node::read()
{
	for(int i = 0; i < tableInstance.attrList.size(); i++)
		if (tableInstance.attrList[i].name == indexName)
		{
			switch(tableInstance.attrList[i].datatype)
			{
			case -1:attrType = _TYPE_FLOAT;break;
			case 0:attrType = _TYPE_INT;break;
			case 1:attrType = _TYPE_STRING;break;
			}
			break;
		}
	memcpy(&nodeType,block.content,1);
	memcpy(&count,block.content + 1,sizeof(int));
	for(int i = 0; i < (ptrN - 1); i++)
	{
		float tempFloat = 0;
		int tempInt = 0;
		string tempString = "";
		PtrType tempPtr = 0;
		Value tempValue(attrType);

		//read ptr//TODO:+5��
		memcpy(&tempPtr,block.content + 5 + i*( typeSize(attrType) + sizeof(int) ),typeSize(_TYPE_INT));
		Value ptrTempValue(_TYPE_INT,tempPtr);//TODO:����ptr����
		info.push_back(ptrTempValue);

		//read key
		switch(attrType)//TODO:+5��
		{
		case _TYPE_FLOAT:
			{
				memcpy(&tempFloat,block.content + 5 + i*( typeSize(attrType) + sizeof(int) ) + sizeof(int),typeSize(_TYPE_FLOAT));
				tempValue.setKey(tempFloat);
				break;
			}
		case _TYPE_INT:
			{
				memcpy(&tempInt,block.content + 5 + i*( typeSize(attrType) + sizeof(int) ) + sizeof(int),typeSize(_TYPE_INT));
				tempValue.setKey(tempInt);
				break;
			}
		case _TYPE_STRING:
			{
				memcpy(&tempString,block.content + 5 + i*( typeSize(attrType) + sizeof(int) ) + sizeof(int),typeSize(_TYPE_STRING));
				tempValue.setKey(tempString);
				break;
			}
		}//switch
		info.push_back(tempValue);
		
	}//for
	PtrType tempPtr = 0;
	memcpy(&tempPtr,block.content + 5 + (ptrN - 1)*( typeSize(attrType) + sizeof(int) ),typeSize(_TYPE_INT));
	Value ptrTempValue(_TYPE_INT,tempPtr);//TODO:����ptr����
	info.push_back(ptrTempValue);
}


void Node::setLastPtr(PtrType ptr)
{
	Value temp(_TYPE_INT,ptr);
	info[info.size() - 1] = temp;
}

void Node::setLastPtr(Value ptr)
{
	info[info.size() - 1] = ptr;
}

void Node::updateCount()
{
	//(info.size() - 1) / 2;
	count = 0;
	for (int i = 0; i < info.size(); i+=2)
	{
		count++;
	}
}










BPTree::BPTree(BufferManager indexBuff,int type):indexBuff(indexBuff),type(type)
{
	int freeSpace = 4*1024 - sizeof(PtrType) - 1 - sizeof(int);
	n  = freeSpace / (sizeof(PtrType) + typeSize(type)) + 1; //������Ӧ��ȡ����������������
}

bool BPTree::createBPTree(SqlCommand sql,table tableInstance,string indexName)
{
	int recordLength = tableInstance.recLength;
	BufferManager recordBuff(sql.getDatabaseName());
	vector<int> blockNum = recordBuff.getTableBlocks(sql.getTableName());

	//������
	for (int i = 0; i < blockNum.size(); i++)
	{
		//TODO:��������ݣ������������м�¼��������
		for (int j = 0; j < recordLength; j++)
		{
			this->insert(value,pointer);
		}
	}

	//�洢��
	indexBuff.storeIndex(indexName);//TODO:�����л����ڴ��е�index��������ͺã���Ϊ�����Ŀ��Ѿ���д��
}

bool BPTree::loadBPTree(string indexName)
{
	int firstBlock = indexBuff.getIndexBlocks(indexName)[0];//��ȡ��ʼ�Ŀ�
	Node rootNode(indexBuff,firstBlock,indexName,tableInstance,n);
	root = rootNode.getInfo()[0].getIntKey();
}

PtrType BPTree::find(Value key)
{
	Node *node = new Node(indexBuff,root,indexName,tableInstance,n);
	//in nonLeafNode
	while (node->getNodeType() != _LEAFNODE)
	{
		vector<Value> temp = node->getInfo();
		int i = 1;
		for(i = 1; i < temp.size(); i+=2)
		{
			if (key.getKey() < temp[i].getKey())//ֻ����С�ڣ���ΪС�ڲŽ�ǰ��
				break;
		}
		if (i >= temp.size())
		{
			delete node;
			Node *node = new Node(indexBuff,atoi(temp[temp.size() - 1].getKey().c_str()),indexName,tableInstance,n);
		}
		else
		{
			delete node;
			Node *node = new Node(indexBuff,atoi(temp[i - 1].getKey().c_str()),indexName,tableInstance,n);
		}
	}

	//in leafNode
	vector<Value> temp = node->getInfo();
	int i = 1;
	for(i = 1; i < temp.size(); i+=2)
	{
		if (key.getKey() == temp[i].getKey())
			break;
	}
	if (i >= temp.size() )
		return -1;
	else
		return i;
	delete node;
}

PtrType BPTree::findLeafNode(Value key)
{
	Node *node = new Node(indexBuff,root,indexName,tableInstance,n);
	parentMap.clear();
	ParentMap *tempMap = new ParentMap();
	tempMap->nodePtr = root;
	tempMap->parentPtr = -1;
	parentMap.push_back(*tempMap);
	int j = 0;
	//in nonLeafNode
	while (node->getNodeType() != _LEAFNODE)
	{
		vector<Value> temp = node->getInfo();
		int i = 1;
		for(i = 1; i < temp.size(); i+=2)
		{
			if (key.getKey() < temp[i].getKey())//ֻ����С�ڣ���ΪС�ڲŽ�ǰ��
				break;
		}
		if (i >= temp.size())
		{
			delete tempMap;
			ParentMap *tempMap = new ParentMap();
			tempMap->nodePtr =  atoi(temp[temp.size() - 1].getKey().c_str());
			tempMap->parentPtr = node->getNodePtr();
			parentMap.push_back(*tempMap);
			delete node;
			Node *node = new Node(indexBuff,atoi(temp[temp.size() - 1].getKey().c_str()),indexName,tableInstance,n);	
		}
		else
		{
			delete tempMap;
			ParentMap *tempMap = new ParentMap();
			tempMap->nodePtr =  atoi(temp[temp.size() - 1].getKey().c_str());
			tempMap->parentPtr = node->getNodePtr();
			parentMap.push_back(*tempMap);
			delete node;
			parentMap[j].nodePtr = atoi(temp[temp.size() - 1].getKey().c_str());
			Node *node = new Node(indexBuff,atoi(temp[i - 1].getKey().c_str()),indexName,tableInstance,n);
		}
	}
	return node->getNodePtr();
}

PtrType BPTree::findParentNode(PtrType ptr)
{
	int i;
	for (i = 0; i < parentMap.size(); i++)
		if (parentMap[i].nodePtr == ptr)
			return parentMap[i].parentPtr;
}

void BPTree::insert(Value key,PtrType pointer)
{
	PtrType nodePtr = findLeafNode(key);
	Node node(indexBuff,nodePtr,indexName,tableInstance,n);
	if (node.getCount() < (n - 1))
		insertLeaf(node,key,pointer);
	else
	{
		//����
		vector<Value> keyList = node.getInfo();//ֻ����ֵ��
		if (key.getKey() < keyList[0].getKey())
		{
			keyList.insert(keyList.begin(),key);
			Value temp(_TYPE_INT,pointer);
			keyList.insert(keyList.begin(),temp);
		}
		else
		{
			for (int i = (keyList.size() - 1 - 1); i >= 0; i-=2)
			{
				if (keyList.at(i).getKey() <= key.getKey())
				{
					Value tempPtr(_TYPE_INT,pointer);
					keyList.insert(keyList.begin() + i+1,tempPtr);
					keyList.insert(keyList.begin() + i+2,key);
					break;
				}
			}
		}
		
		//����βָ��
		Node newNode(indexBuff,indexName,tableInstance,n);
		PtrType newNodePtr = newNode.getNodePtr();
		newNode.setLastPtr(node.getLastPtr());
		node.setLastPtr(newNodePtr);

		//��ֵԪ�ص��õ��ĵط�
		int breakPoint = 0;
		if (n % 2 == 0)
			breakPoint = (n /2)*2;
		else
			breakPoint = ((n / 2) + 1)*2;
		vector<Value> temp(keyList.begin(),keyList.begin() + breakPoint);
		node.set(temp);//ֻд��ֵ��
		vector<Value> temp2(keyList.begin() + breakPoint,keyList.end());//TODO:����ҿ�?
		newNode.set(temp2);

		insertNonleaf(node,temp2[0],newNodePtr);
	}
}





void BPTree::insertLeaf(Node node,Value key,PtrType pointer)
{
	vector<Value> keyList = node.getInfo();//ֻ����ֵ��
	if (key.getKey() < keyList[0].getKey() )
	{
		keyList.insert(keyList.begin(),key);
		Value temp(_TYPE_INT,pointer);
		keyList.insert(keyList.begin(),temp);
	}
	else
	{
		for (int i = (keyList.size() - 1 - 1); i >= 0; i-=2)
		{
			if (keyList.at(i).getKey() <= key.getKey())
			{
				Value tempPtr(_TYPE_INT,pointer);
				keyList.insert(keyList.begin() + i+1,tempPtr);
				keyList.insert(keyList.begin() + i+2,key);
				break;
			}
		}
	}
	node.set(keyList);
}





void BPTree::insertNonleaf(Node node,Value key,PtrType pointer)
{
	if (node.getNodePtr() == root)
	{
		Node newNode(indexBuff,indexName,tableInstance,n);
		vector<Value> keyList;
		Value temp1(_TYPE_INT,node.getNodePtr());
		Value temp2(_TYPE_INT,pointer);
		keyList.push_back(temp1);
		keyList.push_back(key);
		keyList.push_back(temp2);
		newNode.set(keyList);
		root = newNode.getNodePtr();
		//�Ѹ��ڵ�ĸ���д�����
		int firstBlock = indexBuff.getIndexBlocks(indexName)[0];//��ȡ��ʼ�Ŀ�
		Node rootNode(indexBuff,firstBlock,indexName,tableInstance,n);
		Value temp3(_TYPE_INT,root);
		vector<Value> temp4;
		temp4.push_back(temp3);
		rootNode.set(temp4);
	}
	else
	{
		Node parentNode(indexBuff,findParentNode(node.getNodePtr()),indexName,tableInstance,n);
		if (parentNode.getCount() < n)
		{
			vector<Value> keyList = parentNode.getInfo();//ֻ����ֵ��
			if (key.getKey() < keyList[0].getKey())
			{
				Value tempPtr(_TYPE_INT,pointer);
				keyList.insert(keyList.begin()+1,tempPtr);
				keyList.insert(keyList.begin()+1,key);
			}
			else
			{
				for (int i = (keyList.size() - 1 - 1); i >= 0; i-=2)
				{
					if (keyList.at(i).getKey() <= key.getKey())
					{
						Value tempPtr(_TYPE_INT,pointer);
						keyList.insert(keyList.begin() + i+2,tempPtr);//TODO:���һ������ô��?
						keyList.insert(keyList.begin() + i+2,key);
						break;
					}
				}
			}
			parentNode.set(keyList);
		}
		else//����ParentNode
		{
			//����
			vector<Value> keyList = parentNode.getInfo();//ֻ����ֵ��
			if (key.getKey() < keyList[0].getKey())
			{
				Value tempPtr(_TYPE_INT,pointer);
				keyList.insert(keyList.begin()+1,tempPtr);
				keyList.insert(keyList.begin()+1,key);
			}
			else
			{
				for (int i = (keyList.size() - 1 - 1); i >= 0; i-=2)
				{
					if (keyList.at(i).getKey() <= key.getKey())
					{
						Value tempPtr(_TYPE_INT,pointer);
						keyList.insert(keyList.begin() + i+2,tempPtr);//TODO:���һ������ô��?
						keyList.insert(keyList.begin() + i+2,key);
						break;
					}
				}
			}

			//��ֵԪ�ص��õ��ĵط�
			int breakPoint = 0;
			if (n % 2 == 0)
				breakPoint = (n /2);
			else
				breakPoint = ((n / 2) + 1);
			vector<Value> temp;
			temp.push_back(keyList[0]);
			int j = 1;
			for (int i = 1; i < breakPoint; i++)
			{
				temp.push_back(keyList[j]);
				temp.push_back(keyList[++j]);
			}
			parentNode.set(temp);

			Value newK = keyList[++j];
			vector<Value> temp2;
			for (int i = j + 1; i < keyList.size(); i++)
			{
				temp2.push_back(keyList[i]);
			}
			Node newNode(indexBuff,indexName,tableInstance,n);
			newNode.set(temp2);

			insertNonleaf(parentNode,newK,newNode.getNodePtr());
		}
	}
}

string Value::getKey()
{
	switch (type)
	{
		case _TYPE_STRING:return charKey;
		case _TYPE_INT:char temp[260]; sprintf(temp,"%i",intKey); return temp; break;//����sprintf_s(temp,sizeof(float)*260...
		case _TYPE_FLOAT:char temp[260]; sprintf(temp,"%f",floatKey); return temp; break;
		default:return 0;
	}
}