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
    struct Casa *prox;
    struct Casa *ant;
}Casa;
#define true 1
#define false 0
