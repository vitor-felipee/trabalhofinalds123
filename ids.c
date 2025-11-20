#include "ids.h"
#include <stdio.h>

void carregarIds(int *cliente, int *vendedor, int *venda){
  FILE *arqIds = fopen("ids.dat", "rb");

  //Inicia váriaiveis de ID, se não existir arquivo ids.dat
  if(arqIds == NULL){
    *cliente = 1;
    *vendedor = 1;
    *venda = 1;
    printf("Arquivo de registro de ID não existe, iniciando os IDS...");
    return;
  }

  int ids[3];
  for(int i = 0; i < 3; i++){
    ids[i] = 1;
  }

  int lidos = fread(ids, sizeof(int), 3, arqIds);

  if (lidos != 3){
    for(int i = 0; i < 3; i++){
     ids[i] = 1;
    }
    *cliente = ids[0];
    *vendedor = ids[1];
    *venda = ids[2];
    printf("\nErro: não foi possível ler os IDS. Iniciados em 1.\n");
  } else {
    *cliente = ids[0];
    *vendedor = ids[1];
    *venda = ids[2];
    printf("\nPróximos Ids carregados com sucesso");
  }
  fclose(arqIds);
}

void salvarIds(int cliente, int vendedor, int venda){
  FILE *arqIds= fopen("ids.dat", "wb");

  if(arqIds == NULL){
    printf("Erro: Não foi possível abrir o arquivo ids.dat\n");
    return;
  }

  int ids[3];
  ids[0] = cliente;
  ids[1] = vendedor;
  ids[2] = venda;

  fwrite(ids, sizeof(int), 3, arqIds);

  //Fecha o arquivo
  fclose(arqIds);
  printf("\nIds salvos com sucesso.\n");
}
