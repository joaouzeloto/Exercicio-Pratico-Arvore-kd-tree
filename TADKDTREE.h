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

void ordenaList(lTree **l,int n)
{
	int d = n%TF,aux[TF],cont=1,i;
	lTree *conj,*prox;
	for(conj=*l;conj!=NULL;conj = conj->prox)
		cont++;
	for(i=0;i<=cont;i++)
	{
		conj = *l;
		while(conj!=NULL)
		{
			prox = conj->prox;
			if(prox!=NULL&&conj->cord[d]>prox->cord[d])
			{
				//aux = prox->cord;
				//prox->cord = conj->cord;
				//conj->cord = aux;
			}
			conj->prox;
		}
	}
}

void insereBalanceado(kdTree **raiz,lTree *corden,int a)
{
	int n=1,d,j;
	lTree *ladoE, *ladoD, *auxC;
	for(auxC = corden;auxC!=NULL;auxC = auxC->prox)
		n++;
	d = n/2;	
	if(n!=1&&d>1)
	{
		auxC = corden;
		for(j=1;j<d;j++)
		{
			inserePont(&ladoE, auxC->cord[0],auxC->cord[1]);
			auxC = auxC ->prox;
		}
		insereKdTree(&*raiz,auxC->cord,0);
		for(j=j+1;j<=n;j++)
		{
			inserePont(&ladoD, auxC->cord[0],auxC->cord[1]);
			auxC = auxC ->prox;
		}
		ordenaList(&ladoE,a);
		ordenaList(&ladoE,a);
	}
}
