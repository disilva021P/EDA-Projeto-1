/**
 * @file funcoes.h
 * @author Diogo SIlva (a31504@alunos.ipca.pt)
 * @brief HEADER da biblioteca funcoes que contêm as funções para as operações da 
 * lista linkada
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef FUNCOES_H
#define FUNCOES_H
#include"dados.h"
#define vazio '.'

/**
 * @brief Função que cria um espaço de memória para as antenas
 * 
 * @param c: Frequência
 * @param linha: Linha no mapa
 * @param coluna: Coluna no mapa 
 * @return Casa* -> endereço de memória da antena
 */
Casa* CriaCasa(char c, int linha, int coluna,int* erro);

/**
 * @brief Função que cria um espaço na mememória para guardar o efeito nefasto
 * 
 * @param linha: Linha do efeito
 * @param coluna: Coluna do efeito
 * @param x1: Primeira antena que causou o efeito 
 * @param x2: Segunda antena que causou o efeito
 * @return EfeitoNefasto* -> endereço de memória do efeito nefasto
 */
EfeitoNefasto* CriaEfeitoNefasto(int linha, int coluna, Casa* x1, Casa* x2,int* erro);
/**
 * @brief Função que adiciona uma dada casa à lista de antenas
 * 
 * @param[in,out] mapa: Cabeçalho da lista de antenas
 * @param n: Antena a adicionar na lista
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeçalho da lista de antenas depois da adição
 */
Casa* AdicionaCasa(Casa *mapa,Casa* n,EfeitoNefasto** cabeca,int* erro);
/**
 * @brief Função que simplifica o processo de criar e adicionar antenas
 * 
 * @param[in,out] mapa: Cabeçalho da lista de antenas
 * @param c: Fequência
 * @param linha: Linha no mapa 
 * @param coluna: Coluna no mapa
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeçalho da lista de antenas depois da adição
 */
Casa *CriaAdiciona(Casa *mapa,char c, int linha, int coluna,EfeitoNefasto** cabeca,int* erro);
    /**
 * @brief Função que remove uma casa da lista de antenas
 * 
 * @param[in,out] mapa Cabeçalho da lista de antenas
 * @param linha: Linha da antena a remover
 * @param coluna: Coluna da antena a remover
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeçalho da lista de antenas depois da remoção
 */
Casa *RemoverCasa(Casa *mapa, int linha, int coluna,EfeitoNefasto** cabeca,int* erro);
/**
 * @brief Função que remove efeito nefasto que foi causado por uma antena que estava na coluna linha,coluna
 * 
 * @param[in,out] cabeca: Cabeçalho da lista de efeito nefasto
 * @param linha: Linha da antena que vai remover
 * @param coluna: Coluna da antena que vai remover 
 * @return EfeitoNefasto* -> Cabeçalho da lista de efeito nefasto depois de remover
 */
EfeitoNefasto *RemoverNefasto(EfeitoNefasto* cabeca, int linha, int coluna,int* erro);
/**
 * @brief Função que verifica se existe efeito nefaste em certa linha e coluna
 * 
 * @param mapa: Cabeçalho da lista de efeito nefasto
 * @param linha: Linha a verificar 
 * @param coluna: Coluna a verificar 
 * @return 0 se não existe 1 se existe 
 */
int ExisteEfeitoEfeitoNefasto(EfeitoNefasto *mapa, int linha, int coluna,int* erro);

/**
 * @brief Função que verifica se existe efeito nefaste em certa linha e coluna
 * 
 * @param[in,out] cabeca: Cabeçalho da lista de efeito nefasto
 * @param mapa: Cabeçalho da lista de antenas 
 * @return EfeitoNefasto* -> Cabeçalho da lista de efeito nefasto depois de verificar
 */
EfeitoNefasto* CriaListaEfeitoEfeitoNefasto(EfeitoNefasto* cabeca, Casa *mapa,int* erro);

/**
 * @brief Função que adiciona efeito nefasto á lista
 * 
 * @param[in,out] cabeca: Cabeçalho da lista de efeito nefasto
 * @param mapa: Cabeça da lista das antenas
 * @param n: Efeito nefasto que vai adicionar
 * @return Casa* -> Cabeça da lista de efeito nefasto depois de adicionar
 */
EfeitoNefasto* AdicionaCasaEfeitoNefasto(EfeitoNefasto* cabeca, EfeitoNefasto* n,int* erro);

/**
 * @brief Função que simplifica o processo de criar e adicionar efeitos nefastos
 * 
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @param linha: Linha onde inserir
 * @param coluna: Coluna onde inserir
 * @param x1: 1ª Antena causadora
 * @param x2: 2ª Antena causadora
 * @return EfeitoNefasto* -> Cabeça da lista de efeito nefasto depois da inserção
 */
EfeitoNefasto* CriaAdicionaEfeito(EfeitoNefasto *cabeca, int linha, int coluna, Casa* x1, Casa* x2,int* erro);
/**
 * @brief Função que printa o mapa com antenas e efeito nefasto
 * 
 * @param mapa: Cabeça da lista das antenas
 * @param cabeca: Cabeça da lista de efeito nefasto
 */
int MostraListaNovo(Casa *mapa,EfeitoNefasto* cabeca,int* erro);
/**
 * @brief Função que printa de forma tabular as antenas e o efeito nefasto
 * 
 * @param mapa: Cabeça da lista das antenas
 * @param cabeca: Cabeça da lista de efeito nefasto 
 */
int MostraListaCasas(Casa *mapa, EfeitoNefasto* cabeca);

/**
 * @brief Função que lẽ as antenas de um ficheiro txt com o mapa
 * 
 * @param nome: Nome do ficheiro
 * @param[in,out] mapa: Cabeça da lista das antenas 
 * @param hE: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeça da lista das antenas depois da leitura
 */
Casa* CriaMapaCasas(char* nome,Casa *mapa,EfeitoNefasto** hE,int* erro);
/**
 * @brief Função que escreve num ficheiro de texto o mapa sem efeito nefasto
 * 
 * @param mapa: Cabeça da lista das antenas
 */
int criaMapaFicheiro(Casa *mapa);
/**
 * @brief Função que le lista de antenas de ficheiros binários
 * 
 * @param mapa Cabeça da lista de antenas
 * @param[in,out] cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeça da lista das antenas
 */
Casa* LerListaFicheiro(Casa *mapa,EfeitoNefasto** cabeca,int* erro);
/**
 * @brief Função que escreve lista de antenas em ficheiro binário
 * 
 * @param[in,out] mapa: Cabeça da lista de antenas
 * @return Casa* -> Cabeça da lista de antenas
 */
Casa* EscreverListaFicheiro(Casa *mapa,int* erro);

/**
 * @brief Devolve a posição da antena no mapa [1-n*m]
 * 
 * @param c Antena
 * @return int -> Posição no mapa
 */
int Posicao(Casa* c,int* erro);
/**
 * @brief Devolve a posição do efeito nefasto no mapa [1-n*m]
 * 
 * @param c Efeito nefasto
 * @return int -> Posição no mapa
 */
int PosicaoEfeitoNefasto(EfeitoNefasto* c,int* erro);


/**
 * @brief Função que Limpa a memória da lista de Antenas
 * 
 * @param[in,out] efeito Cabeça da lista de efeito nefasto
 * @return EfeitoNefasto* -> Cabeça da lista de efeito nefasto depois da limpeza (NULL)
 */
Casa* LimpaMemoria(Casa* mapa,int* erro);
/**
 * @brief Função que Limpa a memória da lista de efejto nefasto
 * 
 * @param[in,out] efeito Cabeça da lista de efeito nefasto
 * @return EfeitoNefasto* -> Cabeça da lista de efeito nefasto depois da limpeza (NULL)
 */
EfeitoNefasto* LimpaMemoriaEfeito(EfeitoNefasto* efeito,int* erro);
/**
 * @brief Função que vai adicionar uma casa apenas se não causar efeito nefasto
 * 
 * @param mapa: Cabeça da lista de antenas 
 * @param n: antena a adicionar
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeça da lista de antenas 
 */
Casa* AdicionaCasaSemCausarNefasto(Casa *mapa,Casa* n,EfeitoNefasto* cabeca,int* erro);
/**
 * @brief Função que vai adicionar uma casa apenas se não estiver com efeito nefasto na casa
 * 
 * @param mapa: Cabeça da lista de antenas 
 * @param n: antena a adicionar
 * @param cabeca: Cabeça da lista de efeito nefasto
 * @return Casa* -> Cabeça da lista de antenas 
 */
Casa* AdicionaCasaSemSobreposicao(Casa *mapa,Casa* n,EfeitoNefasto* cabeca,int* erro);
#endif 