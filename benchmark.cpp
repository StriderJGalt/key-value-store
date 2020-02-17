#include<bits/stdc++.h>
#include <unistd.h> 
#include <pthread.h>
#include <time.h>
#include "kvStore.cpp"
using namespace std;

string random_key(int stringLength){
	string key = "";
	string letters = "";
	for(char i = 'a';i<='z';i++)letters+=i;
	for(char i = 'A';i<='Z';i++)letters+=i;
	for(int i=0;i<stringLength;i++)
		key = key + letters[rand()%52];

	return key;
}

string random_value(int stringLength){
	string value = "";
	string letters = "";
	for(int i = 0;i<=255;i++)letters+=char(i);

	for(int i=0;i<stringLength;i++)
		value = value + letters[rand()%256];

	return value;
}
long CLOCKS_PER_SECOND = 1000000;
kvstore kv;
map<string,string> db;
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
				strcpy(key.data,random_key(10).c_str());
				bool ans = kv.get(&key,&value);
			}
			else if(x==1)
			{
				int k = rand()%64 + 1;
				int v = rand()%256 + 1;
				Slice key,value;
				strcpy(key.data,random_key(k).c_str());
				key.size = k;
				strcpy(value.data,random_value(v).c_str());
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
				slice check1_key,check1_value;
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
	for(int i=0;i<10000001;i++)
	{
		int k = rand()%64 + 1;
		int v = rand()%256 + 1;
		string key_s = random_key(k);
		string value_s = random_value(v);
		Slice key,value;
		strcpy(key.data,key_s.c_str());
		key.size = k;
		strcpy(value.data,value_s.c_str());
		value.size = v;
		db.insert(pair<string,string>(key_s,value_s));
		kv.put(&key,&value);
		db_size++;
        /* std::cout<<"i:"<<i<<endl; */
	}

	bool incorrect = false;

	// -------------------------------------------------------------------------------------- 
	// start correcting from here downwards
	// ----------------------------------------------------------------------------------------
	for(int k=0;k<1;k++)
	{
        std::cout<<"k:"<<k<<endl;
		int x = rand()%5;
		if(x==0)
		{
			string k = random_key(10);
            Slice key,value;
            strcpy(key.data,k.c_str());
            key.size = k;
			bool ans = kv.get(&key,value);
			map<string,string>:: iterator itr = db.find(k);
			if((ans==false && itr != db.end()) || (ans==true && itr == db.end()) )
				incorrect = true;
		}
		else if(x==1)
		{
			int k = rand()%64 + 1;
			int v = rand()%256 + 1;
			string key_s = random_key(k);
			string value_s = random_value(v);
            Slice key,value;
            strcpy(key.data,key_s.c_str());
            key.size = k;
            strcpy(value.data,value_s.c_str());
            value.size = v;
            db.insert(pair<string,string>(key_s,value_s));
			bool check1 = kv.get(&key,value);
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
			map<string,string>:: iterator itr = db.begin();
            Slice key,value;
			for(int i=0;i<rem;i++)itr++;
            {
                string key = itr->first;
                strcpy(key.data,k.c_str());
                key.size = k;
            }
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
            kv.get(rem,&key,&value);
			pair <string,string> check = make_pair(key.data,value.data);
			map<string,string>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			if(strcmp(key.data,itr->first.c_str())!=0|| strcmp(value.data,itr->second.c_str())!=0)
				incorrect = true;
		}
		else if(x==4)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			map<string,string>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			string key_s = itr->first;
            Slice key,value;
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
