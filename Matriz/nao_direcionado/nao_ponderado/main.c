#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;

typedef struct {
    int numVertices;
    int numArestas;
    bool** matriz;
} Grafo;

void main(){
    printf("Hello World! \n");

    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    int v1,v2;
    v1 = 2;
    v2 = 1;

    initGrafo(g, 5);
    exibeGrafo(g);
    printf("%i \n",insereAresta(g, 0,1));
    printf("%i \n",insereAresta(g, v1,v2));
    printf("%i \n",removeAresta(g, v1,v2));
    printf("o valor aresta [%i][%i] é %i",v1,v2,arestaExiste(g,v1,v2));
    exibeGrafo(g);
    printf("\nNum arestas: %i", numArestas2(g));

    printf("\n");
}

bool initGrafo(Grafo* g, int nVertices) {
    if(!g || nVertices < 1) return false;

    g->numVertices = nVertices;
    g->numArestas = 0;
    
    int x, y;
    g->matriz = (bool**) malloc(sizeof(bool*)*nVertices);
    for(x=0;x<nVertices;x++){
        g->matriz[x] = (bool*) malloc(sizeof(bool)*nVertices);
        for(y=0;y<nVertices;y++){
            g->matriz[x][y] = false;
        }
    }
    return true;
    //O(V²)
}

void exibeGrafo(Grafo* g) {
    if(!g) return;

    int x,y;

    printf("\n Exibindo um Grafo de %i arestas e %i vertices \n", g->numArestas, g->numVertices);

    for(x=0;x<g->numVertices;x++){
        printf("\t%5i", x);
    }
    printf("\n");
    for(x=0;x<g->numVertices;x++) {
        printf("%i",x);
        for(y=0;y<g->numVertices;y++){
            printf("\t%5i",g->matriz[x][y]);
        }
        printf("\n");
    }
    //O(V²)
}

bool liberaGrafo(Grafo* g) {
    if (!g) return false;

    int x;
    for(x=0;x<g->numVertices;x++){
        free(g->matriz[x]);
    }
    free(g->matriz);
    g->numArestas = 0;
    g->numVertices = 0;
    g->matriz = NULL;

    return true;
    //O(V)
}

bool insereAresta(Grafo* g, int v1, int v2) {
    if(!g || v1<0 || v2<0 || v1>=g->numVertices || v2>=g->numVertices || v1==v2) return false;

    if(g->matriz[v1][v2] == false) {
        g->matriz[v1][v2] = true;
        g->matriz[v2][v1] = true;
        g->numArestas++;
    }
    return true;
    //O(1)
}

bool removeAresta(Grafo* g, int v1, int v2) {
    if(!g || v1<0 || v2<0 || v1>=g->numVertices || v2>=g->numVertices || v1==v2) return false;

    if(g->matriz[v1][v2] == true) {
        g->matriz[v1][v2] = false;
        g->matriz[v2][v1] = false;
        g->numArestas--;
    }
    return true;
    //O(1)
}

bool arestaExiste(Grafo* g, int v1, int v2) {
    if(!g || v1<0 || v2<0 || v1>=g->numVertices || v2>=g->numVertices || v1==v2) return false;
    return g->matriz[v1][v2];
    //O(1)
}

int numVertices(Grafo* g) {
    if(!g) return -1;
    return g->numVertices;
    //O(1)
}

int numArestas(Grafo* g) {
    if(!g) return -1;
    return g->numArestas;
    //O(1)
}

int numArestas2(Grafo* g) {
    if(!g) return -1;

    int x,y, nArestas;
    nArestas = 0;
    for(x=0;x<g->numVertices;x++) {
        for(y=x+1;y<g->numVertices;y++) {
            if(g->matriz[x][y]==true) nArestas++;
        }
    }
    /*
    int x,y, nArestas;
    for(x=0;x<g->numVertices;x++) {
        for(y=0;y<g->numVertices;y++) {
            if(g->matriz[x][y]==true) nArestas++;
        }
    }
    nArestas=nArestas/2;
    */
    return nArestas;
    //O(V²)
}

bool possuiVizinho(Grafo* g, int v) {
    if(!g || v<0 || v>=g->numVertices) return false;

    int x;
    for(x=0;x<g->numVertices;x++) {
        if(g->matriz[v][x]==true) return true;
    }
    return false;
    //O(V)
}

int retornaGrauDoVertice(Grafo* g, int v) {
    if(!g || v<0 || v>=g->numVertices) return -1;

    int x, grau = 0;
    for(x=0;x<g->numVertices;x++) {
        if(g->matriz[v][x]==true) grau++;
    }
    return grau;
    //O(V)
}