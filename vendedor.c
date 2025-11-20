#include "vendedor.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void carregarVendedores(Vendedor **lista, int *qtdeVendedor){
  //Abrir arquivo para leitura
  FILE *arqVendedores = fopen("vendedores.dat", "rb");

  if(arqVendedores == NULL){
    *qtdeVendedor = 0;
    *lista = NULL;
    printf("\nArquivo vendedores.dat não encontrado. Inniciando lista vazia.\n");
    return;
  }

  Vendedor vendedorBuffer;
  //Enquanto tiver cliente, vai ler o arquivo
  while(fread(&vendedorBuffer,sizeof(Vendedor),1, arqVendedores) == 1){
    int qtdeAtualizada = *qtdeVendedor + 1;
    //Realoca memória para caber a nova quantidade de vendedores
    Vendedor *novaLista = realloc(*lista, sizeof(Vendedor) * qtdeAtualizada);

    if(novaLista == NULL){
      printf("Erro: não foi possível realocar a memória.\n");
      fclose(arqVendedores);
      return;
    }
    //Atualiza lista
    *lista = novaLista;
    (*lista)[*qtdeVendedor] = vendedorBuffer;
    *qtdeVendedor = qtdeAtualizada;    
  }

  //Fechar o arquivo
  fclose(arqVendedores);
  printf("\n%d vendedores carregados com sucesso.\n", *qtdeVendedor);
}

void salvarVendedores(Vendedor *lista, int qtdeVendedores){
  //Abrir arquivo
  FILE *arqVendedores = fopen("vendedores.dat", "wb");

  //Caso não consiga abrir o arquivo, retorna um erro
  if(arqVendedores == NULL){
    printf("Erro: Não foi possível abrir o arquivo vendedores.dat\n");
    return;
  }

  //Escreve todos os vendedores no arquivo
  for(int i =0; i< qtdeVendedores; i++){
    fwrite(&lista[i], sizeof(Vendedor), 1, arqVendedores);
  }

  //Fecha o arquvio
  fclose(arqVendedores);
  printf("\n%d vendedores salvos com sucesso.\n", qtdeVendedores);
}

void listarVendedores(Vendedor *lista, int qtdeVendedores){
  if(qtdeVendedores == 0 || lista == NULL){
    printf("\nNenhum vendedor cadastrado.\n");
    return;
  }

  printf("\n--- Lista de vendedores (%d) ---\n", qtdeVendedores);
  for(int i = 0; i < qtdeVendedores; i++){
    Vendedor *vendedor = &lista[i];
    printf("ID: %d\n", vendedor->id);
    printf("Nome: %s\n", vendedor->nome);
    printf("CPF: %s\n", vendedor->cpf);
    printf("Email: %s\n", vendedor->email);
    printf("Telefone: %s\n", vendedor->telefone);
    printf("-------------------------------\n");
  }
}

void cadastrarVendedor(Vendedor **lista, int *qtdeVendedor, int *proximoIdVendedor){
  printf("\n-------------------------------------\n");
  printf("CADASTRAR VENDEDOR");
  printf("\n-------------------------------------\n");
  Vendedor novoVendedor;
  char buffer[100];

  //Recebe nome
  while (true){
    printf("Digite o nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    //Verifica se nome é válido
    if(strlen(buffer) > 5){
      strncpy(novoVendedor.nome, buffer, sizeof(novoVendedor.nome)-1);
      novoVendedor.nome[sizeof(novoVendedor.nome)-1] = '\0';
      break;
    } else {
      printf("Erro: O nome deve ter mais de 5 caracteres. Tente novamente.\n");
    }
  }

  // Lê CPF/CNPJ
  while (true) {
    printf("Digite o CPF (apenas números): ");
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
        printf("Erro: o CPF deve conter apenas números. Tente novamente.\n");
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
        strncpy(novoVendedor.cpf, buffer, sizeof(novoVendedor.cpf)-1);
        novoVendedor.cpf[sizeof(novoVendedor.cpf)-1] = '\0';
        break;
      } else {
        printf("Erro: CPF inválido. Digite novamente\n");
        continue;
      }
    } else {
      printf("Erro: Digite um CPF (11 dígitos).\n");
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
    strncpy(novoVendedor.email, buffer, sizeof(novoVendedor.email)-1);
    novoVendedor.email[sizeof(novoVendedor.email)-1] = '\0';
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

      strncpy(novoVendedor.telefone, buffer, sizeof(novoVendedor.telefone)-1);
      novoVendedor.telefone[sizeof(novoVendedor.telefone)-1] = '\0';
      break;
  }

  //Atribui próxido ID ao Cliente
  novoVendedor.id = *proximoIdVendedor;
  (*proximoIdVendedor)++;

  //Realoca a memória
  int novaQtde = (*qtdeVendedor) + 1;
  Vendedor *novo = realloc(*lista, novaQtde * sizeof(Vendedor));
  //Se nãa for possúvel realocar a memória retorna erro ao usuário
  if (novo == NULL) {
    printf("Erro: falha ao adicionar novo vendedor.\n");
   return;
  }
  *lista = novo;
  (*lista)[*qtdeVendedor] = novoVendedor;
  (*qtdeVendedor)++;
  printf("Vendedor cadastrado com sucesso! ID: %d\n", novoVendedor.id);
}