/*----------------------------------------------------------------------------------*/
/*                                FATEC-Ipiranga                                    */        
/*                            ADS - Estrutura de Dados                              */
/*                             Id da Atividade: EDI-Atividade-N1-4                  */
/*                                                                                  */
/*             Objetivo: O objetivo desta atividade ´e dar continuidade ao          */
/*                          desenvolvimento do sistema de gerenciamento de fila de  */
/*                       atendimento hospitalar, utilizando a estrutura de          */
/*                        dados do tipo Fila Dinamica Encadeada na linguagem C.     */
/*                                                                                  */
/*                                  Autor: Ana Beatriz Ximenes Amaral               */
/*                                                                   Data:14/09/2026*/
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int id;
    char nome[50];
    struct no *prox;
} No;

typedef No* NoPtr;

typedef struct {
    NoPtr ini;
    NoPtr fim;
} Cabecalho;

typedef Cabecalho* Fila;

// Criação e inicialização da fila
Fila Criar() {
    Fila f = (Fila) malloc(sizeof(Cabecalho));
    if (f != NULL) {
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

// 1. Verificação de fila vazia
int filaVazia(Fila f) {
    return (f == NULL || f->ini == NULL);
}

// Inserção no final da fila (Enqueue)
int inserir(Fila f, int id, const char *nome) {
    if (f == NULL) return 0;

    NoPtr novo = (NoPtr) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->id = id;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->ini = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    return 1;
}

// 2. Remoção do início da fila (Dequeue / Atendimento)
int atenderPaciente(Fila f) {
    if (filaVazia(f)) {
        printf("\n[AVISO] A fila esta vazia. Nenhum paciente para atender.\n");
        return 0;
    }

    NoPtr aux = f->ini;
    printf("\n>> ATENDENDO PACIENTE: ID: %d | Nome: %s\n", aux->id, aux->nome);

    f->ini = f->ini->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(aux);
    return 1;
}

// 3. Consulta do primeiro paciente sem remover (Peek)
void proximoPaciente(Fila f) {
    if (filaVazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }
    printf("\n>> PROXIMO A SER ATENDIDO: ID: %d | Nome: %s\n", f->ini->id, f->ini->nome);
}

// 4. Contagem da quantidade de elementos na fila
int tamanhoFila(Fila f) {
    if (filaVazia(f)) return 0;

    int total = 0;
    NoPtr atual = f->ini;
    while (atual != NULL) {
        total++;
        atual = atual->prox;
    }
    return total;
}

// Listagem de todos os nós da fila
void listarFila(Fila f) {
    if (filaVazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }

    NoPtr atual = f->ini;
    printf("\n=== FILA DE PACIENTES ===\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("=========================\n");
}

// 5. Destruição completa da fila e liberação de memória
void destruirFila(Fila *f) {
    if (f == NULL || *f == NULL) return;

    NoPtr atual = (*f)->ini;
    while (atual != NULL) {
        NoPtr temp = atual;
        atual = atual->prox;
        free(temp);
    }

    free(*f);
    *f = NULL;
}

int main() {
    Fila filaAtendimento = Criar();
    int opcao, id;
    char nome[50];

    do {
        printf("\n--- SISTEMA HOSPITALAR (FATEC IPIRANGA) ---\n");
        printf("1. Chegada de Paciente (Inserir na Fila)\n");
        printf("2. Atender Paciente (Remover da Fila)\n");
        printf("3. Consultar Proximo Paciente\n");
        printf("4. Listar Todos os Pacientes\n");
        printf("5. Exibir Quantidade de Pacientes na Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            while (getchar() != '\n'); // Limpa entrada inválida
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Informe o ID do paciente: ");
                scanf("%d", &id);
                getchar(); // Limpa buffer do teclado
                printf("Informe o Nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                if (inserir(filaAtendimento, id, nome)) {
                    printf(">> Paciente inserido com sucesso!\n");
                } else {
                    printf(">> Erro de alocacao ao inserir paciente.\n");
                }
                break;

            case 2:
                atenderPaciente(filaAtendimento);
                break;

            case 3:
                proximoPaciente(filaAtendimento);
                break;

            case 4:
                listarFila(filaAtendimento);
                break;

            case 5:
                printf("\n>> Total de pacientes aguardando: %d\n", tamanhoFila(filaAtendimento));
                break;

            case 0:
                printf("\nLiberando recursos e encerrando o sistema...\n");
                destruirFila(&filaAtendimento);
                printf("Sistema encerrado com sucesso.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}