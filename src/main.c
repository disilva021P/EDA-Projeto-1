/**
 * @file main.c
 * @author Diogo SIlva (a31504@alunos.ipca.pt)
 * @brief Ficheiro principal
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include<stdlib.h>
#include<stdio.h>
#include"funcoes.h"
int main(int argc, char const *argv[])
{
    if(argc==1){
        CriaMapaCasas("mapa.txt");
    }
    else{
        CriaMapaCasas((char*)argv[1]);
    }
    CriaA();
    MostraListaNovo();
    RemoverCasa(5,5);
    MostraListaNovo();
    criaMapaFicheiro();
    LimpaMemoria();               
    return 0;
}
