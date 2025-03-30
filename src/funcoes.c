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
Casa *CriaCasa(char c,int linha,int coluna){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL; //validação localização
    if(c=='.'|| c=='#')return NULL; //validação frequência
    Casa* aux = (Casa*)malloc(sizeof(Casa)); //alocação de memória
    if(aux!=NULL){//se alocou insere valores
        aux->c=c;
        aux->linha=linha;
        aux->coluna=coluna;
        aux->prox=NULL;
    }
    return aux;//retorna o apontador para a memório preenchida/NULL
}
EfeitoNefasto *CriaEfeitoNefasto(int linha,int coluna,Casa* x1, Casa* x2){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return NULL;//validação localização
    if(!x1 || !x2)return NULL;//validação das antenas que causaram este efeito
    EfeitoNefasto* aux = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));//alocação de memória
    if(aux!=NULL){//se alocou insere valores
        aux->linha= linha;
        aux->coluna= coluna;
        aux->antenas[0]= x1;
        aux->antenas[1]= x2;
        aux->prox=NULL;
    }
    return aux;//retorna o apontador para a memório preenchida/NULL
}
#pragma endregion
#pragma region LimpaMemória
Casa* LimpaMemoria(Casa* mapa){
    Casa *atual = mapa;//atual começa a apontar para a cabeça
    Casa *proximo=NULL;//define proximo
    while (atual)//enquanto diferente de NULL
    {
        proximo=atual->prox;//proximo vai ser o proximo ao atual (age como auxiliar)
        free(atual);//libertamos o atual
        atual = proximo;//atual vira o proximo da lista
    }
    mapa=NULL;
    return mapa;//mapa retorna sempre NULL
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

#pragma region CálculoPosições
int Posicao(Casa* c){
    int posicao=0;//coloca posicao 0 por default (não se encontra no mapa)
    if(c){//se casa existe
        int linha= c->linha, coluna= c->coluna;// define linha e coluna conforme casa
        posicao=((linha-1)*x)+coluna-1;//calcula a posicao
    }
    return posicao;//retorna a posicao 0 ou a calculada
}
int PosicaoEfeitoNefasto(EfeitoNefasto* c){
    int posicao=0;//coloca posicao 0 por default (não se encontra no mapa)
    if(c){//se casa existe
        int linha= c->linha, coluna= c->coluna;// define linha e coluna conforme casa
        posicao=((linha-1)*x)+coluna-1;//calcula a posicao
    }
    return posicao;//retorna a posicao 0 ou a calculada
}
#pragma endregion

#pragma region Adicionar

Casa* AdicionaCasa(Casa *mapa,Casa* n,EfeitoNefasto** cabeca){
    if(!n) return mapa;//se Casa passada é nulo retorna mapa normal
    if(!mapa){//se mapa é nulo, cria mapa
        mapa=n;
        return mapa;
    }
    Casa *atual=mapa;
    while (atual)
    {
        if(Posicao(n)==Posicao(atual)){//se a posição da inserção é igual a uma antena já no mapa
            printf("Erro, já existe antena na posição (%d,%d)\n",n->linha,n->coluna);
            free(n);
            return mapa;
        }
        if(Posicao(n)<Posicao(atual)){
            //adicionar inicio
            n->prox=atual;
            mapa=n;          
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa);
            return mapa;
        }else if(atual->prox && Posicao(n)<Posicao(atual->prox)){
            //adicionar ao meio
            n->prox=atual->prox;
            atual->prox=n;
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa);
            return mapa;
        }
        if(atual->prox==NULL){
            //adicionar ao fim
            atual->prox=n;
            *cabeca=CriaListaEfeitoEfeitoNefasto(*cabeca,mapa);
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
            //adiciona a seguir de outro efeito nefasto com a mesma posição
            n->prox =atual->prox;
            atual->prox = n;
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

#pragma endregion

#pragma region CriaAdiciona
Casa *CriaAdiciona(Casa *mapa,char c, int linha, int coluna,EfeitoNefasto** cabeca){
    return AdicionaCasa(mapa,CriaCasa(c,linha,coluna),cabeca);//cria a antena e adiciona automaticamente
}
EfeitoNefasto *CriaAdicionaEfeito(EfeitoNefasto *cabeca, int linha, int coluna, Casa* x1,Casa* x2){
    return AdicionaCasaEfeitoNefasto(cabeca,CriaEfeitoNefasto(linha,coluna,x1,x2));//cria o efeito nefasto e adiciona automaticamente
}

#pragma endregion

#pragma region Remove

Casa *RemoverCasa(Casa *mapa, int linha, int coluna,EfeitoNefasto**  cabeca){
    if(coluna<1 || coluna>x || linha<1 || linha>y)return mapa;//verificação da localização no mapa
    Casa *atual=mapa;
    if(atual && atual->coluna==coluna && atual->linha==linha){//verifica se a primeira Casa é a antena a remover
        *cabeca = RemoverNefasto(*cabeca, linha, coluna); //remove efeitos nefastos que são criados pela antena que está a ser removido
        mapa = atual->prox;
        free(atual);//limpa a memória 
        return mapa;
    }
    while (atual)
    {
        if(atual->prox && atual->prox->coluna==coluna && atual->prox->linha==linha){//verifica se encontrou a antena para remover
            *cabeca = RemoverNefasto(*cabeca, linha, coluna);//remove efeitos nefastos que são criados pela antena que está a ser removido
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
EfeitoNefasto *RemoverNefasto(EfeitoNefasto* cabeca, int linha, int coluna){
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
            cabeca=RemoverNefasto(cabeca,linha,coluna);
        } else if((!atual->prox) && (((atual->antenas[0]->coluna==coluna) && (atual->antenas[0]->linha==linha)) ||
        ((atual->antenas[1]->coluna==coluna) && (atual->antenas[1]->linha==linha)))){
            //é o ultimo efeito nefasto
            if(cabeca==atual){
                cabeca=NULL;
                free(atual);
                return cabeca;
            }
            free(atual);
            cabeca= RemoverNefasto(cabeca,linha,coluna);
        }
        atual=atual->prox;
    }
    return cabeca;
    
}

#pragma endregion

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
        printf("     %c     |  %d   |   %d   | Casa 1:%c(%d,%d)| Casa 2:%c(%d,%d) \n",'#',efeito->linha,efeito->coluna,efeito->antenas[0]->c,efeito->antenas[0]->linha,efeito->antenas[0]->coluna,efeito->antenas[1]->c,efeito->antenas[1]->linha,efeito->antenas[1]->coluna);

        efeito=efeito->prox;
    }
}
#pragma endregion

#pragma region LerEscreverFicheiros

Casa* CriaMapaCasas(char* nome,Casa *mapa,EfeitoNefasto** hE){
    FILE* ficheiro = fopen(nome, "r");
    if (ficheiro == NULL) {//verifica se abriu corretamente
        printf("Erro ao abrir o arquivo %s\n", nome);
        return NULL;
    }
    if(mapa!=NULL){
        mapa=LimpaMemoria(mapa);
    }//se mapa não for nulo limpa a lista
    int c=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
        } else {
            x++;
            if(c!=vazio){//Se o caractere não for uma casa vazia, guarda
                mapa=CriaAdiciona(mapa,c,y,x,hE);
            }
        }
    }//le todos os caracteres um a um
    fclose(ficheiro);
    return mapa;
}
void criaMapaFicheiro(Casa *mapa){
    FILE* ficheiro;
    Casa* atual=mapa;
    ficheiro = fopen("mapa.txt", "w");
    if (ficheiro == NULL) {//verifica se abriu corretamente
        printf("Erro ao abrir o ficheiro.\n");
        return;
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
}
Casa* LerListaFicheiro(Casa *mapa,EfeitoNefasto** cabeca){
    mapa=LimpaMemoria(mapa);
    FILE* ficheiro= fopen("ListaCasas.bin","rb");
    CasaF aux;
    if (ficheiro == NULL) {//verifica se abriu corretamente
        printf("Erro ao abrir o ficheiro.\n");
        return NULL ;
    }
    while (fread(&aux,sizeof(aux),1,ficheiro)==1)
    {
        mapa= CriaAdiciona(mapa,aux.c,aux.linha,aux.coluna,cabeca);
    }
    fclose(ficheiro);
    *cabeca = CriaListaEfeitoEfeitoNefasto(*cabeca, mapa);
    return mapa;
}
Casa* EscreverListaFicheiro(Casa *mapa){
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


int ExisteEfeitoEfeitoNefasto(EfeitoNefasto *cabeca, int linha, int coluna){
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
EfeitoNefasto* CriaListaEfeitoEfeitoNefasto(EfeitoNefasto* cabeca, Casa *mapa){
    cabeca=LimpaMemoriaEfeito(cabeca); //dá reset ao efeito nefasto
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
EfeitoNefasto* AntenaCausaNefasto(EfeitoNefasto *cabeca, Casa* c){
    EfeitoNefasto* atual= cabeca;
    while(atual){
        if((atual->antenas[0]->linha==c->linha && atual->antenas[0]->coluna==c->coluna) || (atual->antenas[1]->linha==c->linha && atual->antenas[1]->coluna==c->coluna)){
            //verifica se antena está guardada nas antenas dos efeitos nefastos
            return atual;
        }
        atual=atual->prox;
    }
    return NULL;
}
Casa* AdicionaCasaSemSobreposicao(Casa *mapa,Casa* n,EfeitoNefasto* cabeca){
    
    if(!n) return mapa;
    if(!mapa){//cria mapa
        mapa=n;
        return mapa;
    }
    if(ExisteEfeitoEfeitoNefasto(cabeca,n->linha,n->coluna)){//nao deixa adicionar caso exista efeito nefasto
        return mapa;
    }
    mapa=AdicionaCasa(mapa,n, &cabeca);
    return mapa;
}

Casa* AdicionaCasaSemCausarNefasto(Casa *mapa,Casa* n,EfeitoNefasto* cabeca){
    mapa=CriaAdiciona(mapa,n->c,n->linha,n->coluna,&cabeca);
    EfeitoNefasto* e = AntenaCausaNefasto(cabeca,n);
    if(e){
        printf("Erro, esta antena causa ruido em (%d,%d)",e->linha,e->coluna);
        mapa=RemoverCasa(mapa,n->linha,n->coluna,&cabeca);
    }
    return mapa;
}


