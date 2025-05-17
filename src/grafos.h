/**
 * @file grafos.h
 * @author Diogo Silva (a31504@alunos.ipca.pt)
 * @brief Definições de estruturas e protótipos para manipulação de grafos
 * @version 0.1
 * @date 2025-05-10
 */

 #ifndef GRAFOS_H
 #define GRAFOS_H
 
 #include "dados.h"
 #include <stdio.h>
 #include <stdlib.h>
 #define MAX_CAMINHOS 100
 #define MAX_VERTICES_CAMINHO 100
 // adjacencia dos vertices bidirecional
 typedef struct Adj {
	 struct Vertice* v1;
	 struct Vertice* v2;
	 struct Adj* prox;
 } Adj;
  // vertice básico
 typedef struct Vertice {
	 CasaF* antena;
	 struct Adj* adjacencias;
	 struct Vertice* prox;
	 int visitado;
 } Vertice;
  // grafo
 typedef struct Grafo {
	 Vertice* h;
 } Grafo;

//estruturas para calcular e listar caminhos
typedef struct {
    Vertice* vertices[MAX_VERTICES_CAMINHO];
    int tamanho;
} Caminho;

typedef struct {
    Caminho caminhos[MAX_CAMINHOS];
    int total;
} ListaDeCaminhos;

 // Constantes
 #define VAZIO '.'

 
 // Protótipos de funções
 Grafo* InicializaGrafo(int* erro);
 Vertice* CriarVertice(CasaF* antena, int* erro);
 CasaF* CriarAntena(char c, int linha, int coluna, int* erro);
 Adj* CriarAdj(Vertice* v1, Vertice* v2, int* erro);
 Vertice* ProcuraVertice(Vertice* novo, Grafo* cabeca, int* erro);
 int PosicaoVertice(Vertice* v);
 Grafo* InsereVertice(Vertice* novo, Grafo* cabeca, int* erro);
 Grafo* leTxtGrafos(char* nome, Grafo* cabeca, int* erro);
 Grafo* insereAdjacencias(Grafo* cabeca, int* erro);
 int estaNoRadar(int colunaOrigem, int colunaChegada, int linhaOrigem, int linhaChegada);
 Vertice* insereAdjacenciaVertice(Vertice* h, Adj* adj, int* erro);
 int limpaAdj(Grafo* cabeca);
 Grafo* limpaV(Grafo* cabeca, int* erro);
 int limpaGrafo(Grafo* cabeca, int* erro);
 int limpaConteudoGrafo(Grafo* cabeca,int*erro);
 int mostraVertices(Grafo* g);
 int mostraVerticesCaminho(Grafo* g);
 Grafo* DFSUtil(Vertice* v, Grafo* caminho, int* erro);
 Grafo* DFS_CaminhoGrafo(Grafo* original, int linha, int coluna, int* erro);
 Grafo* leFicheiroBinario(char* nomeFicheiro,Grafo* g,int*erro);
 Grafo* escreveFicheiroBinario(char* nomeFicheiro,Grafo*g,int*erro);
 Vertice* ProcuraVerticeAntena(CasaF *novo, Grafo* cabeca,int*erro);
 ListaDeCaminhos calcularCaminhosSimples(Grafo* g, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int* erro);
 int imprimirCaminhosSimples(ListaDeCaminhos* resultados);
 int mostraVisitados(Vertice** visitados, int count);
 Vertice** BFS(Grafo* g, int linha, int coluna, int* erro, int* visitados_count);
 int detectarCruzamentoGeral(Grafo* g, char freq1, char freq2, int linhas[], int colunas[]) ;
 int imprimirCruzamentosGerais(int linhas[], int colunas[], int total);

	#endif