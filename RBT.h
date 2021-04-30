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

// No externo da RBT, o pai da raiz
// e as sub-arvores dos nos que nao possuem filhos como elementos de informacao
// a esquerda ou a direita deve apontar para ele.
extern no* EXTERNAL;

// Cria e retorna o elemento EXTERNO da RBT.
no *createNoExternal();

// Cria e retorna um elemento da RBT com informacao.
// Informacao que o no deve armazenar.
no *createNo(void *inf);

// Retorna 1 se o valor de color do no eh red e 0 se for black.
// rbt = elemento que deseja-se saber a cor.
int isRed(no *rbt);

// Procura e retorna um elemento na RBT que tenha a mesma informacao fornecida no parametro 'inf'.
// rbt = raiz da arvore.
// inf = informacao buscada.
// infoComp = funcao para comparar informacoes. 
no *search(no *rbt , void *inf, int infoComp(void *, void *));

// Rotacao a esquerda.
// root = raiz da arvore.
// pivo = elemento pivo do no que desbalanceou a arvore.
void L_RotationRBT(no **root, no *pivo);

// Rotacao a direita.
// root = raiz da arvore.
// pivo = elemento pivo do no que desbalanceou a arvore.
void R_RotationRBT(no **root, no *pivo);

// Transfere o pai do no rbt para o no target.
void transferParent(no **root, no *rbt, no *target);

// Retorna o no considerado o menor elemento na sub-arvore de raiz = rbt.
// avl = raiz da subarvore que a funcao comeca a busca.
no *findSmalLestNo(no *rbt);

// Utilizada na remocao, para rebalancear a arvore apos o elemento ser deletado.
// root = raiz da arvore.
// rbt = elemento com uma color black adicional que causou o desbalanceamento.
void balanceDelete(no **root, no *rbt);

// Remove um elemento da arvore.
// root = raiz da arvore.
// delete = elemento que deve ser deletado.
no *deleteRBT(no **root, no *delete);

// Utilizada na incercao, para rebalancear a arvore apos o elemento ser inserido.
// root = raiz da arvore.
// newNo = elemento que causou o desbalanceamento.
void balance(no **root, no *newNo);

// Insere um elemento na arvore.
// root = raiz da arvore.
// inf = elemento de informacao que deve ser inserido.
no *insertRBT(no **root, void *inf, int infoComp(void *, void *));

// Imprime a RBT, visualmente rotacionada em um angulo de 90 graus anti-horario.
// Ex de uma chave impressa abaixo com um elemento de color = black.
// [12: 0]
void toStringRBT(no *rbt , int level, void *toStringInfoId(void *));


#endif // __RBT_H__
