/**
 * @file grafos.c
 * @author Diogo Silva (a31504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include"dados.h"
#include"grafos.h"
#include<stdio.h>
#include<stdlib.h>
#define vazio '.'
int xMapa=0,yMapa=1;
/**
 * @brief Função que serve inicializar um grafo
 * 
 * @param *erro 
 * @return Ponteiro para grafo para ser utilizado
 */
Grafo* InicializaGrafo(int* erro){
    Grafo* resultado= (Grafo*)malloc(sizeof(Grafo));
    if(!resultado){
        *erro=150;
        return NULL;
    }
    resultado->h=NULL;
    *erro=1;
    return resultado;
    
}

/**
 * @brief Função que cria espaço para vertice
 * 
 * @param antena 
 * @param *erro 
 * @return Vertice
 */
Vertice* CriarVertice(CasaF* antena,int* erro){
    if(!antena){
        *erro=3;
        return NULL;
    }
    Vertice* v= (Vertice*)malloc(sizeof(Vertice));
    if(!v){
        *erro=150;
        return NULL;
    }
    v->adjacencias=NULL;
    v->antena=antena;
    v->prox=NULL;
    v->visitado=0;
    *erro=1;
    
    return v;
}

/**
 * 
 * @brief Função que cria Antena
 * 
 * @param c -> Frequência
 * @param linha 
 * @param coluna 
 * @param *erro 
 * @return Antena
 */
CasaF* CriarAntena(char c,int linha, int coluna,int* erro){
    if(coluna<1 || coluna>xMapa || linha<1 || linha>yMapa || c=='.'|| c=='#'){
        *erro=3;
        return NULL; //validação localização e frequencia
    }
    CasaF* antena= (CasaF*)malloc(sizeof(CasaF));
    if(!antena){
        *erro=150;
        return NULL;
    }
    antena->c=c;
    antena->coluna=coluna;
    antena->linha=linha;
    *erro=1;
    return antena;
}

/**
 * @brief Função que cria a adjacência
 * 
 * @param v1 -> Vértice 1
 * @param v2  -> Vértice 2
 * @param *erro 
 * @return Adjacência
 */
Adj* CriarAdj(Vertice* v1, Vertice* v2,int*erro){
    if(!v1||!v2){
        *erro=3;
        return NULL;
    }
    Adj* adjacencia= (Adj*)malloc(sizeof(Adj));
    if(!adjacencia){
        *erro=150;
        return NULL;
    }
    adjacencia->v1=v1;
    adjacencia->v2=v2;
    //adjacencia->peso=abs((v1->antena->linha-v2->antena->linha))-1+abs((v1->antena->coluna-v2->antena->coluna))-1;
    adjacencia->prox=NULL;
    *erro=1;
    return adjacencia;
}

/**
 * @brief Verifica se um vertice já existe na posição de um novo vertice
 * 
 * @param novo -> Vertice recente
 * @param cabeca -> Grafo com os vértices existentes
 * @param *erro 
 * @return Vértice se encontrar e NULL se não encontrar
 */
Vertice* ProcuraVertice(Vertice *novo, Grafo* cabeca,int*erro){
    if(!novo || !cabeca ){
        *erro=3;
        return 0;
    }
    Vertice* aux=cabeca->h;
    *erro=1;
    while(aux)
    {
        if((aux->antena->coluna == novo->antena->coluna) && (aux->antena->linha == novo->antena->linha)){
            *erro=9;
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

/**
 * @brief Verifica se um vertice já existe na posição de um novo vertice
 * 
 * @param novo -> Antena a verificar
 * @param cabeca -> Grafo com os vértices existentes
 * @param *erro 
 * @return Vértice se encontrar e NULL se não encontrar
 */
Vertice* ProcuraVerticeAntena(CasaF *novo, Grafo* cabeca,int*erro){
    if(!novo || !cabeca ){
        *erro=3;
        return 0;
    }
    Vertice* aux=cabeca->h;
    *erro=1;
    while(aux)
    {
        if((aux->antena->coluna == novo->coluna) && (aux->antena->linha == novo->linha)){
            *erro=9;
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

/**
 * @brief Devolve a posição de um vertice no mapa
 * 
 * @param v -> Vértice 
 * @return Posição do vértice
 */
int PosicaoVertice(Vertice* v){

    int posicao=0;//coloca posicao 0 por default (não se encontra no mapa)
    if(v){//se casa existe
        int linha= v->antena->linha, coluna= v->antena->coluna;// define linha e coluna conforme casa
        posicao=((linha-1)*xMapa)+coluna-1;//calcula a posicao
    }
    return posicao;//retorna a posicao 0 ou a calculada
}

/**
 * @brief Função que insere um vértice num grafo
 * 
 * @param novo -> Vértice a inserir
 * @param cabeca -> Grafo
 * @param *erro 
 * @return Grafo com vértice inserido 
 */

Grafo* InsereVertice(Vertice *novo, Grafo* cabeca,int*erro){

    if(!novo || !cabeca){
        *erro=3;
        return NULL;
    }
    Vertice * res =ProcuraVertice(novo,cabeca,erro);
    if(*erro!=1){
        return cabeca;
    }
    if(res){
        return cabeca;
    }
    Vertice* aux=cabeca->h;
    if(!aux){
        *erro=1;
        cabeca->h=novo;
        return cabeca;
    }

    *erro=1;
    while(aux)
    {          
        if(PosicaoVertice(novo)<PosicaoVertice(aux)){
            //adicionar inicio
            novo->prox=aux;
            cabeca->h=novo;
            return cabeca;
        }else if(aux->prox && PosicaoVertice(novo)<PosicaoVertice(aux->prox)){
            //adicionar ao meio
            novo->prox=aux->prox;
            aux->prox=novo;
            return cabeca;
        }
        if(aux->prox==NULL){
            //adicionar ao fim
            aux->prox=novo;
            return cabeca;
        }
        aux=aux->prox;
    }
    *erro=2;
    return cabeca;
    

}

/**
 * @brief Função que le o mapa em formato TXT
 * 
 * @param nome -> Nome do ficheiro
 * @param cabeca -> Grafo
 * @param *erro 
 * @return Grafo* 
 */
Grafo* leTxtGrafos(char* nome,Grafo*cabeca,int* erro){
    FILE* ficheiro = fopen(nome, "r");

    if (ficheiro == NULL) {//verifica se abriu corretamente
        *erro = 102;
        return NULL;
    }
    if(!cabeca){
        *erro=3;
        return cabeca;
    }
    if(cabeca->h){
        limpaConteudoGrafo(cabeca,erro);
    }//se mapa não for nulo limpa a lista
    int c=0;
    Vertice* auxVertice;
    CasaF* auxAntena;
    int i=0;
    while ((c = fgetc(ficheiro)) != EOF) {
        if (feof(ficheiro)) break;
        if (c == '\n') {
            yMapa++;
            xMapa=0;
            
        } else {
            xMapa++;
            if(c!=vazio && c != '\n' && c!='\r'){//Se o caractere não for uma casa vazia, guarda
                auxAntena= CriarAntena(c,yMapa,xMapa,erro);
                if(*erro!=1 || !auxAntena){
                    return cabeca;
                }
                auxVertice= CriarVertice(auxAntena,erro);
                if(*erro!=1 || !auxVertice){
                    free(auxAntena);
                    return cabeca;
                }
                cabeca= InsereVertice(auxVertice,cabeca,erro);
                if(*erro!=1){
                    free(auxAntena);
                    free(auxVertice);
                    return cabeca;
                }
            }
            
        }
        
    }
    fclose(ficheiro);
    if(*erro!=1){
        return cabeca;
    }
    return cabeca;
}

/**
 * @brief Função que insere adjacencias automaticamente dando um grafo
 * 
 * @param cabeca -> Grafo
 * @param *erro 
 * @return Grafo* 
 */
Grafo* insereAdjacencias(Grafo* cabeca,int* erro){
    int er = limpaAdj(cabeca);

    if(er!=1){
        *erro=er;
        return cabeca;
    }
    Vertice* aux,*aux1;
    Adj* auxAdj;
    aux=cabeca->h;
    while (aux)
    {
        aux1=cabeca->h;
        while (aux1)
        {
            if((aux == aux1) || 
            (aux->antena->linha == aux1->antena->linha && 
             aux->antena->coluna == aux1->antena->coluna)){
                aux1=aux1->prox;
                continue;
            }
            if(estaNoRadar(aux->antena->coluna,aux1->antena->coluna,aux->antena->linha,aux1->antena->linha) && aux1->antena->c==aux->antena->c){
                auxAdj= CriarAdj(aux,aux1,erro);
                if(*erro!=1){
                    return cabeca;
                }
                aux=insereAdjacenciaVertice(aux,auxAdj,erro);
                if(*erro!=1){
                    return cabeca;
                }
            }
            aux1=aux1->prox;
            
        }        
        aux=aux->prox;
    }
    return cabeca;
}

/**
 * @brief Funcção que verifica se uma coordenada esta no radar de outras coordenadas
 * 
 * @param colunaOrigem -> coluna da origem do radar
 * @param colunaChegada -> coluna da chegada do radar
 * @param linhaOrigem -> linha da origem do radar
 * @param linhaChegada -> linha da chegada do radar
 * @return retorna se as coordenadas recebidas estão ou não do radar 
 */
int estaNoRadar(int colunaOrigem, int colunaChegada,int linhaOrigem, int linhaChegada){
    int difcoluna, diflinha;
    difcoluna= abs(colunaOrigem-colunaChegada);
    diflinha= abs(linhaOrigem-linhaChegada);
    if(diflinha<=2 && difcoluna<=2){
        return 1;
    }
    return 0;
}

/**
 * @brief Insere Adjacencia num vértice fornecido
 * 
 * @param h -> Vértice recebido
 * @param adj -> Adjacência para adicionar
 * @param *erro 
 * @return Vertice adicionado 
 */
Vertice* insereAdjacenciaVertice(Vertice*h,Adj* adj,int*erro){
    Adj* aux;
    if(!h || !adj){
        *erro=3;
        return NULL;
    }
    aux=h->adjacencias;
    *erro=1;
    if(!aux){
        h->adjacencias=adj;
        return h;
    }
    while(aux)
    {
        if(!aux->prox){
            aux->prox=adj;
            return h;
        }
        aux=aux->prox;
    }
    return h;
}

/**
 * @brief Limpa adjacências de um grafo
 * 
 * @param cabeca -> grafo
 * @return (int)Erro
 */
int limpaAdj(Grafo* cabeca){
    if(!cabeca) return 3;
    Vertice* aux=cabeca->h;
    Adj *auxAdj,*auxlimpaAdj;
    while (aux)
    {
        auxAdj=aux->adjacencias;
        while (auxAdj)
        {
            auxlimpaAdj=auxAdj->prox;
            free(auxAdj);
            auxAdj=auxlimpaAdj;
        }
        aux->adjacencias = NULL;
        aux=aux->prox;
    }
    return 1;
    
}

/**
 * @brief Limpa os vértives de um grafo
 * 
 * @param cabeca -> grafo
 * @param *erro
 * @return Grafo*  
 */
Grafo* limpaV(Grafo* cabeca,int*erro){
    if(!cabeca){
        *erro=3;
        return cabeca;
    } 
    Vertice* aux=cabeca->h,*limpa=NULL;
    while (aux)
    {
        limpa=aux->prox;
        free(aux);
        aux=limpa;
        cabeca->h=NULL;
    }
    return NULL;
    
}

/**
 * @brief Limpa o conteúdo no grafo 
 * 
 * @param cabeca -> grafo
 * @param *erro 
 * @return (int)Sucesso 
 */
int limpaConteudoGrafo(Grafo* cabeca,int*erro){
    int res=limpaAdj(cabeca);
    if(res!=1){
        *erro=res; return 0;
    }
    limpaV(cabeca,erro);
    return 1;
}

/**
 * @brief Limpa o conteúdo e o espaço do grafo 
 * 
 * @param cabeca ->grafo
 * @param *erro 
 * @return (int)Sucesso 
 */
int limpaGrafo(Grafo* cabeca,int*erro){
    int res=limpaAdj(cabeca);
    if(res!=1){
        *erro=res;
        return 0;
    }
    limpaV(cabeca,erro);
    if(*erro==1){
        cabeca->h=NULL;
        free(cabeca);
        cabeca=NULL;
        return 1;
    }
    return 0;
}

/**
 * @brief Função de recursividade do algoritmo DFS
 * 
 * @param v -> Vértice que vai ser visitado (para ver as adjacências)
 * @param caminho -> Caminho que percorreu 
 * @param *erro
 * @return Grafo* Caminho que percorreu 
 */
Grafo* DFSUtil(Vertice* v, Grafo* caminho, int* erro) {

    if (!v || v->visitado) return caminho;

    // Marcar como visitado no grafo original
    v->visitado = 1;

    // Adicionar o vértice ao grafo de caminho (sem duplicatas)
    if (ProcuraVertice(v, caminho, erro) == NULL) { // Verifica se o vértice já não está no caminho
        Vertice* aux = CriarVertice(v->antena,erro);
        caminho = InsereVertice(aux, caminho, erro);
        if (*erro != 1) return caminho;
    }

    // Explorar apenas vértices adjacentes
    Adj* adj = v->adjacencias;
    while (adj) {
        Vertice* vizinho = adj->v2;
        if (!vizinho->visitado) {
            caminho = DFSUtil(vizinho, caminho, erro);
        }
        adj = adj->prox;
    }

    return caminho;
}

/**
 * @brief Função principal DFS
 * 
 * @param original -> grafo que vai ser percorrido
 * @param linha -> linha vertice de começo
 * @param coluna -> coluna vertice de começo
 * @param *erro 
 * @return Caminho percorrido 
 */
Grafo* DFS_CaminhoGrafo(Grafo* original, int linha, int coluna, int* erro) {
    if (!original || !original->h) {
        *erro = 3; 
        return NULL;
    }

    // Colocar todos os "visitados" a 0 no grafo original
    Vertice* aux = original->h;
    while (aux) {
        aux->visitado = 0;
        aux = aux->prox;
    }

    // Encontrar o vértice de origem
    Vertice* origem = original->h;

    while (origem) {
        if (origem->antena->linha == linha && origem->antena->coluna == coluna) break;
        origem = origem->prox;
    }

    if (origem!=NULL) {
        *erro = 4; // antena não encontrada
        return NULL;
    }

    // Criar um novo grafo para guardar o caminho
    Grafo* caminho = InicializaGrafo(erro);

    if (*erro != 1) return NULL;

    // Chamar DFSUtil para receber o caminho
    caminho = DFSUtil(origem, caminho, erro);

    return caminho;
}

/**
 * @brief Mostra o caminho do DFS
 * 
 * @param g -> grafo
 * @return Sucesso(int)
 */
int mostraVerticesCaminho(Grafo* g) {
    if (!g || !g->h) {
        return 3; 
    }

    Vertice* aux = g->h;
    while (aux) {
        if (!aux->antena) {
            return -1;
        }

        printf("Frequência: %c | Posição: (%d, %d)\n", 
               aux->antena->c, 
               aux->antena->linha, 
               aux->antena->coluna);
        aux = aux->prox;
    }

    return 1;  
}


/**
 * @brief Mostra o grafo com adjacencias
 * 
 * @param g -> grafo
 * @return Sucesso(int)
 */
int mostraVertices(Grafo* g) {
        if (!g || !g->h) {
            return 3; 
        }
    
        Vertice* aux = g->h;
        Adj* adja=NULL;
        while (aux) {
            if (!aux->antena) {
                return -1;
            }
    
            printf("Frequência: %c | Posição: (%d, %d)\n", 
                   aux->antena->c, 
                   aux->antena->linha, 
                   aux->antena->coluna);
            adja= aux->adjacencias;
            printf("Adjacjente: ");
            while (adja)
            {
                printf("(%d,%d) ",adja->v2->antena->linha,adja->v2->antena->coluna);
                adja=adja->prox;
            }
            printf("\n");
            
            aux = aux->prox;
        }
    
        return 1;  
    }
    
/**
 * @brief Escreve o grafo e as adjacencias num grafo num ficheiro binario
 * 
 * @param nomeFicheiro -> Nome do ficheiro
 * @param g -> grafo a ser escrito
 * @param *erro 
 * @return Grafo* 
 */
Grafo* escreveFicheiroBinario(char* nomeFicheiro,Grafo*g,int*erro){
    FILE* ficheiro = fopen (nomeFicheiro,"wb");
    if(ficheiro==NULL){
        *erro= 100;
        return g; 
    }
    int totalVertices=0; 
    Vertice* aux1 = g->h; 
    while(aux1){// percorrer a lista para ver nºvertices
        totalVertices++; 
        aux1 = aux1->prox; 
    }
    fwrite(&totalVertices, sizeof(int),1,ficheiro);  
    aux1 = g->h;
    for(int i=0; i<totalVertices; i++){                        // escreve os dados de todos os vertices do grafo 
        fwrite(aux1->antena, sizeof(CasaF),1 ,ficheiro);   // escreve freq do vertice
              // escreve numero de colunas do vertice
        aux1=aux1->prox;
    }        
       aux1 = g->h;

            while(aux1){
            int totalAdjacencias = 0; 
            Adj* aux2= aux1->adjacencias; 
                while(aux2){                                    // contar o numero de adjacencias
                totalAdjacencias++;                         
                aux2 = aux2->prox;
                }
                fwrite(&totalAdjacencias, sizeof(int),1 , ficheiro);  // escreve o numero de adjacencias de cada vertice 
                aux2 = aux1->adjacencias; 
                while(aux2){
                    CasaF* antenaAdj = aux2->v2->antena; 
                    fwrite(antenaAdj, sizeof(CasaF), 1, ficheiro);
                    aux2 = aux2->prox; 
                }                
                aux1=aux1->prox;
            }        
    fclose(ficheiro);
    *erro=1;
    return g;
}

/**
 * @brief le o grafo e as adjacencias de um ficheiro binario
 * 
 * @param nomeFicheiro -> Nome do ficheiro
 * @param g -> grafo lido
 * @param *erro 
 * @return Grafo* lido
 */
Grafo* leFicheiroBinario(char* nomeFicheiro, Grafo* g, int* erro) {
    limpaConteudoGrafo(g, erro);
    if (*erro != 1) return g;

    FILE* ficheiro = fopen(nomeFicheiro, "rb");
    if (!ficheiro) {
        *erro = 100;
        return NULL;
    }

    int totalVertices = 0;
    if (fread(&totalVertices, sizeof(int), 1, ficheiro) != 1) {
        *erro = 101;
        fclose(ficheiro);
        return NULL;
    }

    // Ler e criar vértices
    for (int i = 0; i < totalVertices; i++) {
        CasaF* antena = (CasaF*)malloc(sizeof(CasaF));
        if (!antena) {
            *erro = 150;
            fclose(ficheiro);
            return NULL;
        }
        if (fread(antena, sizeof(CasaF), 1, ficheiro) != 1) {
            *erro = 101;
            free(antena);
            fclose(ficheiro);
            return NULL;
        }

        Vertice* novoVertice = CriarVertice(antena, erro);
        if (*erro != 1) {
            free(antena);
            fclose(ficheiro);
            return NULL;
        }

        g = InsereVertice(novoVertice, g, erro);
        if (*erro != 1) {
            fclose(ficheiro);
            return NULL;
        }
    }

    // Ler adjacências
    Vertice* aux = g->h;
    while (aux) {
        int totalAdj;
        if (fread(&totalAdj, sizeof(int), 1, ficheiro) != 1) {
            *erro = 101;
            fclose(ficheiro);
            return NULL;
        }

        for (int i = 0; i < totalAdj; i++) {
            CasaF* v2 = (CasaF*)malloc(sizeof(CasaF));
            if (!v2) {
                *erro = 150;
                fclose(ficheiro);
                return NULL;
            }
            if (fread(v2, sizeof(CasaF), 1, ficheiro) != 1) {
                *erro = 101;
                free(v2);
                fclose(ficheiro);
                return NULL;
            }

            // Procurar vértice correspondente
            Vertice* auxV2 = g->h;
            while (auxV2) {
                if (auxV2->antena->linha == v2->linha && auxV2->antena->coluna == v2->coluna) break;
                auxV2 = auxV2->prox;
            }

            free(v2); // Libertar memória auxiliar

            if (!auxV2) {
                *erro = 3; // Vértice não encontrado
                fclose(ficheiro);
                return NULL;
            }    


            Adj* novaAdj = CriarAdj(aux, auxV2, erro);

            if (*erro != 1) {
                fclose(ficheiro);
                return NULL;
            }

            insereAdjacenciaVertice(aux, novaAdj, erro);
            if (*erro != 1) {
                fclose(ficheiro);
                return NULL;
            }
        }
        aux = aux->prox;
    }

    fclose(ficheiro);
    *erro = 1;
    return g;
}

/**
 * @brief 
 * 
 * @param visitados lista de vertices visitados
 * @param count -> nº de visitados
 * @return (int)Sucesso
 */
int mostraVisitados(Vertice** visitados, int count) {
    printf("Visitados na BFS:\n");
    for (int i = 0; i < count; i++) {
        printf("Antena: %c (%d,%d)\n", 
               visitados[i]->antena->c,
               visitados[i]->antena->linha,
               visitados[i]->antena->coluna);
    }
    return 1;
}

/**
 * @brief Função de pesquisa BFS
 * 
 * @param g -> grafo
 * @param linha -> linha de inicio
 * @param coluna -> coluna de inicio
 * @param *erro
 * @return Vertice** lista de vertices visitados
 */
Vertice** BFS(Grafo* g, int linha, int coluna, int* erro, int* visitados_count) {
    if (!g || !g->h) {
        *erro = 3;
        return NULL;
    }

    // Resetar visitados
    Vertice* aux = g->h;
    while (aux) {
        aux->visitado = 0;
        aux = aux->prox;
    }

    // Encontrar o vértice de origem
    Vertice* origem = g->h;
    while (origem) {
        if (origem->antena->linha == linha && origem->antena->coluna == coluna) break;
        origem = origem->prox;
    }

    if (origem==NULL) {
        *erro = 4;
        return NULL;
    }

    // Array que guarda os visitados (100 é um tamanho ficcional)
    Vertice* fila[100];
    int inicio = 0, fim = 0;

    // Array para guardar vértices visitados
    Vertice** visitados = malloc(sizeof(Vertice*) * 100);

    if (!visitados) {
        *erro = 5; 
        return NULL;
    }    

    // Enfileirar origem

    fila[fim++] = origem;

    origem->visitado = 1;
    *visitados_count = 0;
    while (inicio < fim) {
        Vertice* atual = fila[inicio++];
        Adj* adj = atual->adjacencias;
        while (adj) {
            Vertice* vizinho = (adj->v1 == atual) ? adj->v2 : adj->v1;
            if (!vizinho->visitado) {
                vizinho->visitado = 1;
                fila[fim++] = vizinho;
                visitados[(*visitados_count)++] = vizinho;
            }
            adj = adj->prox;
        }
    }

    *erro = 1;
    return visitados;
}

/**
 * @brief Função auxiliar para encontrar os caminhos entre os dois vértices
 * 
 * @param atual -> vertice inicio
 * @param destino -> vertice destino
 * @param caminhoAtual -> caminho atual
 * @param indice -> indice array
 * @return int(Sucesso)
 */
int caminhosEntreDoisVertices(
    Vertice* atual,
    Vertice* destino,
    Vertice** caminhoAtual,
    int indice,
    ListaDeCaminhos* resultados
) {
    caminhoAtual[indice] = atual;
    atual->visitado = 1;

    if (atual == destino) {
        if (resultados->total < MAX_CAMINHOS) {
            Caminho* novo = &resultados->caminhos[resultados->total++];
            novo->tamanho = indice + 1;
            for (int i = 0; i <= indice; i++) {
                novo->vertices[i] = caminhoAtual[i];
            }
        }
        return 1;
    } else {
        Adj* adj = atual->adjacencias;
        while (adj) {
            Vertice* vizinho = (adj->v1 == atual) ? adj->v2 : adj->v1;
            if (!vizinho->visitado) {
                caminhosEntreDoisVertices(vizinho, destino, caminhoAtual, indice + 1, resultados);
            }
            adj = adj->prox;
        }
    }

    atual->visitado = 0;
}

/**
 * @brief Calcula todos os caminhos possiveis 
 * 
 * @param g -> grafo
 * @param linhaOrigem -> linha de origem
 * @param colunaOrigem -> coluna de origem
 * @param linhaDestino -> linha de chegada
 * @param colunaDestino -> coluna de chegada
 * @param *erro 
 * @return ListaDeCaminhos 
 */
ListaDeCaminhos calcularCaminhosSimples(Grafo* g, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int* erro) {
    ListaDeCaminhos resultados;
    resultados.total = 0;
    *erro = 0;

    if (!g || !g->h) {
        *erro = 1; // grafo inválido
        return resultados;
    }

    Vertice *origem = NULL, *destino = NULL;
    for (Vertice* v = g->h; v != NULL; v = v->prox) {
        if (v->antena->linha == linhaOrigem && v->antena->coluna == colunaOrigem) origem = v;
        if (v->antena->linha == linhaDestino && v->antena->coluna == colunaDestino) destino = v;
    }

    if (!origem || !destino) {
        *erro = 3; // vértices não encontrados
        return resultados;
    }

    // Resetar visitados
    for (Vertice* v = g->h; v != NULL; v = v->prox) v->visitado = 0;

    Vertice* caminhoAtual[MAX_VERTICES_CAMINHO];
    caminhosEntreDoisVertices(origem, destino, caminhoAtual, 0, &resultados);

    return resultados;
}

/**
 * @brief Mostra os caminhos calculados
 * 
 * @param resultados -> caminhos calculados anteriormente
 * @return int(Sucesso)
 */
int imprimirCaminhosSimples(ListaDeCaminhos* resultados) {
    if (resultados->total == 0) {
        return 0;
    }

    for (int i = 0; i < resultados->total; i++) {
        Caminho* cam = &resultados->caminhos[i];
        for (int j = 0; j < cam->tamanho; j++) {
            printf("%c (%d,%d)",
                   cam->vertices[j]->antena->c,
                   cam->vertices[j]->antena->linha,
                   cam->vertices[j]->antena->coluna);
            if (j < cam->tamanho - 1) printf(" -> ");
        }
        printf("\n");
    }
    return 1;
}

/**
 * @brief Função que calcula cruzamentos feitos por frequencias
 * 
 * @param g -> grafo
 * @param freq1 -> frequência 1
 * @param freq2 -> frequência 2
 * @param linhas -> linhas onde se guarda linhas de cruzamentos
 * @param colunas -> colunas onde se guarda colunas de cruzamentos
 * @return total cruzamentos calculados
 */
int detectarCruzamentoGeral(Grafo* g, char freq1, char freq2, int linhas[], int colunas[]) {
    int total = 0;
    if (!g || !g->h) return 0;
    int jaexiste=0;
    Vertice* a1 = g->h;
    while (a1) {
        if (a1->antena->c == freq1) {
            Vertice* a2 = g->h;
            while (a2) {
                if (a2->antena->c == freq1 && a1 != a2) {
                    Vertice* b1 = g->h;
                    while (b1) {
                        if (b1->antena->c == freq2) {
                            Vertice* b2 = g->h;
                            while (b2) {
                                if (b2->antena->c == freq2 && b1 != b2) {
                                    // coordenadas
                                    int a1l = a1->antena->linha, a1c = a1->antena->coluna;
                                    int a2l = a2->antena->linha, a2c = a2->antena->coluna;
                                    int b1l = b1->antena->linha, b1c = b1->antena->coluna;
                                    int b2l = b2->antena->linha, b2c = b2->antena->coluna;

                                    // Verifica se os As e Bs estão em cantos opostos
                                    if ((a1l < a2l && a1c < a2c) &&      // a1 acima e à esquerda de a2
                                    (b1l < b2l && b1c > b2c) &&      // b1 acima e à direita de b2
                                    (a2c > b2c && a2l>=b1l && b2l>a1l ) //a2 á esquerda de b2, a2 abaixo de b1,b2 abaixo a1
                                    ) {
                                        int l=(a1l + a2l + b1l + b2l) / 4;
                                        int c=(a1c + a2c + b1c + b2c) / 4;
                                        for(int i=0;i<total;i++){
                                            if(linhas[i]==l && colunas[i]==c){
                                                jaexiste=1;
                                            }
                                        }
                                            linhas[total] = l;
                                            colunas[total] = c;
                                            total++;
                                           jaexiste=0;

                                        }
                                    
                                }
                                b2 = b2->prox;
                            }
                        }
                        b1 = b1->prox;
                    }
                }
                a2 = a2->prox;
            }
        }
        a1 = a1->prox;
    }

    return total;
}
/**
 * @brief 
 * 
 * @param linhas -> linhas de cruzamentos
 * @param colunas -> colunas de cruzamentos
 * @param total -> total de cruzamentos
 * @return (int)Sucesso
 */
int imprimirCruzamentosGerais(int linhas[], int colunas[], int total) {
    if (total == 0) {
        printf("Nenhum cruzamento geral entre frequências encontrado.\n");
        return 0;
    }

    printf("Pontos de cruzamento geral entre frequências (pode ter repetidos):\n");
    for (int i = 0; i < total; i++) {
        printf("Cruzamento em (%d, %d)\n", linhas[i], colunas[i]);
        i++;
    }
    return 1;
}
