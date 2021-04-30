// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#include "RBT.h"

// No externo da RBT.
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

// Cria um elemento da RBT com informacao.
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

// Informa se o no eh vermelho.
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
    // Ou seja, se inf existir na RBT, ele estara na subarvore esquerda.
    else if(infoComp(rbt->inf, inf) == 1)
        return search(rbt->left, inf, infoComp);
    // Caso rbt->inf seja considerada menor que inf, pelo faotr de comparacao.
    // Ou seja, se inf existir na RBT, ele estara na subarvore direita.
    else
        return search(rbt->right, inf, infoComp);
}

// Rotacao a esquerda.
void L_RotationRBT(no **root, no *pivo){
    no *y = (pivo)->right;

    // Redefinicoes de referencias.
    (pivo)->right = y->left;
    if (pivo->right != EXTERNAL)
        pivo->right->parent = (pivo);
    y->parent = (pivo)->parent;

    if ((pivo)->parent == EXTERNAL)
        // Atualiza raiz da RBT.
        *root = y;
    else if ((pivo) == (pivo)->parent->left)
        (pivo)->parent->left = y;
    else 
        (pivo)->parent->right = y;

    y->left = (pivo);
    (pivo)->parent = y;
}

// Rotacao a direita.
void R_RotationRBT(no **root, no *pivo){
    no *y = (pivo)->left;

    // Redefinicoes de referencias.
    (pivo)->left = y->right;
    if ((pivo)->left != EXTERNAL)
        pivo->left->parent = (pivo);
    y->parent = (pivo)->parent;

    if ((pivo)->parent == EXTERNAL)
        // Atualiza raiz da RBT.
        *root = y;
    else if ((pivo) == (pivo)->parent->left)
        (pivo)->parent->left = y;
    else
        (pivo)->parent->right = y;

    y->right = (pivo);
    (pivo)->parent = y;
}

// Transfere o pai do no rbt para o no target.
void transferParent(no **root, no *rbt, no *target){
    if (rbt->parent == EXTERNAL){
        // Caso o rbt seja a raiz da arvore.
        // Atualiza a raiz.
        *root = target;
    }
    // Caso rbt seja filho a esquerda de seu pai.
    else if (rbt == rbt->parent->left)
        rbt->parent->left = target;
    else
    // Caso rbt seja filho a direita de seu pai.
        rbt->parent->right = target;
    target->parent = rbt->parent;
}

// Retorna o no considerado o menor elemento na sub-arvore de raiz = rbt.
no *findSmalLestNo(no *rbt){
    if(!rbt || rbt == EXTERNAL) return EXTERNAL;
    // O menor elemento eh o proprio rbt, caso ele nao tenha filho a esquerda.
    if(!(rbt->left) || rbt->left == EXTERNAL)
        return rbt;
    else
        // O menor elemento eh o no mais a esquerda de rbt.
        return findSmalLestNo(rbt->left);
}

// Utilizada na remocao, para rebalancear a arvore apos o elemento ser deletado.
void balanceDelete(no **root, no *rbt){
    no *siblingRbt;

    // O loop se repete ate que a cor preta extra deixa de existir.
    while (rbt != (*root) && rbt->color == black)
    {
        // Caso rbt seja filho a esquerda de seu pai.
        if (rbt == rbt->parent->left){
            siblingRbt = rbt->parent->right;
            // Caso 1: O irmao de rbt eh vermelho.
            if (siblingRbt->color == red){
                siblingRbt->color = black;
                rbt->parent->color = red;
                L_RotationRBT(root, rbt->parent);
                siblingRbt = rbt->parent->right;
            }
            // Caso 2: O irmao de rbt eh negro e os 2 filhos deste irmao tambem sao negros.
            if (siblingRbt->left->color == black && siblingRbt->right->color == black){
                siblingRbt->color = red;
                rbt = rbt->parent;
            }

            else{
                 if (siblingRbt->right->color == black){
                    // Caso 3: O irmao de rbt eh negro,
                    // e este irmao tem filho a esquerda vermelho e filho a direita negro.
                    siblingRbt->left->color = black;
                    siblingRbt->color = red;
                    R_RotationRBT(root, siblingRbt);
                    siblingRbt = rbt->parent->right;
                }
                // Caso 4: O irmao de rbt eh negro,
                // e este irmao tem filho a direita vermelho.
                siblingRbt->color = rbt->parent->color;
                rbt->parent->color = black;
                siblingRbt->right->color = black;
                L_RotationRBT(root, rbt->parent);
                // Para sair do loop.
                rbt = (*root);
            }
        }
        // Caso rbt seja filho a direita de seu pai.
        else {
            siblingRbt = rbt->parent->left;
            // Caso 1: O irmao de rbt eh vermelho.
            if (siblingRbt->color == red){

                siblingRbt->color = black;
                rbt->parent->color = red;
                R_RotationRBT(root, rbt->parent);
                siblingRbt = rbt->parent->left;
            }
            // Caso 2: O irmao de rbt eh negro e os 2 filhos deste irmao tambem sao negros.
            if (siblingRbt->left->color == black && siblingRbt->right->color == black){
                siblingRbt->color = red;
                rbt = rbt->parent;
            }

            else{
                // Caso 3: O irmao de rbt eh negro,
                // e este irmao tem filho a direita vermelho e filho a esquerda negro.
                 if (siblingRbt->left->color == black){
  
                    siblingRbt->right->color = black;
                    siblingRbt->color = red;
                    L_RotationRBT(root, siblingRbt);
                    siblingRbt = rbt->parent->left;
                }
                // Caso 4: O irmao de rbt eh negro,
                // e este irmao tem filho a esquerda vermelho.
                siblingRbt->color = rbt->parent->color;
                rbt->parent->color = black;
                siblingRbt->left->color = black;
                R_RotationRBT(root, rbt->parent);
                // Para sair do loop.
                rbt = (*root);
            }
        }
    }
    rbt->color = black;
}

// Remove um elemento da arvore.
no *deleteRBT(no **root, no *delete){
    // Caso nao seja possivel deletar o elemento retorna NULL para informar isso.
    if (!(*root) || !delete) return NULL;
    if ((*root) == EXTERNAL || delete == EXTERNAL) return NULL;
    
    no *deleted = delete;
    no *auxSuccessor;
    no *successor = delete;
    // Para nao perder a cor original de sucessor, pois esta pode ser sobreescrita.
    colorBR originalColor = successor->color;

    // Caso o no a ser deletado tenha algum filho == EXTERNAL.
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
        originalColor = successor->color;
        auxSuccessor = successor->right;
        
        // Caso o sucessor seja filho a direita do no deletado.
        if (successor->parent == delete)
            auxSuccessor->parent = successor;
        // Caso o filho a direita do no deletado tenha filho a esquerda.
        else{
            transferParent((root), successor, successor->right);
            successor->right = delete->right;
            successor->right->parent = successor;
        }
        // O no deletado eh desacoplado da arvore e o sucessor ocupa a sua posicao e cor.
        transferParent((root), delete, successor);
        successor->left = delete->left;
        successor->left->parent = successor;
        successor->color = delete->color;
    }
    // Se o sucessor tinha color = black, houve um desbalanceamento.s
    // Eh como se auxSucessor tivesse uma cor preta a mais.
    if (originalColor == black){
        balanceDelete((root), auxSuccessor);
    }
    return deleted;
}

// Utilizada na incercao, para rebalancear a arvore apos o elemento ser inserido.
void balance(no **root, no *newNo){
    no *parent, *grandpa, *uncle;

    // Nao pode haver um elemento vermelho com pai vermelho.
    while (isRed(newNo) && isRed((newNo)->parent))
    {
        parent = (newNo)->parent;
        grandpa = parent->parent;
        // Caso o pai de newNo seja filho a esquerda de seu pai, o tio sera filho a direita.
        if (parent == parent->parent->left)
            uncle = grandpa->right;
        // Caso o pai de newNo seja filho a direita de seu pai, o tio sera filho a esquerda..
        else if (parent == parent->parent->right)
            uncle = grandpa->left;

        // Caso 1: O tio de newNo eh rubro.
        if (isRed(uncle)){
            parent->color = black;
            uncle->color = black;
            grandpa->color = red;
            (newNo) = grandpa;
        }
        else if (parent == parent->parent->left){
            // Caso 2: o tio de newNo eh Negro e newNo eh filho a direita de seu pai.
            if (newNo == newNo->parent->right){
                (newNo)->color = black;
                grandpa->color = red;
                newNo = parent;
                L_RotationRBT(root, newNo);
                newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
            // Caso 3: o tio de newNo eh Negro e newNo eh filho a esquerda de seu pai.
            else{
                parent->color = black;
                grandpa->color = red;
                newNo = grandpa;
                R_RotationRBT(root, newNo);
            }
        }
        else if (parent == parent->parent->right){
            // Caso 2: o tio de newNo eh Negro e newNo eh filho a esquerda de seu pai.
            if (newNo == newNo->parent->left){
                (newNo)->color = black;
                grandpa->color = red;
                newNo = parent;

                R_RotationRBT(root, newNo);
                newNo = grandpa;
                L_RotationRBT(root, newNo);
            }
            // Caso 3: o tio de newNo eh Negro e newNo eh filho a direita de seu pai.
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

// Insere um elemento na arvore.
no *insertRBT(no **root, void *inf, int infoComp(void *, void *)){
    no *position = *root;
    no *positionParent = EXTERNAL;
    // Novo elemento que deve ser inserido.
    no *newNo = createNo(inf);

    // Loop para encontrar a posicao que o elemento deve ser inserido.
    while (position && position != EXTERNAL)
    {
        // Caso ja exista um elemento equivalente ao novo no, nao insere. 
        if (infoComp(inf, position->inf) == 0){
            free(newNo);
            return NULL;
        }
        // Armazena o valor do elemento que deve ser o pai do novo no.
        positionParent = position;
        // Decide se deve inserir na sub-arvore esquerda ou direita.
        if (infoComp(inf, position->inf) == -1)
            position = position->left;
        else
            position = position->right;
    }

    // Define o pai do novo no.
    newNo->parent = positionParent;

    if (positionParent == EXTERNAL)
        *root = newNo;
    else if (infoComp(inf, positionParent->inf) == -1)
        positionParent->left = newNo;
    else
        positionParent->right = newNo;
    
    // Rebalancea a arvore.
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