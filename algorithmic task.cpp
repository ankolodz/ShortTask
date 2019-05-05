#include <iostream>
#include <functional>

using namespace std;
struct node{
	int value;
	int numberOfOccurences;
};
bool is_prime (int a){
	if (a<2)
		return false;
	for (int i=2;i*i<=a;i++)
		if(a%i==0)
			return false;
	return true;
}
int * reduceArray (int* input, int size){
	int * output = new int [size];
	for (int i=0;i<size;i++)
		output[i]=input[i];
	return output;
}
int getHashPosition (int value, node* array, int size){
		hash<int> hash_function;
		int tmp=hash_function(value)%size;
		while (array[tmp].value!=value && array[tmp].numberOfOccurences!=0){
				tmp++;//linear conflict resolution
				tmp=tmp%size;
			}	
		return tmp;
}
int * recive_function (int * A,int sizeA,int* B, int sizeB){
	int sizeC = sizeB * 1.5;	 //sizeof hash array
	node analiseB [sizeC];		
	for (int i=0;i<sizeC;i++){
		analiseB[i].value=-1;
		analiseB[i].numberOfOccurences = 0;
	}		
	int tmp;
	//convert B into 
	for(int i=0;i<sizeB;i++){
			tmp=getHashPosition (B[i],analiseB,sizeC);
			if (analiseB[tmp].numberOfOccurences==0){
				analiseB[tmp].value = B[i];
				analiseB[tmp].numberOfOccurences ++;
		}
			else
				analiseB[tmp].numberOfOccurences++;
	}
	int newArray = 0;
	int *C= new int[sizeA];//temporary array with end value
	for (int i=0; i<sizeA;i++){
		tmp=getHashPosition (A[i],analiseB,sizeC);
		if(analiseB[tmp].value==A[i]){
			if(is_prime(analiseB[tmp].numberOfOccurences)==false){
				C[newArray]=A[i];
				newArray++;}	
		}
		else{
			C[newArray]=A[i];
			newArray++;}
	}	
	return reduceArray(C,newArray);			
}
int main(){
	int A[9]={2,3,9,2,5,1,3,7,10};
	int B[13]={2,1,3,4,3,10,6,6,1,7,10,10,10};
	int *C=recive_function (A,9,B,13);
	for (int i=0;i<6;i++)
		cout<<C[i]<<" ";
	
}