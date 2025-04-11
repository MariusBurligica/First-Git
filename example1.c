#include <stdio.h>
#include <stdlib.h>


typedef struct Nod {
    int valoare;
    struct Nod *urmator;
} Nod;


typedef struct Graf {
    int numarNoduri;    
    Nod **listaAdiacenta;  
} Graf;


Nod *creareNod(int valoare) {
    Nod *nodNou = malloc(sizeof(Nod));
    nodNou->valoare = valoare;
    nodNou->urmator = NULL;
    return nodNou;
}


Graf *creareGraf(int noduri) {
    Graf *graf = malloc(sizeof(Graf));
    graf->numarNoduri = noduri;
    graf->listaAdiacenta = malloc(noduri * sizeof(Nod *));
    for (int i = 0; i < noduri; i++) {
        graf->listaAdiacenta[i] = NULL;
    }
    return graf;
}


void adaugaMuchie(Graf *graf, int sursa, int destinatie) {
    Nod *nodNou = creareNod(destinatie);
    nodNou->urmator = graf->listaAdiacenta[sursa];
    graf->listaAdiacenta[sursa] = nodNou;

    nodNou = creareNod(sursa);
    nodNou->urmator = graf->listaAdiacenta[destinatie];
    graf->listaAdiacenta[destinatie] = nodNou;
}


void introduceMuchii(Graf *graf, int numarMuchii) {
    int sursa, destinatie;
    printf("Adauga %d muchii (indexuri de la 0 la %d):\n", numarMuchii, graf->numarNoduri - 1);
    for (int i = 0; i < numarMuchii; i++) {
        scanf("%d %d", &sursa, &destinatie);
        adaugaMuchie(graf, sursa, destinatie);
    }
}

int existaMuchieDirecta(Graf *graf, int sursa, int destinatie) {
    Nod *adj = graf->listaAdiacenta[sursa];
    while (adj != NULL) {
        if (adj->valoare == destinatie)
            return 1; 
        adj = adj->urmator;
    }
    return 0; 
}

int main() {
    int numarNoduri, numarMuchii;

    printf("Cate noduri are graful? ");
    scanf("%d", &numarNoduri);

    printf("Cate muchii are graful? ");
    scanf("%d", &numarMuchii);

    Graf *graf = creareGraf(numarNoduri);
    introduceMuchii(graf, numarMuchii);

    int sursa, destinatie;
    printf("Introdu doua noduri pentru verificare drum direct (ex: 0 1): ");
    scanf("%d %d", &sursa, &destinatie);

    if (existaMuchieDirecta(graf, sursa, destinatie))
        printf("Exista drum direct intre %d si %d\n", sursa, destinatie);
    else
        printf("Nu exista drum direct intre %d si %d\n", sursa, destinatie);

    return 0;
}
