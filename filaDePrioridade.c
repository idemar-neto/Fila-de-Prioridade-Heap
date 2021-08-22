/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020294> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <Idemar Burssed dos Santos Neto>             <11857282>       **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
	PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
	res->maxElementos = max;
	res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
	res->heap = (PONT*) malloc(sizeof(PONT)*max);
	int i;
	for (i=0;i<max;i++) {
		res->arranjo[i] = NULL;
		res->heap[i] = NULL;
	}
	res->elementosNoHeap = 0;
	return res;
}

void exibirLog(PFILA f){
	printf("Log [elementos: %i]\n", f->elementosNoHeap);
	PONT atual;
	int i;
	for (i=0;i<f->elementosNoHeap;i++){
		atual = f->heap[i];
		printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
	}
	printf("\n\n");
}

int tamanho(PFILA f){
	int tam = 0;
	
	/* COMPLETAR */
	for(int i=0; i<f->maxElementos; i++){
		if(f->heap[i] != NULL) tam = tam + 1;
	}
	
	return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
	bool res = false;
	
	/* COMPLETAR */
	if(id < 0 || id>=f->maxElementos || f->arranjo[id] != NULL) res = false;
	else{
		PONT i = malloc(sizeof(ELEMENTO));
		f->arranjo[id] = i;
		i->id = id;
		i->prioridade = prioridade;
		for(int j=0; j<f->maxElementos; j++){
			if(f->heap[j]==NULL){
				f->heap[j] = i;
				i->posicao = j;
				f->elementosNoHeap = f->elementosNoHeap+1;
				break;
			}
		}
		aumentarPrioridadeAux2(f, i);
		res=true;
	}
	
	return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
	bool res = false;
	
	/* COMPLETAR */
	PONT end = f->arranjo[id];
	if(id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL || end->prioridade >= novaPrioridade) res=false;
	else{
		end->prioridade = novaPrioridade;
		aumentarPrioridadeAux2(f, end);
		res = true;
	}

	return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
	bool res = false;
	
	/* COMPLETAR */
	PONT end = f->arranjo[id];
	if(id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL || end->prioridade <= novaPrioridade) res=false;
	else{
		end->prioridade = novaPrioridade;
		reduzirPrioridadeAux2(f, end);
		res = true;
	}
	
	return res;
}

PONT removerElemento(PFILA f){
	PONT res = NULL;
	
	/* COMPLETAR */
	if(f->elementosNoHeap == 0) res = NULL;
	else{
		res = f->heap[0];
		int id = res->id;
		f->arranjo[id]=NULL;
		if(f->elementosNoHeap > 1){
			f->heap[0] = f->heap[f->elementosNoHeap-1];
			f->heap[f->elementosNoHeap-1] = NULL;
			f->elementosNoHeap = f->elementosNoHeap-1;
			PONT atual = f->heap[0];
			atual->posicao = 0;
			reduzirPrioridadeAux2(f, atual);
		}else{
			f->heap[0]=NULL;
			f->elementosNoHeap=0;
		}
	}
	
	return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
	bool res = false;
	
	/* COMPLETAR */
	if(id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL) res=false;
	else{
		*resposta = f->arranjo[id]->prioridade;
		res = true;
	}
	
	return res;
}

void aumentarPrioridadeAux2(PFILA f, PONT atual){
		int pos = atual->posicao;
		int pospai;
		if(pos%2 == 0)pospai = (pos/2)-1;
			else pospai = (pos/2);
		if(pospai >= 0){
			PONT pai = f->heap[pospai];
			PONT aux;
			int auxpos;
			if(pai->prioridade < atual->prioridade){
				aux = atual;
				f->heap[pos] = pai;
				f->heap[pospai] = aux;
				atual->posicao = pospai;
				pai->posicao = pos;
				aumentarPrioridadeAux2(f, atual);
			}
		}
}

void reduzirPrioridadeAux2(PFILA f, PONT atual){
		int pos = atual->posicao;
		int pose = 2*pos+1;
		int posd = 2*pos+2;
			
			PONT e;
			if(pose <= f->elementosNoHeap) e = f->heap[pose];
			else e = NULL;
			
			PONT d;
			if(posd <= f->elementosNoHeap) d= f->heap[posd];
			else d = NULL;
			
			PONT maior;
			int posmaior;
			
			if(e == NULL && d==NULL) return;
			if(d==NULL){
				maior = e;
				posmaior = pose;
			}else{
				if(e->prioridade > atual->prioridade){
					maior = e;
					posmaior = pose;
				}else{
					maior = atual;
					posmaior = pos;
				}if(d->prioridade > maior->prioridade){
						maior = d;
						posmaior = posd;
					}
			}

			PONT aux;
			int auxpos;
			if(maior->prioridade > atual->prioridade){
				aux = atual;
				f->heap[pos] = maior;
				f->heap[posmaior] = aux;
				atual->posicao = posmaior;
				maior->posicao = pos;
				reduzirPrioridadeAux2(f, atual);
			}
}   