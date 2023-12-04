#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações do paciente
typedef struct {
    int numero;
    char nome[50];
    char telefone[20];
} Paciente;

// Estrutura para armazenar informações da dieta
typedef struct {
    int numeroPaciente;
    char data[11];
    char refeicao[20];
    char alimento[50];
    int calorias;
} Dieta;

// Estrutura para armazenar informações do plano nutricional
typedef struct {
    int numeroPaciente;
    char data[11];
    char refeicao[20];
    int caloriasMin;
    int caloriasMax;
} PlanoNutricional;

//funcao para carregar os pacientes
void carregarPacientes(char *filename, Paciente **pacientes, int *numPacientes) {
    FILE *ftpr = fopen(filename, "r");

    if(ftpr != NULL){
        printf("File Open");
    } else{
        printf("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Contar o número de linhas no arquivo para alocar memória suficiente
    int count = 0;
    char ch;
    while (!feof(ftpr)) {
        ch = fgetc(ftpr);
        if (ch == '\n') {
            count++;
        }
    }
    rewind(ftpr);

    // Alocar memória para armazenar os pacientes
    *pacientes = (Paciente *)malloc(count * sizeof(Paciente));
    if (*pacientes == NULL) {
        perror("Erro de alocacao de memória");
        exit(EXIT_FAILURE);
    }

    // Ler os dados dos pacientes do arquivo
    *numPacientes = 0;
    while (fscanf(ftpr, "%d;%49[^;];%19[^\n]\n",
                  &((*pacientes)[*numPacientes].numero),
                  (*pacientes)[*numPacientes].nome,
                  (*pacientes)[*numPacientes].telefone) == 3) {
        (*numPacientes)++;
    }

    fclose(ftpr);
}

// Função para carregar dados da dieta a partir de um arquivo
void carregarDieta(char *filename, Dieta **dietas, int *numDietas) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Contar o número de linhas no arquivo para alocar memória suficiente
    int count = 0;
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);

    // Alocar memória para armazenar as dietas
    *dietas = (Dieta *)malloc(count * sizeof(Dieta));
    if (*dietas == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    // Ler os dados das dietas do arquivo
    *numDietas = 0;
    while (fscanf(file, "%d;%10[^;];%19[^;];%49[^;];%d cal\n",
                  &((*dietas)[*numDietas].numeroPaciente),
                  (*dietas)[*numDietas].data,
                  (*dietas)[*numDietas].refeicao,
                  (*dietas)[*numDietas].alimento,
                  &((*dietas)[*numDietas].calorias)) == 5) {
        (*numDietas)++;
    }

    fclose(file);
}

// Função para carregar dados do plano nutricional a partir de um arquivo
void carregarPlanoNutricional(char *filename, PlanoNutricional **planos, int *numPlanos) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Contar o número de linhas no arquivo para alocar memória suficiente
    int count = 0;
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);

    // Alocar memória para armazenar os planos nutricionais
    *planos = (PlanoNutricional *)malloc(count * sizeof(PlanoNutricional));
    if (*planos == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    // Ler os dados dos planos nutricionais do arquivo
    *numPlanos = 0;
    while (fscanf(file, "%d;%10[^;];%19[^;];%d Cal, %d Cal\n",
                  &((*planos)[*numPlanos].numeroPaciente),
                  (*planos)[*numPlanos].data,
                  (*planos)[*numPlanos].refeicao,
                  &((*planos)[*numPlanos].caloriasMin),
                  &((*planos)[*numPlanos].caloriasMax)) == 5) {
        (*numPlanos)++;
    }

    fclose(file);
}

// Função para calcular a média de calorias consumidas por refeição por paciente
void calcularMediaCalorias(Dieta *dietas, int numDietas, int numeroPaciente) {
    // Implementar o cálculo da média de calorias consumidas
//Cálculo das médias das calorias consumidas por refeição por cada paciente ao longo de um
//determinado período;

}

void Paciente_UltrupassaCalorias(Paciente *pacientes, PlanoNutricional *planos, Dieta *dietas, int numDietas, int numPacientes, int numPlanos) {
    char dataInicio[11];
    char dataFim[11];

    // Solicitar ao usuário as datas de início e fim
    printf("Digite a data de início (formato DD-MM-AAAA): ");
    scanf("%s", dataInicio);
    printf("Digite a data de fim (formato DD-MM-AAAA): ");
    scanf("%s", dataFim);

    int contadorUltrapassagens = 0;

    // Iterar sobre os pacientes
    for (int i = 0; i < numPacientes; i++) {
        int numeroPacienteAtual = pacientes[i].numero;

        // Iterar sobre as dietas para o paciente atual
        for (int j = 0; j < numDietas; j++) {
            if (dietas[j].numeroPaciente == numeroPacienteAtual &&
                strcmp(dietas[j].data, dataInicio) >= 0 &&
                strcmp(dietas[j].data, dataFim) <= 0) {
                // Esta dieta é do paciente no período desejado

                // Encontrar o plano nutricional correspondente
                for (int k = 0; k < numPlanos; k++) {
                    if (planos[k].numeroPaciente == numeroPacienteAtual &&
                        strcmp(planos[k].data, dietas[j].data) == 0 &&
                        strcmp(planos[k].refeicao, dietas[j].refeicao) == 0) {
                        // Este é o plano nutricional correspondente

                        // Verificar se as calorias da dieta ultrapassam os limites do plano nutricional
                        if (dietas[j].calorias < planos[k].caloriasMin || dietas[j].calorias > planos[k].caloriasMax) {
                            printf("Paciente %d ultrapassou as calorias no dia %s, refeição %s, alimento %s, calorias consumidas: %d\n",
                                   numeroPacienteAtual, dietas[j].data, dietas[j].refeicao, dietas[j].alimento, dietas[j].calorias);
                            contadorUltrapassagens++;
                        }

                        break;  // Não é necessário procurar mais planos nutricionais
                    }
                }
            }
        }
    }

    printf("Número total de pacientes que ultrapassaram as calorias: %d\n", contadorUltrapassagens);
}

void Listar_Pacientes_Com_A_Mais(){

}


void Listar_pnutricional_paciente_refeicao_periodo(){

}

void GerarTabela(){

}
// Função para exibir o menu
void exibirMenu() {
    printf("\n===== Menu Principal =====\n");
    printf("1. Carregar dados dos pacientes\n");
    printf("2. Carregar dados da dieta\n");
    printf("3. Carregar dados do plano nutricional\n");
    printf("4. Numero de pacientes que ultrapassaram calorias em um período\n");
    printf("5. Listar pacientes com calorias fora do intervalo em um período\n");
    printf("6. Listar plano nutricional de um paciente para uma refeicao e período\n");
    printf("7. Calcular medias de calorias consumidas por refeicao por paciente em um período\n");
    printf("8. Gerar tabela de refeicoes planeadas e realizadas\n");
    printf("9. Sair\n");
    printf("===========================\n");
}

int main() {
    // Declaração de variáveis
    Paciente *pacientes = NULL;
    Dieta *dietas = NULL;
    PlanoNutricional *planos = NULL;
    int numPacientes = 0, numDietas = 0, numPlanos = 0;

    // Loop do menu principal
    int opcao;
    do {
        exibirMenu();
        printf("Escolha a opcao (1-9): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                carregarPacientes("pacientes.txt", &pacientes, &numPacientes);
                break;
            case 2:

                carregarDieta("dietas.txt", &dietas, &numDietas);
                break;
            case  3:
                carregarPlanoNutricional("planos.txt", &planos, &numPlanos);
                break;
            case  4:
                //int numPacientes = sizeof(pacientes) / sizeof(pacientes[0]);
                //int numPlanos = sizeof(planos) / sizeof(planos[0]);
                //int numDietas = sizeof(dietas) / sizeof(dietas[0]);
                Paciente_UltrupassaCalorias(pacientes, planos, dietas, numDietas, numPacientes, numPlanos);
                break;
            case 5:
                break;
            case 6:
                break;
            case  7:

                break;
            case 8:
                break;
            case 9:
                printf("Encerrando o programa. Até mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 9);

    // Liberar a memória alocada antes de encerrar o programa
    free(pacientes);
    free(dietas);
    free(planos);

    return 0;
}

