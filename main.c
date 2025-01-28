#include <stdio.h>
#include <stdlib.h>

struct no23 {
    int chave_esq; // chave esquerda
    int chave_dir; // chave direita
    struct no23 *esq; // subárvore esquerda
    struct no23 *meio; // subárvore do meio
    struct no23 *dir; // subárvore direita
    int n; // número de chaves no nó
};

typedef struct no23* arvore23;

// Função para criar um nó na árvore 2-3
arvore23 criaNo23(int chaveEsq, int chaveDir, arvore23 esq, arvore23 meio, arvore23 dir, int n) {
    arvore23 novoNo = (arvore23)malloc(sizeof(struct no23));
    
    novoNo->chave_esq = chaveEsq;
    novoNo->chave_dir = (n == 2) ? chaveDir : 0;
    novoNo->esq = esq;
    novoNo->meio = meio;
    novoNo->dir = (n == 2) ? dir : NULL;
    novoNo->n = n;
    return novoNo;
}

// Função para verificar se um nó está vazio
int vazia(arvore23 r) {
    return r == NULL;
}

// Função para verificar se um nó é folha
int eh_folha(arvore23 r) {
    return r->esq == NULL && r->meio == NULL && r->dir == NULL;
}

// Adiciona uma chave em um nó que tem 1 chave
void adicionaChave(arvore23 r, int chave, arvore23 p) {
    if (r->chave_esq < chave) {
        r->chave_dir = chave;
        r->dir = p;
    } else {
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = p;
    }
    r->n = 2;
}

// Divide um nó da árvore 2-3
arvore23 split(arvore23 p, int chave, arvore23 subarvore, int *chave_promovida) {
    arvore23 paux;
    if (chave > p->chave_dir) {
        *chave_promovida = p->chave_dir;
        paux = p->dir;
        p->dir = NULL;
        p->n = 1;
        return criaNo23(chave, 0, paux, subarvore, NULL, 1);

    } else if (chave >= p->chave_esq) {
        *chave_promovida = chave;
        paux = p->dir;
        p->dir = NULL;
        p->n = 1;
        return criaNo23(p->chave_dir, 0, subarvore, paux, NULL, 1);
        
    } else {
        *chave_promovida = p->chave_esq;
        paux = criaNo23(p->chave_dir, 0, p->meio, p->dir, NULL, 1);
        p->chave_esq = chave;
        p->n = 1;
        p->dir = NULL;
        p->meio = subarvore;
        return paux;
    }
}

// Insere uma chave em uma árvore 2-3
arvore23 inserir_aux(arvore23 r, int chave, int *chave_promovida) {
    if (eh_folha(r)) {
        if (r->n == 1) {
            adicionaChave(r, chave, NULL);
            return NULL;
        } else {
            return split(r, chave, NULL, chave_promovida);
        }
    } else {
        arvore23 paux;
        int ch_aux;
        if (chave < r->chave_esq) {
            paux = inserir_aux(r->esq, chave, &ch_aux);
        } else if (r->n == 1 || chave < r->chave_dir) {
            paux = inserir_aux(r->meio, chave, &ch_aux);
        } else {
            paux = inserir_aux(r->dir, chave, &ch_aux);
        }
        if (paux == NULL) {
            return NULL;
        }
        if (r->n == 1) {
            adicionaChave(r, ch_aux, paux);
            return NULL;
        } else {
            return split(r, ch_aux, paux, chave_promovida);
        }
    }
}

// Insere uma chave na árvore 2-3
arvore23 inserir(arvore23 r, int chave) {
    if (vazia(r)) {
        return criaNo23(chave, 0, NULL, NULL, NULL, 1);
    } else {
        int chave_promovida;
        arvore23 aux = inserir_aux(r, chave, &chave_promovida);
        if (!vazia(aux)) {
            return criaNo23(chave_promovida, 0, r, aux, NULL, 1);
        } else {
            return r;
        }
    }
}

// Busca uma chave na árvore 2-3
arvore23 busca(arvore23 r, int chave) {
    if (vazia(r)) {
        return NULL;
    }
    if (r->chave_esq == chave) {
        return r;
    }
    if (r->n == 2 && r->chave_dir == chave) {
        return r;
    }
    if (chave < r->chave_esq) {
        return busca(r->esq, chave);
    } else if (r->n == 1 || chave < r->chave_dir) {
        return busca(r->meio, chave);
    } else {
        return busca(r->dir, chave);
    }
}

void imprimeArvore(arvore23 r, int nivel) {
    if (vazia(r)) return;
    printf("Nivel %d: ", nivel);
    printf("[%d", r->chave_esq);

    if (r->n == 2) printf(", %d", r->chave_dir);
    printf("]\n");

    imprimeArvore(r->esq, nivel + 1);
    imprimeArvore(r->meio, nivel + 1);
    
    if (r->n == 2) imprimeArvore(r->dir, nivel + 1);
}

int minimo(arvore23 r) {
    if(!vazia(r)){
        if(eh_folha(r)){
            return r->chave_esq;
        }
        return minimo(r->chave_esq);
    } 
    return -1;
}

int maximo(arvore23 r){
    if(!vazia(r)){
        if(eh_folha(r)){
            return r->chave_dir;
        }
        return maximo(r->chave_dir);
    }
    return -1;
}

int conta_nos(arvore23 r){

}

void in_ordem(arvore23 r){

}

// Função principal para testar inserção e impressão
int main() {
    arvore23 raiz = NULL;

    // Inserção de chaves
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 80);

    // Imprime a árvore resultante
    printf("Árvore 2-3 após as inserções:\n");
    imprimeArvore(raiz, 0);

    return 0;
}