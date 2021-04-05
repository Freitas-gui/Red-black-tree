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

// // Retorna a altura da AVL que eh relativa ao nivel maximo das folhas.
// int height(no *avl){
//     if (!avl)
//         return 0;
//     // Compara a altura da sub-arvore esquerda com a direita.
//     // Vai incrementando o valor da altura a cada retorno da chamada recursiva,
//     // ate que tenhamos o maior caminho possivel da raiz ate a folha de maior nivel.
//     else if( height(leftAVL(avl)) >= height(rightAVL(avl)) )
//         return 1 + height(leftAVL(avl));
//     else
//         return 1 + height(rightAVL(avl));
// }

// // Retorna o no considerado o menor elemento na AVL.
// no *findSmalLestNo(no *avl){
//     if(!avl) return NULL;
//     if(!(leftAVL(avl)))
//         return avl;
//     else
//         return findSmalLestNo(leftAVL(avl));
// }

// Insercao na sub-arvore direita, da sub-arvore direita da raiz.
// Rotacao a esquerda.
void R_RotationRBT(no **pivo){
    no *a = (*pivo)->right;

    // Redefinicoes de referencias.
    if ((*pivo)->parent != NULL){
        if ( (*pivo) == (*pivo)->parent->left)
            (*pivo)->parent->left = a;
        else
            (*pivo)->parent->right = a;
    }
    a->parent = (*pivo)->parent;

    (*pivo)->right = a->left;
    a->left->parent = (a->left == NULL) ? NULL : (*pivo);

    a->left = (*pivo);
    (*pivo)->parent = a;

    // A raiz da subárvore passada no parâmetro é atualizada.
    *pivo = a;
}

// Insercao na sub-arvore esquerda, da sub-arvore esquerda da raiz.
// Rotacao a direita.
void L_RotationRBT(no **pivo){

    // Redefinicoes de referencias.
    if ((*pivo)->parent != NULL){
        if ( (*pivo) == (*pivo)->parent->left)
            (*pivo)->parent->left = (*pivo)->left;
        else
            (*pivo)->parent->right = (*pivo)->left;
    }
    (*pivo)->left->parent = (*pivo)->parent;
    printf("\n\n aki S \n\n");
    
    if ((*pivo)->left->right)
        (*pivo)->left->right->parent = (*pivo);

    (*pivo)->parent = (*pivo)->left;

    // Redefinicoes de referencias.
    (*pivo)->left = (*pivo)->left->right;

    (*pivo)->parent->right = (*pivo);

    // A raiz da subárvore passada no parâmetro é atualizada.
    *pivo = (*pivo)->parent;
}

void balance3(no **rbt, no **root){
    if (!(*rbt)) return;
    printf("\n\nsimmm\n\n");

    if ((*rbt)->parent){
        if (isleaf(*rbt)){
            return;
        }
        
        if ((isleaf((*rbt)->left) || !(*rbt)->left) && (isleaf((*rbt)->right) || !(*rbt)->right)){
            return;
        }
    }

    if ((*rbt)->color == black){
        if ((*rbt)->left && (*rbt)->right){
            if (isRed((*rbt)->left) && isRed((*rbt)->right)){
                if (isRed((*rbt)->left->left) || isRed((*rbt)->left->right) || isRed((*rbt)->right->left) || isRed((*rbt)->right->right)){
                    (*rbt)->left->color = black;
                    (*rbt)->right->color = black;
                    (*rbt)->color = red;
                }
            }
        }
        
        if (isRed((*rbt)->left) && !isRed((*rbt)->right)){
            if (isRed((*rbt)->left->right))
                R_RotationRBT(&(*rbt)->left);
            if (isRed((*rbt)->left->left)){
                (*root)->left->color = black;
                (*root)->color = red;
                L_RotationRBT(rbt);
                printf("rotation");
            }
            // if (!(*rbt)->parent){
            //     // *root = rbt;
            //     return;
            // }
        }
    }
    
}

void balance2(no **rbt, no **root){
    if (!(*rbt)) return;
    printf("\n\nsimmm\n\n");

    if ((*rbt)->parent){
        if (isleaf(*rbt)){
            *rbt = (*rbt)->parent;
            return balance2(rbt, root);
        }
        
        if ((isleaf((*rbt)->left) || !(*rbt)->left) && (isleaf((*rbt)->right) || !(*rbt)->right)){
            *rbt = (*rbt)->parent;
            return balance2(rbt, root);
        }
    }

    if ((*rbt)->color == black){
        if ((*rbt)->left && (*rbt)->right){
            if (isRed((*rbt)->left) && isRed((*rbt)->right)){
                if (isRed((*rbt)->left->left) || isRed((*rbt)->left->right) || isRed((*rbt)->right->left) || isRed((*rbt)->right->right)){
                    (*rbt)->left->color = black;
                    (*rbt)->right->color = black;
                    (*rbt)->color = red;
                }
            }
        }
        
        if (isRed((*rbt)->left) && !isRed((*rbt)->right)){
            if (isRed((*rbt)->left->right))
                R_RotationRBT(&(*rbt)->left);
            if (isRed((*rbt)->left->left)){
                (*root)->left->color = black;
                (*root)->color = red;
                L_RotationRBT(root);
                printf("rotation");
            }
            // if (!(*rbt)->parent){
            //     root = rbt;
            //     return;
            // }
        }
    }
    
}

void balance(no **inserted, no **avl){

    if ( !(*inserted) || !(*inserted)->parent) return;
    if ((*inserted)->parent->color == black) return;

    // Caso 1: tio do novo no eh rubro.
    if (uncle(*inserted) && uncle(*inserted)->color == red){
        (*inserted)->parent->color = black;
        uncle(*inserted)->color = black;
        (*inserted)->parent->parent->color = red;

        return balance(&(*inserted)->parent->parent, avl);
    }

    else{
        if (positionChildFromParent((*inserted)->parent) == 1){
            switch (positionChildFromParent(*inserted)){
                case 1:
                    (*inserted)->parent->color = black;
                    (*inserted)->parent->parent->color = red;
                    L_RotationRBT(&(*inserted)->parent->parent);
                    break;
                case 0:
                    break;
                case -1:
                    R_RotationRBT(&(*inserted)->parent->parent);
                    balance(inserted, avl);
                    break;
            }
        }
        else if (positionChildFromParent((*inserted)->parent) == -1){
            switch (positionChildFromParent(*inserted)){
                case 1:
                     R_RotationRBT(&(*inserted)->parent->parent);
                     balance(inserted, avl);
                     break;
                case 0:
                    break;
                case -1:
                    (*inserted)->parent->color = black;
                    (*inserted)->parent->parent->color = red;
                    L_RotationRBT(&(*inserted)->parent->parent);
                    break;
            }
        }
    }
}

no *insertRBT(no **rbt, void *inf, int infoComp(void *, void *)){
    if ( *rbt == NULL ){
        // printf("aki");
        // Caso basico em que a rbt eh NULL, portanto rbt recebe um novo no que sera a sua raiz.
        *rbt = createNo(inf);

        // Insercao bem sucedida, retorna a informacao que foi inserida.
        return (*rbt);
    }

    // Se o no ja existe, o mesmo nao sera inserido, unico caso que retorna NULL.
    if (infoComp(inf, (*rbt)->inf) == 0) return NULL;

    no *inserted = NULL;
    // Insercao na sub-arvore esquerda.
    if (infoComp(inf, (*rbt)->inf) == -1){
        inserted = insertRBT(&(*rbt)->left, inf, infoComp);
        inserted->parent = searchParent(*rbt, inf, infoComp);
    }

    // insercao na sub-arvore direita.
    else if (infoComp(inf, (*rbt)->inf) == 1){
        inserted = insertRBT(&(*rbt)->right, inf, infoComp);
        inserted->parent = searchParent(*rbt, inf, infoComp);
    }

    if ((inserted->parent->parent) == NULL)
        inserted->parent->color = black;

    for (no *pivo = inserted; pivo; pivo = pivo->parent){
        balance3(&pivo, rbt);
    }
        
    return inserted;
}

// // Deleta um elemento na AVL e realiza rotacoes caso necessario.
// no *deleteNo(no **avl, void *inf, int infoComp(void *, void *) ){
//     // Caso basico em que a avl eh nula, portanto nao ha elemento para se deletar.
//     if (!(*avl))
//         return NULL;
//     no *deleted = createNo((*avl)->inf);
//     // Deleta elemento na sub-arvore esquerda.
//     if (infoComp(inf, (*avl)->inf) == -1)
//         deleted = deleteNo(&(*avl)->left, inf, infoComp);

//     // Deleta elemento na sub-arvore direita.
//     else if (infoComp(inf, (*avl)->inf) == 1)
//         deleted = deleteNo(&(*avl)->right, inf, infoComp);

//     // Caso tenha encontrado o elemento que deve ser deletado.
//     else{
//         // Caso o elemento que deve ser deletado tenha algum filho igual a NULL.
//         if( ((*avl)->left == NULL) || ((*avl)->right == NULL) ){
//             // temp utilizado para setar o novo valor de avl, apos a delecao.
//             no *temp;
//             if((*avl)->left)
//                 temp = (*avl)->left;
//             else
//                 temp = (*avl)->right;
//             // Caso o elemento seja um no folha.
//             if (temp == NULL){
//                 temp = *avl;
//                 *avl = NULL;
//             }
//             else
//                 **avl = *temp;
//             free(temp);
//         }
//         else{
//             // O no que deve ser deletado recebe uma sobrescrita de informacao do "temp" = (menor elemento de sua sub-arvore direita).
//             // Temp pode ser deletado pois sua informacao foi preservada,
//             // e a informacao do elemento que deveria ser deletado na chamada da funcao principal se perdeu.
//             no *temp = findSmalLestNo((*avl)->right);
//             (*avl)->inf = temp->inf;
//             deleteNo(&(*avl)->right, temp->inf, infoComp);
//         }
//     }
//     // Elemento deletado com sucesso, retorna o no que foi deletado, agora desconectado da AVL.
//     if ((*avl) == NULL)
//       return deleted;

//     // Recalculando o fator de balanceamento, apos a delecao.
//     (*avl)->balance = height((*avl)->left) - height((*avl)->right);

//     int balance = (*avl)->balance;

//     // Realiza as rotacoes necessarias, para rebalancear a AVL.
//     if (balance > 1 && (*avl)->left->balance >= 0)
//         LL_RotationRBT(avl);

//     else if (balance > 1 && (*avl)->left->balance < 0)
//         LR_RotationRBT(&(*avl)->left);

//     else if (balance < -1 && (*avl)->right->balance <= 0)
//         RR_RotationAVL(avl);

//     else if (balance < -1 && (*avl)->right->balance > 0)
//         RL_RotationAVL(&(*avl)->right);

//     // Elemento deletado com sucesso, arvore balanceada, retorna o no que foi deletado, agora desconectado da AVL.
//     return deleted;
// }

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
