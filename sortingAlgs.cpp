#include <iostream>
using namespace std;

void print(int* S, int n){
    cout<<endl;
    for(int i=0; i<n; i++){
        cout<<S[i]<<' ';
    }              //wyswietla dane
    cout<<endl;
}

void init(int* S, int n){   //n-liczba elementow
    for(int i=0; i<n; i++){
        S[i] = rand() % 10;//10-przedzial gorny
    }           //generuje losowe dane
}


void insertionSort(int* S, int n){
    for (int i = 1; i < n; i++)
      for(int j=i;j>0;j--)
        if(S[j-1] > S[j]) swap(S[j], S[j-1]);
}

void selectionSort(int* S, int n){
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j=i+1; j<n; j++)
            if(S[j]<S[min]) min = j;
        swap(S[min], S[i]);
    }
}

void bubbleSort(int* S, int n){
    for(int i=0; i<n; i++){
        for(int j=1; j<n-i; j++){
            if(S[j-1]>S[j]) swap(S[j-1], S[j]);
        }
    }
 }

void quickSort(int* S, int left, int right){
    if(right <= left) return;

	int i = left - 1,
      j = right + 1,
      pivot = S[(left+right)/2]; //wybieramy punkt odniesienia

	while(1)
	{
		while(pivot>S[++i]);

		while(pivot<S[--j]);

		if( i <= j)
			swap(S[i],S[j]);
		else break;
	}

	if(j > left) quickSort(S, left, j);
	if(i < right) quickSort(S, i, right);
}

void cntSort(int* S, int n){

    int* countArray = new int [10];//10-gorny przedzial wystepujacych liczb do sortowania
    for(int i=0;i<10; i++)
        countArray[i]=0;

    int* outputArray = new int [n];//10-gorny przedzial wystepujacych liczb do sortowania
    for(int i=0;i<n; i++)
        outputArray[i]=0;

    //wypelniamy countarray liczbami wystapien
    for(int i=0; i<10; i++){
        for(int j=0; j<n; j++){
            if(S[j] == i)
                countArray[i]++;
        }
    }

    //zamieniamy na sume wszystkich poprzednich zliczen
    for(int i=9; i>0; i--){
        int sumOfPrevious = 0;
        for(int j=0; j<=i;j++)
            sumOfPrevious+=countArray[j];
        countArray[i] = sumOfPrevious;
    }

    //wstawiamy liczby do output array
    for(int i=0; i<n; i++){
        int idx = countArray[S[i]]-1;
        outputArray[idx] = S[i];
        countArray[S[i]]--;
    }

    for(int i=0; i<n; i++)
        S[i]=outputArray[i];

}

int main(){
    int n = 10; //przykladowy rozmiar
    int *S = new int[n];

    cout<<"\nInsertion sort: ";
    init(S,n);
    print(S, n);// generacja i wyswietlenie danych
    insertionSort(S, n);//sortowanie i wyswietlenie danych
    print(S,n);

     cout<<"\nSelection sort: ";
    init(S,n);
    print(S, n);// generacja i wyswietlenie danych
    selectionSort(S, n);//sortowanie i wyswietlenie danych
    print(S,n);

    cout<<"\nBubble sort: ";
    init(S,n);
    print(S, n);// generacja i wyswietlenie danych
    bubbleSort(S, n);//sortowanie i wyswietlenie danych
    print(S,n);

    cout<<"\nQuick sort: ";
    init(S,n);
    print(S, n);// generacja i wyswietlenie danych
    quickSort(S,0,n-1);//sortowanie i wyswietlenie danych
    print(S,n);

    cout<<"\nCounting sort: ";
    init(S,n);
    print(S, n);// generacja i wyswietlenie danych
    cntSort(S,n);//sortowanie i wyswietlenie danych
    print(S,n);

    return 0;
}

