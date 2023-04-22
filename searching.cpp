//wyszukiwania
#include <iostream>
#include <algorithm>
using namespace std;

void print(int* S, int n){  
    for(int i=0; i<n; i++){
        cout<<S[i]<<' ';
    }      
    cout<<endl;  
}//wyświetla dane na monitorze

int linearSearch1(int* S, int n, int x){
    for(int i = 0; i<n; i++){
        if(S[i]==x) return i;
    }
    return -1;
}

int linearSearch2(int* S, int n, int x){
    int count=0;
    for(int i = 0; i<n; i++){
        count++;
        if(S[i]==x) break;
    }
    return count;
}

int binarySearch1(int* S, int n, int x){   //wersja iteracyjna
    int left = 0;
    int right = n-1;
    while(left<=right){
        int mid=(left+right)/2;
        if(S[mid]==x) return mid;
        else if(S[mid]>x) right = mid-1;
        else left = mid+1;
    }
    return -1;
}

int binarySearch2(int* S, int n, int x){   //wersja iteracyjna
    int count = 0;
    int left = 0;
    int right = n-1;
    while(left<=right){
        count++;
        int mid=(left+right)/2;
        if(S[mid]==x) break;
        else if(S[mid]>x) right = mid-1;
        else left = mid+1;
    }
    return count;
}

int main(){
    int n = 20;
    int *S = new int[n]{1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    print(S,n);
    sort(S,S+19);
    print(S,n);
    int x;
    cin>>x; //wczytanie/ustawienie x
    cout<<endl<<"Przypadek 1: x na pozycji - "<<linearSearch1(S,n,x); 
    cout<<endl<<"Przypadek 1: liczba krokow liniowo - "<<linearSearch2(S,n,x);
    cout<<endl<<"Przypadek 1: x na pozycji - "<<binarySearch1(S,n,x);
    cout<<endl<<"Przypadek 1: liczba krokow binarnie - "<<binarySearch2(S,n,x);
    return  0;
}