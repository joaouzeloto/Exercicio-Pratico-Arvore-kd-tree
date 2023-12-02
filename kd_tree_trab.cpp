#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<math.h>
#include"TADKDTREE.h" 

int main()
{
	int cord[2] = {25,15}; 
	kdTree *arv=NULL; //declarando arvore
	lTree *alePonts=NULL, *valueProx=NULL; //declarando lista de pontos
	geraPontos(&alePonts,20); //gerando pontos
	insertBalancedKdTree(&arv,alePonts,0); //inserindo na arvore de forma balanceada
	exibeArv(arv); // exibindo a arvore deitada
	distanciaEuclidiana(&valueProx,arv,cord,8); //  mede a distancia entre pontos
	printf("\nCOORDENADAS PROXIMAS A (25,15): ");
	exibe(valueProx); // exibe os pontos proximos
}
