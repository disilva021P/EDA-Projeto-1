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
void CriaMapa(char* ficheiro);
Casa *CriaCasa(char c,int linha,int coluna);
Casa* CriaAdicionaFim(char c,int linha, int coluna);
void MostraLista();
void LimpaMemoria();
Casa* TrocarCasaInicial(Casa *n);
Casa* TrocarCasaMeio(Casa *n);
Casa* TrocarCasaFinal(Casa *n);
Casa* TrocarCasa(Casa *n);
Casa* RemoverAntena(int linha, int coluna);
Casa* AdicionaCasaInicio(Casa *n);
Casa* AdicionarCasaMeio(Casa *n);
Casa* AdicionarCasaFim(Casa *n);
Casa* CalculaEfeitoNefastoFrente();
Casa* CalculaEfeitoNefastoTras();
int Posicao(Casa* c);  
 
