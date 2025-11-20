#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>

typedef struct {
    int id;
    char nome[50];
    char cnpjCpf[16];
    char email[50];
    char telefone[13];
} Cliente;

// Deifinindo estrutra das funções
void carregarClientes(Cliente **lista, int *qtdeClientes);
void salvarClientes(Cliente *lista, int qtdeClientes);
void listarClientes(Cliente *lista, int qtdeClientes);
void cadastrarCliente(Cliente **lista, int *qtdeClientes, int *proximoIdCliente);

#endif