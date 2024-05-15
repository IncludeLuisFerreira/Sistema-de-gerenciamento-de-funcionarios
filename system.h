#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOCERROR "Erro ao alocar memoria dinamicamente.\n"
#define NOTFOUND    "Funcionario nao encontrado.\n"
#define DATAERROR   "Erro ao abrir/criar arquivo.\n"
#define MAXNAME     50
#define MAXCARGO    30

typedef struct funcionario{
    char nome[50];
    int idade;
    float salario;
    char cargo[30];
    struct funcionario *prox;
}Funcionario;

typedef struct lista{
    Funcionario *inicio;
    int TAM;
}Lista;

int menu(){
    int user_op;
    printf("\n1-Cadastro de funcionário.\n"
    "2-Busca de funcionário por nome.\n"
    "3-Edição de informações de um funcionário\n"
    "4-Remoção de um funcionário\n"
    "5-Geração de relatórios em arquivos\n: "
    );
    scanf("%d", &user_op);
    fflush(stdin);
    return user_op;
}

void init_lista(Lista *ptr){
    ptr->inicio = NULL;
    ptr->TAM = 0;
}

Funcionario ler_funcionario(){
    Funcionario f;

    printf("Nome: ");
    fgets(f.nome,MAXNAME,stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &f.idade); 
    fflush(stdin);

    printf("Cargo: ");
    fgets(f.cargo,MAXCARGO,stdin);
    f.cargo[strcspn(f.cargo, "\n")] = '\0';

    printf("Salário: ");
    scanf("%f", &f.salario);

    return f;
}

void swap(Funcionario *a, Funcionario *b){
    Funcionario temp = *a;
    *a = *b;
    *b = temp;
}

int particiona_idade(Funcionario vetor[], int inicio, int fim){
    int pivo = vetor[fim].idade;
    int i = inicio - 1;
    
    for (int j = inicio; j <= fim - 1; j++)
    {
        if(vetor[j].idade < pivo)
        {
            i++;
            swap(&vetor[j], &vetor[i]);
        }
    }
    swap(&vetor[i + 1], &vetor[fim]);

    return i + 1;
}

int particiona_nome(Funcionario vetor[], int inicio, int fim){
    char *pivo = vetor[fim].nome;
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++)
    {
        if (strcmp(vetor[j].nome, pivo) < 0)
        {
            i++;
            swap(&vetor[j], &vetor[i]);
        }
    }
    swap(&vetor[i + 1], &vetor[fim]);
    
    return i + 1;
}

int particiona_cargo(Funcionario vetor[], int inicio, int fim){
    char *pivo = vetor[fim].cargo;
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++)
    {
        if (strcmp(vetor[j].cargo, pivo) < 0)
        {
            i++;
            swap(&vetor[j], &vetor[i]);
        }
    }
    swap(&vetor[i + 1], &vetor[fim]);
    
    return i + 1;
}

int particiona_salario(Funcionario vetor[], int inicio, int fim){
    float pivo = vetor[fim].salario;
    int i = inicio - 1;
    
    for (int j = inicio; j <= fim - 1; j++)
    {
        if(vetor[j].salario < pivo)
        {
            i++;
            swap(&vetor[j], &vetor[i]);
        }
    }
    swap(&vetor[i + 1], &vetor[fim]);

    return i + 1;
}

void quickSort_nome(Funcionario vetor[], int inicio, int fim){
    if (inicio < fim)
    {
        int pi = particiona_nome(vetor, inicio, fim);
        quickSort_nome(vetor, inicio, pi - 1);
        quickSort_nome(vetor, pi + 1, fim);
    }
}

void quickSort_idade(Funcionario vetor[], int inicio, int fim){
    if (inicio < fim)
    {
        int pi = particiona_idade(vetor, inicio, fim);
        quickSort_idade(vetor, inicio, pi - 1);
        quickSort_idade(vetor, pi + 1, fim);
    }
}

void quickSort_salario(Funcionario vetor[], int inicio, int fim){
    if (inicio < fim)
    {
        int pi = particiona_salario(vetor, inicio, fim);
        quickSort_salario(vetor, inicio, pi - 1);
        quickSort_salario(vetor, pi + 1, fim);
    }
}

void quickSort_cargo(Funcionario vetor[], int inicio, int fim){
    if (inicio < fim)
    {
        int pi = particiona_cargo(vetor, inicio, fim);
        quickSort_cargo(vetor,inicio, pi - 1);
        quickSort_cargo(vetor, pi + 1, fim);
    }
}


void inserir_funcionario(Lista *lista, Funcionario nod){
    Funcionario *novo = (Funcionario*)malloc(sizeof(Funcionario));
    if(novo)
    {
        *novo = nod;
        if(!lista->inicio)
        {
            lista->inicio = novo;
            novo->prox = NULL;
        }
        else
        {
            Funcionario *aux = lista->inicio;
            while(aux->prox)
                aux = aux->prox;
            aux->prox = novo;
            novo->prox = NULL;
        }
        lista->TAM++;
    }
    else
    {
        printf(MALLOCERROR);
    }
}

void remover_funcionario(Lista *lista, Funcionario *nod){
    Funcionario *remover = NULL, *aux = lista->inicio;

    if(lista->inicio)
    {
        if (lista->inicio == nod)
        {
            remover = lista->inicio;
            lista->inicio = remover->prox;
        }
        else
        {
            while(aux->prox != nod)
                aux = aux->prox;
            remover = aux->prox;
            aux->prox = remover->prox;
            
        }
        lista->TAM--;
        free(remover);
        remover = NULL;
    }
    else
    {
        printf(NOTFOUND);
    }
}

Funcionario* busca_funcionario(Funcionario *inicio, const char nome[50]){
    if(inicio)
    {
        if(strcmp(inicio->nome, nome) == 0)
            return inicio;
        else
            return busca_funcionario(inicio->prox, nome);
    }
    return NULL;
}

void editar_funcionario(Lista *lista, const char nome[50]){
    if (lista->inicio)
    {
        Funcionario *aux = lista->inicio, *backup;
        while(aux)
        {
            if (strcmp(aux->nome, nome) == 0)
            {
                backup = aux->prox;
                *aux = ler_funcionario();
                aux->prox = backup;
                printf("Funcionário editado com sucesso.\n");
                return ;
            }
            aux = aux->prox;
        }
    }
}

int verifica_busca(Funcionario *ptr){
    if(ptr)
    {
        printf("\n\n- Nome: %s\n", ptr->nome);
        printf("- Idade: %d anos\n", ptr->idade);
        printf("- Cargo: %s\n", ptr->cargo);
        printf("- Salário: R$ %.2f\n", ptr->salario);
        return 1;
    }
    else
    {
        printf(NOTFOUND);
        return 0;
    }
}

void print_lista_funcioanarios(Lista *lista){
    Funcionario *aux = lista->inicio;
    while(aux)
    {
        printf("\n- Nome: %s\n", aux->nome);
        printf("- Idade: %d anos\n", aux->idade);
        printf("- Cargo: %s\n", aux->cargo);
        printf("- Salário: R$ %.2f\n", aux->salario);
        aux = aux->prox;
    }
    printf("\n\n");
}

int descobre_quantidade_funcionarios(FILE *arq, Lista *ptr){
    Funcionario aux;
    int count = 0;
    while(!feof(arq))
    {
        if (fscanf(arq, "%s %d %f %s\n", aux.nome, aux.idade, aux.salario, aux.cargo))
        {
            count++;
            inserir_funcionario(ptr, aux);
        }
    }
    return count;
}

void ler_arquivo(Lista *ptr){
    FILE *func_arq = fopen("Funcionarios.dat", "rb");
    Funcionario aux;
    int count = 0;

    if (func_arq)
    {
        while(!feof(func_arq))
        {
            if (fread(&aux, sizeof(Funcionario), 1, func_arq))
            {
                inserir_funcionario(ptr, aux);
                count++;
            }
        }
        fclose(func_arq);
        printf("%d funcionários registrados.\n", count);
    }
    else
    {
        printf(DATAERROR);
    }
}

void criar_documento(Lista *lista){
    FILE *func_arq = fopen("Funcionarios.dat", "wb");
    Funcionario *inicio = lista->inicio;

    if (func_arq)
    {
        while (inicio)
        {
            fwrite(inicio, sizeof(Funcionario), 1, func_arq);
            inicio = inicio->prox;
        }
        fclose(func_arq);
    }
}

void gerar_relatorio_nao_ordenado(Lista *lista){
    FILE *arq = fopen("relatorio_funcionario.txt", "w");
 
    if (arq)
    {
        Funcionario *aux = lista->inicio;
        if(aux){
            while(aux)
            {
                fprintf(arq, "%s %d %.2f %s\n", aux->nome, aux->idade, aux->salario, aux->cargo);
                aux = aux->prox;
            }
        }
        fclose(arq);
    }
    else
    {
        printf(DATAERROR);
    }
}

void ordenar(Funcionario vetor[], int n, int type){

    switch (type)
    {
    case 1:
        quickSort_nome(vetor, 0, n - 1);
        break;
    case 2:
        quickSort_idade(vetor, 0, n - 1);
        break;
    case 3:
        quickSort_salario(vetor, 0, n - 1);
        break;
    case 4:
        quickSort_cargo(vetor, 0, n - 1);
        break;
    }
}

void gerar_relatorio(Lista *lista){
    Funcionario vetor[lista->TAM], *aux = lista->inicio;
    int user_op;

    for (int i = 0; i < lista->TAM; i++)
    {
        vetor[i] = *aux;
        aux = aux->prox;
    }

    do
    {
        printf("\n---ESCOLHA A FORMA DE SAIDA DO ARQUIVO---\n");
        printf("1-Ordenar por ordem alfabetica.\n"
        "2-Ordenar por idade.\n"
        "3-Ordenar por salário.\n"
        "4-Ordenar por cargo.\n"
        "5-Nao ordenar.\n");
        scanf("%d", &user_op);

    }while(user_op <= 0 || user_op > 5);

    if (user_op != 5)
        ordenar(vetor, lista->TAM, user_op);
    else
        gerar_relatorio_nao_ordenado(lista);

    FILE *arq = fopen("relatorio_funcionario.txt", "w");

    if (arq)
    {
        fprintf(arq,"\t\t\t\t\t\t\t\t\t---RELATÓRIOS DE FUNCIONÁRIOS---\n");
        switch (user_op)
        {
        case 1:
            fprintf(arq,"Ordenação --- alfabética\n\n");
            break;
        case 2:
            fprintf(arq,"Ordenação --- idade\n\n");
            break;
        case 3:
            fprintf(arq,"Ordenação --- salário\n\n");
            break;
        case 4:
            fprintf(arq,"Ordenação --- cargo\n\n");
            break;
        case 5:
            fprintf(arq,"Ordenação --- não ordenado\n\n");
            break;
        }

        fprintf(arq,"%20s %20s %20s %20s\n", "NOME", "IDADE", "SALÁRIO", "CARGO");
        for (int i = 0; i < lista->TAM; i++)
        {
            fprintf(arq, "%22s | %15d | %18.2f | %20s |\n", vetor[i].nome, vetor[i].idade, vetor[i].salario, vetor[i].cargo);
        }
        fclose(arq);
    }
    else
    {
        printf(DATAERROR);
    }
}

#endif