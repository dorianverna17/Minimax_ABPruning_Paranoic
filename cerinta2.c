#include "cerinta2.h"

// Functie prin care se initializeaza un nod
// oarecare al arborelui. Aceasta este similara
// celei de la cerinta 1
void init_node2(tree_node **root)
{
	*root = malloc(sizeof(tree_node));
	(*root)->next = NULL;
	(*root)->prev = NULL;
	(*root)->parent = NULL;
	(*root)->child = NULL;
	(*root)->value_min = -100000;
}

// Functie ajutatoare de inserare a unui numar nr
// de noduri copil unui nod da ca parametru
// Functia este folosita in functia generare_arbore2
void inserare_noduri(tree_node **root, int nr)
{
	int i;
	tree_node *it;

	it = (*root)->child;
	for (i = 0; i < nr; i++) {
		tree_node *new_node;

		init_node2(&new_node);
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

// Functie de scriere a arborelui in file_out. Aceasta este
// similara celei de la cerinta 1
void afisare_arbore_min(tree_node *root, FILE *file_out, int height)
{
	int i;
	tree_node *it = root;

	while (it) {
		for (i = 1; i <= height; i++)
			fprintf(file_out, "\t");
		fprintf(file_out, "%d", it->value_min);
		fprintf(file_out, "\n");
		if (it->child)
			afisare_arbore_min(it->child, file_out, height + 1);
		it = it->next;
	}
}

// functie ajutatoare pentru functia genereare_arbore2.
// Aceasta functie cauta primul element din arbore care
// sa nu fie frunza si sa se afle pe nivelul mentionat
// intre parametrii functiei ca nivel. Pointerul pe care
// il va returna functia va constitui prima adresa spre
// care va arata iteratorul it din functia generare_arbore2
tree_node *seek_aux(tree_node *root, int height, int nivel)
{
	tree_node *it = root, *aux = NULL;
	int i;

	while (it) {
		if (height == nivel && it->value_min == -100000)
			return it;
		if (it->child && it->value_min == -100000)
			aux = seek_aux(it->child, height + 1, nivel);
		if (aux)
			return aux;
		it = it->next;
	}
	return NULL;
}

// Functia care imi citeste inputul din fisier si care
// genereaza arborele in functie de informatiile date acolo
void generare_arbore2(tree_node **root,
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
					inserare_noduri(root, str[1] - '0');
				else
					inserare_noduri(root, atoi(str + 1));
			} else {
				tree_node *new_node;

				init_node2(&new_node);
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
						inserare_noduri(&it,
							atoi(string + 1));
						nr1 = nr1 + atoi(string + 1);
					} else {
						inserare_noduri(&it,
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
// Acum stabilesc urmatoarea valoare pentru it
// iar apoi pentru aux (care si el da valoarea
// lui it la un urmatorul height)
// Am folosit si instructiunea goto, deoarece
// am considerat-o mai potrivita

// Aici am primit totodata eroare la checkerul
// de coding style, aceasta fiind din cauza punerii
// prea multor taburi
// Totusi, am observat ca e ok daca indentez asa
// (nu primeam eroare)
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
				while (it->value_min != -100000
					&& it->next)
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
// Aici modific valoarea lui aux
// si numarul de fii pe care trebuie
// sa il adaug la pasul urmator
		nr = nr1;
		aux = seek_aux(*root, 1, i + 1);
		}
	}
}

// Fucntia care, odata ce este generat arborele, imi calculeaza
// valorile din nodurile superioare, pe baza algoritmului
// minimax, si modifica arborele, punand aceste valori in el
int umple_arbore(tree_node **root, int height, int player)
{
	int i, m;
	tree_node *it = *root;

	if (player == 1)
		m = 10000;
	else
		m = -10000;
	while (it) {
		if (it->child)
			it->value_min = umple_arbore(&it->child,
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

// Functie care imi elibereaza memoria unui nod
void eliberare_nod_min(tree_node **root)
{
	free(*root);
}

// Functie care imi elibereaza memoria arborelui in mod
// recursiv. Aceasta apeleaza functia eliberare_nod
void eliberare_memorie_min(tree_node **root)
{
	tree_node *it, *aux;

	if ((*root)->child) {
		it = (*root)->child;
		eliberare_memorie_min(&it);
	}
	if ((*root)->next)
		eliberare_memorie_min(&(*root)->next);
	eliberare_nod_min(root);
}

// Functia pentru cerinta 2 care este apelata in
// main.c. Aceasta contine apelurile functiilor
// scrise mai sus
void cerinta2(FILE *file_in, FILE *file_out)
{
	int height, i, size;
	tree_node *root;

	fseek(file_in, 0, SEEK_END);
	size = ftell(file_in);
	rewind(file_in);
	fscanf(file_in, "%d", &height);
	init_node2(&root);
	generare_arbore2(&root, file_in, height, size);
	umple_arbore(&root, height, 1);
	afisare_arbore_min(root, file_out, 0);
	eliberare_memorie_min(&root);
}
