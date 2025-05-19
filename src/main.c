/**
 * @file main.c
 * @author Diogo SIlva (a31504@alunos.ipca.pt)
 * @brief Ficheiro principal
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include<stdlib.h>
#include<stdio.h>
#include"funcoes.h"
#include"erros.h"
#include"grafos.h"
int main(int argc, char const *argv[])
{/*
    int erro=1;
    limpaMemoriaErros();
    int erroPreencher = preencheDicionario("erros.txt");
    Grafo* grafo = InicializaGrafo(&erro);
    if (erro != 1) {
        printf("Erro ao inicializar grafo: %d\n", erro);
        return 1;
    }
    printf("Grafo inicializado com sucesso!\n");

    // Carrega mapa de um arquivo (exemplo: "mapa.txt")
    char* filename = "mapa.txt";

    grafo = leTxtGrafos(filename, grafo, &erro);

    if (erro != 1) {
        printf("Erro ao carregar mapa: %d\n", erro);
        return 2;
    }
    printf("Mapa carregado com sucesso!\n");
    // Executa DFS a partir de uma antena específica (ex: linha 1, coluna 1)7
    insereAdjacencias(grafo,&erro);
    grafo=escreveFicheiroBinario("grafos.bin",grafo,&erro);
    limpaGrafo(grafo,&erro);
    grafo=NULL;
    if(erro!=1){
        printf("%s\n",ErroPorPais_Cod("pt-pt",erro));
        return -1;
    }
    printf("-------------------------------------------------\n");
    grafo= InicializaGrafo(&erro);
    grafo=leFicheiroBinario("grafos.bin",grafo,&erro);
    mostraVertices(grafo);
    if(erro!=1){
        printf("%s\n",ErroPorPais_Cod("pt-pt",erro));
        return -1;
    }
    
    erro = 1;
    /*Grafo* caminho = DFS_CaminhoGrafo(grafo, 2, 9, &erro);
    if (!caminho) {
        printf("Erro ao executar DFS: %d\n", erro);
        return -1;
    }
    mostraVerticesCaminho(caminho);
    printf("-------------------------\n");
    int visitados;
    BFS(grafo,2,9,&erro);
    listarCaminhosSimples(grafo,2,9,5,5);
    // Limpa memória do grafo
    erro=1;
    */

/*
    int linhas[100], colunas[100];
    int total = detectarCruzamentoGeral(grafo, 'A', 'B', linhas, colunas);
    imprimirCruzamentosGerais(linhas, colunas, total);

    limpaGrafo(grafo, &erro);
    grafo=NULL;

    if (erro != 1) {
        printf("Erro ao limpar grafo: %d\n", erro);
        return 3;
    }
    printf("\nMemória liberada com sucesso!\n");
    limpaMemoriaErros();*/
    int erro;
    int erroPreencher = preencheDicionario("erros.txt");
    Grafo* grafo = InicializaGrafo(&erro);
    if(erro != 1){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
        return -1;
    }

    // Teste 1: Ler mapa de um ficheiro de texto
    printf("=== Teste 1: Ler mapa de texto ===\n");
    grafo = leTxtGrafos("mapa.txt", grafo, &erro);
    if(erro != 1){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
        return -1;
    }
    printf("Mapa carregado com sucesso!\n");
    insereAdjacencias(grafo,&erro);
    mostraVertices(grafo);


    // Teste 3: DFS a partir de uma posição
    printf("\n=== Teste 3: DFS ===\n");
    Grafo* caminhoDFS = DFS_CaminhoGrafo(grafo, 2, 3, &erro);
    if(erro != 1){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
    } else {

            printf("Caminho DFS encontrado:\n");
            mostraVerticesCaminho(caminhoDFS);
    }

    // Teste 4: BFS a partir de uma posição
    printf("\n=== Teste 4: BFS ===\n");
    int visitados_count;
    Vertice** visitadosBFS = BFS(grafo, 2, 3, &erro, &visitados_count);
    if(erro != 1){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
    } else {
        mostraVisitados(visitadosBFS, visitados_count);
        free(visitadosBFS);
    }

    // Teste 5: Caminhos entre dois pontos
    printf("\n=== Teste 5: Caminhos entre vértices ===\n");
    ListaDeCaminhos caminhos = calcularCaminhosSimples(grafo, 2, 3, 6, 11, &erro);
    if(erro != 0){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
    } else {
        printf("Caminhos encontrados:\n");
        imprimirCaminhosSimples(&caminhos);
    }

    // Teste 6: Detetar cruzamentos
    printf("\n=== Teste 6: Cruzamentos entre frequências ===\n");
    int linhas[100], colunas[100];
    int total = detectarCruzamentoGeral(grafo, 'A', 'B', linhas, colunas);
    imprimirCruzamentosGerais(linhas, colunas, total);

    // Teste 7: Escrever e ler binário
    printf("\n=== Teste 7: Gravar/Ler binário ===\n");
    grafo = escreveFicheiroBinario("grafo.bin", grafo, &erro);
    if(erro != 1){
        printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
        return -1;
    } else {
        Grafo* grafoBinario = InicializaGrafo(&erro);
        grafoBinario = leFicheiroBinario("grafo.bin", grafoBinario, &erro);
        if(erro != 1){
            printf("%s\n", ErroPorPais_Cod("pt-pt", erro));
            return -1;
        } else {
            printf("Grafo lido do binário:\n");
            mostraVertices(grafoBinario);
        }
        limpaGrafo(grafoBinario, &erro);
    }

    // Limpar recursos
    limpaGrafo(grafo, &erro);
    /*Casa* h=NULL;
    EfeitoNefasto* hE=NULL;
    if(argc==1){
        h=CriaMapaCasas("mapa.txt",h,&hE,&erro);

        int erroPreencher = preencheDicionario("erros.txt");
        if(erroPreencher!=1){
            printf("Erro a carregar ficheiro de erros (erros.txt)");
            return -1;
        }
        definirLingua("pt-pt");
    }
    else{
        h=CriaMapaCasas((char*)argv[1],h,&hE,&erro);
    }
    MostraListaNovo(h,hE);
    h=CriaAdiciona(h,'F',1,2,&hE,&erro);
    MostraListaNovo(h,hE);
    h=RemoverCasa(h,1,2,&hE,&erro);
    MostraListaNovo(h,hE);
    h=CriaAdiciona(h,'F',1,2,&hE,&erro);
    criaMapaFicheiro(h);
    h=EscreverListaFicheiro(h,&erro);
    h=LerListaFicheiro(h,&hE,&erro);
    MostraListaCasas(h,hE);
    hE=LimpaMemoriaEfeito(hE,&erro);      
    h=LimpaMemoria(h,&erro);*/
    return 0;
}
