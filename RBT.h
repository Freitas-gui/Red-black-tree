// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#ifndef __RBT_H__
#define __RBT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {black, red} colorBR;

// Estrutura para representar um elemento da RBT.
typedef struct no{
    void *inf;
    struct no *right, *left, *parent;
    colorBR color;
}no;

// Cria um elemento da RBT.
no *createNo(void *inf);

extern no* EXTERNAL;

no *createNoExternal();

int positionChildFromParent(no *rbt);

no *uncle(no *rbt);

no *sibling(no *rbt);

int isleaf(no *rbt);

int isRed(no *rbt);

no *search(no *rbt , void *inf, int infoComp(void *, void *));

no *searchParent(no *rbt , void *inf, int infoComp(void *, void *));

void R_RotationRBT(no **root ,no *pivo);

void L_RotationRBT(no **root, no *pivo);

void transferParent(no **root, no *rbt, no *target);

no *findSmalLestNo(no *avl);

void balanceDelete(no **root, no *rbt);

void balance(no **root, no *newNo);

no *deleteRBT(no **root, no *delete);

no *insertRBT(no **root, void *inf, int infoComp(void *, void *));

void toStringRBT(no *rbt , int level, void *toStringInfoId(void *));

void toStringColorRBT(no *rbt , int level);




// // Retorna sub-arvore esquerda.
// no *leftRBT(no *rbt);

// // Retorna sub-arvore direita.
// no *rightRBT(no *rbt);

// // Retorna um elemento na RBT que tenha a mesma informacao fornecida no parametro 'inf'.
// // Se nao encontrado retorna NULl.
// no *search(no *rbt , void *inf, int infoComp(void *, void *));

// // Retorna a altura da RBT que eh relativa ao nivel maximo das folhas.
// int height(no *rbt);

// // Retorna o no considerado o menor elemento na RBT.
// no *findSmalLestNo(no *rbt);

// // Insercao na sub-arvore direita, da sub-arvore esquerda da raiz.
// // Rotacao dupla a direita.
// void LR_RotationRBT(no **rbt);

// // Insercao na sub-arvore esquerda, da sub-arvore direita da raiz.
// // Rotacao dupla a esquerda.
// void RL_RotationRBT(no **rbt);

// // Insercao na sub-arvore direita, da sub-arvore direita da raiz.
// // Rotacao a esquerda.
// void RR_RotationRBT(no **rbt);

// // Insercao na sub-arvore esquerda, da sub-arvore esquerda da raiz.
// // Rotacao a direita.
// void LL_RotationRBT(no **rbt);

// // Segunda parte para lidar com a logica de insercao balanceada. Utilizada pela insertRBT.
// // Se a insercao for bem sucedida, retorna o no que foi inserido, se o elemento ja existir,
// //na RBT, retorna NULL.
// no *auxInsertRBT(no **rbt, void *inf, int *growup, int infoComp(void *, void *));

// // Insere um novo elemento na RBT e realiza rotacoes caso necessario. Utiliza a auxInsertRBT.
// no *insertRBT(no **rbt, void *inf, int infoComp(void *, void *));

// // Deleta um elemento na RBT e realiza rotacoes caso necessario.
// no *deleteNo(no **rbt, void *inf, int infoComp(void *, void *) );

// // Imprime a RBT, visualmente rotacionada em um angulo de 90 graus anti-horario.
// void toStringRBT(no *rbt , int nivel, void *toStringInfoId(void *));

#endif // __RBT_H__
