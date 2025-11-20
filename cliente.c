#include "cliente.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void carregarClientes(Cliente **lista, int *qtdeClientes){
  //Abrir arquivo para leitura
  FILE *arqClientes = fopen("clientes.dat", "rb");

  if(arqClientes == NULL){
    *qtdeClientes = 0;
    *lista = NULL;
    printf("\nArquivo clientes.dat não encontrado. Inniciando lista vazia.\n");
    return;
  }

  Cliente clienteBuffer;
  //Enquanto tiver cliente, vai ler o arquivo
  while(fread(&clienteBuffer,sizeof(Cliente),1, arqClientes) == 1){
    int qtdeAtualizada = *qtdeClientes + 1;
    //Realoca memória para caber a nova quantidade de clientes
    Cliente *novaLista = realloc(*lista, sizeof(Cliente) * qtdeAtualizada);

    if(novaLista == NULL){
      printf("Erro: não foi possível realocar a memória.\n");
      fclose(arqClientes);
      return;
    }
    //Atualiza lista
    *lista = novaLista;
    (*lista)[*qtdeClientes] = clienteBuffer;
    *qtdeClientes = qtdeAtualizada;    
  }

  //Fechar o arquivo
  fclose(arqClientes);
   printf("\n%d clientes carregados com sucesso.\n", *qtdeClientes);
}

void salvarClientes(Cliente *lista, int qtdeClientes){
  //Abrir arquivo
  FILE *arqClientes = fopen("clientes.dat", "wb");

  //Caso não consiga abrir o arquivo, retorna um erro
  if(arqClientes == NULL){
    printf("Erro: Não foi possível abrir o arquivo clientes.dat\n");
    return;
  }

  //Escreve todos os cliente no arquivo
  for(int i =0; i< qtdeClientes; i++){
    fwrite(&lista[i], sizeof(Cliente), 1, arqClientes);
  }

  //Fecha o arquvio
  fclose(arqClientes);
  printf("\n%d clientes salvos com sucesso.\n", qtdeClientes);
}

void listarClientes(Cliente *lista, int qtdeClientes){
  if(qtdeClientes == 0 || lista == NULL){
    printf("\nNenhum Cliente cadastrado.\n");
    return;
  }

  printf("\n--- Lista de clientes (%d) ---\n", qtdeClientes);
  for(int i = 0; i < qtdeClientes; i++){
    Cliente *cliente = &lista[i];
    printf("ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);
    printf("CPF/CNPJ: %s\n", cliente->cnpjCpf);
    printf("Email: %s\n", cliente->email);
    printf("Telefone: %s\n", cliente->telefone);
    printf("-------------------------------\n");
  }
}

void cadastrarCliente(Cliente **lista, int *qtdeClientes, int *proximoIdCliente){
  printf("\n-------------------------------------\n");
  printf("CADASTRAR CLIENTE");
  printf("\n-------------------------------------\n");
  Cliente novoCliente;
  char buffer[100];

  //Recebe nome
  while (true){
    printf("Digite o nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    //Verifica se nome é válido
    if(strlen(buffer) > 5){
      strncpy(novoCliente.nome, buffer, sizeof(novoCliente.nome)-1);
      novoCliente.nome[sizeof(novoCliente.nome)-1] = '\0';
      break;
    } else {
      printf("Erro: O nome deve ter mais de 5 caracteres. Tente novamente.\n");
    }
  }

  // Lê CPF/CNPJ
  while (true) {
    printf("Digite o CPF/CNPJ (apenas números): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int tamanho = strlen(buffer);

    // Verifica se há apenas digitos
    bool soDigitos = true;
    for (int i = 0; i < tamanho; i++){
      if (!isdigit(buffer[i])){
        soDigitos = false;
      } 
    }
    //Se não tiver apenas digitos, vai retornar um erro
    if (!soDigitos) {
        printf("Erro: CPF/CNPJ deve conter apenas números. Tente novamente.\n");
        continue;
    }

    //Verifica se o número é um CPF
    if (tamanho == 11) {
      int dig[11];
      //Guarda todos os números do CPF em um array
      for (int i = 0; i < 11; i++){
        dig[i] = buffer[i] - '0';
      }
      bool iguais = true;
      //Verifica se os diggtios são iguais
      for (int i = 1; i < 11; i++){
        if (dig[i] != dig[0]){
          iguais = false;
          break;
        }
      } 
      if (iguais) { printf("Erro: CPF inválido (todos os digitos iguais).\n"); continue; }
      //Cálculo do primeiro digitos verificador do CPF
      int soma = 0;
      for (int i = 0; i < 9; i++){
        soma += dig[i] * (10 - i);
      }
      int resto = soma % 11;
      int d1 = 0;
      if(resto<2){
        d1=0;
      } else{
        d1 = 11-resto;
      }

      //Cálculo do segundo digito verificador
      soma = 0;
      for (int i = 0; i < 9; i++){
        soma += dig[i] * (11 - i);
       }
      soma += d1 * 2;
      resto = soma % 11;
      int d2;
      if (resto < 2){
        d2 = 0;
      } else {
        d2 = 11 -resto;
      }

      if (d1 == dig[9] && d2 == dig[10]) {
        strncpy(novoCliente.cnpjCpf, buffer, sizeof(novoCliente.cnpjCpf)-1);
        novoCliente.cnpjCpf[sizeof(novoCliente.cnpjCpf)-1] = '\0';
        break;
      } else {
        printf("Erro: CPF inválido. Digite novamente\n");
        continue;
      }
    } else if (tamanho == 14) { // Verifica se número é um CNPJ
      int dig[14];
      //Guarda os digitos do CNPj em um array
      for (int i = 0; i < 14; i++){
        dig[i] = buffer[i] - '0';
      }
      //Verifica se todos os dígityos são iguais
      bool iguais = true;
      for (int i = 1; i < 14; i++){
        if (dig[i] != dig[0]){ 
          iguais = false;
          break;
        }
      }
      if (iguais) { 
        printf("Erro: CNPJ invalido (todos os digitos iguais).\n");
        continue;
      }

      //Verifica primeiro digito de verificação do CNPJ
      int peso1[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
      int soma = 0;
      for (int i = 0; i < 12; i++){
        soma += dig[i] * peso1[i];
      }
      int resto = soma % 11;
      int d1;
      if (resto < 2){
        d1 = 0;
      } else {
        d1 = 11-resto;
      }

      //Verifica segundo digito de verificação do CNPJ
      int peso2[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};
      soma = 0;
      for (int i = 0; i < 13; i++){
        soma += dig[i] * peso2[i];
      }
      resto = soma % 11;
      int d2;
      if(resto<2){
        d2 = 0;
      } else {
        d2 = 11 -resto;
      }

      if (d1 == dig[12] && d2 == dig[13]) {
        strncpy(novoCliente.cnpjCpf, buffer, sizeof(novoCliente.cnpjCpf)-1);
        novoCliente.cnpjCpf[sizeof(novoCliente.cnpjCpf)-1] = '\0';
        break;
      } else {
        printf("Erro: CNPJ inválido. Digite novamente.\n");
        continue;
      }
    } else {
      printf("Erro: Digite um CPF (11 dígitos) ou CNPJ (14 digitos).\n");
    }
  }

  // Recebe EMAIL
  while (true) {
    printf("Digite o email: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int tamanho = strlen(buffer);

    //Verifica se email é muito curto, caso sim declara como inválido
    if (tamanho < 6) { 
      printf("Erro: Email muito curto. Tente novamente.\n");
      continue; 
    }

    //Verifica se email começa com caractere especial (@ ou .)
    if (buffer[0] == '@' || buffer[0] == '.'){
      printf("Erro: Email não pode começar com @ ou .\n");
      continue;
    }

    //Verifica se email termina com caractere especial (@ ou .)
    if (buffer[tamanho - 1] == '.' || buffer[tamanho - 1] == '@'){
      printf("Erro: Email não pode terminar com @ ou .\n");
      continue;
    }

    int arroba = 0;
    int posicaoArroba = -1;

    //Verifica quantos arrobas tem no email, e a posicao dele
    for (int i = 0; i < tamanho; i++){ 
      if (buffer[i] == '@'){
        arroba++;
        posicaoArroba = i;
      }
    }
    //Verifica se o email contem apenas um arroba
    if (arroba != 1){
      printf("Erro: Email deve conter um @.\n");
      continue; 
    }

    //Verifica se tem pelo menos um ponto após o arroba
    bool pontoDepois = false;
    for (int i = posicaoArroba + 1; i < tamanho; i++){
      if (buffer[i] == '.') {
        pontoDepois = true;
        break;
      }
    }
    //Caso não tenha nenhum ponto, retorna erro.
    if (!pontoDepois) { 
      printf("Erro: Email deve conter um . após o @.\n");
      continue; 
    }

    //Guarda 50 caracteres no campo email
    strncpy(novoCliente.email, buffer, sizeof(novoCliente.email)-1);
    novoCliente.email[sizeof(novoCliente.email)-1] = '\0';
    break;
  }

  // Recebe o TELEFONE
  while (true) {
      printf("Digite o telefone (11 digitos, ex: 41999887766): ");
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = '\0';
      int tamanho = strlen(buffer);
      //Verifica se foram digitados apenas 11 Dígitos
      if (tamanho != 11) {
        printf("Erro: O telefone deve conter exatamente 11 dígitos.\n");
        continue; 
      }
      bool soDigitos = true;
      //Verifica se só foram digitados números
      for (int i = 0; i < 11; i++){
        if (!isdigit(buffer[i])){
          soDigitos = false;
          break;
        } 
      }
      if (!soDigitos) {
        printf("Erro: O telefone deve conter apenas números.\n");
        continue;
      }

      strncpy(novoCliente.telefone, buffer, sizeof(novoCliente.telefone)-1);
      novoCliente.telefone[sizeof(novoCliente.telefone)-1] = '\0';
      break;
  }

  //Atribui próxido ID ao Cliente
  novoCliente.id = *proximoIdCliente;
  (*proximoIdCliente)++;

  //Realoca a memória
  int novaQtde = (*qtdeClientes) + 1;
  Cliente *novo = realloc(*lista, novaQtde * sizeof(Cliente));
  //Se nãa for possúvel realocar a memória retorna erro ao usuário
  if (novo == NULL) {
    printf("Erro: falha ao adicionar novo cliente.\n");
   return;
  }
  *lista = novo;
  (*lista)[*qtdeClientes] = novoCliente;
  (*qtdeClientes)++;
  printf("Cliente cadastrado com sucesso! ID: %d\n", novoCliente.id);
}
