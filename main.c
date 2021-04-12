// Guilherme Freitas da Silva
// Gustavo Henrique Vago Brunetti

#include "RBT.c"

// Estrutura para representar uma informacao que se refere ao cadastro de uma pessoa.
typedef struct info{
    int id;
    char *name;
    int age;
}info;

info *createInfo(int id, char name[], int age){
    // Aloca espaco de memoria.
    info *newInfo = (info*)malloc(sizeof(info));
    char *newName = (char*)malloc(sizeof(char)*(strlen(name)));

    if(!newInfo || !newName)
        return NULL;
    else{
        // Copia o valor passado no parametro para o novo espaco de memoria alocado.
        strcpy(newName, name);

        // Se tiver conseguido alocar, entao seta os valores novo info.
        newInfo->id = id;
        newInfo->name = newName;
        newInfo->age = age;

        return newInfo;
    }
}

// Imprime todos os valores da informacao de uma pessoa em formato JSON.
void toStringInfo(info *inf){
    if (!inf) return;
    printf("info {\n id : %d,", inf->id);
    printf("\n nome : %s,", inf->name);
    printf("\n idade : %d \n}", inf->age);
}

// Imprime o valor do id de uma pessoa.
void toStringInfoid(info *inf){
    printf("%d\n", inf->id);
}
// Ponteiro para usar toStringInfoid dentro das funcoes de AVL, que manipulam tipo generico de dados.
void (*toStringInfoid_ptr)(info *) = &toStringInfoid;

// Verifica se o id de (a) é menor, igual ou maior que (b).
int infoComp(info *a, info *b){
    if (a->id < b->id) return -1;
    if (a->id == b->id) return 0;
    if (a->id > b->id) return 1;
}
// Ponteiro para usar infoComp dentro das funcoes de AVL, que manipulam tipo generico de dados.
int (*infoComp_ptr)(info *, info *) = &infoComp;

// Limpa o buffer do teclado, utilizado apos um scanf.
void cleanBuffer(){
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main()
{
    int op;
    // Estrutura utilizada para inserir, deletar e mostrar dados de pessoas.
	no *rbt = NULL;

    while( op != 5){
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
            char name[30];
            int age, id;
            info *inf;
            no *deleted, *inserted, *searched;

            case 0:
                printf("Digite um numero inteiro para representar o id da pessoa a ser buscada: ");
                scanf("%d", &id);
                cleanBuffer();

                // inf = createInfo(9, name, age);
                // rbt = createNo(inf);

                // inf = createInfo(8, name, age);
                // inserted = createNo(inf);
                // rbt->left = inserted;
                // inserted->parent = rbt;

                // inf = createInfo(7, name, age);
                // deleted = createNo(inf);
                // inserted->left = deleted;
                // deleted->parent = inserted;

                // inf = createInfo(6, name, age);
                // inserted = createNo(inf);
                // deleted->left = inserted;
                // inserted->parent = deleted;

                // inf = createInfo(5, name, age);
                // deleted = createNo(inf);
                // inserted->left = deleted;
                // deleted->parent = inserted;

                inf = createInfo(id, "name", 0);
                searched = search(rbt, inf, infoComp_ptr);
                // printf("\n");
                // toStringInfo(searched->inf);
                // printf("\n");
                if (!searched) break;
                    deleted = deleteRBT(&rbt, &searched, infoComp_ptr);

                printf("\n");
                toStringInfo(deleted->inf);
                printf("\n");
                
                // callBackRevert(&searched);

                break;

            // Insere um elemento na arvore.
            case 1:
                printf("Digite um numero inteiro para representar o id da pessoa a ser cadastrada: ");
                scanf("%d", &id);
                cleanBuffer();

                printf("Digite o primeiro nome da pessoa: ");
                scanf("%30s", name);
                cleanBuffer();

                printf("Digite a idade da pessoa: ");
                scanf("%d", &age);
                cleanBuffer();

                inf = createInfo(id, name, age);
                inserted = insertRBT(&rbt, inf, infoComp_ptr);


                if( inserted == NULL )
                    printf("\nErro: id ja existente\n");
                else{
                    printf("\n");
                    toStringInfo(inserted->inf);
                    printf("\n");
                }
                break;

            case 2:
                srand(time(NULL));
                int range = 0;
                printf("Digite a quantidade de elementos aleatorios que deseja inserir: ");
                scanf("%d", &range);
                for(int index = 0; index < range; index ++){
                    inf = createInfo(rand() % 1000, "Aleatorio", 0);
                    inserted = insertRBT(&rbt, inf, infoComp_ptr);
                }
            case 3:
                printf("\n");
                toStringColorRBT(rbt, 0);
                break;
            case 4:
                printf("\n");
                toStringRBT(rbt, 0, toStringInfoid_ptr);
                break;
        }
    }
}
