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

    if (rbt == rbt->parent->left)
        return 1;
    else return -1;

    return NULL;
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

no *sibling(no *rbt){
    if (!rbt || !rbt->parent) return NULL;

    switch (positionChildFromParent(rbt)){
        case 1:
            return rbt->parent->right;
        case 0:
            return NULL;
        case -1:
            return rbt->parent->left;
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
void R_RotationRBT(no **root ,no **pivo){
    if (!(*pivo)) return;
    
    no *pivoParent = (*pivo)->parent;
    // Redefinicoes de referencias.
    if (pivoParent != NULL){
        if (positionChildFromParent(*pivo) == 1)
            pivoParent->left = (*pivo)->right;
        else
            pivoParent->right = (*pivo)->right;
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
void L_RotationRBT(no **root, no **pivo){
    if (!(*pivo)) return;
    no *pivoParent = (*pivo)->parent;

    // Redefinicoes de referencias.
    if (pivoParent != NULL){
        if (positionChildFromParent(*pivo) == 1)
            pivoParent->left = (*pivo)->left;
        else
            pivoParent->right = (*pivo)->left;
    }
    (*pivo)->left->parent = (*pivo)->parent;

    if ((*pivo)->left->right)
        (*pivo)->left->right->parent = (*pivo);

    (*pivo)->parent = (*pivo)->left;

    // Redefinicoes de referencias.
    (*pivo)->left = (*pivo)->left->right;

    (*pivo)->parent->right = (*pivo);

    *pivo = (*pivo)->parent;

    // A raiz da subárvore passada no parâmetro é atualizada.
    if (!(*pivo)->parent) 
        *root = *pivo;
}

void transferParent(no **root, no **parent, no **rbt, no **target){
    if ( !(*rbt) || (*rbt)->parent != (*parent) )
        return;
    if (!(*parent))
        *root = *target;
    else if (positionChildFromParent(*rbt) == 1)
        (*parent)->left = *target;
    else if (positionChildFromParent(*rbt) == -1)
        (*parent)->right = *target;
    if (*target)
        (*target)->parent = *parent;
}

// Retorna o no considerado o menor elemento na AVL.
no *findSmalLestNo(no *avl){
    if(!avl) return NULL;
    if(!(avl->left))
        return avl;
    else
        return findSmalLestNo(avl->left);
}

no *deleteRBT(no **root, no **delete, int infoComp(void *, void *)){
    if (!(*root) || !(*delete)) return NULL;
    no *deleted, *successor;
    deleted = *delete;
    colorBR color = (*delete)->color;

    // Caso o no a ser deletado tenha algum filho = NULL.
    if (!(*delete)->right || !(*delete)->left){
        if ((*delete)->right){
            successor = (*delete)->right;
            transferParent(root, &(*delete)->parent, delete, &successor);
        }
        else if ((*delete)->left)
            successor = (*delete)->left;
            transferParent(root, &(*delete)->parent, delete, &successor);
    }

    // Caso em que o menor elemento a direita de (*delete) eh o (*delete)->right.
    else if (!(*delete)->right->left){
        successor = (*delete)->right;
        color = successor->color;
        successor->left = (*delete)->left;
        (*delete)->left->parent = successor->left;
        transferParent(root, &(*delete)->parent, delete, &successor);
    }

    // Caso (*delete)->right tenha filho a esquerda.
    else{
        successor = findSmalLestNo((*delete)->right);
        color = successor->color;

        successor->parent->left = successor->right;
        successor->right->parent = successor->parent->left;
        successor->right = successor->parent;
        successor->parent->parent = successor;

        successor->left = (*delete)->left;
        (*delete)->left->parent = successor;

        transferParent(root, &(*delete)->parent, delete, &successor);
    }

    // if (color == black)
    //     balanceDelete(no **root, &successor);
    
}

void reverteChildParent(no **rbt){
    if (!(*rbt) || !(*rbt)->parent) return;

    no *parent, *child, *grandpa;
    parent = (*rbt)->parent;
    child = (*rbt)->left;
    grandpa = parent->parent;
    
    grandpa->left = child;
    child->parent = grandpa;

    parent->left = child->left;
    child->left = (*rbt);
    (*rbt)->parent = child;

    (*rbt)->left = parent;
    parent->parent = (*rbt);
    
    
    *rbt = child;
    printf("aki");
}

void callBackRevert(no **rbt){
    no *parent = (*rbt)->parent->parent;
    reverteChildParent(&parent);
}

void balance(no **root, no **newNo){
    no *parent, *grandpa;

    while (isRed(*newNo) && isRed((*newNo)->parent))
    {
        parent = (*newNo)->parent;
        grandpa = parent->parent;
        
        if (isRed(uncle(*newNo))){
            parent->color = black;
            uncle(*newNo)->color = black;
            grandpa->color = red;
            (*newNo) = grandpa;
        }
        else if (positionChildFromParent(parent) == 1){
            if (positionChildFromParent(*newNo) == -1){
                (*newNo)->color = black;
                grandpa->color = red;
                *newNo = parent;
                R_RotationRBT(root, newNo);
                *newNo = grandpa;
                L_RotationRBT(root, newNo);
            }
            else{
                parent->color = black;
                grandpa->color = red;
                *newNo = grandpa;
                L_RotationRBT(root, newNo);
            }
        }
        else if (positionChildFromParent(parent) == -1){
            if (positionChildFromParent(*newNo) == 1){
                (*newNo)->color = black;
                grandpa->color = red;
                *newNo = parent;
                L_RotationRBT(root, newNo);
                *newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
            else{
                parent->color = black;
                grandpa->color = red;
                *newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
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