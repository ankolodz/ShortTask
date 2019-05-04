#include <iostream>
#include <functional>

using namespace std;
struct node{
	int number;
	int value;
};
bool is_prime (int a){
	if (a<2)
		return false;
	for (int i=2;i*i<=a;i++)
		if(a%i==0)
			return false;
	return true;
}
int * recive_function (int * A,int sizeA,int* B, int sizeB){
	int sizeC = sizeB * 1.5; //sizeof hash array
	node analiseB [sizeC];//create temporary array for result
	for (int i=0;i<sizeC;i++){
		analiseB[i].number=-1;
		analiseB[i].value = 0;
	}
	cout<<"Before hash\n";
	hash<int> hash_function;//prepare hash fun
	int tmp;
	//convert B into 
	for(int i=0;i<sizeB;i++){
		tmp=hash_function(B[i])%sizeC;
		cout<<"i: "<<i<<" hash: "<<tmp<<" B[i] "<<B[i]<<endl;
		while (analiseB[tmp].number!=B[i]&&analiseB[tmp].value!=0){
				cout<<"   *"<<analiseB[tmp].number<<endl;
				tmp++;//linear conflict resolution
				tmp=tmp%sizeC;
			}	
			cout<<"i: "<<i<<" hash: "<<tmp<<" B[i] "<<B[i]<<endl;		
			if (analiseB[tmp].value==0){//first contact with the number
				analiseB[tmp].number = B[i];
				analiseB[tmp].value ++;
		}
			else
				analiseB[tmp].value++;//other situation
	}
	int newArray = 0;
	int *C= new int[sizeA];//temporary array with end number
	for (int i=0; i<sizeA;i++){
		tmp=hash_function(A[i])%sizeC;
		while (analiseB[tmp].number!=A[i]&&analiseB[tmp].value!=0)
			tmp++;
		cout<<"i: "<<i<<" hash: "<<tmp<<" C[i] "<<C[i]<<endl;
		if(analiseB[tmp].number==A[i]){//number from A exist in B AND it is exist prime in B
			if(is_prime(analiseB[tmp].value)==false){
				C[newArray]=A[i];
				newArray++;
			}	
		}
		else{
			C[newArray]=A[i];
			newArray++;
		}
	}
	
	int *finalC = new int [newArray];//prepare final array C
	for (int i=0;i<newArray;i++){
		finalC[i]=C[i];
		cout<<finalC[i]<<endl;
	}
	
	//return	
	return finalC;			
}
int main(){
	int A[9]={2,3,9,2,5,1,3,7,10};
	int B[13]={2,1,3,4,3,10,6,6,1,7,10,10,10};
	int *C=recive_function (A,9,B,13);
	for (int i=0;i<6;i++)
		cout<<C[i]<<" ";
	
}
