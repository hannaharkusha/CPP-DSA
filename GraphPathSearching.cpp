#include <iostream>
#include <cfloat>
using namespace std;

struct weightedEdge{
    int s;//poczatek krawedzi
    int t;//koniec krawedzi
    double w; //waga krawedzi
};

class WeightedGraph{
    private:

        double** adjWeightMatrix;
        int n;                //liczba wezlow
        bool directed;

    public:

        WeightedGraph(int n, int m, weightedEdge edges[], bool directed){

            this->n=n;
            this->directed=directed;

            //tworzymy macierz sasiedztwa
            adjWeightMatrix = new double* [n];
            for(int i=0; i<n; i++){
                adjWeightMatrix[i] = new double[n];
                for(int j=0;j<n; j++)
                    adjWeightMatrix[i][j] = DBL_MAX;
            }
            //wypelniamy macierz
            if(directed){
                for(int i=0; i<m; i++)
                    adjWeightMatrix[edges[i].s][edges[i].t] = edges[i].w;
            }
            else{
                for(int i=0; i<m; i++){
                    adjWeightMatrix[edges[i].s][edges[i].t] = edges[i].w;
                    adjWeightMatrix[edges[i].t][edges[i].s] = edges[i].w;
                }
            }
        }; //tworzy graf w oparciu o podana liste krawedzi z wagami

        void printOut(){
            for(int i=0; i<n;i++){
                for(int j=0; j<n;j++)
                {
                    cout<<adjWeightMatrix[i][j]<<' ';
                }
                cout<<endl;
            }
        };



        void Dijkstra(int s){

            bool* visited = new bool[n]; //do niego juz wziete pod uwage wierzcholki
            double* distances = new double[n]; //zawiera dlugosci sciezek od s do poszczegolnych wierzcholkow
            int* lastNodes = new int[n];
            //ustawiamy wszystkie dystansy na infinity
            for(int i=0; i<n; i++){
                distances[i] = DBL_MAX;
                visited[i] = false;
                lastNodes[i] = -1;
            }
            //wstawiamy zero jako dystans do wierzcholka zrodlowego
            distances[s] = 0;
            lastNodes[s] = s;

            int idx = 0;

            for(int j=0; j<n; j++){
                //szukamy min
                double min = DBL_MAX;
                for(int i=0; i<n; i++)
                    if(distances[i]<min && !visited[i]){
                        min = distances[i];
                        idx=i;
                    }
                //oznaczamy minimum jako odwiedzony
                visited[idx] = true;
                //uaktualniamy dystansy do wezlow sasiadow
                for(int i = 0; i<n; i++){
                    if (adjWeightMatrix[idx][i]<DBL_MAX){
                        if(adjWeightMatrix[idx][i]+distances[idx]<distances[i]){
                            distances[i]=adjWeightMatrix[idx][i]+distances[idx];
                            lastNodes[i]=idx;
                        }
                    }
                }

            }
            for(int i=0; i<n; i++)
                        cout<<i<<"-"<<distances[i]<<"(parent: "<<lastNodes[i]<<") ";
                    cout<<endl;

            shortestPath(s,2,lastNodes);
        };

        void shortestPath(int s, int t, int* parent){
            int pom=t;
            cout<<"Shortest path from "<<s<<" to "<<t<<": "<<s<<' ';
            while(parent[t]!=s){
                cout<<parent[t]<<' ';
                t=parent[t];
            }
            cout<<pom<<endl;

        }; //wyswietla wezly nalezace do najkrotszej sciezki od wezla s do wezla t

       void WarshallFloyd(){

             for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (adjWeightMatrix[i][j] > (adjWeightMatrix[i][k] + adjWeightMatrix[k][j])
                            && (adjWeightMatrix[k][j] != DBL_MAX
                            && adjWeightMatrix[i][k] != DBL_MAX))
                            adjWeightMatrix[i][j] = adjWeightMatrix[i][k] + adjWeightMatrix[k][j];
                    }
                }
            }

            cout << "The following matrix shows the shortest distances between every pair of vertices \n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adjWeightMatrix[i][j] == DBL_MAX)
                        cout << "INF"<< " ";
                    else
                        cout << adjWeightMatrix[i][j] << "   ";
                }
                cout << endl;
            }
        };


        ~WeightedGraph(){
            for(int i=0; i<n; i++)
                delete adjWeightMatrix[i];
            delete [] adjWeightMatrix;
        };
};


int main()
{
    int n = 6, m =15;
    weightedEdge edges[]={{0,4,1.0},{0,5,2.0},{1,0,3.0},{1,2,4.0},{1,4,5.0},{2,1,5.5},{2,3,6.0},{2,4,6.5},{3,2,7.0},{3,5,7.5},{4,0,10.0},{4,1,12.0},{4,3,4.5},{5,3,1.5},{5,4,1.7}};
    WeightedGraph g(n,m,edges,true);
    g.printOut(); cout<<endl;

    g.Dijkstra(0);
    g.WarshallFloyd();
    return 0;
}
