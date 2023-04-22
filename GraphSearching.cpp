#include <iostream>
#include <list>
using namespace std;

struct edge{
    int s;//node poczatka
    int t;//node konca
}; //struktura do tworzenia krawedzi

class Graph{
    private:

        int** adjMatrix;//macierz sasiedztwa
        int n;//liczba wezlow
        bool directed;//true - graf skierowany, false - graf nieskierowany

        void dfs(int s, int* visited){
            visited[s] = 1;
            cout<<s<<' ';

            for (int i = 0; i < n; i++)
                if(adjMatrix[s][i] == 1){
                    if (visited[i]==0)
                        dfs(i, visited);
                }
        };//wykonuje przeszukiwanie i wyswietla wezly w porzadku odwiedzenia

    public:

        Graph(int n, int m, edge edges[], bool directed){
            this->n = n;
            this->directed = directed;

            adjMatrix = new int* [n];
            for (int i = 0; i < n; i++) {
                adjMatrix[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    adjMatrix[i][j] = 0;
                }
            }//tworzenie macierzy i wypelnienie zerami

            if (directed) {
                for (int i = 0; i < m; i++) {
                    adjMatrix[edges[i].s][edges[i].t] = 1;
                }
            }

            else {
                for (int i = 0; i < m; i++) {
                    adjMatrix[edges[i].s][edges[i].t] = 1;
                    adjMatrix[edges[i].t][edges[i].s] = 1;
                }
            } //wypelnienie zgodnie z lista krawedzi

        };    //tworzy graf w oparciu o podana liste krawedzi

        void dfs(int s){
            int* visited = new int[n];
            for(int i =0; i<n; i++){
                visited[i] = 0;
            }
            dfs(0, visited);
        };  //metoda pomocnicza dla dfs - tworzy tabele visited i wywoluje metode prywatna dfs

        void bfs(int s){
            //Declare a queue and insert the starting vertex.
            list <int> fifo;
            fifo.push_back(s);

            //Initialize a visited array and mark the starting vertex as visited
            int* visited = new int [n];
            for(int i=0; i<n; i++)
                visited[i]=0;

            visited[s] = 1;

            while(!fifo.empty()){
                 //Remove the first vertex of the queue.
                 s=fifo.front();
                 cout<<s<<' ';
                 fifo.pop_front();

                 //Insert all the unvisited neighbors of the vertex into the queue.
                 for (int i = 0; i < n; i++)
                    if(adjMatrix[s][i] == 1){
                        if (visited[i]==0)
                            fifo.push_back(i);
                            visited[i]=1;
                 }

            }
        };  //wykonuje przeszukiwanie i wyswietla wezly w porzadku odwiedzenia


        /*friend ostream& operator<<(ostream& out, Graph& g){

        };  //wyswietla graf
        */

       void printOutGraph(){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++)
                cout<<adjMatrix[i][j]<<' ';
            cout<<endl;
        }
       };

        ~Graph(){
            for(int i=0; i<n; i++)
                delete adjMatrix[i];
            delete [] adjMatrix;
        };

};

int main()
{
    int n = 6, m =15;// liczba wezlow i krawedzi

    edge directedGraph[]={{0,4},{0,5},{1,0},{1,2},{1,4},{2,1},{2,3},{2,4},{3,2},{3,5},{4,0},{4,1},{4,3},{5,3},{5,4}};  //przykladowy graf

    Graph g(n,m,directedGraph,true);

    g.printOutGraph();

    g.dfs(0);
    cout<<endl;
    g.bfs(0);

    return 0;
}
