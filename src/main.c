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
    if(argc==1){
        h=CriaMapaCasas("mapa.txt",h,&hE);
    }
    else{
        h=CriaMapaCasas((char*)argv[1],h,&hE);
    }
    MostraListaNovo(h,hE);
    h=CriaAdiciona(h,'F',1,2,&hE);
    MostraListaNovo(h,hE);
    h=RemoverCasa(h,1,2,&hE);
    MostraListaNovo(h,hE);
    h=CriaAdiciona(h,'F',1,2,&hE);
    criaMapaFicheiro(h);
    h=EscreverListaFicheiro(h);
    h=LerListaFicheiro(h,&hE);
    MostraListaCasas(h,hE);
    hE=LimpaMemoriaEfeito(hE);      
    h=LimpaMemoria(h);    
    return 0;
}
