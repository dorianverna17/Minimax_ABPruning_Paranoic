#include "cerinta1.h"

// Functie care imi initializeaza radacina
// arborelui (starea de pe tabla ce este data
// ca input). Aici aloc dinamic nodul de arbore,
// iar starea de pe tabla este codificata intr-o
// matrice de int-uri. Aceasta matrice o alocata
// dinamic. 1 reprezinta B, iar -1 reprezinta R,
// iar 0 reprezinta un patrat gol.
void init_root(tree_node **root, FILE *file_in,
	int row, int col)
{
	int nr1 = 0, nr2 = -1, i;
	char str[100];

	*root = malloc(sizeof(tree_node));
	(*root)->next = NULL;
	(*root)->prev = NULL;
	(*root)->parent = NULL;
	(*root)->child = NULL;
	(*root)->value = malloc(row * sizeof(int *));
	for (i = 0; i < row; i++)
		(*root)->value[i] = malloc(col * sizeof(int));
	fscanf(file_in, "%s", str);
	while (nr1 != row - 1 || nr2 != col - 1) {
		nr2++;
		if (nr2 == col) {
			nr1++;
			nr2 = 0;
		}
		if (strcmp(str, "B") == 0)
			(*root)->value[nr1][nr2] = 1;
		else if (strcmp(str, "R") == 0)
			(*root)->value[nr1][nr2] = -1;
		else
			(*root)->value[nr1][nr2] = 0;
		fscanf(file_in, "%s", str);
	}
}

// Functie de afisare a unui nod
// Functia preia nodul, ia matricea corespunzatoare
// si o decodifica si realizeaza scrierea in fisier
// a nodului
void afisare_nod(tree_node *root, int row, int col,
	int k, FILE *file_out)
{
	int i, j, h;

	for (i = 0; i < row; i++) {
		for (h = 1; h <= k; h++)
			fprintf(file_out, "\t");
		if (root->value[i][0] == 1)
			fprintf(file_out, "%c", 'B');
		else if (root->value[i][0] == -1)
			fprintf(file_out, "%c", 'R');
		else
			fprintf(file_out, "%c", '-');
		for (j = 1; j < col; j++)
			if (root->value[i][j] == 1)
				fprintf(file_out, " %c", 'B');
		else if (root->value[i][j] == -1)
			fprintf(file_out, " %c", 'R');
		else
			fprintf(file_out, " %c", '-');
		fprintf(file_out, "\n");
	}
}

// Functie care verifica daca un nod reprezinta
// o stare terminala a jocului (daca este un nod
// frunza).
int verificare_frunza(tree_node *root, int row,
	int col, int player)
{
	int i, j;

	for (i = 0; i < row - 3; i++)
		for (j = 0; j < col - 3; j++)
			if (root->value[i][j] == player &&
				root->value[i + 1][j + 1] == player &&
				root->value[i + 2][j + 2] == player &&
				root->value[i + 3][j + 3] == player)
				return 1;
	for (i = 0; i < row - 3; i++)
		for (j = 3; j < col; j++)
			if (root->value[i][j] == player &&
				root->value[i + 1][j - 1] == player &&
				root->value[i + 2][j - 2] == player &&
				root->value[i + 3][j - 3] == player)
				return 1;
	for (i = 0; i < row; i++)
		for (j = 0; j < col - 3; j++)
			if (root->value[i][j] == player &&
				root->value[i][j + 1] == player &&
				root->value[i][j + 2] == player &&
				root->value[i][j + 3] == player)
				return 1;
	for (i = 0; i < row - 3; i++)
		for (j = 0; j < col; j++)
			if (root->value[i][j] == player &&
				root->value[i + 1][j] == player &&
				root->value[i + 2][j] == player &&
				root->value[i + 3][j] == player)
				return 1;
	int nr = 0;

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			if (root->value[i][j] != 0)
				nr++;
	if (nr == row * col)
		return 1;
	return 0;
}

// Functie care initializeaza un nod oarecare
// Aloca memorie pentru acesta
void init_nod(tree_node **root, int row, int col)
{
	int i;

	*root = malloc(sizeof(tree_node));
	(*root)->next = NULL;
	(*root)->prev = NULL;
	(*root)->parent = NULL;
	(*root)->child = NULL;
	(*root)->value = malloc(row * sizeof(int *));
	for (i = 0; i < row; i++)
		(*root)->value[i] = malloc(col * sizeof(int));
}

// Functie care verifica daca o anumita stare
// poate exista pe tabla de joc si returneaza
// un pointer la acel nod in cazul in care acesta
// exista (este generat in cadrul acestei functii)
// Daca nu poate exista, atunci se returneaza NULL
tree_node *generare_nod(tree_node *root, int row,
	int col, int coloana, int player)
{
	int i, j, ok = -1;
	tree_node *new_node;

	for (i = 0; i < row; i++) {
		if (root->value[i][coloana] == 0)
			ok = i;
	}
	if (ok != -1) {
		init_nod(&new_node, row, col);
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				new_node->value[i][j] = root->value[i][j];
			new_node->value[ok][coloana] = player;
		return new_node;
	} else
		return NULL;
}

// Functie care imi insereaza un nod in arbore
// Arborele este implementat pe modelul leftChild
// rightSibling
void inserare_nod(tree_node **root, tree_node **new_node,
	int row, int col, int i)
{
	if (i == 0) {
		(*root)->child = *new_node;
		(*new_node)->parent = (*root);
	} else {
		tree_node *it = (*root)->child;

		while (it->next)
			it = it->next;
		it->next = *new_node;
		(*new_node)->prev = it;
	}
}

// Functia care imi genereaza recursiv arborele
void generare_arbore(tree_node **root, int row,
	int col, int player)
{
	int i, nr = 0;

	if (verificare_frunza(*root, row, col, -player))
		return;
	for (i = 0; i < col; i++) {
		tree_node *new_node = generare_nod(*root, row,
			col, i, player);
		if (new_node == NULL)
			continue;
		else {
			inserare_nod(root, &new_node, row, col, nr);
			generare_arbore(&new_node, row, col, -player);
			nr++;
		}
	}
}

// Functia care imi afiseaza recursiv arborele
void afisare_arbore(tree_node *root, int row, int col,
	int player, int k, FILE *file_out)
{
	int i = 0;
	tree_node *it = root;

	while (it) {
		afisare_nod(it, row, col, k, file_out);
		fprintf(file_out, "\n");
		if (it->child)
			afisare_arbore(it->child, row, col,
				-player, k + 1, file_out);
		it = it->next;
	}
}

// Functie care imi elibereaza memoria unui nod
void eliberare_nod(tree_node **root, int row, int col)
{
	int i;

	for (i = 0; i < row; i++)
		free((*root)->value[i]);
	free((*root)->value);
	free(*root);
}

// Functie care imi elibereaza memoria arborelui in mod
// recursiv. Aceasta apeleaza functia eliberare_nod
void eliberare_memorie(tree_node **root, int row, int col)
{
	tree_node *it, *aux;
	int i;

	if ((*root)->child) {
		it = (*root)->child;
		eliberare_memorie(&it, row, col);
	}
	if ((*root)->next)
		eliberare_memorie(&(*root)->next, row, col);
	eliberare_nod(root, row, col);
}

// Functia care este apelata in main.c
// Aceasta contine in general doar apeluri de functii
// si declarari de variabile
void cerinta1(FILE *file_in, FILE *file_out)
{
	tree_node *root;
	int row, col, i, player;
	char Max[2];

	fscanf(file_in, "%d%d", &row, &col);
	fscanf(file_in, "%s", Max);
	if (strcmp(Max, "R") == 0)
		player = -1;
	else
		if (strcmp(Max, "B") == 0)
			player = 1;
		else
			player = 0;
	init_root(&root, file_in, row, col);
	generare_arbore(&root, row, col, player);
	afisare_arbore(root, row, col, player, 0, file_out);
	eliberare_memorie(&root, row, col);
}
