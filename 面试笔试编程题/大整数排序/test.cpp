#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#include<vector>

bool comp(string str1, string str2){
	if(str1.length() < str2.length()){
		return true;
	}
	if(str1.length() > str2.length()){
		return false;
	}
	if(str1.length() == str2.length()){
		return str1 < str2;
	}

	return false;
}

int main(){
	int num = 0;
	
	while (cin>>num)
	{
		vector<string> arr(num,"");

		for(int i = 0;i < num;i++){
			cin>>arr[i];
		}
		sort(arr.begin(), arr.end(), comp);

		for(int i = 0;i < num;i++){
			cout<<arr[i]<<endl;
		}
	}

	system("pause");
	return 0;
}