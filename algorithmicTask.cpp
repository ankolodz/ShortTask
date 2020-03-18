#include <iostream>
#include <vector>

using namespace std;

struct node{
	int value;
	int numberOfOccurences;
};

bool isPrime(int n);
int getHash(int n, vector <node>& hashArray);
vector < int > getOnlyPrimeElemens(vector <int>& A, vector <int>& B);


int main(){
    vector <int> A = {2,3,9,2,5,1,3,7,10};
    vector <int> B = {2,1,3,4,3,10,6,6,1,7,10,10,10};
    vector <int> C = getOnlyPrimeElemens(A,B);
    
    for (int i=0 ; i<C.size() ; i++)
    	cout<<C[i]<<" ";
    return 0;
}


//functon
bool isPrime(int n){
    if(n<2) return false;
    
    for(int i=2; i*i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

int getHash(int value, vector < node >& hashArray){
    hash < int > hashFunction;
    int place = hashFunction(value) % hashArray.size();
    while (hashArray[place].value != value && hashArray[place].value != -1){
            place++;//linear conflict resolution
            place= place % hashArray.size();
        }	
    return place;
}


vector < int > getOnlyPrimeElemens(vector <int>& A, vector <int>& B){	
	vector < int > result;
	
	vector < node > hashArray;
	for(int i=0 ; i<B.size() * 1.5 + 1 ; i++){
		node next;
		next.numberOfOccurences = 0;
		next.value = -1;
		hashArray.push_back(next);
	}

	
	for(int i=0 ; i<B.size() ; i++){
		int place = getHash(B[i] , hashArray);
		hashArray[place].value = B[i];
		hashArray[place].numberOfOccurences++;
	}
	for (int j=0 ; j<hashArray.size() ; j++)
    		cout<<hashArray[j].value<<" ";
    cout<<endl;
    	for (int j=0 ; j<hashArray.size() ; j++)
    		cout<<hashArray[j].numberOfOccurences<<"  ";
    cout<<endl;
	
	for(int i=0 ; i<A.size() ; i++){
		int place = getHash(A[i] , hashArray);
		if(!isPrime(hashArray[place].numberOfOccurences))
		   	result.push_back(A[i]);
	}
	return result;
}
	 
	    
