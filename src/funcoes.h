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
Casa* AdicionarCasa(Casa *n);
void CriaMapa(char* ficheiro);
Casa *CriaCasa(char c);
Casa* CriaAdiciona(char c);
void MostraLista();
void LimpaMemoria();
Casa* AdicionarAntena(char c, int linha, int coluna);
Casa* RemoverAntena(int linha, int coluna);