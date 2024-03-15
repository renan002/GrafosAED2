#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;

typedef struct aux{
    int vertice;
    struct aux* prox;
} ElemLista, *PONT;

typedef struct {
    int numVertices;
    int numArestas;
    ElemLista** A;
} Grafo;

bool inicializaGrafo(Grafo* g, int vertices) {
    if(!g || vertices<1) return false;

    g->numArestas=0;
    g->numVertices=vertices;

    g->A = (ElemLista**)malloc(sizeof(ElemLista*)*vertices);

    int x;
    for (x=0;x<vertices;x++){
        g->A[x] = NULL;
    }
    return true; //O(V)
}

void exibeGrafo(Grafo* g){
    if(!g) return;

    printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n",g->numVertices,g->numArestas);

    ElemLista* atual;
    int x;

    for (x = 0; x < g->numVertices; x++)
    {
        printf("[%2i]",x);
        atual=g->A[x];
        while(atual) {
            printf(" ->%3i ",atual->vertice);
            atual=atual->prox;
        }
        printf("\n");
    }
    //O(V) + O(E) E = numero de arestas
    /*
        Nao eh V^2 pois eu nao necessariamente percorro V^2 arestas, apenas a quantidade que ele possui, diferente da matriz que sempre
        percorre V^2
    */
}

bool liberaGrafo(Grafo* g) {
    if(!g) return false;

    ElemLista *atual, *apagar;

    int x;
    for (x = 0; x < g->numVertices; x++)
    {
        atual=g->A[x];
        while (atual)
        {
            apagar = atual;
            atual = atual->prox;
            free(apagar);
        }
        
    }
    free(g->A);

    g->numArestas = 0;
    g->numVertices = 0;
    g->A = NULL;

    return true;
    
}

bool insereArestaAux(Grafo* g, int v1, int v2) {
    ElemLista *novo, *ant = NULL; //ElemLista* tipo e ElemLista *tipo eh a msm coisa
    ElemLista* atual = g->A[v1];

    
    while (atual && atual->vertice<v2) //atual->vertice == (*atual).vertice
    {
        ant = atual;
        atual = atual->prox;
    }
    
    if(atual && atual->vertice == v2) return false;

    novo = (ElemLista*)malloc(sizeof(ElemLista));
    novo->vertice = v2;
    novo->prox = atual;

    if(ant) ant->prox = novo;
    else g->A[v1] = novo;

    return true;
    //O(adj(v1)) adj == numero de adjacentes a v1
}

bool insereAresta(Grafo* g, int v1, int v2) {
    if(!g || v1 < 0 || v2 < 0 || v1>=g->numVertices ||v2>=g->numVertices || v1 == v2) return false;

    if(insereArestaAux(g, v1, v2)) {
        insereArestaAux(g, v2, v1);
        g->numArestas++;
    }
    return true;

    //O(1) + O(insereArestaAux)
}

bool removeArestaAux(Grafo* g, int v1, int v2) {
    ElemLista* ant = NULL;
    ElemLista* atual = g->A[v1];
    while (atual || atual->vertice<v2)
    {
        ant = atual;
        atual = atual->prox;
    }

    if (atual && atual->vertice==v2)
    {
        if (ant) ant->prox = atual->prox;
        else g->A[v1] = atual->prox;
        free(atual);
        return true;
        
    }
    return false;
    //O(adj(v1))
}

bool removeAresta(Grafo* g, int v1, int v2) {
    if(!g || v1 < 0 || v2 < 0 || v1>=g->numVertices || v2>=g->numVertices || v1 == v2) return false;

    if(removeArestaAux(g, v1, v2)){
        removeArestaAux(g, v1, v2);
        g->numArestas--;
        return true;
    }
    return false;
    //O(1) + O(removeArestaAux)
}

bool arestaExiste(Grafo* g, int v1, int v2) {
    if(!g || v1<0 || v2< 0  ||v1 >= g->numVertices || v2 >= g->numVertices) return false;

    ElemLista* atual = g->A[v1];
    while (atual && atual->vertice < v2)
        atual = atual->prox;
    if (atual && atual->vertice == v2) return true;

    return false;
    //O(adj(v1))
}

int numeroDeVertices(Grafo* g){
    if (g!=NULL) return g->numVertices;
    else return -1;
    //O(1)
}
    
int numeroDeArestas(Grafo* g){
    if (g!=NULL) return g->numArestas;
    else return -1;
}

int numeroDeArestas2(Grafo* g){
    if (g==NULL) return -1;

    ElemLista *atual;
    int x, arestas = 0;
    for (x=0; x<g->numVertices; x++){
        atual = g->A[x];
    while (atual){
        arestas++;
        atual = atual->prox;
    }
    }
    return arestas/2;
}

bool possuiVizinhos(Grafo* g, int v){
    if (!g || v < 0 || v >= g->numVertices || !(g->A[v]))
        return false;
    return true;
}

int retornaGrauDoVertice(Grafo* g, int v){
    if (!g || v < 0 || v >= g->numVertices) return -1;

    int grau = 0;
    ElemLista* atual = g->A[v];
    while (atual){
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int main(){
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));

    inicializaGrafo(g, 10);
    insereAresta(g, 1, 4);
    exibeGrafo(g);
}