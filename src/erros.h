/**
 * @file erros.h
 * @author Diogo Silva (a31504@alunos.ipca.pt)
 * @brief Header do ficheiro dos tratamentos
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include<stdio.h>
#ifndef ERROS_H
#define ERROS_H
// Funções principais
int preencheDicionario(char* nomeFicheiro);
char* ErroPorCod(int codErro);
char* ErroPorPais_Cod(char* lingua, int codErro);

int limpaMemoriaErros();
int definirLingua(char* lingua);
#endif