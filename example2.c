#include <stdlib.h>
#include <stdio.h>

// Structura pentru nodurile listei de adiacenta
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

// Structura pentru graf
typedef struct Graph {
    int varfuri;
    int *vizitat;
    NODE **liste_adiacenta;
} GRAF;

// Functie pentru a crea un nod nou
NODE *creeaza_nod(int valoare) {
    NODE *nod_nou = malloc(sizeof(NODE));
    if (!nod_nou) {
        fprintf(stderr, "Eroare alocare memorie pentru nod.\n");
        exit(EXIT_FAILURE);
    }
    nod_nou->data = valoare;
    nod_nou->next = NULL;
    return nod_nou;
}

// Functie pentru a crea un graf gol
GRAF *creeaza_graf(int varfuri) {
    GRAF *graf = malloc(sizeof(GRAF));
    if (!graf) {
        fprintf(stderr, "Eroare alocare memorie pentru graf.\n");
        exit(EXIT_FAILURE);
    }

    graf->varfuri = varfuri;
    graf->liste_adiacenta = malloc(varfuri * sizeof(NODE *));
    graf->vizitat = malloc(varfuri * sizeof(int));

    if (!graf->liste_adiacenta || !graf->vizitat) {
        fprintf(stderr, "Eroare alocare memorie pentru componentele grafului.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < varfuri; i++) {
        graf->liste_adiacenta[i] = NULL;
        graf->vizitat[i] = 0;
    }

    return graf;
}

// Functie pentru a adauga o muchie (inserare la finalul listei)
void adauga_muchie(GRAF *graf, int src, int dest) {
    NODE *nod_nou = creeaza_nod(dest);
    if (graf->liste_adiacenta[src] == NULL) {
        graf->liste_adiacenta[src] = nod_nou;
    } else {
        NODE *temp = graf->liste_adiacenta[src];
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nod_nou;
    }
}

// Functie pentru a adauga mai multe muchii
void insereaza_muchii(int varfuri, int muchii, GRAF *graf) {
    int src, dest;
    printf("Introdu %d muchii (de la 0 la %d):\n", muchii, varfuri - 1);
    for (int i = 0; i < muchii; i++) {
        scanf("%d%d", &src, &dest);
        adauga_muchie(graf, src, dest);
    }
}

// Verifica daca o coada este goala
int is_empty(NODE *coada) {
    return coada == NULL;
}

// Adauga in coada
void enqueue(NODE **coada, int data) {
    NODE *nod_nou = creeaza_nod(data);

    if (is_empty(*coada)) {
        *coada = nod_nou;
    } else {
        NODE *temp = *coada;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nod_nou;
    }
}

// Scoate din coada
int dequeue(NODE **coada) {
    if (is_empty(*coada)) {
        fprintf(stderr, "Underflow coada.\n");
        exit(EXIT_FAILURE);
    }

    int valoare = (*coada)->data;
    NODE *temp = *coada;
    *coada = (*coada)->next;
    free(temp);
    return valoare;
}

// Resetare vector de vizitat
void resetare_vizitat(GRAF *graf) {
    for (int i = 0; i < graf->varfuri; i++) {
        graf->vizitat[i] = 0;
    }
}

// Parcurgere DFS
void DFS(GRAF *graf, int nod) {
    if (!graf || nod < 0 || nod >= graf->varfuri) return;

    graf->vizitat[nod] = 1;
    printf("%d ", nod);

    NODE *temp = graf->liste_adiacenta[nod];
    while (temp) {
        int vecin = temp->data;
        if (!graf->vizitat[vecin]) {
            DFS(graf, vecin);
        }
        temp = temp->next;
    }
}

// Parcurgere BFS
void BFS(GRAF *graf, int start) {
    if (!graf || start < 0 || start >= graf->varfuri) return;

    NODE *coada = NULL;
    graf->vizitat[start] = 1;
    enqueue(&coada, start);

    while (!is_empty(coada)) {
        int nod_curent = dequeue(&coada);
        printf("%d ", nod_curent);

        NODE *temp = graf->liste_adiacenta[nod_curent];
        while (temp) {
            int vecin = temp->data;
            if (!graf->vizitat[vecin]) {
                graf->vizitat[vecin] = 1;
                enqueue(&coada, vecin);
            }
            temp = temp->next;
        }
    }
}

// Functie principala
int main() {
    int varfuri, muchii, start;

    printf("Cate varfuri are graful? ");
    scanf("%d", &varfuri);

    printf("Cate muchii are graful? ");
    scanf("%d", &muchii);

    GRAF *graf = creeaza_graf(varfuri);
    insereaza_muchii(varfuri, muchii, graf);

    printf("Varful de start pentru DFS: ");
    scanf("%d", &start);
    printf("Parcurgere DFS: ");
    DFS(graf, start);
    printf("\n");

    resetare_vizitat(graf);

    printf("Varful de start pentru BFS: ");
    scanf("%d", &start);
    printf("Parcurgere BFS: ");
    BFS(graf, start);
    printf("\n");

    return 0;
}
