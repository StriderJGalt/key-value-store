#include<bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "kvStore.cpp"
using namespace std;

struct CharCompare {
	bool operator()(char const *a,char const *b) const
	{
		return std::strcmp(a,b) <0;
	}
};
char *random_key(int stringLength){
	char *key = (char *)malloc(stringLength+1);
	string letters = "";
	for(char i = 'a';i<='z';i++)letters+=i;
	for(char i = 'A';i<='Z';i++)letters+=i;
	for(int i=0;i<stringLength;i++)
		key[i] = letters[rand()%52];
	key[stringLength] = '\0';

	return key;
}

char *random_value(int stringLength){
	char *value = (char *)malloc(stringLength+1);
	string letters = "";
	for(int i = 0;i<=255;i++)letters+=char(i);

	for(int i=0;i<stringLength;i++)
		value[i] = letters[rand()%52+int('A')];
	value[stringLength] = '\0';

	return value;
}
long CLOCKS_PER_SECOND = 1000000;
kvstore kv;
map<char *,char *, CharCompare> db;
int db_size = 0;
int num = 0;

void *myThreadFun(void *vargp)
{
	int transactions=0;
	clock_t start = clock();
	int time = 10;
	clock_t tt = clock();
	while((float(tt-start)/CLOCKS_PER_SECOND)<=time)
	{

		for(int i=0;i<10000;i++)
		{
			transactions+=1;
			int x = rand()%5;
			if(x==0)
			{
				Slice key,value;
				strcpy(key.data,random_key(10));
				bool ans = kv.get(&key,&value);
			}
			else if(x==1)
			{
				int k = rand()%64 + 1;
				int v = rand()%256 + 1;
				Slice key,value;
				strcpy(key.data,random_key(k));
				key.size = k;
				strcpy(value.data,random_value(v));
				value.size = v;
				bool ans = kv.put(&key,&value);
				db_size++;
			}
			else if(x==2)
			{
				int temp=db_size;
				if (temp == 0)
					continue;
				int rem = rand()%temp;
				Slice check1_key,check1_value;
				kv.get(rem,&check1_key,&check1_value);
				bool check2 = kv.del(&check1_key);
				db_size--;
			}
			else if(x==3)
			{
				int temp=db_size;
				if (temp == 0)
					continue;
				int rem = rand()%temp;
				Slice check_key,check_value;
				bool check = kv.get(rem,&check_key,&check_value);
			}
			else if(x==4)
			{
				int temp=db_size;
				if (temp == 0)
					continue;
				int rem = rand()%temp;
				bool check = kv.del(rem);
				db_size--;
			}
		}
		tt=clock();
	}
	cout<<transactions/time<<endl;
	return NULL;
}

int main()
{
	Slice key1,value1;
	key1.data = (char *)malloc(64);
	value1.data = (char *)malloc(256);
	for(int i=0;i<100001;i++)
	{
		int k = rand()%64 + 1;
		int v = rand()%256 + 1;
		char *key_s = random_key(k);
		char *value_s = random_value(v);
		strcpy(key1.data,key_s);
		key1.size = k;
		strcpy(value1.data,value_s);
		value1.size = v;
		db.insert(pair<char *,char *>(key_s,value_s));
		kv.put(&key1,&value1);
		db_size++;
         std::cout<<"i:"<<i<<endl;
	}

	// map<char *,char *, CharCompare>:: iterator itr = db.begin();
	// for(int i=0;i<db_size;i++)
	// {
	// 	std::cout<<itr->first<<endl;
	// 	itr++;
	// }

	bool incorrect = false;

	// --------------------------------------------------------------------------------------
	// start correcting from here downwards
	// ----------------------------------------------------------------------------------------
	for(int k12=0;k12<100000;k12++)
	{
        std::cout<<"k:"<<k12<<endl;
		int x = rand()%4;
		if(x==0)
		{
			char *k = random_key(10);
      Slice key,value;
			key.data = (char *)malloc(64);
			value.data = (char *)malloc(256);
      strcpy(key.data,k);
      key.size = 10;
			bool ans = kv.get(&key,&value);
			map<char *,char *, CharCompare>:: iterator itr = db.find(k);
			if((ans==false && itr != db.end()) || (ans==true && itr == db.end()) )
				incorrect = true;
		}
		else if(x==2)
		{
			int k = rand()%64 + 1;
			int v = rand()%256 + 1;
			char *key_s = random_key(k);
			char *value_s = random_value(v);
	    Slice key,value;
			key.data = (char *)malloc(64);
			value.data = (char *)malloc(256);
	    strcpy(key.data,key_s);
	    key.size = k;
	    strcpy(value.data,value_s);
	    value.size = v;
	    db.insert(pair<char *,char *> (key_s,value_s));
			bool check1 = kv.get(&key,&value);
			bool ans = kv.put(&key,&value);
			bool check2 = kv.get(&key,&value);
			db_size++;
			if(check2 == false || check1 != ans)
				incorrect = true;
		}
		else if(x==2)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			map<char *,char *, CharCompare>:: iterator itr = db.begin();
      Slice key,value;
			key.data = (char *)malloc(64);
			value.data = (char *)malloc(256);
			for(int i=0;i<rem;i++)itr++;
            strcpy(key.data,itr->first);
            key.size = strlen(itr->first);
			bool check = kv.del(&key);
			db_size--;
			db.erase(itr);
			bool check2 = kv.get(&key,&value);
			if(check2 == true)
				incorrect = true;
		}
		else if(x==3)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
      Slice key,value;
			key.data = (char *)malloc(64);
			value.data = (char *)malloc(256);
      kv.get(rem,&key,&value);
			pair <char *,char *> check = make_pair(key.data,value.data);
			map<char *,char *, CharCompare>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			if(strcmp(key.data,itr->first)!=0|| strcmp(value.data,itr->second)!=0)
			{
				incorrect = true;
				std::cout<<key.data<<endl<<itr->first<<endl;
				std::cout<<value.data<<endl<<itr->second<<endl;
			}
		}
		else if(x==4)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			map<char *,char *, CharCompare>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			string key_s = itr->first;
            Slice key,value;
						key.data = (char *)malloc(64);
						value.data = (char *)malloc(256);
            strcpy(key.data,key_s.c_str());
            key.size = key_s.length();
			bool check = kv.del(rem);
			db.erase(itr);
			db_size--;
			bool check2 = kv.get(&key,&value);
			if(check2 == true)
				incorrect = true;
		}
	}
	if(incorrect == true)
	{
        std::cout<<0<<endl;
		return 0;
	}
	int threads = 4;

	/* pthread_t tid[threads]; */
	/* for (int i = 0; i < threads; i++) */
	/* { */
	/* 	tid[i] = i; */
        /* pthread_create(&tid[i], NULL, myThreadFun, (void *)&tid[i]); */
	/* } */
	/* for(int i=0;i<threads;i++) */
	/* 	pthread_join(tid[i],NULL); */
	return 0;
}
