#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "cliente.h"
#include "venda.h"
#include "vendedor.h"

void relatorioVendasCliente(Cliente *listaClientes, int qtdeClientes, Venda *listaVendas, int qtdeVendas);
void relatorioVendasVendedor(Vendedor *listaVendedores, int qtdeVendedores, Venda *listaVendas, int qtdeVendas);

#endif