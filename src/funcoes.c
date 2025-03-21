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
Casa *mapa,*fim;
int x=0,y=1;
void CriaMapa(char* nome){
    FILE* ficheiro = fopen(nome, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    
    int c=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            CriaAdicionaFim(c,y,x);
        }
    }
    printf("linhas:%d,colunas:%d",y,x);
    fclose(ficheiro);

}
void EscreveMapa(char* ficheiro){
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
            CriaAdicionaFim(c,y,x);
        }

    }
    
    fclose(arquivo);

}
Casa *CriaCasa(char c,int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    Casa* aux = (Casa*)malloc(sizeof(Casa));
    aux->c=c;
    aux->linha=linha;
    aux->coluna=coluna;
    aux->efeitoNefasto=0;
    aux->prox=NULL;
    aux->ant=NULL;
    return aux;
}
Casa *CriaCasaSemAntena(int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    Casa* aux = (Casa*)malloc(sizeof(Casa));
    aux->c=vazio;
    aux->linha=linha;
    aux->coluna=coluna;
    aux->efeitoNefasto=0;
    aux->prox=NULL;
    aux->ant=NULL;
    return aux;
}
#pragma region AdicionaCasa


Casa* AdicionaCasaInicio(Casa *n){
    if(!n) return mapa;//n é nulo
    if(!mapa){
        //mapa não existe
        mapa=n;
        fim=n;
    } 
    else{
        //adiciona ao inicio
        n->prox=mapa;
        mapa->ant=n;
        mapa=n;
    }
    return mapa;
}
Casa* AdicionarCasaMeio(Casa *n){
    if(!n) return mapa;//n é nulo
    if(!mapa){
        //mapa não existe
        mapa=n;
        fim=n;
    }else{
        Casa* atual= mapa;
        while (atual)
        {
            if(atual->coluna==n->coluna && atual->linha==n->linha){
                n->prox=atual->prox;
                n->ant=atual->ant;
                n->ant->prox=n;
                n->prox->ant=n;
                free(atual);
                return mapa;     
            }
            atual= atual->prox;
        } 
    }
    return mapa;
}
Casa* AdicionarCasaFim(Casa *n){
    if(!n) return mapa;//n é nulo
    if(!mapa){
        //mapa não existe
        mapa=n;
        fim=n;
    } 
    else{
        fim->prox= n;
        n->ant= fim;
        fim= n;
    }
    return mapa;
}
#pragma endregion
#pragma region TrocaCasa

Casa* TrocarCasa(Casa *n){
    if(!n) return mapa;
    if(!mapa)mapa=AdicionaCasaInicio(n);
    if(Posicao(n)==1)mapa= TrocarCasaInicial(n);
    else if(Posicao(n)<x*y) mapa=TrocarCasaMeio(n);
    else if(Posicao(n)==x*y) mapa=TrocarCasaFinal(n);
    return mapa;
}

Casa *TrocarCasaInicial(Casa* n){
    n->prox=mapa->prox;
    free(mapa);
    mapa=n;
    return mapa;
}
Casa* TrocarCasaMeio(Casa *n){
    if(!n) return mapa;//n é nulo
    if(!mapa){
        //mapa não existe
        mapa=n;
        fim=n;
    }else{
        Casa* atual= mapa;
        while (atual)
        {
            if(atual->coluna==n->coluna && atual->linha==n->linha){
                n->prox=atual->prox;
                n->ant=atual->ant;
                n->ant->prox=n;
                n->prox->ant=n;
                free(atual);
                return mapa;     
            }
            atual= atual->prox;
        } 
    }
    return mapa;
}
Casa* TrocarCasaFinal(Casa *n){
    if(!n) return mapa;
    if(!mapa) mapa=AdicionaCasaInicio(n);
    else{
        n->ant=fim->ant;
        n->ant->prox=n;
        free(fim);
        fim=n;
    }
    return mapa;
}
#pragma endregion 
Casa* CriaAdicionaFim(char c,int linha, int coluna){
    Casa* aux = CriaCasa(c,linha,coluna);
    return AdicionarCasaFim(aux);
}
Casa* CriaAdicionaMeio(char c,int linha, int coluna){
    Casa* aux = CriaCasa(c,linha,coluna);
    return AdicionarCasaMeio(aux);
}
Casa* RemoverAntena(int linha, int coluna){
    TrocarCasa(CriaCasaSemAntena(linha,coluna));
    return mapa;
}
Casa* CalculaEfeitoNefastoFrente(){
    Casa* atual =mapa,*proxAtual=atual->prox, *nefastofrente=atual;
    int p=1;
    while (atual)
    {
        p=1;            
        proxAtual=atual->prox;
        if(atual->c!=vazio && proxAtual->c!=atual->c && atual->prox!=NULL){
            while (proxAtual)
            {
                if(proxAtual->c==atual->c){
                    nefastofrente=proxAtual;  
                    if(Posicao(proxAtual)+p<x*y){
                        for (int i = 0; i < p; i++)
                        {
                            nefastofrente=nefastofrente->prox;
                        }
                        nefastofrente->efeitoNefasto=1;
                    }
                    p++;
                }else{
                    p++;
                }
                proxAtual=proxAtual->prox;
            }
            
        }
        atual=atual->prox;
    }
    return mapa;
}
Casa* CalculaEfeitoNefastoTras(){
    Casa* atual =fim,*proxAtual=atual->ant,*nefastoatras=atual;
    int p=1;
    while (atual)
    {
        p=1;            
        proxAtual=atual->ant;
        if(atual->c!=vazio && proxAtual->c!=atual->c && atual->ant!=NULL){
            while (proxAtual)
            {
                if(proxAtual->c==atual->c){
                    nefastoatras=proxAtual;  
                    if(Posicao(proxAtual)-p>1){
                        for (int i = 0; i < p; i++)
                        {
                            nefastoatras=nefastoatras->ant;
                        }
                        nefastoatras->efeitoNefasto=1;
                    }
                    p++;
                }else{
                    p++;
                }
                proxAtual=proxAtual->ant;
            }        
        }
        atual=atual->ant;
    }
    return mapa;
}
Casa* CalculaEfeitoNefasto(){
    CalculaEfeitoNefastoFrente();
    CalculaEfeitoNefastoTras();
    return mapa;
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
void MostraLista(){     
    Casa *atual = mapa;
    int i=0;
    while (atual->prox)
    {
        i++;
        if(atual->efeitoNefasto && atual->c!=vazio){
            printf("\033[43m\033[30m%c\033[0m",atual->c); 
        }else if (atual->efeitoNefasto){
            printf("#"); 
        }else{
            printf("%c",atual->c); 
        }   
        if(i%x==0){
            printf("\n");
        }
        atual= atual->prox;
    }

    printf("%c\n",atual->c);
}