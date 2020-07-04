#ifndef __TREE_H__
#define __TREE_H__

// definirea structurii nodului de arbore
// folosit la task-ul 1
typedef struct tree_node {
	struct tree_node *next;
	struct tree_node *prev;
	struct tree_node *parent;
	struct tree_node *child;
	int **value;
	int value_min;
	int alpha;
	int beta;
} tree_node;

// definirea structurii nodului de arbore
// folosit la bonus
typedef struct tree_node_para {
	struct tree_node_para *next;
	struct tree_node_para *prev;
	struct tree_node_para *parent;
	struct tree_node_para *child;
	int *value;
} tree_node_para;

#endif /* __TREE_H__ */
