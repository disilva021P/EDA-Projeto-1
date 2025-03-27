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
    Casa* h=NULL;
    EfeitoNefasto* hE=NULL;
    printf("ola\n");
    if(argc==1){
        h=CriaMapaCasas("mapa.txt",h,hE);
    }
    else{
        h=CriaMapaCasas((char*)argv[1],h,hE);
    }
    printf("ola1\n");
    MostraListaNovo(h,hE);
    printf("ola2\n");
    hE= CriaListaEfeitoEfeitoNefasto(hE,h);
    printf("ola3\n");
    MostraListaNovo(h,hE);
    MostraListaCasas(h,hE);
    printf("ola4\n");
    LimpaMemoria(h);    
    LimpaMemoriaEfeito(hE);           
    return 0;
}
