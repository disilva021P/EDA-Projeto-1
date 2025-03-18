/**
 * @file funcoes.c
 * @author Diogo SIlva (a31504@alunos.ipca.pt)
 * @brief CORPO da biblioteca funcoes que contêm as funções para as operações da 
 * lista linkada
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include"funcoes.h"
#include<stdio.h>
#include<stdlib.h>
Casa *mapa,*fim;
int x=0,y=1;
/**
 * @brief Função para inicializar o mapa a partir de um ficheiro
 * 
 * @param ficheiro: Local do ficheiro para carregar
 */
void CriaMapa(char* ficheiro){
    FILE* arquivo = fopen(ficheiro, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", ficheiro);
        return;
    }
    
    int c=0;
    while ((c = fgetc(arquivo)) != EOF) {
        
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            CriaAdiciona(c);
        }

    }
    
    fclose(arquivo);

}
/**
 * @brief Função que cria um local para colocar no mapa
 * 
 * @param c: Caractér a inserir no local
 * @return Casa*
 */
Casa *CriaCasa(char c){
    Casa* aux = (Casa*)malloc(sizeof(Casa));
    aux->c=c;
    aux->prox=NULL;
    aux->ant=NULL;
    return aux;
}
/**
 * @brief Função que adiciona uma Casa ao mapa
 * 
 * @param n: Casa a adicionar no mapa
 * @return Casa* que aponta para o início mapa
 */
Casa* AdicionarCasa(Casa *n){
    if(!n) return mapa;
    if(!mapa){
        mapa=n;
        fim=n;
    } 
    else{
        if(!mapa->prox){
            mapa->prox=n;
            n->ant=mapa;
            fim=n;
        }else{
            fim->prox= n;
            n->ant= fim;
            fim= n;
        }
    }
    return mapa;
}
/**
 * @brief Junção de duas funções para facilitar a criação e adição das casas no mapa
 * 
 * @param c: caracter a inserir no mapa
 * @return Casa* que aponta para o mapa
 */
Casa* CriaAdiciona(char c){
    Casa* aux = CriaCasa(c);
    return AdicionarCasa(aux);
}
/**
 * @brief Escreve o mapa na consola
 * 
 */
void MostraLista(){
    Casa *atual = mapa;
    int i=0;
    while (atual->prox)
    {
        i++;
        printf("%c",atual->c);
        if(i%x==0){
            printf("\n");
        }
        atual= atual->prox;
    }
    
    printf("%c\n",atual->c);
}
void LimpaMemoria(){
    Casa *atual = mapa;
    Casa *proximo=NULL;
    while (atual->prox)
    {
        proximo=atual->prox;
        free(atual);
        atual = proximo;
    }
    free(atual);
    mapa=NULL;
}
/**
 * @brief Adiciona uma antena na posição indicada 
 * 
 * @param c: Caractér antena
 * @param linha: Linha da antena 
 * @param coluna: Coluna da antena
 * @return Casa* que aponta para o mapa 
 */
Casa* AdicionarAntena(char c, int linha, int coluna){
    //TODO: Lembrar de atualizar os ruídos quando fizer a função!
    if(coluna==0 || coluna>x || linha==0 || linha>y)return mapa;
    Casa* atual=mapa;
    int posicao=0;
    if(linha< coluna || coluna==linha){
        posicao=coluna*linha;     
    }else{
        posicao=((linha-1)*x)+coluna-1;   
    }
    
    for (int i = 0; i < posicao; i++)
    {
        atual = atual->prox;
    }
    atual->c=c;
    return mapa;
}
/**
 * @brief Remove uma antena e corrige o ruído automaticamente
 * 
 * @param linha: Linha da antena que deseja remover
 * @param coluna: Coluna da antena que deseja remover
 * @return Casa* que aponta para o mapa
 */
Casa* RemoverAntena(int linha, int coluna){
    //TODO: Lembrar de atualizar os ruídos quando fizer a função!
    return AdicionarAntena('.',linha,coluna);
}