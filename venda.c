#include "venda.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void carregarVendas(Venda **lista, int *qtdeVendas){
  //Abrir arquivo para leitura
  FILE *arqVendas = fopen("vendas.dat", "rb");

  if(arqVendas == NULL){
    *qtdeVendas = 0;
    *lista = NULL;
    printf("\nArquivo vendas.dat não encontrado. Iniciando lista vazia.\n");
    return;
  }

  Venda vendaBuffer;
  //Enquanto tiver venda, vai ler o arquivo
  while(fread(&vendaBuffer,sizeof(Venda),1, arqVendas) == 1){
    int qtdeAtualizada = *qtdeVendas + 1;
    //Realoca memória para caber a nova quantidade de vendedores
    Venda *novaLista = realloc(*lista, sizeof(Venda) * qtdeAtualizada);

    if(novaLista == NULL){
      printf("Erro: não foi possível realocar a memória.\n");
      fclose(arqVendas);
      return;
    }
    //Atualiza lista
    *lista = novaLista;
    (*lista)[*qtdeVendas] = vendaBuffer;
    *qtdeVendas = qtdeAtualizada; 
  }
  fclose(arqVendas);
  printf("\n%d vendas carregados com sucesso.\n", *qtdeVendas);
}

void salvarVendas(Venda *lista, int qtdeVendas){
  //Abrir arquivo
  FILE *arqVendas = fopen("vendas.dat", "wb");

  //Caso não consiga abrir o arquivo, retorna um erro
  if(arqVendas == NULL){
    printf("Erro: Não foi possível abrir o arquivo clientes.dat\n");
    return;
  }

  //Escreve todos as vendas no arquivo
  for(int i =0; i< qtdeVendas; i++){
    fwrite(&lista[i], sizeof(Venda), 1, arqVendas);
  }

  //Fecha o arquivo
  fclose(arqVendas);
  printf("\n%d vendas salvas com sucesso.\n", qtdeVendas);  
}

void listarVendas(Venda *listaVendas, int qtdeVendas, Cliente *listaClientes, int qtdeClientes, Vendedor *listaVendedores, int qtdeVendedores){
    if(qtdeVendas == 0 || listaVendas == NULL){
    printf("\nNenhuma vendas lançada.\n");
    return;
  }

  printf("\n--- Lista de vendas (%d) ---\n", qtdeVendas);
  for(int i = 0; i < qtdeVendas; i++){
    Venda *venda = &listaVendas[i];

    // Busca nome do cliente da venda
    char nomeCliente[50] = "Cliente não encontrado";
    for (int j = 0; j < qtdeClientes; j++) {
      if (listaClientes[j].id == venda->idCliente) {
        strncpy(nomeCliente, listaClientes[j].nome, sizeof(nomeCliente)-1);
        nomeCliente[sizeof(nomeCliente)-1] = '\0';
        break;
      }
    }

    //Busca Vendedor da venda
    char nomeVendedor[50] = "Vendedor não encontrado";
    for (int m = 0; m < qtdeVendedores; m++) {
      if (listaVendedores[m].id == venda->idVendedor) {
        strncpy(nomeVendedor, listaVendedores[m].nome, sizeof(nomeVendedor)-1);
        nomeVendedor[sizeof(nomeVendedor)-1] = '\0';
        break;
      }
    }

    printf("ID: %d\n", venda->id);
    printf("Cliente: %s\n", nomeCliente);
    printf("Vendedor: %s\n", nomeVendedor);
    printf("Valor Total: R$%.2f\n", venda->total);
    printf("-------------------------------\n");
  }
}

void lancarVenda(Venda **listaVendas, int *qtdeVendas, int *idProximaVenda, Cliente *listaClientes, int qtdeClientes, Vendedor *listaVendedores, int qtdeVendedores){
  printf("\n-------------------------------------\n");
  printf("LANÇAR VENDAS");
  printf("\n-------------------------------------\n");
  Venda novaVenda;
  char buffer[100];

  //Recebe id Cliente
  while (true) {
    printf("Digite o id do cliente:");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int tamanho = strlen(buffer);

    bool soDigitos = true;
    //Verifica se só foram digitados números
    for (int i = 0; i < tamanho; i++){
      if (!isdigit(buffer[i])){
        soDigitos = false;
        break;
      } 
    }
    if (!soDigitos) {
      printf("Erro: O id do cliente deve conter apenas números.\n");
      continue;
    }

    float idCliente = atoi(buffer);
    bool clienteExiste = false;
    //Verificar se id do cliente realmente existe
    for(int i = 0; i < qtdeClientes; i++){
      if(listaClientes[i].id == idCliente){
        clienteExiste = true;
        break;
      }
    }

    if(!clienteExiste){
      printf("\nErro: Cliente com id %d não existe\n", idCliente);
      continue;
    }

    novaVenda.idCliente = idCliente;
    break;
  }

  //Recebe id do vendedor e verifica se existe
  while (true) {
    printf("Digite o id do vendedor:");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int tamanho = strlen(buffer);

    bool soDigitos = true;
    //Verifica se só foram digitados números
    for (int i = 0; i < tamanho; i++){
      if (!isdigit(buffer[i])){
        soDigitos = false;
        break;
      } 
    }
    if (!soDigitos) {
      printf("Erro: O id do vendedor deve conter apenas números.\n");
      continue;
    }

    int idVendedor = atoi(buffer);
    bool vendedorExiste = false;
    //Verificar se id do cliente realmente existe
    for(int i = 0; i < qtdeVendedores; i++){
      if(listaVendedores[i].id == idVendedor){
        vendedorExiste = true;
        break;
      }
    }

    if(!vendedorExiste){
      printf("\nErro: Vendedor com id %d não existe\n", idVendedor);
      continue;;
    }

    novaVenda.idVendedor = idVendedor;
    break;
  }

  while(true){
    printf("Digite o valor da venda: R$");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int tamanho = strlen(buffer);

    int posPonto = 0;

    for(int i =0; i < tamanho; i++){
      if(buffer[i] == '.'){
        posPonto = i;
      }
    }

    bool soDigitos = true;
    //Verifica se só foram digitados números
    for (int i = 0; i < tamanho; i++){
      if (!isdigit(buffer[i])){
        if(!(i == posPonto)){
          soDigitos = false;
          break;
        }
      } 
    }
    if (!soDigitos) {
      printf("Erro: O id do vendedor deve conter apenas números.\n");
      continue;
    }

    int valorVenda = atof(buffer);
    if(valorVenda <= 0){
      printf("Erro: digite uma valor válido (acima de R$0.00)");
      continue;
    }    

    novaVenda.total = valorVenda;
    break;
  }

  //Atribui id a venda
  novaVenda.id = *idProximaVenda;
  (*idProximaVenda)++;

  //Realoca a memória
  int novaQtde = (*qtdeVendas) + 1;
  Venda *novo = realloc(*listaVendas, novaQtde * sizeof(Venda));
  //Se nãa for possúvel realocar a memória retorna erro ao usuário
  if (novo == NULL) {
    printf("Erro: falha ao adicionar nova venda.\n");
    return;
  }
  *listaVendas = novo;
  (*listaVendas)[*qtdeVendas] = novaVenda;
  (*qtdeVendas)++;
  printf("Venda lançada com sucesso! ID: %d\n", novaVenda.id);
}