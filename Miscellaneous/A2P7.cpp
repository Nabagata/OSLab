#include<bits/stdc++.h>
using namespace std;
map<string,int> m;
struct bs{
string str;
};
ifstream fin;
void *addfreq(void *v){

		string s;
		long off=(*(long*)v);
		fin.seekg(off,ios::beg);
		getline(fin,s);
		cout<<s<<endl;
		string  wrd;
		stringstream ss;
		ss<<s;
		while(ss>>wrd){
			if(m.find(wrd)==m.end())
				m[wrd]=0;
			m[wrd]++;
		}
}

int main(int argc,char *argv[]){
	
	fin.open("/home/cs15/c157154/File1.txt");

	
	vector<pthread_t> v;
	while(fin){
		pthread_t t;
		long pos=fin.tellg();
		pthread_create(&t,NULL,&addfreq,(void*)(&pos));
		pthread_join(t, NULL);
	}

	//for(int i=0;i<v.size();i++)
	//	pthread_join(v[i], NULL);


	map<string,int> ::iterator it=m.begin();

	while(it!=m.end()){
		cout<<it->first<<" "<<it->second<<endl;
		it++;
	}
	return 0;
}

