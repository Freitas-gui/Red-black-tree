// Guilherme Freitas da Silva

#include "RBT.h"

// Cria um elemento da RBT.
no *createNo(void *inf){
    // Aloca espaco de memoria.
    no *newNo = (no*)malloc(sizeof(no));
    if(!newNo)
        return NULL;
    else{
        // Se tiver conseguido alocar, entao seta os valores do no.
        newNo->inf = inf;
        newNo->left = NULL;
        newNo->right = NULL;
        newNo->parent = NULL;
        newNo->color = red;
    }
    return newNo;
}

int positionChildFromParent(no *rbt){
    if (!rbt || !rbt->parent) return NULL;

    if (rbt->parent != NULL){
        if (rbt == rbt->parent->left)
            return 1;
        else return -1;
    }
    // Parent is NULL.
    return 0;
}

no *uncle(no *rbt){
    if (!rbt || !rbt->parent || !rbt->parent->parent) return NULL;

    switch (positionChildFromParent(rbt->parent)){
        case 1:
            return rbt->parent->parent->right;
        case 0:
            return NULL;
        case -1:
            return rbt->parent->parent->left;
    }
}

int isleaf(no *rbt){
    if (!rbt) return 0;
    if ( (!(rbt)->left) && (!(rbt)->right) )
        return 1;
    return 0;
}

int isRed(no *rbt){
    if (!rbt) return 0;
    if (rbt->color == black) return 0;
    return 1;
}

// Procura um elemento na RBT que tenha a mesma informacao fornecida no parametro 'inf'.
no *search(no *rbt , void *inf, int infoComp(void *, void *)){
    if(!rbt)
        return NULL;
    // Caso as informacoes sejam equivalentes, esse sera o elemento retornado.
    else if(infoComp(rbt->inf, inf) == 0)
        return rbt;
    // Caso rbt->inf seja considerada maior que inf, pelo fator de comparacao.
    // Se inf existir na RBT, ele estara na subarvore esquerda.
    else if(infoComp(rbt->inf, inf) == 1)
        return search(rbt->left, inf, infoComp);
    // Caso rbt->inf seja considerada menor que inf, pelo faotr de comparacao.
    // Se inf existir na RBT, ele estara na subarvore direita.
    else
        return search(rbt->right, inf, infoComp);
}

no *searchParent(no *rbt , void *inf, int infoComp(void *, void *)){
    if(!rbt ||( !(rbt->left) && !(rbt->right)))
        return NULL;

    if (rbt->left){
        if(infoComp(rbt->left->inf, inf) == 0)
            return rbt;

        else if(infoComp(rbt->left->inf, inf) == 1)
            return searchParent(rbt->left, inf, infoComp);

        else
            return searchParent(rbt->right, inf, infoComp);
    }

    if (rbt->right){
        if(infoComp(rbt->right->inf, inf) == 0)
            return rbt;

        else if(infoComp(rbt->right->inf, inf) == 1)
            return searchParent(rbt->right, inf, infoComp);

        else
            return searchParent(rbt->left, inf, infoComp);
    }
}

// Insercao na sub-arvore direita.
// Rotacao a esquerda.
void R_RotationRBT(no **root, no **pivoParent ,no **pivo){
    if (!(*pivo)) return;

    // Redefinicoes de referencias.
    if (*pivoParent != NULL){
        if (positionChildFromParent(*pivo) == 1)
            (*pivoParent)->left = (*pivo)->right;
        else
            (*pivoParent)->right = (*pivo)->right;
    }
    (*pivo)->right->parent = (*pivo)->parent;

    if ((*pivo)->right->left)
        (*pivo)->right->left->parent = (*pivo);

    (*pivo)->parent = (*pivo)->right;

    (*pivo)->right = (*pivo)->right->left;

    (*pivo)->parent->left = (*pivo);

    *pivo = (*pivo)->parent;

    if (!(*pivo)->parent)
        *root = *pivo;
}

// Insercao na sub-arvore esquerda.
// Rotacao a direita.
void L_RotationRBT(no **root, no **pivoParent, no **pivo){
    if (!(*pivo)) return;

    // Redefinicoes de referencias.
    if (*pivoParent != NULL){
        if (positionChildFromParent(*pivo) == 1)
            (*pivoParent)->left = (*pivo)->left;
        else
            (*pivoParent)->right = (*pivo)->left;
    }
    (*pivo)->left->parent = (*pivo)->parent;


    if ((*pivo)->left->right)
        (*pivo)->left->right->parent = (*pivo);

    (*pivo)->parent = (*pivo)->left;

    // Redefinicoes de referencias.
    (*pivo)->left = (*pivo)->left->right;

    (*pivo)->parent->right = (*pivo);

    // A raiz da subárvore passada no parâmetro é atualizada.
    *pivo = (*pivo)->parent;

    if (!(*pivo)->parent) 
        *root = *pivo;
}

void balance(no **root, no **newNo){
    no *parent, *grandpa, *uncle;

    while (isRed((*newNo)->parent))
    {
        parent = (*newNo)->parent;
        grandpa = parent->parent;
        if (parent == grandpa->left)
            uncle = grandpa->right;
        else
            uncle = grandpa->left;
        if (isRed(uncle)){
            parent->color = black;
            uncle->color = black;
            grandpa->color = red;
            (*newNo) = grandpa;
        }
        else if (positionChildFromParent(parent) == 1){
            if (positionChildFromParent(*newNo) == -1){
                *newNo = parent;
                R_RotationRBT(root, &(*newNo)->parent, newNo);
            }
            parent->color = black;
            grandpa->color = red;
            *newNo = grandpa;
            L_RotationRBT(root, &(*newNo)->parent, newNo);
        }
        else if (positionChildFromParent(parent) == -1){
            if (positionChildFromParent(*newNo) == 1){
                *newNo = parent;
                L_RotationRBT(root, &(*newNo)->parent, newNo);
            }
            parent->color = black;
            grandpa->color = red;
            *newNo = grandpa;
            R_RotationRBT(root, &(*newNo)->parent, newNo);
        }
    }
    (*root)->color = black;
}

no *insertRBT(no **root, void *inf, int infoComp(void *, void *)){
    no *position = *root;
    no *positionParent = NULL;
    no *newNo = createNo(inf);

    while (position)
    {
        if (infoComp(inf, position->inf) == 0){
            free(newNo);
            return NULL;
        }
        positionParent = position;
        if (infoComp(inf, position->inf) == -1)
            position = position->left;
        else
            position = position->right;
    }

    newNo->parent = positionParent;

    if (!positionParent)
        *root = newNo;
    else if (infoComp(inf, positionParent->inf) == -1)
        positionParent->left = newNo;
    else
        positionParent->right = newNo;

    balance(root, &newNo);

    return newNo;
}

// Imprime a RBT, visualmente rotacionada em um angulo de 90 graus anti-horario.
void toStringRBT(no *rbt , int level, void *toStringInfoId(void *)){
    int i;
    if (rbt){
        // Chamada recursiva para imprimir os elementos da sub-arvore a direita.
        toStringRBT (rbt->right, level + 1, toStringInfoId) ;
        // Os elementos sao separados na horizontal por um espaco de tab.
        for(i = 0; i < level; i++) printf ("\t");
        // O elemento a ser impresso eh definido pela chave escolida no programa cliente.
        toStringInfoId(rbt->inf);
        // Os elementos sao separados na vertical por uma quebra de linha.
        printf("\n");
        // Chamada recursiva para imprimir os elementos da sub-arvore a esquerda.
        toStringRBT (rbt->left, level + 1, toStringInfoId) ;
    }
}

// Imprime as  cores de cada elemento da RBT, visualmente rotacionada em um angulo de 90 graus anti-horario.
void toStringColorRBT(no *rbt , int level){
    int i;
    if (rbt){
        // Chamada recursiva para imprimir os elementos da sub-arvore a direita.
        toStringColorRBT (rbt->right, level + 1) ;
        // Os elementos sao separados na horizontal por um espaco de tab.
        for(i = 0; i < level; i++) printf ("\t");
        // O elemento a ser impresso eh definido pela chave escolida no programa cliente.
        printf("%d", rbt->color);
        // Os elementos sao separados na vertical por uma quebra de linha.
        printf("\n");
        // Chamada recursiva para imprimir os elementos da sub-arvore a esquerda.
        toStringColorRBT (rbt->left, level + 1) ;
    }
}