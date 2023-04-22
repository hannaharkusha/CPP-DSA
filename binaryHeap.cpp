#include <iostream>

using namespace std;

class MinHeap{
    private:
        int* kopiec;
        int capacity;
        int size;
    public:

        MinHeap(int c){
            capacity = c;
            size = 0;
            kopiec = new int[c];
        };            //tworzy pusty kopiec o pojemnosci c

        MinHeap(){
            kopiec = new int []{1,2,4,6,5,4,7,7,7,9,6};
            size = 11;
            capacity = 15;
        };                //konstruktor do testow kopca - nalezy utworzyc kopiec z nastepujaca zawartoscia: 1, 2, 4, 6, 5, 4, 7, 7, 7, 9, 6

        bool empty(){
            if(size==0) return true;
            else return false;
        };

        bool full(){
            if (size == capacity) return true;
            else return false;
        };

        int getLeft(int i){
            if(2*i+1<size) return 2*i+1;
            else return -1;
        };                    //zwraca pozycje lewego syna (2n+1)
        int getRight(int i){
            if(2*i+2<size) return 2*i+2;
            else return -1;
        };                //zwraca pozycje prawego syna (2n+2)

        int getParent(int i){
            if(2*i+2>size) return (i-1)/2;
            else return -1;
        };                //zwraca pozycje ojca (n-1)/2

        int getSize(){
            return size;
        };                        //zwraca rozmiar kopca

        void setSize(int s){
            if(s<=capacity) size = s;
            else cout<<"S is bigger than capacity!"<<endl;
        };                //ustawia rozmiar kopca na s??????????????????????????????????????????????????????

        int getValue(int i){
            if(i<size) return kopiec[i];
            else return -100;//przykladowa wartosc pustej pozycji
        };                //zwraca wartosc z pozycji i

        void setValue(int i, int x){

            if(i<size) {
                    kopiec[i] = x;
                    bottomUp(i);
                    topDown(i);
            }
            if(i==size){
                    kopiec[i] = x;
                    size++;
                    bottomUp(i);
                    topDown(i);
            }
        };        //ustawia wartosc x na pozycji i (czyli wartosci sie zamieniaja???????????)

        void bottomUp(int i){
            if(i>0){
                int p = getParent(i);
                if(kopiec[i]<kopiec[p]){
                    swap(kopiec[i],kopiec[p]);
                    bottomUp(p);
                }
            }
        };         //przywraca wlasnosc kopca metoda wynurzania

        void topDown(int i){

            int l = getLeft(i);
            int r = getRight(i);
            int g = i;
            if(l==(2*i+1) && kopiec[l]<kopiec[i])
                g = l;
            if(r==(2*i+2) && kopiec[r]<kopiec[g])
                g = r;
            if(g != i){
                swap(kopiec[i], kopiec[g]);
                topDown(g);
            }
        };         //przywraca wlasnosc kopca metoda zatapiania

        void printOut(){
            for(int i=0; i<size; i++){
                cout<<kopiec[i];
            }
             cout<<endl;
        }
//dla kolejki priorytetowej opartej na kopcu binarnym
        void insert(int x){
            if(full()) cout<<"The heap is full";
            else{
                kopiec[size] = x;
                bottomUp(size);
                size++;
            }
        };                    //wstawia element z wartoscia x (tutaj wartosc jest jednoczesnie priorytetem)

        void deleteMin(){
            if(empty()) cout<<"The heap is empty!";
            else{
                size--;
                swap(kopiec[0], kopiec[size]);
                topDown(0);
            }
        };                     //usuwa element z minimalna wartoscia

        int minimum(){
            if(!empty()) return kopiec[0];
        };                        //zwraca minimalna wartosc

        void del(int i){
             if(empty()) cout<<"The heap is empty!";
             else{
                size--;
                swap(kopiec[i],kopiec[size]);
                topDown(i);
                bottomUp(i);
             }
        };  //usuwa element na pozycji i

        void decreaseKey(int i, int x){
            kopiec[i] = x;
            topDown(i);
            bottomUp(i);
        };        //zmniejsza wartosc priotytetu dla danych na pozycji i, ustawia x ????????????????????????????????????????
};

int main()
{
    cout<<endl<<"Zadanie 1 - test"<<endl;
    MinHeap* h = new MinHeap(); //1, 2, 4, 6, 5, 4, 7, 7, 7, 9, 6
    h->printOut();

    h->del(0);
    h->printOut();

    h->insert(3);
    h->printOut();

    h->setValue(1,8);
    h->printOut();

    h->deleteMin();
    h->printOut();

    cout<<endl<<"Is empty: 0 - "<<h->empty()<<endl;
    cout<<"The left son of 3 (7) - "<<h->getLeft(3)<<endl;
    cout<<"The right son of 4 (10) - "<<h->getRight(4)<<endl;
    cout<<"The parent of 7 (3) - "<<h->getParent(7)<<endl;
    cout<<"Value from 7 (7) - "<<h->getValue(7)<<endl;
    h->setValue(0, 10);
    cout<<"Value of 0 is now 10 - "<< h->getValue(0)<<endl;
    h->del(11);
    cout<<"Value of 11 is now 'none' - "<< h->getValue(11)<<endl;
    cout<<"Value from 10 (6) - "<<h->getValue(10)<<endl;


    cout<<endl<<"Is full(): 0 - "<< h->full();
    return 0;
}
