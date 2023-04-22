#include <iostream>
using namespace std;

//Zadanie 1
class Node{
    private:
        int value;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int v, Node* l, Node* r, Node* p){
            value = v;
            left = l;
            right = r;
            parent = p;
        };
        int getValue(){
            return value;
        };
        Node* getLeft(){
            return left;
        };
        Node* getRight(){
            return right;
        };
        Node* getParent(){
            return parent;
        };
        void setValue(int v){
            value=v;
        };
        void setLeft(Node* l){
            left=l;
        };
        void setRight(Node* r){
            right=r;
        };
        void setParent(Node* p){
            parent=p;
        };
};

class BSTree{
    private:
        Node* root;
    public:
        BSTree(){
            root=NULL;
        };       //tworzy puste drzewo

        Node* getRoot(){
            return root;
        };            //zwraca wskaznik do root - metoda pomocnicza w testowaniu

        bool empty(Node* p){
            if(p==NULL) return true;
            else return false;
        };        //zwraca prawde gdy (pod)drzewo o korzeniu p jest puste

        void inorder(Node* p){
            if(p==NULL) return;
            else{
                inorder(p->getLeft());
                cout<<p->getValue()<<' ';
                inorder(p->getRight());
            }
        };      //wyswietla w porzadku inorder

        void preorder(Node* p){
            if(p==NULL) return;
            else{
            cout<<p->getValue()<<' ';
            preorder(p->getLeft());
            preorder(p->getRight());
            }
        }    //wyswietla w porzadku preorder

    //BST
        void insert(int x){
            Node* n = new Node(x, NULL, NULL, NULL);
            //drzewo jest puste
            if(empty(root)) root = n;
            else{ //nie jest puste
                Node* pom = root;
                bool stop = false;
                while(!stop){
                    if(pom->getValue()>x){
                        if(pom->getLeft()!=NULL)
                            pom=pom->getLeft();
                        else{
                            pom->setLeft(n);
                            n->setParent(pom);
                            stop=true;
                        }
                    }
                    else{
                        if(pom->getRight()!=NULL)
                            pom=pom->getRight();
                        else{
                            pom->setRight(n);
                            n->setParent(pom);
                            stop=true;
                        }
                    }
                }
            }
        }; //wstawia wezel z wartoscia x

        Node* search(int x){
            if(!empty(root)){
            Node* pom = root;
            while(pom->getValue()!=x){
                if(pom->getValue()>x)
                    pom=pom->getLeft();
                else pom=pom->getRight();
            }
            return pom;
            }
        };         //zwraca wskaznik do wezla z wartoscia x (lub NULL jesli nie istnieje)

        Node* minimum(Node* p){
            if(!empty(p)){
                Node* pom = p;
                while(pom->getLeft()!=NULL){
                    pom=pom->getLeft();
                }
                return pom;
            }
            else return NULL;
        };            //zwraca wskaznik do wezla z minimalna wartoscia w (pod)drzewie p

        Node* maximum(Node* p){
            if(!empty(p)){
                Node* pom = p;
                while(pom->getRight()!=NULL){
                    pom=pom->getRight();
                }
                return pom;
            }
        };            //zwraca wskaznik do wezla z maksymalna wartoscia w (pod)drzewie p

        Node* successor(Node* p){
            if (empty(p)) return NULL;
            else
                return minimum(p->getRight());
        };    //zwraca wskaznik do nastepnika p

        Node* predecessor(Node* p){
            if (empty(p)) return NULL;
            else
                return maximum(p->getLeft());
        };    //zwraca wskaznik do poprzednika p

        void del(Node* p){

            Node* par = p->getParent();

            //jezeli wezel p nie istnieje
            if(search(p->getValue())==NULL) {
                cout<<"Nie istnieje";
            }
            else{
                //nie ma dzieci
                if(p->getLeft()==NULL && p->getRight()==NULL){
                    if(par==NULL){
                        p=NULL;
                        root=NULL;
                    }
                    else if(par->getLeft()==p)
                        par->setLeft(NULL);
                    else par->setRight(NULL);
                    delete p;
                }
                //ma dwa dziecka
                else if(p->getLeft()!=NULL && p->getRight()!=NULL){
                    Node* s = successor(p);
                    p->setValue(s->getValue());
                    del(s);
                }
                //ma jedno dziecko
                else{
                    Node* child = (p->getLeft())? p->getLeft(): p->getRight();
                    if(par==NULL){
                        p=child;
                        root = child;
                    }
                    else if(par->getLeft()==p){
                        par->setLeft(child);
                        child->setParent(par);
                    }
                    else {
                        par->setRight(child);
                        child->setParent(par);
                    }
                    delete p;
                }
            }
        };            //usuwa wezel wskazywany przez p

        int size(Node* p){
            // base case: empty tree has size 0
            if (p == NULL) {
                return 0;
            }
            // recursively calculate the size of the left and right subtrees and
            // return the sum of their sizes + 1 (for root node)
            return size(p->getLeft()) + 1 + size(p->getRight());
        }                 //zwraca rozmiar (pod)drzewa o korzeniu p


        int height(Node* p){
            if (p == NULL) {
                return -1;
            }

            int lefth = height(p->getLeft());
            int righth = height(p->getRight());

            if (lefth > righth) {
                return lefth + 1;
            } else {
                return righth + 1;
            }

        };              //zwraca wysokosc (pod)drzewa o korzeniu p


        void clear(Node *p){
           if(p!=NULL)
            {
                clear(p->getLeft());
                clear(p->getRight());
                del(p);
            }
        };  //usuwa wszystkie wezly z (pod)drzewa o korzeniu p

        ~BSTree(){
            delete root;
        };
};


int main(){

    //Zadanie 1 - test
    cout<<endl<<"Zadanie 1 - test"<<endl;

    BSTree* t = new BSTree();

    cout<<"\nIs empty - 1: "<<t->empty(t->getRoot())<<endl;
    cout<<"Adding nodes\n";
    t->insert(100);
    t->insert(20);
    t->insert(10);
    t->insert(30);
    t->insert(200);
    t->insert(150);
    t->insert(300);

    cout<<"Is empty - 0: "<<t->empty(t->getRoot())<<endl;

    cout << "\nInorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;
    cout << "Preorder Traversal: "; t->preorder(t->getRoot()); cout<<endl;
    cout << "\nThe size of the BST is " <<t->size(t->getRoot())<<endl;
    cout << "The height of the BST is " <<t->height(t->getRoot())<<endl;

    cout << "\nThe minimum of the tree is - "<< t->minimum(t->getRoot())->getValue()<<endl;
    cout << "The maximum of the tree is - "<< t->maximum(t->getRoot())->getValue()<<endl;

    cout << "The minimum of the right subtree is - "<< t->minimum(t->getRoot()->getRight())->getValue()<<endl;
    cout << "The maximum of the left subtree is - "<< t->maximum(t->getRoot()->getLeft())->getValue()<<endl;


    cout << "\nThe successor of the root is " << t->successor(t->getRoot())->getValue()<<endl;
    cout << "The predecessor of the root is " << t->predecessor(t->getRoot())->getValue()<<endl;
    /*
    cout << "\nDeleting the root"<<endl; t->del(t->getRoot());
    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;


    cout << "\nDeleting the root"<<endl; t->del(t->getRoot());
    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;

    cout << "\nDeleting the root"<<endl; t->del(t->getRoot());
    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;

    cout << "\nDeleting the root"<<endl; t->del(t->getRoot());
    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;

    cout << "\nDeleting the min"<<endl; t->del(t->minimum(t->getRoot()));
    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;
    */
    cout<<"\nWszystkie wezly sa usuwane\n"<<endl;

    t->clear(t->getRoot());

    cout << "Inorder Traversal: "; t->inorder(t->getRoot()); cout<<endl;
    cout << "The size of the BST is " <<t->size(t->getRoot())<<endl;
    cout << "The height of the BST is " <<t->height(t->getRoot())<<endl;
    cout<<"Is empty - 1: "<<t->empty(t->getRoot())<<endl;


    return 0;
}
