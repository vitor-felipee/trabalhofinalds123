#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <stdio.h>

typedef struct {
    int id;
    char nome[50];
    char cpf[16];
    char email[50];
    char telefone[13];
} Vendedor;

//Definir escopo funções de vendedor
void carregarVendedores(Vendedor **lista, int *qtdeVendedor);
void salvarVendedores(Vendedor *lista, int qtdeVendedores);
void listarVendedores(Vendedor *lista, int qtdeVendedores);
void cadastrarVendedor(Vendedor **lista, int *qtdeVendedor, int *proximoIdVendedor);

#endif