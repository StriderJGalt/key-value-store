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

// void *myThreadFun(void *vargp)
// {
// 	int transactions=0;
// 	clock_t start = clock();
// 	int time = 10;
// 	clock_t tt = clock();
// 	while((float(tt-start)/CLOCKS_PER_SECOND)<=time)
// 	{
//
// 		for(int i=0;i<1000000;i++)
// 		{
// 			transactions+=1;
// 			int x = rand()%5;
// 			if(x==0)
// 			{
// 				string k = random_key(10);
// 				bool ans = kv.get(k);
// 			}
// 			else if(x==1)
// 			{
// 				int k = rand()%64 + 1;
// 				int v = rand()%256 + 1;
// 				string key = random_key(k);
// 				string value = random_value(v);
// 				bool ans = kv.put(key,value);
// 				db_size++;
// 			}
// 			else if(x==2)
// 			{
// 				int temp=db_size;
// 				if (temp == 0)
// 					continue;
// 				int rem = rand()%temp;
// 				pair <string,string> check = kv.get(rem);
// 				bool check2 = kv.del(check.first);
// 				db_size--;
// 			}
// 			else if(x==3)
// 			{
// 				int temp=db_size;
// 				if (temp == 0)
// 					continue;
// 				int rem = rand()%temp;
// 				pair <string,string> check = kv.get(rem);
// 			}
// 			else if(x==4)
// 			{
// 				int temp=db_size;
// 				if (temp == 0)
// 					continue;
// 				int rem = rand()%temp;
// 				bool check = kv.del(rem);
// 				db_size--;
// 			}
// 		}
// 		tt=clock();
// 	}
// 	cout<<transactions/time<<endl;
// 	return NULL;
// }

int main()
{
/*     kv.put("abc","Val 2"); */
/*     kv.put("bcd","Val 3"); */
/*     kv.put("aab","Val 1"); */
/*     kv.put("cde","Val 4"); */
/*     kv.put("dab","Val 5"); */
/*     kv.put("ede","Val 6"); */
/*     kv.put("fde","Val 7"); */
/*     kv.put("gde","Val 8"); */
/*     kv.put("hde","Val 9"); */
/*     std::cout<<kv.get(9).second<<endl; */
	for(int i=0;i<100000;i++)
	{
		int k = rand()%64 + 1;
		int v = rand()%256 + 1;
		string key = random_key(k);
		string value = random_value(v);
		db.insert(pair<string,string>(key,value));
		kv.put(key,value);
		db_size++;
		// kv.disp();
		// printf("\n\nNew thing\n\n");
	}

	bool incorrect = false;

	for(int i=0;i<10000;i++)
	{
		int x = rand()%5;
		// int x = 3;
		if(x==0)
		{
			string k = random_key(10);
			bool ans = kv.get(k);
			map<string,string>:: iterator itr = db.find(k);
			if((ans==false && itr != db.end()) || (ans==true && itr == db.end()) )
				incorrect = true;
		}
		else if(x==1)
		{
			int k = rand()%64 + 1;
			int v = rand()%256 + 1;
			string key = random_key(k);
			string value = random_value(v);
			db.insert(pair<string,string>(key,value));
			bool check1 = kv.get(key);
			bool ans = kv.put(key,value);
			bool check2 = kv.get(key);
			db_size++;
			if(check2 == false || check1 != ans)
				incorrect = true;
		}
		else if(x==2 && db.size() > 0)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			map<string,string>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			string key = itr->first;
			bool check = kv.del(key);
			db_size--;
			db.erase(itr);
			bool check2 = kv.get(key);
			if(check2 == true){
				incorrect = true;
				printf("Delete wrong\n");
			}
		}
		else if(x==3 && db.size() > 0)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			pair <string,string> check = kv.get(rem);
			map<string,string>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			if(check.first != itr->first || check.second != itr->second)
      {
          incorrect = true;
					std::cout<<check.first<<" "<<" "<<itr->first<<" "<<endl;
      }
    }
		else if(x==4 && db.size() > 0)
		{
			int max_size = db.size();
			int rem = rand()%max_size;
			map<string,string>:: iterator itr = db.begin();
			for(int i=0;i<rem;i++)itr++;
			string key = itr->first;
			bool check = kv.del(rem);
			// std::cout<<key<<endl;
			db.erase(itr);
			db_size--;
			bool check2 = kv.get(key);
			if(check2 == true)
				incorrect = true;
		}
	}
	if(incorrect == true)
	{
		cout<<0<<endl;
		return 0;
	}
	// int threads = 4;

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
