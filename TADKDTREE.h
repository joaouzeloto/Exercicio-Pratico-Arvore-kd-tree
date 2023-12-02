#define TF 2

struct listtree
{
	int cord[TF];
	struct listtree *prox,*ant;
};
typedef struct listtree lTree;

struct kdtree
{
	int cord[TF];
	struct kdtree *esq, *dir;
};
typedef struct kdtree kdTree;

int sortearNumero() {
    int numeroAleatorio = rand() % 50;
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

void insereOrdD(lTree **a,lTree *cop,int d)
{
	int i;
	lTree *aux = *a,*anterior=NULL;
	lTree *novo = (lTree*) malloc(sizeof(lTree));
	for(i=TF-1;i>-1;i--)
		novo->cord[i] = cop->cord[i];
	novo->prox = novo->ant =NULL;
	if(*a==NULL)
	{
		*a = novo;
	}
	else
	{
		while(aux!=NULL&&aux->cord[d]>novo->cord[d])
		{
			anterior = aux;
			aux = aux->prox;
		}	
		if(anterior==NULL)
		{
			novo->prox = aux;
			aux->ant = novo;
			*a = novo;
		}
		else
		{
			if(aux==NULL)
			{
				anterior->prox = novo;
				novo->ant = anterior;
			}
			else
			{
				novo->ant = anterior;
				novo->prox = aux;
				anterior->prox = novo;
				aux->ant = novo;
			}
		}	
	}
	
}

void insereLKD(lTree **l,kdTree *kd)
{
	lTree *novo = (lTree*) malloc(sizeof(lTree));
	int i;
	for(i=0;i<TF;i++)
		novo->cord[i] = kd->cord[i];
	if(*l==NULL)
		*l = novo;
	else
	{
		novo->prox = *l;
		*l = novo;
	}
}

void inserePontD(lTree *l,lTree **ori,lTree *limite,int d)
{
	lTree *aux = l;
	while(aux!=NULL&&aux!=limite)
	{
		insereOrdD(&*ori,aux,d);
		aux = aux->prox;
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

kdTree* Cria_no(int xY[TF])
{
	int sup = TF-1;
	kdTree *novo = (kdTree*) malloc(sizeof(kdTree));
	for(;sup>-1;sup--)
		novo->cord[sup] = xY[sup];
	novo->esq = novo->dir = NULL;
	return novo;
	
}

void insereKdTree(kdTree **raiz,int xY[TF],int n)
{
	int d;
	if (*raiz==NULL)
		*raiz = Cria_no(xY);
	else
	{
		d = n%TF; 
		if (xY[d] < (*raiz)->cord[d])
			insereKdTree(&(*raiz)->esq, xY, n+1);
		else
			insereKdTree(&(*raiz)->dir, xY, n+1);
	}
}

int contL(lTree *l)
{
	int i;
	for(i=0;l!=NULL;i++)
	{
		l = l->prox;
	}
	return i-1;
}

lTree* achaMeio(lTree *l,int j)
{
	int i;
	for(i=0;i!=j;i++)
	{
		l = l->prox;
	}
	return l;
}

void insertBalancedKdTree(kdTree **raiz,lTree *l,int n)
{
	int tam = contL(l),d;
	lTree *meio = achaMeio(l,tam/2),*ladoE=NULL,*ladoD=NULL;
	if(tam>0)
	{
		if(*raiz == NULL)
		{
			*raiz = Cria_no(meio->cord);
		}
		d = n%TF;
		printf("\n%d,%d",d,tam);
		inserePontD(l,&ladoE,meio,d); // insere o número restante de pontos da esquerda em outra lista
		inserePontD(meio->prox,&ladoD,NULL,d); // insere o número restante de pontos da direita em outra lista
		insertBalancedKdTree(&(*raiz)->esq,ladoE,n+1); // chama a função passando o lado esquerdo 
		insertBalancedKdTree(&(*raiz)->dir,ladoD,n+1); // chama a função chamando o lado direito
	}
	else
	{
		if(meio!=NULL)
			*raiz = Cria_no(meio->cord);
	}
}

void exibeArv(kdTree *a)
{
	int i;
	static int n = -1;
	if( a==NULL) return;
	n++;
	exibeArv(a->dir);
	for(i=0; i<5*n;i++) printf("  ");
	printf(" (%d,%d)\n\n",a->cord[0],a->cord[1]);
	exibeArv(a->esq);
	n--;
}

int medeDistancia(kdTree *kd,int cord[],int n)
{
	int i;
	double f=0,d;
	for(i=0;i<TF;i++)
	{
		d = (kd->cord[i])-cord[i];
		d = pow(d,2);
		f = f + d;
	}
	if(sqrt(f) <= n)
	{
		return 1;	
	}
	else
		return 0;
}

void distanciaEuclidiana(lTree **l,kdTree *kd,int cord[],int n)
{
	if(kd!=NULL)
	{
		if(medeDistancia(kd,cord,n)==1)
			insereLKD(*&l,kd);
		distanciaEuclidiana(*&l,kd->esq,cord,n);
		distanciaEuclidiana(*&l,kd->dir,cord,n);
	}
}

void exibe(lTree *l)
{
	int i;
	if(l!=NULL)
	{
		printf("\n(%d",l->cord[0]);
		for(i=1;i<TF;i++)
			printf(",%d",l->cord[i]);
		printf(")");
		exibe(l->prox);
	}
}

