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
#define vazio '.'
#include"funcoes.h"
#include<stdio.h>
#include<stdlib.h>
Casa *mapa;
int x=0,y=1;

Casa* CriaMapaCasas(char* nome){
    FILE* ficheiro = fopen(nome, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return NULL;
    }
    if(mapa!=NULL){
        LimpaMemoria();
    }
    mapa=NULL;
    int c=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            if(c!=vazio){
                mapa=CriaAdiciona(c,y,x);
            }
        }
    }
    fclose(ficheiro);
    return mapa;
}
Casa *CriaCasa(char c,int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    Casa* aux = (Casa*)malloc(sizeof(Casa));
    aux->c=c;
    aux->linha=linha;
    aux->coluna=coluna;
    aux->prox=NULL;
    return aux;
}
int Posicao(Casa* c){
    int posicao=0, linha= c->linha, coluna= c->coluna;
    posicao=((linha-1)*x)+coluna-1;
    return posicao;
}
void LimpaMemoria(){
    Casa *atual = mapa;
    Casa *proximo=NULL;
    while (atual)
    {
        proximo=atual->prox;
        free(atual);
        atual = proximo;
    }
    mapa=NULL;
}
void MostraListaNovo(){
    Casa* atual=mapa;
    for(int i=1;i<=y;i++){
        for (int j = 1; j <= x; j++)
        {
            if(atual && atual->linha==i && atual->coluna==j){
                if(ExisteEfeitoEfeitoNefasto(i,j)){
                    printf("\033[0;33m%c\033[0m",atual->c);
                }else{
                    printf("%c",atual->c);
                }
                atual=atual->prox;
            }else{
                if(ExisteEfeitoEfeitoNefasto(i,j)){
                    printf("#");
                }
                else{
                    printf("%c",vazio);
                }
            }
            if(j==x){
                printf("\n");
            }
            
        }
        
    }
}
int ExisteEfeitoEfeitoNefasto(int linha, int coluna){
    Casa* atual= mapa,*prox = atual->prox;
    int difC, difL;
    while(atual){
        prox=atual->prox;
        while (prox)
        {
            if(prox->c==atual->c){
                difL=abs(atual->linha-prox->linha);
                difC=abs(atual->coluna-prox->coluna);
                if(prox->coluna+difC<x && prox->linha+difL<y){//efeito nefasto para frente
                    if(coluna==prox->coluna+difC && linha==prox->linha+difL){
                        return 1;
                    }
                }
                if(atual->coluna-difC<x && atual->linha-difL<y && atual->coluna-difC>0 && atual->linha-difL>0){//efeito nefasto para trás
                    if(coluna==atual->coluna-difC && linha==atual->linha-difL){
                        return 1;
                    }
                }
            }
            prox=prox->prox;
        }
        atual=atual->prox;
    }
    return 0;  
}
Casa* AdicionaCasa(Casa* n){

    if(!n) return mapa;
    if(!mapa){//cria mapa
        mapa=n;
        return mapa;
    }
    if(ExisteEfeitoEfeitoNefasto(n->linha,n->coluna)){
        printf("Existe efeito nefasto na posição deseja mesmo inserir?[Y/n]:");
        char resposta;
        scanf("%c",&resposta);
        if(resposta!='y' && resposta!='Y'){
            return mapa;
        }
    }
    Casa *atual=mapa;
    while (atual)
    {
        if(Posicao(n)==Posicao(atual)){
            printf("Erro, já existe antena na posição (%d,%d)\n",n->linha,n->coluna);
            return mapa;
        }
        if(Posicao(n)<Posicao(atual)){
            //adicionar inicio
            n->prox=atual;
            mapa=n;          
            return mapa;
        }else if(atual->prox && Posicao(n)<Posicao(atual->prox)){
            //adicionar ao meio
            n->prox=atual->prox;
            atual->prox=n;
            return mapa;
        }
        if(atual->prox==NULL){
            //adicionar ao fim
            atual->prox=n;
            return mapa;
        }
        atual=atual->prox;
    }
    printf("Erro inesperado\n");
    return mapa;
    
}
Casa *CriaAdiciona(char c, int linha, int coluna){
    return AdicionaCasa(CriaCasa(c,linha,coluna));
}
Casa *RemoverCasa(int linha, int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return mapa;
    Casa *atual=mapa;
    if(atual && atual->coluna==coluna && atual->linha==linha){
        mapa= atual->prox;
        free(atual);
        return mapa;
    }
    while (atual)
    {
        if(atual->prox && atual->prox->coluna==coluna && atual->prox->linha==linha){
            Casa *temp = atual->prox;
            atual->prox = temp->prox;
            free(temp);
            return mapa;
        }
        atual=atual->prox;
    }
    printf("Antena não localizada\n");
    return mapa;
    
}
void criaMapaFicheiro(){
    FILE* ficheiro;
    Casa* atual=mapa;
    ficheiro = fopen("mapa.txt", "w");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    for(int i=1;i<=y;i++){
        for (int j = 1; j <= x; j++)
        {
            if(atual && atual->linha==i && atual->coluna==j){
                fprintf(ficheiro,"%c",atual->c);
                atual=atual->prox;
            }else{
                fprintf(ficheiro, "%c",vazio);
            }
            if(j==x && i!=y){
                fprintf(ficheiro,"\n");
            }
            
        }
        
    }
    
    fclose(ficheiro);
}
void MostraListaC(){
    Casa* atual=mapa;
    while (atual)
    {
        printf("%c",atual->c);
        atual=atual->prox;
    }
    
}
