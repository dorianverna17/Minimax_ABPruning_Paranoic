#include "cerinta3.h"

// Functie de initializare a unui nod
// Aceasta este identica cu cea de la
// task-ul 2
void init_node_task3(tree_node **root)
{
	*root = malloc(sizeof(tree_node));
	(*root)->next = NULL;
	(*root)->prev = NULL;
	(*root)->parent = NULL;
	(*root)->child = NULL;
	(*root)->value_min = -100000;
}

// Functie de inserare noduri. Aceasta este
// o functie ajutatoare pentru functia de
// generare arbore. Este idetica cu functia
// de la task-ul 2
void inserare_noduri_task3(tree_node **root, int nr)
{
	int i;
	tree_node *it;

	it = (*root)->child;
	for (i = 0; i < nr; i++) {
		tree_node *new_node;

		init_node_task3(&new_node);
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
tree_node *seek_aux_task3(tree_node *root, int height, int nivel)
{
	tree_node *it = root, *aux = NULL;
	int i;

	while (it) {
		if (height == nivel && it->value_min == -100000)
			return it;
		if (it->child && it->value_min == -100000)
			aux = seek_aux_task3(it->child, height + 1, nivel);
		if (aux)
			return aux;
		it = it->next;
	}
	return NULL;
}

// Functie identica cu cea de la task-ul 2.
// Aceasta imi genereaza arborele pe baza
// valorilor pe care le citesc din fisier.
void generare_arbore_task3(tree_node **root,
	FILE *file_in, int height, int size)
{
	int i, j, nr, nr1, size1, nr2;
	char str[10], string[10];
	tree_node *aux, *it;

	for (i = 1; i <= height; i++) {
		if (i == 1) {
			fscanf(file_in, "%s", str);
			if (str[0] == '(') {
				if (!strlen(str) > 3)
					inserare_noduri_task3(root,
						str[1] - '0');
				else
					inserare_noduri_task3(root,
						atoi(str + 1));
			} else {
				tree_node *new_node;

				init_node_task3(&new_node);
				new_node->value_min = str[1] - '0';
				(*root)->child = new_node;
				new_node->parent = (*root);
			}
			aux = (*root)->child;
			if (!strlen(str) > 3)
				nr = str[1] - '0';
			else
				nr = atoi(str + 1);
		} else {
			it = aux;
			nr1 = 0;
			for (j = 1; j <= nr; j++) {
				fscanf(file_in, "%s", string);
				size1 = ftell(file_in);
				if (string[0] == '(') {
					if (strlen(string) > 3) {
						inserare_noduri_task3(&it,
							atoi(string + 1));
						nr1 = nr1 + atoi(string + 1);
					} else {
						inserare_noduri_task3(&it,
							string[1] - '0');
						nr1 = nr1 + string[1] - '0';
					}
				} else {
					if (strlen(string) > 3)
						it->value_min =
					atoi(string + 1);
					else
						it->value_min = string[1] - '0';
				}
				if (size == size1)
					return;
// La fel ca la task-ul 2, aici gasesc
// noua valoare a lui it
// Am ales sa indentez in acelasti fel si aici,
// deoarece checker-ul de coding style nu dadea
// nicio eroare
	if (!it->next && j != nr) {
eticheta:;
		while (!it->next) {
			while (it->prev)
				it = it->prev;
			it = it->parent;
		}
		if (it->next) {
			if (it->next->value_min != -100000) {
				it = it->next;
				while (it->value_min != -100000 && it->next)
					it = it->next;
				if (it->value_min != -100000)
					goto eticheta;
				else
					while (it->child)
						it = it->child;
				if (it->value_min != -100000)
					goto yes;
			} else {
				it = it->next;
				while (it->child)
					it = it->child;
yes:;
				while (it->value_min != -100000 && it->next)
					it = it->next;
				if (it->value_min != -100000)
					goto eticheta;
				else {
					while (it->child)
						it = it->child;
					if (it->value_min != -100000)
						goto yes;
				}
			}
		} else
			goto eticheta;
	} else
		it = it->next;
	}
	nr = nr1;
	aux = seek_aux_task3(*root, 1, i + 1);
	}
}
}

// Functie identica cu cea de la task-ul 2.
// Aceasta afiseaza arborele in fisier.
void afisare_arbore_task3(tree_node *root, FILE *file_out, int height)
{
	int i;
	tree_node *it = root;

	while (it) {
		for (i = 1; i <= height; i++)
			fprintf(file_out, "\t");
		fprintf(file_out, "%d", it->value_min);
		fprintf(file_out, "\n");
		if (it->child)
			afisare_arbore_task3(it->child, file_out, height + 1);
		it = it->next;
	}
}

// Functie care imi elibereaza memoria unui nod
void eliberare_nod_task3(tree_node **root)
{
	free(*root);
}

// Functie care imi elibereaza memoria arborelui in mod
// recursiv. Aceasta apeleaza functia eliberare_nod
void eliberare_memorie_task3(tree_node **root)
{
	tree_node *it, *aux;

	if ((*root)->child) {
		it = (*root)->child;
		eliberare_memorie_task3(&it);
	}
	if ((*root)->next)
		eliberare_memorie_task3(&(*root)->next);
	eliberare_nod_task3(root);
}

// Functie similara celei de la task-ul 2. Aceasta functie
// stabileste valorile nodurilor superioare pe baza valorilor
// frunzelor
int umple_arbore_task3(tree_node **root, int height, int player)
{
	int i, m;
	tree_node *it = *root;

	if (player == 1)
		m = 10000;
	else
		m = -10000;
	while (it) {
		if (it->child)
			it->value_min = umple_arbore_task3(&it->child,
				height, -player);
		if (player == -1)
			if (m < it->value_min)
				m = it->value_min;
		if (player == 1)
			if (m > it->value_min)
				m = it->value_min;
		it = it->next;
	}
	return m;
}

// Functia care imi aplica algoritmul alpha-beta pruning
// Aceasta este o functie recursiva care parcurge arborele
// si modifica valorile alpha si beta ale fiecarui nod, valori
// pe care le foloseste in evaluarea redundantei unui subarbore
// Daca alpha este la un moment dat mai mare decat beta, atunci
// se scot subarborii fiilor urmatori ai nodului care indeplineste
// conditia
void alpha_beta_pruning(tree_node **root, int height,
	int player, tree_node *root_comp)
{
	tree_node *it = *root, *aux, *aux2;

	if (it->parent)
		aux = it->parent;
	while (it) {
		if (it->child) {
			it->child->beta = it->beta;
			it->child->alpha = it->alpha;
			alpha_beta_pruning(&it->child, height,
				-player, root_comp);
			if (it == root_comp)
				return;
		} else {
			it->beta = it->value_min;
			it->alpha = it->value_min;
		}
		if (player == 1) {
			if ((aux->beta >= it->beta &&
				aux->beta <= it->alpha) ||
				(aux->beta >= it->beta &&
					aux->beta >= it->alpha &&
					(it->alpha >= it->beta))) {
				aux->beta = it->beta;
			} else if ((aux->beta >= it->alpha &&
				aux->beta <= it->beta) ||
				(aux->beta >= it->alpha &&
					aux->beta >= it->beta &&
					it->beta >= it->alpha)) {
				aux->beta = it->alpha;
			}
		} else {
			if ((aux->alpha >= it->beta &&
				aux->alpha <= it->alpha) ||
				(aux->alpha <= it->beta &&
				it->beta <= it->alpha))
				aux->alpha = it->alpha;
			else if ((aux->alpha >= it->alpha &&
				aux->alpha <= it->beta) ||
				(aux->alpha <= it->alpha &&
				it->beta <= it->beta))
				aux->alpha = it->beta;
		}
		if (aux->alpha >= aux->beta)
			while (it->next) {
				if (it->next) {
					if (it->next->next) {
						aux2 = it->next->next;
						it->next->prev = NULL;
						it->next->next = NULL;
						eliberare_memorie_task3(
							&it->next);
						aux2->prev = it;
						it->next = aux2;
					} else {
						aux2 = it->next;
						it->next->prev = NULL;
						it->next = NULL;
						eliberare_memorie_task3(&aux2);
					}
				}
			}
			it = it->next;
			if (it) {
				if (it->child && it->prev) {
					it->alpha = aux->alpha;
					it->beta = aux->beta;
				}
			}
	}
}

// Functia de cerinta 3. Aceasta contine apelurile
// unora din functiile implementate mai sus. Functia
// cerinta3() este apelata in main.c.
void cerinta3(FILE *file_in, FILE *file_out)
{
	int height, i, size;
	tree_node *root;

	fseek(file_in, 0, SEEK_END);
	size = ftell(file_in);
	rewind(file_in);
	fscanf(file_in, "%d", &height);
	init_node_task3(&root);
	root->alpha = -100000000;
	root->beta = 100000000;
	generare_arbore_task3(&root, file_in, height, size);
	umple_arbore_task3(&root, height, 1);
	alpha_beta_pruning(&root, height, 1, root);
	umple_arbore_task3(&root, height, 1);
	afisare_arbore_task3(root, file_out, 0);
	eliberare_memorie_task3(&root);
}
