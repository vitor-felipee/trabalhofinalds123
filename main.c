//ALUNO: VITOR FELIPE LUCINDO DE ANDRADE
//GRR20252106

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

//Traz arquivos dos outros módulos
#include "ids.h"
#include "cliente.h"
#include "vendedor.h"
#include "venda.h"
#include "relatorios.h"

int main (){
  setlocale(LC_ALL, "pt_BR.UTF-8");
  
  //Declaração dos ponteiros
  Cliente *listaClientes = NULL;
  Vendedor *listaVendedores = NULL;
  Venda *listaVendas = NULL;

  //Declaração dos contadores
  int qtdeClientes = 0;
  int qtdeVendas = 0;
  int qtdeVendedores = 0;

  //Declaração Próximo ID
  int proximoIdCliente = 0;
  int proximoIdVendedor = 0;
  int proximoIdVenda = 0;

  int opcao = 0;

  //Carregando Informaçoes
  carregarClientes(&listaClientes, &qtdeClientes);
  carregarVendedores(&listaVendedores, &qtdeVendedores);
  carregarVendas(&listaVendas, &qtdeVendas);
  carregarIds(&proximoIdCliente, &proximoIdVendedor, &proximoIdVenda);

  //Interação com usuário, direciona para cada uma das funções escolhidas
  while(opcao != 9){
    printf("\n-------------------------------------\n");
    printf("UFPR - GESTOR DE VENDAS");
    printf("\n-------------------------------------\n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Listar Clientes\n");
    printf("3 - Cadastrar Vendedor\n");
    printf("4 - Listar Vendedores\n");    
    printf("5 - Lançar Venda\n");
    printf("6 - Mostrar Vendas\n");
    printf("7 - Relatório de Vendas por Cliente\n");
    printf("8 - Relatório de Vendas por Vendedor\n");
    printf("9 - Sair e Salvar\n");
    printf("Digite a opção desejada: ");

    char opcaoString[8];
    while (true) {
      fgets(opcaoString, sizeof(opcaoString), stdin);
      opcaoString[strcspn(opcaoString, "\n")] = '\0';
      bool soDigito = true;
      int tamanho = strlen(opcaoString);
      //Verifica se tamanho é valido
      if (tamanho == 0){
        soDigito = false;
      }
      //Verifica se o que foi digitado é numero
      for (int i = 0; i < tamanho; i++) {
        if (!isdigit(opcaoString[i])){
           soDigito = false;
           break;
        }
      }
      if (!soDigito) {
        printf("Digite um número.\n");
        continue;
      }
      opcao = atoi(opcaoString);
      //Verifica se opção digitada é váluda
      if (opcao < 1 || opcao > 9) {
        printf("Digite uma opção válida.\n");
        continue;
      }
      break;
    }
   switch (opcao) {
    case 1:
      cadastrarCliente(&listaClientes, &qtdeClientes, &proximoIdCliente);
      break;
    case 2:
      listarClientes(listaClientes, qtdeClientes);
      break;
    case 3:
      cadastrarVendedor(&listaVendedores, &qtdeVendedores, &proximoIdVendedor);
      break;
    case 4:
      listarVendedores(listaVendedores, qtdeVendedores);
      break;
    case 5:
      lancarVenda(&listaVendas, &qtdeVendas, &proximoIdVenda, listaClientes, qtdeClientes, listaVendedores, qtdeVendedores);
      break;
    case 6:
      listarVendas(listaVendas, qtdeVendas, listaClientes, qtdeClientes, listaVendedores, qtdeVendedores);
      break;
    case 7:
      relatorioVendasCliente(listaClientes, qtdeClientes, listaVendas, qtdeVendas);
      break;
    case 8:
      relatorioVendasVendedor(listaVendedores, qtdeVendedores, listaVendas, qtdeVendas);
      break;
    case 9:
      salvarClientes(listaClientes, qtdeClientes);
      salvarVendedores(listaVendedores, qtdeVendedores);
      salvarVendas(listaVendas, qtdeVendas);
      salvarIds(proximoIdCliente, proximoIdVendedor, proximoIdVenda);
      printf("Encerrando o programa...");
      break;
    default:
      printf("Essa opção não existe.");
      break;
   }
  }
  return 0;
}