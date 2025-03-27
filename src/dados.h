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
typedef struct Casa
{
    char c;
    int linha;
    int coluna;
    struct Casa *prox;
}Casa;
typedef struct CasaF
{
    char c;
    int linha;
    int coluna;
}CasaF;
typedef struct EfeitoNefasto
{
    int linha;
    int coluna;
    struct Casa *antenas[2];//Antenas que causam o efeito
    struct EfeitoNefasto* prox;
}EfeitoNefasto;
