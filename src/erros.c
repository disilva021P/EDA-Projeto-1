/**
 * @file erros.c
 * @author Diogo Silva (a31504@alunos.ipca.pt)
 * @brief Ficheiro para tratar de erros no trabalho
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include"erros.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//mensagem com id
typedef struct Mensagem
{
    int idMensagem;
    char* mensagem;
    struct Mensagem* proxima; 
}Mensagem;
//keys
typedef struct LinguaDicionario {
    int id;
    char linguaCod[6];
    Mensagem *mensagens; 
    struct LinguaDicionario* prox;
    
} LinguaDicionario;

// Funções para manipulação de línguas
LinguaDicionario* CriaLingua(char* cod, int* erro);
int AdicionarLingua(LinguaDicionario* lingua);
int CriaAdicionaLingua(char* cod);
LinguaDicionario* ProcurarLingua(char *cod);

// Funções para manipulação de mensagens
Mensagem* CriaMensagem(int cod, char* mensagem, int* erro);
int AdicionarMensagem(Mensagem* mensagem, char* codPais);
int AdicionarMensagemLista(Mensagem** h, Mensagem* mensagem);
int CriaAdicionaMensagem(int cod, char* mensagem, char* codPais);
int leFicheiro(FILE* f);
int AdicionarLingua(LinguaDicionario* lingua);
int CriaAdicionaLingua(char* cod);
LinguaDicionario* ProcurarLingua(char *cod);




LinguaDicionario *dicionario=NULL;
char* linguadefinida;
int ids=0; //ids de linguas

/**
 * @brief Função que cria linguas
 * 
 * @param cod -> código da lingua
 * @param *erro
 * @return LinguaDicionario* 
 */
LinguaDicionario *CriaLingua(char* cod,int*erro){
    if(!cod){
        *erro=150;
        return NULL; //validação localização
    } 
    LinguaDicionario* aux = (LinguaDicionario*)malloc(sizeof(LinguaDicionario)); //alocação de memória
    if(aux){
        strncpy(aux->linguaCod, cod, 5);
        aux->linguaCod[sizeof(aux->linguaCod) - 1] = '\0';
        aux->id = ids;
        aux->mensagens =NULL;
        return aux;//retorna o apontador para a memório preenchida/NULL
    }
    *erro = 149;
    return NULL;
}

/**
 * @brief Adiciona Lingua ao dicionário
 * 
 * @param lingua -> Lingua a adicionar
 * @return (int)Erro
 */
int AdicionarLingua(LinguaDicionario* lingua){
    if(!lingua)return 151; //validação localização
    if(!dicionario){
        dicionario = lingua;
        return 1;
    }
    LinguaDicionario *aux= dicionario;
    while (aux->prox)
    {
        aux=aux->prox;
    }
    aux->prox= lingua;
    return 1;
}

/**
 * @brief Resume o processo de criação e adicionar Linguas
 * 
 * @param cod -> cod Lingua
 * @return (int)Erro 
 */
int CriaAdicionaLingua(char* cod){
    int erro=1;
    LinguaDicionario* lingua=CriaLingua(cod,&erro);
    if(erro != 1){
        return erro;
    }
    erro = AdicionarLingua(lingua);
    return erro;//retorna o apontador para a memório preenchida/NULL
}

/**
 * @brief Procura uma lingua pelo código
 * 
 * @param cod -> cod Lingua
 * @return LinguaDicionario* ou NULL
 */
LinguaDicionario* ProcurarLingua(char *cod){
    if(!cod)return NULL; //validação localização
    LinguaDicionario* aux= dicionario;
    while (aux)
    {
        if(strcmp(aux->linguaCod,cod)==0){
            return aux;
        }
        aux= aux->prox;
    }
    return NULL;
    
}

/**
 * @brief Função a ser chamada pelo utilizador para preencher o dicionario
 * 
 * @param nomeFicheiro 
 * @return (int)Erro 
 */
int preencheDicionario(char* nomeFicheiro){
    FILE* f;
    if(!nomeFicheiro){
        if((f = fopen("erros.txt","r"))==NULL){
            return 101;
        }

    } else if((f=fopen(nomeFicheiro,"r"))==NULL){
        return 100; //ficheiro não existe
    }
    leFicheiro(f);
    fclose(f);
    return 1;
}

/**
 * @brief Procura o erro pelo código da mensagem (por uma lingua definida)
 * 
 * @param codErro -> Erro de mensagem
 * @return char* mensagem de erro
 */
char* ErroPorCod(int codErro){
    if(linguadefinida==NULL)return NULL;
    LinguaDicionario* keys = dicionario;
    Mensagem* mensagens = dicionario->mensagens;
    while (keys)
    {
        if(strcmp(keys->linguaCod,linguadefinida)==0){
            while (mensagens)
            {
                if(mensagens->idMensagem==codErro){
                    return mensagens->mensagem;
                }
                mensagens=mensagens->proxima;
            }
        }
        keys = keys->prox;
    }
    return NULL;
}

/**
 * @brief Procura o erro pelo código do país e da mensagem 
 * 
 * @param lingua -> cod Lingua
 * @param codErro -> cod erro
 * @return char* mensagem de erro
 */
char* ErroPorPais_Cod(char* lingua, int codErro){
    LinguaDicionario* keys = dicionario;
    Mensagem* mensagens = dicionario->mensagens;
    while (keys)
    {
        if(strcmp(keys->linguaCod,lingua)==0){
            while (mensagens)
            {
                if(mensagens->idMensagem==codErro){
                    return mensagens->mensagem;
                }
                mensagens=mensagens->proxima;
            }
        }
        keys = keys->prox;
    }
    return NULL;
}

/**
 * @brief Le o ficheiro e preenche o dicionario
 * 
 * @param f -> Ficheiro
 * @return (int)Erro
 */
int leFicheiro(FILE* f) {
    if(!f) return 103; // ficheiro inválido
    int cod = 0;
    char codPais[6], erro[255];
    LinguaDicionario* linguas;

    while (fscanf(f, "%5[^;];%d;%255[^\n]\n", codPais, &cod, erro) == 3) {
        linguas = ProcurarLingua(codPais);
        if(!linguas) {
            ids++;
            int resultado = CriaAdicionaLingua(codPais);
            if(resultado != 1) {
                return resultado;
            }
        }
        
        int resultado = CriaAdicionaMensagem(cod, erro, codPais);
        if(resultado != 1) {
            return resultado;
        }
    }
    
    return 1; // sucesso
}

/**
 * @brief Cria espaço para uma mensagem
 * 
 * @param cod -> cod da mensagem
 * @param mensagem -> mensagem
 * @param *erro 
 * @return Mensagem* ou NULL
 */
Mensagem *CriaMensagem(int cod,char* mensagem,int*erro){
    if(!cod){
        *erro=150;
        return NULL; //validação localização
    } 
    Mensagem* aux = (Mensagem*)malloc(sizeof(Mensagem)); //alocação de memória

    if(aux){
        aux->idMensagem=cod;
        aux->mensagem = (char*)malloc(strlen(mensagem)+1); //alocação de memória
        strcpy(aux->mensagem, mensagem);
        aux->proxima = NULL;
        return aux;//retorna o apontador para a memório preenchida/NULL
    }
    *erro= 149;
    return NULL;
}

/**
 * @brief  Adiciona mensagem ao dicionário
 * 
 * @param mensagem -> mensagem a adicionar
 * @param codPais -> cod do pais a que a mensagem pertence
 * @return (int) Erro
 */
int AdicionarMensagem(Mensagem* mensagem,char* codPais){
    if(!mensagem)return 151; //validação localização
    if(!dicionario){
        return 901;
    }
    LinguaDicionario *aux= dicionario;
    while (aux)
    {
        if(strcmp(aux->linguaCod,codPais)==0){
            AdicionarMensagemLista(&aux->mensagens,mensagem);
        }
        aux=aux->prox;
    }
    
    return 1;
}

/**
 * @brief Adicionar Mensagens a uma lista de Mensagens
 * 
 * @param h -> cabeça das mensagens
 * @param mensagem -> mensagem a adicionar
 * @return (int) Erro
 */
int AdicionarMensagemLista(Mensagem** h, Mensagem* mensagem){
    if(!mensagem)return 151; //validação localização
    if(!dicionario){
        return 901;
    }
    if(!*h){
        *h=mensagem;
        return 1;
    }
    Mensagem *aux= *h;
    while (aux->proxima)
    {
        aux=aux->proxima;
    }
    aux->proxima=mensagem;

    return 1;
}

/**
 * @brief Resume o processo de criação e adicionar Mensagens
 * 
 * @param cod -> cod da mensagem
 * @param mensagem -> mensagem
 * @param codPais -> pais da mensagem
 * @return (int) Erro 
 */
int CriaAdicionaMensagem(int cod,char* mensagem,char* codPais){
    int erro=1;
    Mensagem* m=CriaMensagem(cod,mensagem,&erro);
    if(erro !=1 ){
        return erro;
    }
    erro = AdicionarMensagem(m,codPais);
    return erro;//retorna o apontador para a memório preenchida/NULL
}
/**
 * @brief Limpa o dicionário da mensagem
 * 
 * @return (int)Sucesso
 */
int limpaMemoriaErros() {
    LinguaDicionario* atual = dicionario;
    LinguaDicionario* proximo = NULL;
    
    while (atual != NULL) {
        Mensagem* msg_atual = atual->mensagens;
        Mensagem* msg_proximo = NULL;
        
        while (msg_atual != NULL) {
            
            msg_proximo = msg_atual->proxima;
            free(msg_atual->mensagem);
            free(msg_atual);       
            msg_atual = msg_proximo;
        }
        
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    dicionario = NULL;
    ids = 0;
    
    return 1;  // Indica sucesso
}
/**
 * @brief Define uma linguagem (para utilizar ErroPorCod)
 * 
 * @param lingua -> cod a definir
 * @return int Sucesso
 */
int definirLingua(char* lingua){
    linguadefinida = (char*)malloc(strlen(lingua)+1);
    if(!linguadefinida) return 0;
    strcpy(linguadefinida,lingua);
    return 1;
}