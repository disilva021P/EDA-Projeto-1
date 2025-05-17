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

#pragma region Criacao

Casa *CriaCasa(char c,int linha,int coluna, int* erro){
    if(coluna<1 || coluna>x || linha<1 || linha>y || c=='.'|| c=='#'){
        *erro=3;
        return NULL; //validação localização e frequencia
    }
    Casa* aux = (Casa*)malloc(sizeof(Casa)); //alocação de memória
    if(aux){//se alocou insere valores
        aux->c=c;
        aux->linha=linha;
        aux->coluna=coluna;
        aux->prox=NULL;
        *erro=1;
        return aux;//retorna o apontador para a memório preenchida/NULL
    }
    *erro = 150;
    return NULL;
}
EfeitoNefasto *CriaEfeitoNefasto(int linha,int coluna,Casa* x1, Casa* x2, int* erro){
    if(coluna<1 || coluna>x || linha<1 || linha>y && (x1 && x2)){
        *erro= 3;
        return NULL;//validação localização e das antenas que causaram este efeito
    }
    EfeitoNefasto* aux = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));//alocação de memória
    if(aux){//se alocou insere valores
        aux->linha= linha;
        aux->coluna= coluna;
        aux->antenas[0]= x1;
        aux->antenas[1]= x2;
        aux->prox=NULL;
        *erro=1;
        return aux;//retorna o apontador para a memório preenchida/NULL
    }
    *erro=150;
    return NULL;
}
#pragma endregion
#pragma region LimpaMemória
Casa* LimpaMemoria(Casa* mapa, int *erro){
    *erro=2;
    Casa *atual = mapa;//atual começa a apontar para a cabeça
    Casa *proximo=NULL;//define proximo
    while (atual)//enquanto diferente de NULL
    {
        proximo=atual->prox;//proximo vai ser o proximo ao atual (age como auxiliar)
        free(atual);//libertamos o atual
        atual = proximo;//atual vira o proximo da lista
    }
    mapa=NULL;
    *erro=1;
    return mapa;//mapa retorna sempre NULL
}
EfeitoNefasto* LimpaMemoriaEfeito(EfeitoNefasto* efeito, int* erro){
    *erro=2;
    EfeitoNefasto *atual = efeito;
    EfeitoNefasto *proximo=NULL;
    while (atual)
    {
        proximo=atual->prox;
        free(atual);
        atual = proximo;
    }
    efeito=NULL;
    *erro=1;
    return efeito;
}
#pragma endregion

#pragma region CálculoPosições
int Posicao(Casa* c,int* erro){
    int posicao=0;//coloca posicao 0 por default (não se encontra no mapa)
    if(c){//se casa existe
        int linha= c->linha, coluna= c->coluna;// define linha e coluna conforme casa
        posicao=((linha-1)*x)+coluna-1;//calcula a posicao
        *erro=1;
    }else{
        *erro=4;
    }
    return posicao;//retorna a posicao 0 ou a calculada
}
int PosicaoEfeitoNefasto(EfeitoNefasto* c,int* erro){
    int posicao=0;//coloca posicao 0 por default (não se encontra no mapa)
    if(c){//se casa existe
        int linha= c->linha, coluna= c->coluna;// define linha e coluna conforme casa
        posicao=((linha-1)*x)+coluna-1;//calcula a posicao
        *erro=1;
    }else{
        *erro=4;
    }
    return posicao;//retorna a posicao 0 ou a calculada
}
#pragma endregion

#pragma region Adicionar

Casa* AdicionaCasa(Casa *mapa,Casa* n,EfeitoNefasto** cabeca,int* erro){
    if(!n){
        *erro= 4;
        return mapa;//se Casa passada é nulo retorna mapa normal
    } 
    if(!mapa){//se mapa é nulo, cria mapa
        mapa=n;
        return mapa;
    }
    Casa *atual=mapa;
    while (atual)
    {
        if(Posicao(n,erro)==Posicao(atual,erro)){//se a posição da inserção é igual a uma antena já no mapa
            *erro=10;
            free(n);
            return mapa;
        }
        if(Posicao(n,erro)<Posicao(atual,erro)){
            //adicionar inicio
            n->prox=atual;
            mapa=n;          
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa,erro);
            return mapa;
        }else if(atual->prox && Posicao(n,erro)<Posicao(atual->prox,erro)){
            //adicionar ao meio
            n->prox=atual->prox;
            atual->prox=n;
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa,erro);
            return mapa;
        }
        if(atual->prox==NULL){
            //adicionar ao fim
            atual->prox=n;
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa,erro);
            return mapa;
        }
        atual=atual->prox;
    }
    return mapa;
}

EfeitoNefasto* AdicionaCasaEfeitoNefasto(EfeitoNefasto* cabeca,EfeitoNefasto* n,int*erro){
    if(!n){
        *erro=4;
        return cabeca;
    } 
    if(!cabeca){//cria mapa
        cabeca=n;
        return cabeca;
    }
    EfeitoNefasto *atual=cabeca;
    while (atual)
    {
        if(PosicaoEfeitoNefasto(n,erro)==PosicaoEfeitoNefasto(atual,erro)){
            //adiciona a seguir de outro efeito nefasto com a mesma posição
            n->prox =atual->prox;
            atual->prox = n;
            return cabeca;
        }
        if(PosicaoEfeitoNefasto(n,erro)<PosicaoEfeitoNefasto(atual,erro)){
            //adicionar inicio
            n->prox=atual;
            cabeca=n;          
            return cabeca;
        }else if(atual->prox && PosicaoEfeitoNefasto(n,erro)<PosicaoEfeitoNefasto(atual->prox,erro)){
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

#pragma endregion

#pragma region CriaAdiciona
Casa *CriaAdiciona(Casa *mapa,char c, int linha, int coluna,EfeitoNefasto** cabeca,int*erro){
    return AdicionaCasa(mapa,CriaCasa(c,linha,coluna,erro),cabeca,erro);//cria a antena e adiciona automaticamente
}
EfeitoNefasto *CriaAdicionaEfeito(EfeitoNefasto *cabeca, int linha, int coluna, Casa* x1,Casa* x2, int* erro){
    return AdicionaCasaEfeitoNefasto(cabeca,CriaEfeitoNefasto(linha,coluna,x1,x2,erro),erro);//cria o efeito nefasto e adiciona automaticamente
}

#pragma endregion

#pragma region Remove

Casa *RemoverCasa(Casa *mapa, int linha, int coluna,EfeitoNefasto**  cabeca,int* erro){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return mapa;//verificação da localização no mapa
    Casa *atual=mapa;
    if(atual && atual->coluna==coluna && atual->linha==linha){//verifica se a primeira Casa é a antena a remover
        *cabeca = RemoverNefasto(*cabeca, linha, coluna,erro); //remove efeitos nefastos que são criados pela antena que está a ser removido
        mapa = atual->prox;
        free(atual);//limpa a memória 
        return mapa;
    }
    while (atual)
    {
        if(atual->prox && atual->prox->coluna==coluna && atual->prox->linha==linha){//verifica se encontrou a antena para remover
            *cabeca = RemoverNefasto(*cabeca, linha, coluna,erro);//remove efeitos nefastos que são criados pela antena que está a ser removido
            Casa *temp = atual->prox;
            atual->prox = temp->prox;
            free(temp); //limpa memoria
            return mapa;
        }

        atual=atual->prox;
    }
    printf("Antena não localizada\n");
    return mapa;
    
}
EfeitoNefasto *RemoverNefasto(EfeitoNefasto* cabeca, int linha, int coluna,int* erro){
    EfeitoNefasto *atual=cabeca;
    if((atual) && (((atual->antenas[0]->coluna==coluna) && (atual->antenas[0]->linha==linha)) ||
     ((atual->antenas[1]->coluna==coluna) && (atual->antenas[1]->linha==linha)))){
        //verifica se as antenas que o causaram estão na linha e coluna da casa que se vai remover
        EfeitoNefasto *temp = atual;
        atual = atual->prox;
        free(temp);
        cabeca = atual;
    }
    while (atual)
    {
        if((atual->prox) && (((atual->prox->antenas[0]->coluna==coluna) && (atual->prox->antenas[0]->linha==linha)) || ((atual->prox->antenas[1]->linha==linha) && (atual->prox->antenas[1]->coluna==coluna)))){
            //verifica se existe proximo e se existir verificar se as antenas que o causaram estão na linha e coluna da casa que se vai remover
            EfeitoNefasto *temp = atual->prox;
            atual->prox = temp->prox;
            free(temp);
            cabeca=RemoverNefasto(cabeca,linha,coluna,erro);
        } else if((!atual->prox) && (((atual->antenas[0]->coluna==coluna) && (atual->antenas[0]->linha==linha)) ||
        ((atual->antenas[1]->coluna==coluna) && (atual->antenas[1]->linha==linha)))){
            //é o ultimo efeito nefasto
            if(cabeca==atual){
                cabeca=NULL;
                free(atual);
                return cabeca;
            }
            free(atual);
            cabeca= RemoverNefasto(cabeca,linha,coluna,erro);
        }
        atual=atual->prox;
    }
    return cabeca;
    
}

#pragma endregion

#pragma region Prints
int MostraListaNovo(Casa *mapa,EfeitoNefasto* cabeca,int* erro){
    Casa* atual=mapa;
    *erro=-1;
    for(int i=1;i<=y;i++){
        for (int j = 1; j <= x; j++)
        {
            if(atual && atual->linha==i && atual->coluna==j){
                if(ExisteEfeitoEfeitoNefasto(cabeca,i,j,erro)){
                    printf("\033[0;33m%c\033[0m",atual->c);
                }else{
                    printf("%c",atual->c);
                }
                atual=atual->prox;
            }else{
                if(ExisteEfeitoEfeitoNefasto(cabeca,i,j,erro)){
                    
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
        return 1;
        
    }
}
int MostraListaCasas(Casa *mapa,EfeitoNefasto* cabeca){
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
        printf("     %c     |  %d   |   %d   | Casa 1:%c(%d,%d)| Casa 2:%c(%d,%d) \n",'#',efeito->linha,efeito->coluna,efeito->antenas[0]->c,efeito->antenas[0]->linha,efeito->antenas[0]->coluna,efeito->antenas[1]->c,efeito->antenas[1]->linha,efeito->antenas[1]->coluna);

        efeito=efeito->prox;
    }
}
#pragma endregion

#pragma region LerEscreverFicheiros

Casa* CriaMapaCasas(char* nome,Casa *mapa,EfeitoNefasto** hE,int* erro){
    FILE* ficheiro = fopen(nome, "r");
    if (ficheiro == NULL) {//verifica se abriu corretamente
        *erro = 102;
        return NULL;
    }
    if(mapa!=NULL){
        mapa=LimpaMemoria(mapa,erro);
    }//se mapa não for nulo limpa a lista
    int c=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            if(c!=vazio){//Se o caractere não for uma casa vazia, guarda
                mapa=CriaAdiciona(mapa,c,y,x,hE,erro);
            }
        }
    }//le todos os caracteres um a um
    fclose(ficheiro);
    *erro=1;
    return mapa;
}
int criaMapaFicheiro(Casa *mapa){
    FILE* ficheiro;
    if(!mapa){
        return 7;
    }
    Casa* atual=mapa;
    ficheiro = fopen("mapa.txt", "w");
    if (ficheiro == NULL) {//verifica se abriu corretamente
        return 102;
    }
    for(int i=1;i<=y;i++){
        for (int j = 1; j <= x; j++)
        {
            if(atual && atual->linha==i && atual->coluna==j){//se tiver frequencia
                fprintf(ficheiro,"%c",atual->c);
                atual=atual->prox;
            }else{
                fprintf(ficheiro, "%c",vazio);//se nao tiver nada
            }
            if(j==x && i!=y){//se chegar a ultima coluna
                fprintf(ficheiro,"\n");
            }
            
        }
        
    }
    
    fclose(ficheiro);
    return 1;
}
Casa* LerListaFicheiro(Casa *mapa,EfeitoNefasto** cabeca,int* erro){
    mapa=LimpaMemoria(mapa,erro);
    FILE* ficheiro= fopen("ListaCasas.bin","rb");
    CasaF aux;
    if (ficheiro == NULL) {//verifica se abriu corretamente
        printf("Erro ao abrir o ficheiro.\n");
        return NULL ;
    }
    while (fread(&aux,sizeof(aux),1,ficheiro)==1)
    {
        mapa= CriaAdiciona(mapa,aux.c,aux.linha,aux.coluna,cabeca,erro);
    }
    fclose(ficheiro);
    *cabeca = CriaListaEfeitoEfeitoNefasto(*cabeca, mapa,erro);
    return mapa;
}
Casa* EscreverListaFicheiro(Casa *mapa,int* erro){
    FILE* ficheiro= fopen("ListaCasas.bin","wb");
    Casa* atual= mapa;
    CasaF aux;
    if (ficheiro == NULL) {//verifica se abriu corretamente
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }
    while (atual)
    {
        aux.c=atual->c;
        aux.coluna =atual->coluna;
        aux.linha = atual->linha;
        fwrite(&aux,sizeof(aux),1,ficheiro);
        atual=atual->prox;
    }
    fclose(ficheiro);
    return mapa;
}
#pragma endregion


int ExisteEfeitoEfeitoNefasto(EfeitoNefasto *cabeca, int linha, int coluna,int* erro){
    *erro=1;
    if(!cabeca){
        *erro=8;
    }
    EfeitoNefasto* atual= cabeca;
    while(atual){
        if(atual->linha==linha && atual->coluna == coluna){
            //verifica se existe efeito nefasto na linha e coluna indicada
            return 1;
        }
        atual=atual->prox;
    }
    return 0;
}
EfeitoNefasto* CriaListaEfeitoEfeitoNefasto(EfeitoNefasto* cabeca, Casa *mapa,int* erro){
    cabeca=LimpaMemoriaEfeito(cabeca,erro); //dá reset ao efeito nefasto
    if(*erro==1){
        return cabeca;
    }
    Casa* atual= mapa,*prox = mapa->prox;
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
                        cabeca=CriaAdicionaEfeito(cabeca,prox->linha+difL,prox->coluna+difC,atual,prox,erro);
                    }
                    if(atual->coluna-difC>0 && atual->linha-difL>0){//efeito nefasto para trás
                        cabeca=CriaAdicionaEfeito(cabeca,atual->linha-difL,atual->coluna-difC,atual,prox,erro);
                    }
                }else{
                    if(prox->coluna-difC>0 && prox->linha+difL<=y){//efeito nefasto para frente
                        cabeca=CriaAdicionaEfeito(cabeca,prox->linha+difL,prox->coluna-difC,atual,prox,erro);
                    }
                    if(atual->coluna+difC<=x && atual->linha-difL>0){//efeito nefasto para trás
                        cabeca=CriaAdicionaEfeito(cabeca,atual->linha-difL,atual->coluna+difC,atual,prox,erro);
                    }
                }
                
            }
            prox=prox->prox;
        }
        atual=atual->prox;
    }
    return cabeca;
}
EfeitoNefasto* AntenaCausaNefasto(EfeitoNefasto *cabeca, Casa* c,int* erro){
    if(!c){
        *erro=4;
        return NULL;
    }
    if(!cabeca){
        *erro=8;
        return NULL;
    }
    EfeitoNefasto* atual= cabeca;
    while(atual){
        if((atual->antenas[0]->linha==c->linha && atual->antenas[0]->coluna==c->coluna) || (atual->antenas[1]->linha==c->linha && atual->antenas[1]->coluna==c->coluna)){
            //verifica se antena está guardada nas antenas dos efeitos nefastos
            return atual;
        }
        atual=atual->prox;
    }
    *erro=1;
    return NULL;
}
Casa* AdicionaCasaSemSobreposicao(Casa *mapa,Casa* n,EfeitoNefasto* cabeca,int* erro){
    *erro=1;
    if(!n){
        *erro=4;
        return mapa;
    } 
    if(!mapa){//cria mapa
        mapa=n;
        return mapa;
    }
    if(ExisteEfeitoEfeitoNefasto(cabeca,n->linha,n->coluna,erro)){//nao deixa adicionar caso exista efeito nefasto
        if(erro==1){
            *erro=6;
        }
        return mapa;
    }
    mapa=AdicionaCasa(mapa,n, &cabeca,erro);
    return mapa;
}

Casa* AdicionaCasaSemCausarNefasto(Casa *mapa,Casa* n,EfeitoNefasto* cabeca,int* erro){
    *erro=1;
    mapa=CriaAdiciona(mapa,n->c,n->linha,n->coluna,&cabeca,erro);
    if(*erro!=1){
        return mapa;
    }
    EfeitoNefasto* e = AntenaCausaNefasto(cabeca,n,erro);
    if(e){
        *erro=5;
        mapa=RemoverCasa(mapa,n->linha,n->coluna,&cabeca,erro);
    }
    return mapa;
}


