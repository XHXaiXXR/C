#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

void test(){
	int num = 0;
	vector<int> arr;
	int key = 0;

	while(cin>>num){
		vector<int> arr;
		while(num > 0){
			key = num % 8;
			arr.push_back(key);
			num /= 8;
		}

		for(int i = arr.size()-1;i >= 0;i--){
			cout<<arr[i];
		}
		cout<<endl;
	}
}

int main(){
	test();
	return 0;
}