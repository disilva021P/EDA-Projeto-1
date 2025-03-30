/**
 * @file dados.h
 * @author Diogo SIlva (a31504@alunos.ipca.pt)
 * @brief Ficheiro de estrutura de dados
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef DADOS_H
#define DADOS_H
 /**
  * @brief Struct que guarda as antenas
  * 
  */    
typedef struct Casa
{
    char c; //Frequência
    int linha; //linha no mapa
    int coluna; //coluna no mapa
    struct Casa *prox; //proxima antena na lista
}Casa;

/**
 * @brief Struct que ajuda a salvar as antenas
 * 
 */
typedef struct CasaF
{
    char c; //Frequência
    int linha; //linha no mapa
    int coluna; //coluna no mapa
}CasaF;

/**
 * @brief Struct que guarda os efeitos nefastos
 * 
 */
typedef struct EfeitoNefasto
{
    int linha; //linha no mapa
    int coluna; //coluna no mapa
    struct Casa *antenas[2];//Antenas que causam o efeito
    struct EfeitoNefasto* prox; // //proximo efeito nefasto na lista
}EfeitoNefasto;
#endif 
