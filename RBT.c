// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#include "RBT.h"

no* EXTERNAL = NULL;

// Cria um elemento da RBT.
no *createNoExternal(){
    // Aloca espaco de memoria.
    no *newNo = (no*)malloc(sizeof(no));
    if(!newNo)
        return NULL;
    else{
        // Se tiver conseguido alocar, entao seta os valores do no.
        newNo->inf = NULL;
        newNo->left = NULL;
        newNo->right = NULL;
        newNo->parent = NULL;
        newNo->color = black;
    }
    return newNo;
}

no *createNo(void *inf){
    // Aloca espaco de memoria.
    no *newNo = (no*)malloc(sizeof(no));
    if(!newNo)
        return NULL;
    else{
        // Se tiver conseguido alocar, entao seta os valores do no.
        newNo->inf = inf;
        newNo->left = EXTERNAL;
        newNo->right = EXTERNAL;
        newNo->parent = EXTERNAL;
        newNo->color = red;
    }
    return newNo;
}

int positionChildFromParent(no *rbt){
    if (!rbt || !rbt->parent || rbt == EXTERNAL) return NULL;

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
    if(!rbt || rbt == EXTERNAL)
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
    if (!(*pivo) || *pivo == EXTERNAL) return;
    
    no *pivoParent = (*pivo)->parent;
    // Redefinicoes de referencias.
    if (pivoParent != NULL && pivoParent != EXTERNAL){
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
    if (!(*pivo) || *pivo == EXTERNAL) return;
    no *pivoParent = (*pivo)->parent;

    // Redefinicoes de referencias.
    if (pivoParent != NULL && pivoParent != EXTERNAL){
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

void transferParent(no **root, no **rbt, no **target){
    no *parent = (*rbt)->parent;
    if (parent == EXTERNAL)
        *root = *target;
    else if (positionChildFromParent(*rbt) == 1)
        parent->left = *target;
    else if (positionChildFromParent(*rbt) == -1)
        parent->right = *target;
    if (*target)
        (*target)->parent = parent;
}

// Retorna o no considerado o menor elemento na AVL.
no *findSmalLestNo(no *avl){
    if(!avl || avl == EXTERNAL) return EXTERNAL;
    if(!(avl->left) || avl->left == EXTERNAL)
        return avl;
    else
        return findSmalLestNo(avl->left);
}

void balanceDelete(no **root, no **rbt){
    if (!(*root)) return;
    no *newRbt = *rbt, *siblingRbt, *parentRbt;

    while (newRbt != (*root) && newRbt->color == black)
    {
        if (newRbt == newRbt->parent->left){
            siblingRbt = sibling(newRbt);
                parentRbt = newRbt->parent;

            printf("\n\nLeft\n\n");
            if (isRed(siblingRbt)){
                    siblingRbt->color = black;
                    parentRbt->color = red;
                R_RotationRBT(root, &parentRbt);
                siblingRbt = sibling(newRbt);
                    parentRbt = newRbt->parent;
            }

            if (siblingRbt && (!isRed(siblingRbt->left)) && !isRed(siblingRbt->right)){
                siblingRbt->color = red;
                newRbt = parentRbt;
                parentRbt = newRbt->parent;
                siblingRbt = sibling(newRbt);
            }

            else{
                 if (siblingRbt && !isRed(siblingRbt->right)){
                    siblingRbt->left->color = black;
                    siblingRbt->color = red;
                    L_RotationRBT(root, &siblingRbt);
                    siblingRbt = sibling(newRbt);
                    parentRbt = newRbt->parent;
                    parentRbt = EXTERNAL;
                }
                siblingRbt->color = parentRbt->color;
                parentRbt->color = black;
                siblingRbt->right->color = black;

                R_RotationRBT(root, &parentRbt);
                newRbt = (*root);
            }
        }

        else if (newRbt != (*root) && newRbt->color == black){
            siblingRbt = sibling(newRbt);
            parentRbt = newRbt->parent;

            printf("\n\nRight\n\n");
            if (isRed(siblingRbt)){
                siblingRbt->color = black;
                parentRbt->color = red;
                L_RotationRBT(root, &parentRbt);
                siblingRbt = sibling(newRbt);
                parentRbt = newRbt->parent;
            }

            if (siblingRbt && (!isRed(siblingRbt->left)) && !isRed(siblingRbt->right)){
                siblingRbt->color = red;
                newRbt = parentRbt;
                parentRbt = newRbt->parent;
                parentRbt = EXTERNAL;
                siblingRbt = sibling(newRbt);
            }

            else{
                 if (siblingRbt && !isRed(siblingRbt->left)){
                    siblingRbt->right->color = black;
                    siblingRbt->color = red;
                    R_RotationRBT(root, &siblingRbt);
                    siblingRbt = sibling(newRbt);
                    parentRbt = newRbt->parent;
                }
                siblingRbt->color = parentRbt->color;
                parentRbt->color = black;
                siblingRbt->right->color = black;

                L_RotationRBT(root, &parentRbt);
                newRbt = (*root);
            }
        }
    }
    newRbt->color = black;
}

no *deleteRBT(no **root, no **delete){
    if (!(*root) || !(*delete) || ((*delete) == EXTERNAL)) return NULL;
    no *deleted, *successor, *auxSuccessor, *successorRight;
    successorRight = EXTERNAL;
    auxSuccessor = EXTERNAL;
    deleted = *delete;
    successor = *delete;
    colorBR color = successor->color;

    // Caso o no a ser deletado tenha algum filho == NULL.
    if ((*delete)->left == EXTERNAL){
        auxSuccessor = (*delete)->right;
        transferParent(root, delete, &auxSuccessor);
    }
    else {
        if ((*delete)->right == EXTERNAL){
            auxSuccessor = (*delete)->left;
            transferParent(root, delete, &auxSuccessor);
        }
         else{
            successor = findSmalLestNo((*delete)->right);
            if (successor){
                color = successor->color;
                auxSuccessor = successor->right;
            }
            else
                color = black;
            if (successor && successor->parent == (*delete)){
                if (auxSuccessor)
                    auxSuccessor->parent = successor;
            }
            
            else{
                if (successor)
                    successorRight = successor->right;
                transferParent(root, &successor, &successorRight);
                if (successor)
                    successor->right = (*delete)->right;
                if (successor->right)
                    successor->right->parent = successor;
            }
            transferParent(root, delete, &successor);
            if (successor){
                successor->left = (*delete)->left;
                if (successor->left)
                    successor->left->parent = successor;
                if (successor)
                    successor->color = (*delete)->color;
            }
        }
    }
    if (color == black){
        if (auxSuccessor)
            balanceDelete(root, &auxSuccessor);
    }
    return deleted;
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

    while (position && position != EXTERNAL)
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
    if (rbt && rbt != EXTERNAL){
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
    if (rbt && rbt != EXTERNAL){
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