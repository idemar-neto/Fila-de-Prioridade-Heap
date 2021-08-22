#include "filaDePrioridade.c"

void inserir(PFILA f){
	int id;
	float prioridade;
  scanf("%i",&id);
  scanf("%f",&prioridade);
  if(inserirElemento(f, id, prioridade)) printf("Funcao inserir retornou true, foi adicionado o elemento de id %i com prioridade %f\n", id, prioridade);
  else printf("Funcao inserir retornou false\n");
  exibirLog(f);
  }

void aumentar(PFILA f){
	int id;
  float prioridade;
  scanf("%i",&id);
  scanf("%f",&prioridade);
  if(aumentarPrioridade(f, id, prioridade)) printf("Funcao aumentar retornou true, foi modificado o elemento de id %i com prioridade %f\n", id, prioridade);
  else printf("Funcao aumentar retornou false\n");
  exibirLog(f);
}

void reduzir(PFILA f){
	int id;
  float prioridade;
  scanf("%i",&id);
  scanf("%f",&prioridade);
  if(reduzirPrioridade(f, id, prioridade)) printf("Funcao reduzir retornou true, foi modificado o elemento de id %i com prioridade %f\n", id, prioridade);
  else printf("Funcao reduzir retornou false\n");
  exibirLog(f);
}

void consultar(PFILA f){
 	float p;
 	int id;
  scanf("%i",&id);
  if(consultarPrioridade(f, id, &p)) printf("Funcao consultar retornou true, %i com prioridade %f \n",id, p);
  else printf("Funcao consultar retornou false\n");
}

void excluir(PFILA f){
	PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia\n");
  exibirLog(f);
}

void help(){
  printf("Comandos validos: \n");
  printf("   i <id do elemento> <prioridade> : inserir elemento\n");
  printf("   a <id do elemento> <nova prioridade>: aumentar prioridade de um elemento\n");
  printf("   r <id do elemento> <nova prioridade>: reduzir prioridade de um elemento\n");
  printf("   c <id do elemento> : consultar prioridade de um elemento\n");
  printf("   e : excluir elemento de maior prioridade\n");
  printf("   h : ajuda\n");
  printf("   q : sair\n");
}


int main(){
  printf("Insira o numero de elementos na lista:");
  int max;
  scanf("%i",&max);
  PFILA f = criarFila(max);
  exibirLog(f);
	help();
  int id;
  float prioridade;
  char comando = ' ';
  scanf("%c",&comando);
  while (comando != 'q'){
    switch (comando) {
      case 'i' : inserir(f); break;
      case 'a' : aumentar(f); break;
      case 'r' : reduzir(f); break;
      case 'c' : consultar(f); break;
      case 'e' : excluir(f); break;
      case 'h' : help(); break;

      default: {while (comando != '\n') scanf("%c",&comando);}break;
    }
    scanf("%c",&comando);
  } 

  return 0;
}
