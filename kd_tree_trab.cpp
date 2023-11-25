#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include"TADKDTREE.h" 

int main()
{
	kdTree *arv=NULL; //declarando arvore
	lTree *alePonts=NULL; //declarando lista de pontos
	geraPontos(&alePonts,20); //gerando pontos
	insertBalancedKdTree(&arv,alePonts,0); //inserindo na arvore de forma balanceada
	exibeArv(arv); // exibindo a arvore deitada
}
