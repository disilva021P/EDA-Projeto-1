# 📡 Projeto 1ªFase EDA

Este projeto foi desenvolvido no âmbito da disciplina de **Estruturas de Dados Avançadas** e tem como objetivo a manipulação de antenas em uma cidade, utilizando **listas ligadas simples** para armazenar e processar as informações. Além disso, o projeto aborda conceitos como **manipulação de ficheiros**, **modularização** e **documentação do código**.

## 📌 Estrutura do Projeto

```
├── src
│   ├── dados.h
│   ├── funcoes.c
│   ├── funcoes.h
│   ├── main.c
│   ├── makefile
│   ├── mapa.txt
├── doxydox
│   ├── DoxygenConfig
│   ├── index.html (gerado pelo Doxygen)
│   ├── ...
├── doc
│   ├── RelatórioTpEda.pdf
└── README.md

```

---

## 🔧 Como Compilar o Projeto

O projeto usa um **Makefile** para facilitar a compilação. Para compilar, basta executar:

```sh
cd src
make
./programaCompilado
```



## 📜 Relatório do Projeto

O relatório do projeto está disponível no arquivo:

```
doc/RelatórioTpEda.pdf
```

Este documento contém a explicação detalhada da implementação, as estruturas utilizadas e a lógica de funcionamento do programa.

---

## 📖 Gerar Documentação com Doxygen

O projeto inclui documentação gerada pelo **Doxygen**. Para criar ou atualizar a documentação:

1. Ter o **Doxygen** instalado.

2. No projeto, execute:

   ```sh
   cd doxydoc/
   doxygen Doxyfile
   ```


O projeto é escrito em **C** e requer o gcc.

Se houver necessidade de carregar um mapa específico:

```sh
./programaCompilado nomemapa.txt
```


🖥 **Desenvolvido por Diogo Silva nº31504**
