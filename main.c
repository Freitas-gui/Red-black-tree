// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#include "RBT.h"

// Estrutura para representar uma informacao que se refere ao cadastro de uma pessoa.
typedef struct article{
    int id;
    int year;
    char *author;
    char *title;
    char *magazine;
    char *DOI;
    char *keyword;
}article;

article *createArticle(int id, int year, char author[], char title[], char magazine[], char DOI[], char keyword[]){
    // Aloca espaco de memoria.
    article *newArticle = (article*)malloc(sizeof(article));
    char *newAuthor = (char*)malloc(sizeof(char)*(strlen(author)));
    char *newTitle = (char*)malloc(sizeof(char)*(strlen(title)));
    char *newMagazine = (char*)malloc(sizeof(char)*(strlen(magazine)));
    char *newDOI = (char*)malloc(sizeof(char)*(strlen(DOI)));
    char *newKeyword = (char*)malloc(sizeof(char)*(strlen(keyword)));

    if(!newArticle || !newAuthor || !newTitle || !newMagazine || !newDOI || !newKeyword)
        return NULL;
    else{
        // Copia o valor passado no parametro para o novo espaco de memoria alocado.
        strcpy(newAuthor, author);
        strcpy(newTitle, title);
        strcpy(newMagazine, magazine);
        strcpy(newDOI, DOI);
        strcpy(newKeyword, keyword);
        

        // Se tiver conseguido alocar, entao seta os valores novo article.
        newArticle->id = id;
        newArticle->author = newAuthor;
        newArticle->title = newTitle;
        newArticle->magazine = newMagazine;
        newArticle->DOI = newDOI;
        newArticle->keyword = newKeyword;
        newArticle->year = year;

        return newArticle;
    }
}

// Imprime todos os valores da articlermacao de uma pessoa em formato JSON.
void toStringarticle(article *inf){
    if (!inf) return;
    printf("article {\n id : %d,", inf->id);
    printf("\n author : %s,", inf->author);
    printf("\n title : %s,", inf->title);
    printf("\n magazine : %s,", inf->magazine);
    printf("\n DOI : %s,", inf->DOI);
    printf("\n keyword : %s,", inf->keyword);
    printf("\n year : %d \n}", inf->year);
}

// Imprime o valor do id de uma pessoa.
void toStringArticleid(article *inf){
    printf("%d", inf->id);
}
// Ponteiro para usar toStringArticleid dentro das funcoes de AVL, que manipulam tipo generico de dados.
void (*toStringArticleid_ptr)(article *) = &toStringArticleid;

// Verifica se o id de (a) é menor, igual ou maior que (b).
int articleComp(article *a, article *b){
    if (a->id < b->id) return -1;
    if (a->id == b->id) return 0;
    if (a->id > b->id) return 1;
}
// Ponteiro para usar articleComp dentro das funcoes de AVL, que manipulam tipo generico de dados.
int (*articleComp_ptr)(article *, article *) = &articleComp;

// Limpa o buffer do teclado, utilizado apos um scanf.
void cleanBuffer(){
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main()
{
    EXTERNAL = createNoExternal();
    int op;
    // Estrutura utilizada para inserir, deletar e mostrar dados de pessoas.
	no *rbt = NULL;
    
    while(op != 5){
        // Menu para orientar a interacao com o usuario.
        printf("\n1 INSERIR UMA PESSOA\n");
        // printf("\n2 REMOVER UMA PESSOA\n");
        printf("\n2 INSERIR ALEATORIAMENTE VARIAS PESSOAS\n");
        // printf("\n3 PROCURAR UMA PESSOA \n");
        printf("\n3 IMPRIMIR A ARVORE POR COR \n");
        printf("\n4 IMPRIMIR A ARVORE POR ID \n");
        printf("\n5 SAIR\n");
        printf("\nDIGITE UM NUMERO PARA ESCOLHER SUA OPCAO: ");

        scanf("%d", &op);
        cleanBuffer();

        switch (op){
            char author[200];
            char title[200];
            char magazine[200];
            char DOI[20];
            char keyword[200];
            int year, id;
            article *inf;
            no *deleted, *inserted, *searched;

            case 0:
                printf("Digite um numero inteiro para representar o id da pessoa a ser buscada: ");
                scanf("%d", &id);
                cleanBuffer();

                inf = createArticle(id, 0, "", "", "", "", "");
                searched = search(rbt, inf, articleComp_ptr);
                // printf("\n");
                // toStringarticle(searched->inf);
                // printf("\n");
                if (!searched || searched == EXTERNAL) break;
                    deleted = deleteRBT(&rbt, searched);

                printf("\n");
                if (deleted)
                    toStringarticle(deleted->inf);
                printf("\n");

                // callBackRevert(&searched);

                break;

            // Insere um elemento na arvore.
            case 1:
                printf("Digite um numero inteiro para representar o id da pessoa a ser cadastrada: ");
                scanf("%d", &id);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%200s", author);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%200s", title);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%200s", magazine);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%20s", DOI);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%200s", keyword);
                cleanBuffer();

                printf("Digite a idade da pessoa: ");
                scanf("%d", &year);
                cleanBuffer();

                inf = createArticle(id, year, author, title, magazine, DOI, keyword);
                insertRBT(&rbt, inf, articleComp_ptr);
                
                break;

            case 2:
                // srand(time(NULL));
                // int range = 0;
                // printf("Digite a quantidade de elementos aleatorios que deseja inserir: ");
                // scanf("%d", &range);
                // for(int index = 0; index < range; index ++){
                //     inf = createArticle(rand() % 1000, "Aleatorio", 0);
                //     insertRBT(&rbt, inf, articleComp_ptr);
                // }
            case 3:
                printf("\n");
                toStringColorRBT(rbt, 0);
                break;
            case 4:
                printf("\n");
                toStringRBT(rbt, 0, toStringArticleid_ptr);
                break;
        }
    }
}
