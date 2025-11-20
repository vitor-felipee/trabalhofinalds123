#ifndef VENDA_H
#define VENDA_H

#include <stdio.h>
#include <time.h>
#include "cliente.h"
#include "vendedor.h"

typedef struct {
    int id;
    int idCliente;
    int idVendedor;
    float total;
} Venda;

//Escopo funções de venda
void carregarVendas(Venda **lista, int *qtdeVendas);
void salvarVendas(Venda *lista, int qtdeVendas);
void listarVendas(Venda *listaVendas, int qtdeVendas, Cliente *listaClientes, int qtdeClientes, Vendedor *listaVendedores, int qtdeVendedores);
void lancarVenda(Venda **listaVendas, int *qtdeVendas, int *idProximaVenda, Cliente *listaClientes, int qtdeClientes, Vendedor *listaVendedores, int qtdeVendedores);

#endif