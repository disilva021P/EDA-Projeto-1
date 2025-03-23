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


#include"dados.h"
void criaMapaFicheiro();
void EscreveMapa(char* ficheiro);
Casa *RemoverCasa(int linha, int coluna);
void MostraListaC();
Casa* AdicionaCasa(Casa* n);
int ExisteEfeitoEfeitoNefasto(int coluna, int linha);
void MostraListaNovo();
Casa *CriaCasa(char c,int linha,int coluna);
Casa* CriaMapaCasas(char* nome);
Casa* AdicionaCasa(Casa* n);
Casa *CriaAdiciona(char c, int linha, int coluna);
void criaMapaFicheiro();
void LimpaMemoria();
int Posicao(Casa* c);  
 
