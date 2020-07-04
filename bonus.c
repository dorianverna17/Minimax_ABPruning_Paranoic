#include "bonus.h"

// Functie de initializare a unui nod
// Aceasta este identica cu cea de la
// task-ul 2
void init_node_bonus(tree_node_para **root, int nr_players)
{
	*root = malloc(sizeof(tree_node_para));
	(*root)->next = NULL;
	(*root)->prev = NULL;
	(*root)->parent = NULL;
	(*root)->child = NULL;
	(*root)->value = calloc((nr_players + 1), sizeof(tree_node_para));
}

// Functie de inserare noduri. Aceasta este
// o functie ajutatoare pentru functia de
// generare arbore. Este identica cu functia
// de la task-ul 2
void inserare_noduri_bonus(tree_node_para **root, int nr, int nr_players)
{
	int i;
	tree_node_para *it;

	it = (*root)->child;
	for (i = 0; i < nr; i++) {
		tree_node_para *new_node;

		init_node_bonus(&new_node, nr_players);
		if (it) {
			it->next = new_node;
			new_node->prev = it;
			it = it->next;
		} else {
			(*root)->child = new_node;
			new_node->parent = (*root);
			it = new_node;
		}
	}
}

// Functie ajutatoare pentru cea de genereare arbore
// Este identica cu cea de la task-ul 2
tree_node_para *seek_aux_bonus(tree_node_para *root, int height, int nivel)
{
	tree_node_para *it = root, *aux = NULL;
	int i;

	while (it) {
		if (height == nivel && it->value[0] == 0)
			return it;
		if (it->child && it->value[0] == 0)
			aux = seek_aux_bonus(it->child, height + 1, nivel);
		if (aux)
			return aux;
		it = it->next;
	}
	return NULL;
}

// Functie ajutatoare pentru cea de generare a
// arborelui
void generare_arbore_bonus_helper(tree_node_para **root,
	int nr1, int nr, int size, int size1, char *sep,
	FILE *file_in, int nr_players, int height)
{
	int j, k, i;
	char string[30];
	char *p;
	tree_node_para *it, *aux;

	aux = (*root)->child;
	for (i = 2; i <= height; i++) {
		it = aux;
		nr1 = 0;
		for (j = 1; j <= nr; j++) {
			fscanf(file_in, "%s", string);
			size1 = ftell(file_in);
			if (string[0] == '(') {
				if (strlen(string) > 3) {
					inserare_noduri_bonus(&it,
					atoi(string + 1), nr_players);
					nr1 = nr1 + atoi(string + 1);
				} else {
					inserare_noduri_bonus(&it,
					string[1] - '0', nr_players);
					nr1 = nr1 + string[1] - '0';
				}
				} else {
					(it)->value[0] = 1;
					p = strtok(string, sep);
					if (strlen(p) > 1)
						(it)->value[1] = atoi(p);
					else
						(it)->value[1] = p[0] - '0';
				for (k = 2; k <= nr_players; k++) {
					p = strtok(0, sep);
					if (strlen(p) > 1)
						(it)->value[k] = atoi(p);
					else
						(it)->value[k] = p[0] - '0';
				}
				}
				if (size == size1)
					return;
// Aici calculez valoarea urmatoare a lui it
// Am modificat, la fel ca la task-urile
// anterioare, indentarea la portiunea aceasta,
// checkerul de coding style spunand ca e ok
			if (!(it)->next && j != nr) {
eticheta:;
				while (!(it)->next) {
					while ((it)->prev)
						it = (it)->prev;
				it = (it)->parent;
					}
		if ((it)->next) {
			if ((it)->next->value[0] != 0) {
				it = (it)->next;
				while ((it)->value[0] != 0 &&
				(it)->next)
					(it) = (it)->next;
				if ((it)->value[0] != 0)
					goto eticheta;
				else
					while ((it)->child)
						it = (it)->child;
				if ((it)->value[0] != 0)
					goto yes;
		} else {
			it = (it)->next;
			while ((it)->child)
				it = (it)->child;
yes:;
			while ((it)->value[0] != 0 && (it)->next)
				it = (it)->next;
			if ((it)->value[0] != 0)
				goto eticheta;
				else {
					while ((it)->child)
						it = (it)->child;
					if ((it)->value[0] != 0)
						goto yes;
				}
			}
			} else
				goto eticheta;
		} else
			it = (it)->next;
	}
	nr = nr1;
	aux = seek_aux_bonus(*root, 1, i + 1);
	}
}

// Functie identica cu cea de la task-ul 2.
// Aceasta imi genereaza arborele pe baza
// valorilor pe care le citesc din fisier.
void generare_arbore_bonus(tree_node_para **root,
	FILE *file_in, int height, int size, int nr_players)
{
	int i, j, nr, nr1, size1, nr2, k;
	char str[30], string[10];
	tree_node_para *aux, *it;
	char *sep = "[,]", *p;

	for (i = 1; i <= height; i++) {
		if (i == 1) {
			fscanf(file_in, "%s", str);

			if (str[0] == '(') {
				if (!strlen(str) > 3)
					inserare_noduri_bonus(root,
						str[1] - '0', nr_players);
				else
					inserare_noduri_bonus(root,
						atoi(str + 1), nr_players);
			} else {
				tree_node_para *new_node;

				init_node_bonus(&new_node, nr_players);
				new_node->value[0] = 1;
				p = strtok(str, sep);
				if (strlen(p) > 1)
					new_node->value[1] = atoi(p);
				else
					new_node->value[1] = p[0] - '0';
				for (k = 2; k <= nr_players; k++) {
					p = strtok(0, sep);
					if (strlen(p) > 1)
						new_node->value[k] = atoi(p);
					else
						new_node->value[k] = p[0] - '0';
				}
				(*root)->child = new_node;
				new_node->parent = (*root);
			}
			aux = (*root)->child;
			if (!strlen(str) > 3)
				nr = str[1] - '0';
			else
				nr = atoi(str + 1);
		}
	}
	generare_arbore_bonus_helper(root,
	nr1, nr, size, size1, sep, file_in,
	nr_players, height);
}

// Functie asemanatoare cu cea de la task-ul 2.
// Aceasta afiseaza arborele in fisier.
void afisare_arbore_bonus(tree_node_para *root,
	FILE *file_out, int height, int nr_players)
{
	int i, k;
	tree_node_para *it = root;

	while (it) {
		for (i = 1; i <= height; i++)
			fprintf(file_out, "\t");
		fprintf(file_out, "[");
		for (k = 1; k < nr_players; k++)
			fprintf(file_out, "%d,", it->value[k]);
		fprintf(file_out, "%d]", it->value[nr_players]);
		fprintf(file_out, "\n");
		if (it->child)
			afisare_arbore_bonus(it->child,
				file_out, height + 1, nr_players);
		it = it->next;
	}
}

// Functie care imi elibereaza memoria unui nod
void eliberare_nod_bonus(tree_node_para **root)
{
	free((*root)->value);
	free(*root);
}

// Functie care imi elibereaza memoria arborelui in mod
// recursiv. Aceasta apeleaza functia eliberare_nod
void eliberare_memorie_bonus(tree_node_para **root)
{
	tree_node_para *it, *aux;

	if ((*root)->child) {
		it = (*root)->child;
		eliberare_memorie_bonus(&it);
	}
	if ((*root)->next)
		eliberare_memorie_bonus(&(*root)->next);
	eliberare_nod_bonus(root);
}

// Functia recursiva care se ocupa de umplerea cu valori
// a arborelui. Prezinta similitudini cu cea de la task-ul 2
// doar ca am modificat-o pentru a returna un vector de int
// si am adaugat niste conditii suplimentare
int *umple_arbore_bonus(tree_node_para **root,
	int height, int player, int nr_players, int *m)
{
	int i, j, *v, aux[100];
	tree_node_para *it = *root;

	if (player % nr_players == 1) {
		aux[0] = -10000;
		m[0] = -10000;
	} else {
		aux[0] = 10000;
		m[0] = 10000;
	}
	while (it) {
		if (it->child) {
			v = umple_arbore_bonus(&it->child,
				height, player + 1, nr_players, m);
			for (j = 1; j <= nr_players; j++)
				it->value[j] = v[j - 1];
		}
		if (player % nr_players == 1) {
			if (aux[0] < it->value[1])
				for (j = 0; j < nr_players; j++) {
					aux[j] = it->value[j + 1];
					m[j] = it->value[j + 1];
			} else {
				for (j = 0; j < nr_players; j++)
					m[j] = aux[j];
			}
		} else {
			if (aux[0] > it->value[1])
				for (j = 0; j < nr_players; j++) {
					aux[j] = it->value[j + 1];
					m[j] = it->value[j + 1];
				}
			else {
				for (j = 0; j < nr_players; j++)
					m[j] = aux[j];
			}
		}
		it = it->next;
	}
	return m;
}

// Functia de bonus. Aceasta contine apelurile
// unora din functiile implementate mai sus. Functia
// bonus() este apelata in main.c.
void bonus(FILE *file_in, FILE *file_out)
{
	int height, nr_players, size;
	tree_node_para *root;
	int v[30];

	fseek(file_in, 0, SEEK_END);
	size = ftell(file_in);
	rewind(file_in);
	fscanf(file_in, "%d", &height);
	fscanf(file_in, "%d", &nr_players);
	init_node_bonus(&root, nr_players);
	generare_arbore_bonus(&root, file_in, height, size, nr_players);
	umple_arbore_bonus(&root, height, 0, nr_players, v);
	afisare_arbore_bonus(root, file_out, 0, nr_players);
	eliberare_memorie_bonus(&root);
}
