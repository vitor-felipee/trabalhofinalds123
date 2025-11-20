#include "relatorios.h"
#include <stdio.h>

void relatorioVendasCliente(Cliente *listaClientes, int qtdeClientes, Venda *listaVendas, int qtdeVendas) {
    printf("\n--------------------------------------\n");
    printf("RELATÓRIO DE COMPRAS POR CLIENTE");
    printf("\n--------------------------------------\n");

    //Se não tiver cliente cadastrado, não exibirá nenhuma venda
    if (qtdeClientes == 0) {
        printf("Nenhum cliente cadastrado para exibir.\n");
        return;
    }

    for (int i = 0; i < qtdeClientes; i++) {
      Cliente *c = &listaClientes[i];
      int contCompras = 0;
      float totalCompras = 0.0;

      for (int j = 0; j < qtdeVendas; j++) {
        //Compara id cliente com venda
        if (listaVendas[j].idCliente == c->id) {
          contCompras++;
          totalCompras += listaVendas[j].total;
        }
      }

      printf("CLIENTE: %s (ID: %d)\n", c->nome, c->id);
      printf("* Qtd. Compras: %d\n", contCompras);
      printf("* Total Gasto: R$ %.2f\n", totalCompras);
      printf("---------------------------------------\n");
}
  printf("\nPressione Enter para voltar...");
  getchar(); 
}

void relatorioVendasVendedor(Vendedor *listaVendedores, int qtdeVendedores, Venda *listaVendas, int qtdeVendas) {
  printf("\n---------------------------------------\n");
  printf("RELATÓRIO DE VENDAS POR VENDEDOR");
  printf("\n---------------------------------------\n");

  //Se não tiver vendedor cadastrado, não exibirá nenhuma venda
  if (qtdeVendedores == 0) {
    printf("Nenhum vendedor cadastrado para exibir.\n");
    return;
  }

  for (int i = 0; i < qtdeVendedores; i++) {
    Vendedor *v = &listaVendedores[i];
    
    int contVendas = 0;
    float totalVendas = 0.0;

    for (int j = 0; j < qtdeVendas; j++) {
      //Verifica se a venda é de determinado vendedor
      if (listaVendas[j].idVendedor == v->id) {
        contVendas++;
        totalVendas += listaVendas[j].total;
      }
    }

    printf("VENDEDOR: %s (ID: %d)\n", v->nome, v->id);
    printf("* Vendas Realizadas: %d\n", contVendas);
    printf("* Total Vendido: R$ %.2f\n", totalVendas);
    printf("---------------------------------------\n");

  }

  printf("\nPressione Enter para voltar...");
  getchar();
}