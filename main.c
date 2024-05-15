#include "system.h"

int main(){
    Lista lista;
    Funcionario *busca;
    char nome[MAXNAME];
    int user_op = 0;
    init_lista(&lista);
    ler_arquivo(&lista);

    do
    {
        user_op = menu();

        switch (user_op)
        {
        case 1:
            inserir_funcionario(&lista, ler_funcionario());
            criar_documento(&lista);
            break;
        case 2:
            printf("Digite o nome: ");
            gets(nome);
            busca = busca_funcionario(lista.inicio, nome);
            verifica_busca(busca);
            break;
        case 3:
            printf("Digite o nome: ");
            fgets(nome, MAXNAME, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            editar_funcionario(&lista, nome);
            break;
        case 4:
            printf("Digite o nome: ");
            fgets(nome, MAXNAME, stdin);
            nome[strcspn(nome, "\n")] = '\0';            
            busca = busca_funcionario(lista.inicio, nome);
            if (verifica_busca(busca)){
                remover_funcionario(&lista, busca);
                criar_documento(&lista);
            }
            break;
        case 5:
            gerar_relatorio(&lista);
            break;
        default:
            break;
        }
    } while (user_op != 6);
    
}