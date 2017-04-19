#include<stdio.h>
#include<vector>
using namespace std;

struct nodo
{
    vector<int> ady;
    int chainPos,chain,sizeSubTree;
} T[100000];

struct chains
{
    vector< int > node;
} CN[100000] ;
int n,a,b,c,x=-1,total_chain=1;
int chainHead[100000],chainSize[100000];

void HLD(int nd, int ant,int chain_no)
{
    /// Establecer representante de cada cadena, el nodo mas "arriba"
    if(chainHead[chain_no] == -1)
        chainHead[chain_no] = nd;

    T[nd].chain = chain_no;                 /// Guardar a que cadena pertenece cada nodo
    T[nd].chainPos = chainSize[chain_no];   /// Guardar en que posición de su cadena esta cada nodo
    chainSize[chain_no]++;                  /// Aumentar el tamaño de la cadena actual

    CN[chain_no].node.push_back(nd);

    int aux=-1,eN;

    /// Establecer el nodo especial y guardarlo en eN
    for(int i = 0; i < T[nd].ady.size(); i++)
    {
        if(T[nd].ady[i] == ant) continue;

        if(T[T[nd].ady[i]].sizeSubTree > aux)
        {
            aux=T[T[nd].ady[i]].sizeSubTree;
            eN = T[nd].ady[i];
        }

    }
    for(int i = 0; i < T[nd].ady.size(); i++)
    {
        if( T[nd].ady[i] == ant ) continue;

        /// Si es el nodo especial asignar la misma cadena si no cambiar de cadena
        if( T[nd].ady[i] == eN )
        {
            HLD( T[nd].ady[i] , nd , chain_no);
        }
        else
        {
            total_chain++;
            HLD( T[nd].ady[i] , nd , total_chain);
        }
    }
    return;
}
void dfs(int nd, int ant)
{
    T[nd].sizeSubTree = 1;

    for(int i = 0; i < T[nd].ady.size(); i++)
    {
        if(T[nd].ady[i] == ant) continue;

        dfs( T[nd].ady[i] , nd );

        T[nd].sizeSubTree += T[T[nd].ady[i]].sizeSubTree;
    }

    return;
}
int main()
{
    /*
    Caso de ejemplo
    18
    1 2
    1 3
    1 4
    2 6
    2 7
    3 8
    4 9
    4 10
    4 11
    4 5
    6 12
    7 13
    12 14
    12 15
    13 16
    13 17
    13 18
    */
    scanf("%d",&n);

    for(int i=1; i<=n; i++) chainHead[i]=-1;

    /// Un arbol con N nodos numerados de 1 a N
    for(int i=1; i<n; i++)
    {
        scanf("%d %d",&a,&b);
        T[a].ady.push_back(b);
        T[b].ady.push_back(a);
    }

    /// Obtener el tamaño de cada subarbol
    dfs(1,1);

    HLD(1,1,1);

    for(int i=1; i<=total_chain; i++)
    {
        printf("Nodos de la cadena # %d : ",i);
        for(int j=0; j<CN[i].node.size(); j++)
            printf("%d ",CN[i].node[j]);
        printf("\n");
    }
    return 0;
}

