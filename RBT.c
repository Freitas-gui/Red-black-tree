// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#include "RBT.h"

no* EXTERNAL;

// Cria o elemento EXTERNO da RBT.
no *createNoExternal(){
    // Aloca espaco de memoria.
    no *newNo = (no*)malloc(sizeof(no));
    if(!newNo)
        return NULL;
    else{
        // Se tiver conseguido alocar, entao seta todos valores do no.
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
    if (!rbt || !rbt->parent || rbt == EXTERNAL || rbt->parent == EXTERNAL) return EXTERNAL;

    if (rbt == rbt->parent->left)
        return 1;
    else return -1;

    return NULL;
}

no *uncle(no *rbt){
    if (!rbt || !rbt->parent || rbt->parent == EXTERNAL || !rbt->parent->parent || rbt->parent->parent == EXTERNAL) return EXTERNAL;

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
void L_RotationRBT(no **root ,no *pivo){
    no *y = (pivo)->right;

    (pivo)->right = y->left;
    if (pivo->right && pivo->right != EXTERNAL) {
        pivo->right->parent = (pivo);
    }
    y->parent = (pivo)->parent;

    if ((pivo)->parent == EXTERNAL)
        *root = y;
    else if ((pivo) == (pivo)->parent->left)
        (pivo)->parent->left = y;
    else 
        (pivo)->parent->right = y;

    y->left = (pivo);
    (pivo)->parent = y;
}

// Insercao na sub-arvore esquerda.
// Rotacao a direita.
void R_RotationRBT(no **root, no *pivo){
    no *y = (pivo)->left;
    (pivo)->left = y->right;
    if ((pivo)->left != EXTERNAL)
        pivo->left->parent = (pivo);
    y->parent = (pivo)->parent;

    if ((pivo)->parent == EXTERNAL)
        *root = y;
    else if ((pivo) == (pivo)->parent->left)
        (pivo)->parent->left = y;
    else
        (pivo)->parent->right = y;

    y->right = (pivo);
    (pivo)->parent = y;
}

void transferParent(no **root, no *rbt, no *target){
    if (rbt->parent == EXTERNAL){
        *root = target;
    }
    else if (rbt == rbt->parent->left)
        rbt->parent->left = target;
    else
        rbt->parent->right = target;
    target->parent = rbt->parent;
}

// // Retorna o no considerado o menor elemento na AVL.
// no *findSmalLestNo(no *avl){
//     if(!avl || avl == EXTERNAL) return EXTERNAL;
//     if(!(avl->left) || avl->left == EXTERNAL)
//         return avl;
//     else
//         return findSmalLestNo(avl->left);
// }


no *findSmalLestNo(no *avl){
    no *aux = avl;
    while (aux && aux->left != EXTERNAL)
        aux = aux->left;

    return aux;
}

void balanceDelete(no **root, no *rbt){
    no *siblingRbt;

    while (rbt != (*root) && rbt->color == black)
    {
        if (rbt == rbt->parent->left){
            siblingRbt = rbt->parent->right;

            if (siblingRbt->color == red){
                siblingRbt->color = black;
                rbt->parent->color = red;
                L_RotationRBT(root, rbt->parent);
                siblingRbt = rbt->parent->right;
            }

            if (siblingRbt->left->color == black && siblingRbt->right->color == black){
                siblingRbt->color = red;
                rbt = rbt->parent;
            }

            else{
                 if (siblingRbt->right->color == black){
                    siblingRbt->left->color = black;
                    siblingRbt->color = red;
                    R_RotationRBT(root, siblingRbt);
                    siblingRbt = rbt->parent->right;
                }
                siblingRbt->color = rbt->parent->color;
                rbt->parent->color = black;
                siblingRbt->right->color = black;
                L_RotationRBT(root, rbt->parent);
                rbt = (*root);
            }
        }

        else {
            siblingRbt = rbt->parent->left;

            if (siblingRbt->color == red){

                siblingRbt->color = black;
                rbt->parent->color = red;
                R_RotationRBT(root, rbt->parent);
                siblingRbt = rbt->parent->left;
            }

            if (siblingRbt->left->color == black && siblingRbt->right->color == black){
                siblingRbt->color = red;
                rbt = rbt->parent;
            }

            else{
                 if (siblingRbt->left->color == black){

                    siblingRbt->right->color = black;
                    siblingRbt->color = red;
                    L_RotationRBT(root, siblingRbt);
                    siblingRbt = rbt->parent->left;
                }
                siblingRbt->color = rbt->parent->color;
                rbt->parent->color = black;
                siblingRbt->left->color = black;
                R_RotationRBT(root, rbt->parent);
                rbt = (*root);
            }
        }
    }
    rbt->color = black;
}

no *deleteRBT(no **root, no *delete){
    if (!(*root) || !delete) return NULL;
    if ((*root) == EXTERNAL || delete == EXTERNAL) return NULL;
    no *deleted = delete;
    no *auxSuccessor;
    no *successor = delete;
    colorBR color = successor->color;

    // Caso o no a ser deletado tenha algum filho == NULL.
    if (delete->left == EXTERNAL){
        auxSuccessor = (delete)->right;
        transferParent((root), delete, delete->right);
    }
    else if (delete->right == EXTERNAL){
            auxSuccessor = delete->left;
            transferParent((root), delete, delete->left);
    }
    else{
        successor = findSmalLestNo(delete->right);
        color = successor->color;
        auxSuccessor = successor->right;
        
        if (successor->parent == delete)
            auxSuccessor->parent = successor;

        else{
            transferParent((root), successor, successor->right);
            successor->right = delete->right;
            successor->right->parent = successor;
        }
        transferParent((root), delete, successor);
        successor->left = delete->left;
        successor->left->parent = successor;
        successor->color = delete->color;
        
    }

    if (color == black){
        balanceDelete((root), auxSuccessor);
    }
    return deleted;
}

void balance(no **root, no *newNo){
    no *parent;
    no *grandpa;
    no *uncle;
    while (isRed(newNo) && isRed((newNo)->parent))
    {
        parent = (newNo)->parent;
        grandpa = parent->parent;

        if (parent == parent->parent->left)
            uncle = grandpa->right;
        else if (parent == parent->parent->right)
            uncle = grandpa->left;

        if (isRed(uncle)){

            parent->color = black;
            uncle->color = black;
            grandpa->color = red;
            (newNo) = grandpa;
        }
        else if (parent == parent->parent->left){
            if (newNo == newNo->parent->right){
                (newNo)->color = black;
                grandpa->color = red;
                newNo = parent;
                L_RotationRBT(root, newNo);
                newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
            else{
                parent->color = black;
                grandpa->color = red;
                newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
        }
        else if (parent == parent->parent->right){
            if (newNo == newNo->parent->left){
                (newNo)->color = black;
                grandpa->color = red;
                newNo = parent;

                R_RotationRBT(root, newNo);
                newNo = grandpa;

                L_RotationRBT(root, newNo);
            }
            else{
                parent->color = black;
                grandpa->color = red;
                newNo = grandpa;
                L_RotationRBT(root, newNo);
            }
        }
    }
    (*root)->color = black;
}

no *insertRBT(no **root, void *inf, int infoComp(void *, void *)){
    no *position = *root;
    no *positionParent = EXTERNAL;
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

    if (positionParent == EXTERNAL)
        *root = newNo;
    else if (infoComp(inf, positionParent->inf) == -1)
        positionParent->left = newNo;
    else
        positionParent->right = newNo;
    
    balance(&(*root), newNo);
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
        printf("[");
        toStringInfoId(rbt->inf);
        printf(": %d]", rbt->color);
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