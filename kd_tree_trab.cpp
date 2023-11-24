#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include"TADKDTREE.h"

int sortearNumero() {
    int numeroAleatorio = rand() % 600;
	return numeroAleatorio;
}

void insereOrd(lTree **a,lTree **b)
{
	lTree *aux = *a,*anterior=NULL;
	while(aux!=NULL&&aux->cord[0]<(*b)->cord[0])
	{
		anterior = aux;
		aux = aux->prox;
	}	
	if(anterior==NULL)
	{
		(*b)->prox = aux;
		aux->ant = *b;
		*a = *b;
	}
	else
	{
		if(aux==NULL)
		{
			anterior->prox = *b;
			(*b)->ant = anterior;
		}
		else
		{
			(*b)->ant = anterior;
			(*b)->prox = aux;
			anterior->prox = *b;
			aux->ant = *b;
		}
	}
	
}

void inserePont(lTree **l,int x,int y)
{
	lTree *novo = (lTree*) malloc(sizeof(lTree));
	novo->cord[0] = x;
	novo->cord[1] = y;
	novo->prox = novo->ant = NULL;
	if(*l==NULL)
	{
		*l = novo;
	}
	else
	{
		insereOrd(&*l,&novo);
	}
}

void geraPontos(lTree **l,int nLimite)
{
	int i;
	for(i=0;i<nLimite;i++)
		inserePont(&*l,sortearNumero(),sortearNumero());
}

int main()
{
	lTree *alePonts=NULL,*exibe;
	geraPontos(&alePonts,20);	
	exibe = alePonts;
}
