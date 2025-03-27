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

int x=0,y=1;
//TODO: VALIDAÇÕES GERAIS

#pragma region Criacao
Casa *CriaCasa(char c,int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    Casa* aux = (Casa*)malloc(sizeof(Casa));
    aux->c=c;
    aux->linha=linha;
    aux->coluna=coluna;
    aux->prox=NULL;
    return aux;
}
CasaF *CriaCasaF(char c,int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    CasaF* aux = (CasaF*)malloc(sizeof(CasaF));
    aux->c=c;
    aux->linha=linha;
    aux->coluna=coluna;
    return aux;
}
EfeitoNefasto *CriaEfeitoNefasto(int linha,int coluna,Casa* x1, Casa* x2){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;
    EfeitoNefasto* aux = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
    aux->linha= linha;
    aux->coluna= coluna;
    aux->antenas[0]= x1;
    aux->antenas[1]= x2;
    aux->prox=NULL;
    return aux;
}
#pragma endregion


int ExisteEfeitoEfeitoNefasto(EfeitoNefasto *mapa, int linha, int coluna){
    EfeitoNefasto* atual= mapa;
    while(atual){
        if(atual->linha==linha && atual->coluna == coluna){
            return 1;
        }
        atual=atual->prox;
    }
    return 0;
}
EfeitoNefasto* CriaListaEfeitoEfeitoNefasto(EfeitoNefasto* cabeca, Casa *mapa){
    LimpaMemoriaEfeito(cabeca);
    Casa* atual= mapa,*prox = atual->prox;
    int difC, difL;
    while(atual){
        prox=atual->prox;
        while (prox)
        {
            if(prox->c==atual->c){
                difL=prox->linha-atual->linha;
                difC=abs(atual->coluna-prox->coluna);
                if(atual->coluna<prox->coluna){
                    if(prox->coluna+difC<=x && prox->linha+difL<=y){//efeito nefasto para frente
                        cabeca=CriaAdicionaEfeito(cabeca,prox->linha+difL,prox->coluna+difC,atual,prox);
                    }
                    if(atual->coluna-difC>0 && atual->linha-difL>0){//efeito nefasto para trás
                        cabeca=CriaAdicionaEfeito(cabeca,atual->linha-difL,atual->coluna-difC,atual,prox);
                    }
                }else{
                    if(prox->coluna-difC>0 && prox->linha+difL<=y){//efeito nefasto para frente
                        cabeca=CriaAdicionaEfeito(cabeca,prox->linha+difL,prox->coluna-difC,atual,prox);
                    }
                    if(atual->coluna+difC<=x && atual->linha-difL>0){//efeito nefasto para trás
                        cabeca=CriaAdicionaEfeito(cabeca,atual->linha-difL,atual->coluna+difC,atual,prox);
                    }
                }
                
                
            }
            prox=prox->prox;
        }
        atual=atual->prox;
    }
    return cabeca;
}

Casa* AdicionaCasa(Casa *mapa,Casa* n,EfeitoNefasto* cabeca){


    if(!n) return mapa;
    if(!mapa){//cria mapa
        mapa=n;
        return mapa;
    }
    if(ExisteEfeitoEfeitoNefasto(cabeca,n->linha,n->coluna)){
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
    return mapa;
}
EfeitoNefasto* AdicionaCasaEfeitoNefasto(EfeitoNefasto* cabeca,EfeitoNefasto* n){

    if(!n) return cabeca;
    if(!cabeca){//cria mapa
        cabeca=n;
        return cabeca;
    }
    EfeitoNefasto *atual=cabeca;
    while (atual)
    {
        if(PosicaoEfeitoNefasto(n)==PosicaoEfeitoNefasto(atual)){
            return cabeca;
        }
        if(PosicaoEfeitoNefasto(n)<PosicaoEfeitoNefasto(atual)){
            //adicionar inicio
            n->prox=atual;
            cabeca=n;          
            return cabeca;
        }else if(atual->prox && PosicaoEfeitoNefasto(n)<PosicaoEfeitoNefasto(atual->prox)){
            //adicionar ao meio
            n->prox=atual->prox;
            atual->prox=n;
            return cabeca;
        }
        if(atual->prox==NULL){
            //adicionar ao fim
            atual->prox=n;
            return cabeca;
        }
        atual=atual->prox;
    }
    return cabeca;
}

Casa *CriaAdiciona(Casa *mapa,char c, int linha, int coluna,EfeitoNefasto* cabeca){
    return AdicionaCasa(mapa,CriaCasa(c,linha,coluna),cabeca);
}
EfeitoNefasto *CriaAdicionaEfeito(EfeitoNefasto *cabeca, int linha, int coluna, Casa* x1,Casa* x2){
    return AdicionaCasaEfeitoNefasto(cabeca,CriaEfeitoNefasto(linha,coluna,x1,x2));
}

Casa *RemoverCasa(Casa *mapa, int linha, int coluna){
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

#pragma region Prints
void MostraListaNovo(Casa *mapa,EfeitoNefasto* cabeca){
    Casa* atual=mapa;
    for(int i=1;i<=y;i++){
        for (int j = 1; j <= x; j++)
        {
            if(atual && atual->linha==i && atual->coluna==j){
                if(ExisteEfeitoEfeitoNefasto(cabeca,i,j)){
                    printf("\033[0;33m%c\033[0m",atual->c);
                }else{
                    printf("%c",atual->c);
                }
                atual=atual->prox;
            }else{
                if(ExisteEfeitoEfeitoNefasto(cabeca,i,j)){
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
void MostraListaCasas(Casa *mapa,EfeitoNefasto* cabeca){
    Casa* atual=mapa;
    EfeitoNefasto*  efeito=cabeca;
    printf("Frequência | Linha | Coluna |\n");
    while (atual)
    {
        printf("     %c     |  %d   |   %d   |\n",atual->c,atual->linha,atual->coluna);
        atual=atual->prox;
    }
    while (efeito)
    {
        printf("     %c     |  %d   |   %d   |\n",'#',efeito->linha,efeito->coluna);
        efeito=efeito->prox;
    }
}
#pragma endregion

#pragma region LerEscreverFicheiros

Casa* CriaMapaCasas(char* nome,Casa *mapa,EfeitoNefasto* hE){
    FILE* ficheiro = fopen(nome, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return NULL;
    }
    if(mapa!=NULL){
        mapa=LimpaMemoria(mapa);
    }
    int c=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            if(c!=vazio){
                mapa=CriaAdiciona(mapa,c,y,x,hE);
            }
        }
    }
    fclose(ficheiro);
    return mapa;
}
void criaMapaFicheiro(Casa *mapa){
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
Casa* LerListaFicheiro(Casa *mapa,EfeitoNefasto* cabeca){
    mapa=LimpaMemoria(mapa);
    FILE* ficheiro= fopen("ListaCasas.bin","rb");
    CasaF aux;
    while (fread(&aux,sizeof(aux),1,ficheiro)==1)
    {
        mapa= CriaAdiciona(mapa,aux.c,aux.linha,aux.coluna,cabeca);
    }
    fclose(ficheiro);
    return mapa;
}
Casa* EscreverListaFicheiro(Casa *mapa){
    FILE* ficheiro= fopen("ListaCasas.bin","wb");
    Casa* atual= mapa;
    CasaF aux;
    while (atual)
    {
        aux.c=atual->c;
        aux.coluna =atual->coluna;
        aux.linha = atual->linha;
        fwrite(&aux,sizeof(aux),1,ficheiro);
    }
    fclose(ficheiro);
    return mapa;
}
#pragma endregion

#pragma region CálculoPosições
int Posicao(Casa* c){
    int posicao=0, linha= c->linha, coluna= c->coluna;
    posicao=((linha-1)*x)+coluna-1;
    return posicao;
}
int PosicaoEfeitoNefasto(EfeitoNefasto* c){
    int posicao=0, linha= c->linha, coluna= c->coluna;
    posicao=((linha-1)*x)+coluna-1;
    return posicao;
}
#pragma endregion 
#pragma region LimpaMemória
Casa* LimpaMemoria(Casa* mapa){
    Casa *atual = mapa;
    Casa *proximo=NULL;
    while (atual)
    {
        proximo=atual->prox;
        free(atual);
        atual = proximo;
    }
    mapa=NULL;
    return mapa;
}
EfeitoNefasto* LimpaMemoriaEfeito(EfeitoNefasto* efeito){
    EfeitoNefasto *atual = efeito;
    EfeitoNefasto *proximo=NULL;
    while (atual)
    {
        proximo=atual->prox;
        free(atual);
        atual = proximo;
    }
    efeito=NULL;
    return efeito;
}
#pragma endregion
