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
        CriaMapa("mapa.txt");
    }
    else{
        CriaMapa((char*)argv[1]);
    }
    /*
    Casa* ola = CriaCasa('W',1,1);
    TrocarCasa(ola);
    */
    CalculaEfeitoNefastoFrente();
    CalculaEfeitoNefastoTras();
    MostraLista();    
    LimpaMemoria();               
    return 0;
}
