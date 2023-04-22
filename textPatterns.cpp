#include <iostream>
#include <cmath>
using namespace std;

void naiveStringMatching(string T, string p){

	int n = T.length();
	int m = p.length();

	for(int i=0; i<=n-m; i++){
		int j;
		for( j = 0; j<m; j++)
            if (p[j] != T[i+j]) break;
		if(j == m) cout<<"Wzorzec wystepuje od pozycji "<<i<<endl;
	}

}

void RabinKarp(string T, string p){ //https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/

	int hp = 0, hT = 0;
	int m = p.length();
	int n = T.length();

	//	Initially calculate the hash value of the pattern.
	for(int i =0; i<m; i++){
		hp+=pow(2,m-1-i)*p[i];
	}

	//	Initially calculate the hash value of the text.
	for(int i =0; i<m; i++){
		hT+=pow(2,m-1-i)*T[i];
	}

	//Start iterating from the starting of the string:
	for(int i = 0 ; i<=n-m; i++){
		if(hp==hT){
			//If the hash value of the current substring and the pattern are same check if the substring is same as the pattern.
			int j;
            for( j = 0; j<m; j++)
                if (p[j] != T[i+j]) break;
            if(j == m) cout<<"Wzorzec wystepuje od pozycji "<<i<<endl;
            }
            else {
                hT = (hT - pow(2,m-1)*T[i])*2 + T[i+m];
            }
	}
}



void BoyerMoore(string T, string p){ //https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/

	int m = p.length();
	int n = T.length();

	int bc[256];

	for (int i = 0; i < 256; i++)
    	bc[i] = -1;

	// Fill the actual value of last occurrence
	// of a character
	for (int i = 0; i < m; i++)
    	bc[(int) p[i]] = i;

	//main part
	int i = 0; // i defines how much pattern is shifted

	while(i<=(n-m)){
		int j = m - 1;
		 // Reducing j of p until we gets a mismatch character, at this shift i
		while( j>=0 && p[j]==T[i+j]){
			j--;
		}
		// In case if we get j=-1 which signify that pattern is present at current shift
		if(j==-1) {
			cout<<"Wzorzec wystepuje od pozycji "<<i<<endl;
			/* We will shift p such that the next
			character in T aligns with the last
			occurrence of it in P.
			To cover the case when P occur at end
			of T we need the condition i+m < n */

      		i += (i+m < n) ? m - bc[(int)T[i + m]] : 1;
		}
		else{
			/* In this case also, We will shift P such
			that the next character in T aligns
			with the last occurrence of it in P.
			To unsure that we get positive
			shift we are using max function.
			The negative shift may occur when the
			last occurrence of bad character in P
			is on the right side of the current
			character. */

      		i+= max(1, j - bc[(int)T[i + j]]);
		}
 	}
}

int main(){

	//Zadanie 1 - testy

	string text="Tekst wzorzec zawierajacy wzorzec";
	string pattern="wzorzec";

	naiveStringMatching(text, pattern);

	RabinKarp(text, pattern);

	BoyerMoore(text, pattern);


	return 0;
}
