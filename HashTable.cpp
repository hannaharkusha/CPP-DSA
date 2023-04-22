// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

//Zadanie 1
class HashTable{
    private:
        string* t;
        int capacity;
        int size;
    public:
        HashTable(int c){
            t = new string[c];
            capacity = c;
            size = 0;
        };                //konstruktor tworzący pustą tablicę o pojemności c
        int getSize(){
            return size;
        }
        bool empty(){
            if ( size==0 ) return true;
            else return false;
        };                  

        bool full(){
            if( size==capacity ) return true;
            else return false;
        };                   

        int hashFunction(string s){
            return stoi(s)%capacity;
        };        //funkcja haszująca dla klucza s

        int insert(string s){
            if(!full()){
            if(t[hashFunction(s)] == "") {
                t[hashFunction(s)] = s; 
                size++;
                return 0;
            }
            else {
                int count = 0;
                for(int i = hashFunction(s)+1; i<capacity;  i++){
                    count++;
                    if(t[i] == "") {
                    t[i] = s; 
                    size++;
                    return count;
                    }
                }
                for(int i = 0; i<hashFunction(s); i++){
                    count++;
                    if(t[i] == "") {
                    t[i] = s; 
                    size++;
                    return count;
                    }
                }
            }
            }
        };            //wstawienie klucza s (zwraca liczbę prób przy wystąpieniu kolizji - 0 jeśli kolizja nie wystąpiła)(udana proba sie nie zlicza)

        void del(string s){
            if(!empty()){
            if(t[hashFunction(s)]==s){
                t[hashFunction(s)]="";
                size--;
            }
            else{
                for(int i = hashFunction(s); i<capacity;  i++){
                    if(t[i] == s)  {
                        t[i]="";
                        size--;
                    }
                 }
                for(int i = 0; i<hashFunction(s); i++){
                    if(t[i] == s)  {
                        t[i]="";
                        size--;
                    }
                }
            }
            }
        };                //usuwa klucz s

        string search(string s){
            if(t[hashFunction(s)]==s) return t[hashFunction(s)];
            else{
                 for(int i = hashFunction(s); i<capacity;  i++){
                    if(t[i] == s) return t[i];
                 }
                for(int i = 0; i<hashFunction(s); i++){
                    if(t[i] == s) return t[i];
                }
            }
        };        //wyszukuje i zwraca s

        int search1(string s){
             if(t[hashFunction(s)]!=s){
                int count =0;
                 for(int i = hashFunction(s)+1; i<capacity;  i++){
                    count++;
                    if(t[i] == s) return count;
                 }
                for(int i = 0; i<hashFunction(s); i++){
                    count ++;
                    if(t[i] == s) return count;
                }
            }
            else return 0;
        };            //wyszukuje s i zwraca liczbę prób przy wystąpieniu kolizji - 0 jeśli kolizja nie wystąpiła(udana proba sie nie zlicza)

        void print(){
            cout<<endl;
            for(int i=0; i<capacity; i++) cout<<i<<" - "<<t[i]<<endl;
        }; //wypisuje tablicę (z numerami pól), pozostawia puste dla wolnych pól

        ~HashTable(){
            delete [] t;
        }
};

int main(){
    int n = 10;                //pojemność tablicy z haszowaniem

    HashTable h(10);

    cout<<"empty(): 1 - "<<h.empty();cout<<endl;
    cout<<"insert(5):"<<h.insert("5"); h.print();  
    cout<<"insert(12):"<<h.insert("12"); h.print(); 
    cout<<"insert(34):"<<h.insert("34"); h.print(); 
    cout<<"insert(16):"<<h.insert("16"); h.print(); 
    cout<<"insert(65):"<<h.insert("65"); h.print(); 
    cout<<"insert(75):"<<h.insert("75"); h.print(); 
    cout<<"insert(14):"<<h.insert("14"); h.print(); 
    cout<<"insert(1):"<<h.insert("1"); h.print();  
    cout<<"insert(89):"<<h.insert("89"); h.print();
    cout<<"insert(26):"<<h.insert("26"); h.print();

    cout<<"full(): 1 - "<<h.full(); cout<<endl;
    cout<<h.getSize()<<endl;
    
    cout<<"del(26):"; h.del("26"); h.print();
     
    cout<<"full(): 0 - "<<h.full(); cout<<endl;
    cout<<h.getSize()<<endl;
     
    cout<<"insert(99):"<<h.insert("99"); h.print();
    cout<<"full(): 1 - "<<h.full(); cout<<endl;
    cout<<h.getSize()<<endl;
     
    cout<<"search(16):"<<h.search("16"); h.print();
    cout<<"search1(16):"<<h.search1("16"); h.print();
    
    cout<<"search(16):"<<h.search("16"); h.print();
    cout<<"search1(16):"<<h.search1("16"); h.print();
    
    cout<<"search(14):"<<h.search("14"); h.print();
    cout<<"search1(14):"<<h.search1("14"); h.print();
    
    cout<<"search(99):"<<h.search("99"); h.print();
    cout<<"search1(99):"<<h.search1("99"); h.print();
    
    return 0;
}

