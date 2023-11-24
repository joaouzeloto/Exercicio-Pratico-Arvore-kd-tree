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
	struct ktree *esq, *dir;
};
typedef struct kdtree kdTree;

