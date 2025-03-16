#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo constantes
#define MAX_STRING 255
#define MAX_PASSAGEIROS 10

typedef struct {
    char cpf[MAX_STRING];
    char nome[MAX_STRING];
    char endereco[MAX_STRING];
    char telefone[MAX_STRING];
    char numPassagem[MAX_STRING];
    char numPoltrona[MAX_STRING];
    char numVoo[MAX_STRING];
    char horario[MAX_STRING];
} Passageiro;

/**
 * Descrição da Função:
 *    Escreve as informações dos passageiros em um arquivo.
 *
 * Parâmetros:
 *    - filePath (const std::string&):
 *        O caminho do arquivo de destino.
 *    - passageiros (const Passageiro[]):
 *        O array de objetos Passageiro contendo as informações a serem escritas.
 *    - numPassageiros (int):
 *        O número de passageiros a serem escritos no arquivo.
 *
 * Retorno:
 *    void
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> writeFile(filePath, passageiros, numPassageiros)
 *
 * Notas:
 *    - Se o arquivo não puder ser aberto para escrita, uma mensagem de erro será exibida.
 */
void writeFile(const char* filePath, const Passageiro passageiros[], int numPassageiros) {
    FILE* file = fopen(filePath, "w");

    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    for (int i = 0; i < numPassageiros; i++) {
        fprintf(
            file,
            "CPF: %s\nNome: %s\nEndereço: %s\nTelefone: %s\nNúmero da Passagem: %s\nNúmero da Poltrona: %s\nNúmero do Voo: %s\nHorário: %s\n\n",
            passageiros[i].cpf, passageiros[i].nome, passageiros[i].endereco,
            passageiros[i].telefone, passageiros[i].numPassagem,
            passageiros[i].numPoltrona, passageiros[i].numVoo,
            passageiros[i].horario);
    }

    fclose(file);
}

/**
 * Descrição da Função:
 *    Lê um arquivo de passageiros e armazena as informações em um array de objetos Passageiro.
 *
 * Parâmetros:
 *    - filePath (string):
 *        O caminho do arquivo a ser lido.
 *    - passageiros (Passageiro[]):
 *        O array de objetos Passageiro para armazenar as informações.
 *    - passageirosCount (int):
 *        O número atual de passageiros no array.
 *
 * Retorno:
 *    int:
 *        O novo número de passageiros no array após a leitura do arquivo.
 *
 * Exemplos:
 *    - Exemplo 1:
 *        >>> readFile(filePath, passageiros, passageirosCount)
 *        retornoExemplo1
 *
 *    - Exemplo 2:
 *        >>> readFile(filePath, passageiros, passageirosCount)
 *        retornoExemplo2
 *
 * Notas:
 *    Informações adicionais ou considerações relevantes.
 */
int readFile(const char* filePath, Passageiro passageiros[], int passageirosCount) {
    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return passageirosCount;
    }

    char line[MAX_STRING];
    passageirosCount = 0;

    while (fgets(line, MAX_STRING, file)) {
        if (line[0] == '\n' && passageirosCount <= MAX_PASSAGEIROS - 1) {
            passageirosCount++;
        } else {
            char key[MAX_STRING], value[MAX_STRING];
            sscanf(line, "%[^:]: %[^\n]", key, value);

            if (strcmp(key, "CPF") == 0) {
                strncpy(passageiros[passageirosCount].cpf, value, sizeof(passageiros[passageirosCount].cpf) - 1);
            } else if (strcmp(key, "Nome") == 0) {
                strncpy(passageiros[passageirosCount].nome, value, sizeof(passageiros[passageirosCount].nome) - 1);
            } else if (strcmp(key, "Endereço") == 0) {
                strncpy(passageiros[passageirosCount].endereco, value, sizeof(passageiros[passageirosCount].endereco) - 1);
            } else if (strcmp(key, "Telefone") == 0) {
                strncpy(passageiros[passageirosCount].telefone, value, sizeof(passageiros[passageirosCount].telefone) - 1);
            } else if (strcmp(key, "Número da Passagem") == 0) {
                strncpy(passageiros[passageirosCount].numPassagem, value, sizeof(passageiros[passageirosCount].numPassagem) - 1);
            } else if (strcmp(key, "Número da Poltrona") == 0) {
                strncpy(passageiros[passageirosCount].numPoltrona, value, sizeof(passageiros[passageirosCount].numPoltrona) - 1);
            } else if (strcmp(key, "Número do Voo") == 0) {
                strncpy(passageiros[passageirosCount].numVoo, value, sizeof(passageiros[passageirosCount].numVoo) - 1);
            } else if (strcmp(key, "Horário") == 0) {
                strncpy(passageiros[passageirosCount].horario, value, sizeof(passageiros[passageirosCount].horario) - 1);
            }
        }
    }

    fclose(file);

    return passageirosCount;
}

/**
 * Descrição da Função:
 *    Busca um passageiro pelo CPF no array de passageiros e retorna o objeto Passageiro correspondente.
 *
 * Parâmetros:
 *    - passageiros (Passageiro[]):
 *        O array de objetos Passageiro onde a busca será realizada.
 *    - searchTerm (char[]):
 *        O CPF a ser buscado.
 *
 * Retorno:
 *    Passageiro:
 *        O objeto Passageiro correspondente ao CPF buscado. Se não for encontrado, retorna um Passageiro vazio.
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> buscarPassageiroPorCpf(passageiros, searchTerm)
 *        retornoExemplo1
 *
 * Notas:
 *    - Se o array de passageiros for nulo ou o searchTerm for uma string vazia, a função retorna um Passageiro vazio.
 */
Passageiro buscarPassageiroPorCpf(Passageiro passageiros[], const char searchTerm[]) {
    Passageiro passageiroDefault;
    memset(&passageiroDefault, 0, sizeof(Passageiro));

    if (passageiros != NULL && searchTerm[0] != '\0') {
        for (int i = 0; i < MAX_PASSAGEIROS; i++) {
            if (strcmp(passageiros[i].cpf, searchTerm) == 0) {
                return passageiros[i];
            }
        }
    }

    return passageiroDefault;
}

/**
 * Descrição da Função:
 *    Busca um passageiro pelo nome no array de passageiros e retorna o objeto Passageiro correspondente.
 *
 * Parâmetros:
 *    - passageiros (Passageiro[]):
 *        O array de objetos Passageiro onde a busca será realizada.
 *    - searchTerm (char[]):
 *        O nome a ser buscado.
 *
 * Retorno:
 *    Passageiro:
 *        O objeto Passageiro correspondente ao nome buscado. Se não for encontrado, retorna um Passageiro vazio.
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> buscarPassageiroPorNome(passageiros, searchTerm)
 *        retornoExemplo1
 *
 * Notas:
 *    - Se o array de passageiros for nulo ou o searchTerm for uma string vazia, a função retorna um Passageiro vazio.
 */
Passageiro buscarPassageiroPorNome(Passageiro passageiros[], const char searchTerm[]) {
    Passageiro passageiroDefault;
    memset(&passageiroDefault, 0, sizeof(Passageiro));

    if (passageiros != NULL && searchTerm[0] != '\0') {
        for (int i = 0; i < MAX_PASSAGEIROS; i++) {
            if (strcmp(passageiros[i].nome, searchTerm) == 0) {
                return passageiros[i];
            }
        }
    }

    return passageiroDefault;
}

/**
 * Descrição da Função:
 *    Exibe os dados dos passageiros.
 *
 * Parâmetros:
 *    - passageiro (Passageiro):
 *        O objeto Passageiro contendo os dados a serem exibidos.
 *    - numPassageiros (int):
 *        O número de passageiros a serem exibidos.
 *
 * Retorno:
 *    void
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> exibirDadosPassageiros(passageiro, numPassageiros)
 *
 * Notas:
 *    - A função realiza as seguintes ações:
 *        1. Percorre o array de passageiros.
 *        2. Exibe os dados de cada passageiro, incluindo CPF, nome, endereço, telefone, número da passagem, número da poltrona, número do voo e horário.
 */
int exibirDadosPassageiros(const Passageiro passageiros[], int numPassageiros) {
    for (int i = 0; i < numPassageiros; i++) {
        printf("\nCPF: %s\n", passageiros[i].cpf);
        printf("Nome: %s\n", passageiros[i].nome);
        printf("Endereco: %s\n", passageiros[i].endereco);
        printf("Telefone: %s\n", passageiros[i].telefone);
        printf("Número da Passagem: %s\n", passageiros[i].numPassagem);
        printf("Número da Poltrona: %s\n", passageiros[i].numPoltrona);
        printf("Número do Voo: %s\n", passageiros[i].numVoo);
        printf("Horário: %s\n", passageiros[i].horario);
    }
    return 1;
}

/**
 * Descrição da Função:
 *    Adiciona um passageiro em um voo. Verifica se o passageiro já está no voo ou na fila de espera e realiza as ações necessárias.
 *
 * Parâmetros:
 *    - passageiro (Passageiro):
 *        O objeto Passageiro a ser adicionado.
 *    - vooPath (std::string):
 *        O caminho do arquivo do voo.
 *    - passageiros (Passageiro[]):
 *        O array de objetos Passageiro contendo os passageiros do voo.
 *    - arraySize (int):
 *        O tamanho do array de passageiros.
 *
 * Retorno:
 *    void
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> adicionarPassageiroNoVoo(passageiro, vooPath, passageiros, arraySize)
 *
 * Notas:
 *    - A função realiza as seguintes ações:
 *        1. Lê as informações dos passageiros existentes no arquivo do voo.
 *        2. Verifica se o passageiro já está no voo.
 *        3. Se o voo não estiver lotado (menos de 10 passageiros):
 *            - Adiciona o passageiro no voo.
 *            - Escreve as informações atualizadas no arquivo do voo.
 *            - Imprime uma mensagem de sucesso.
 *        4. Se o voo estiver lotado:
 *            - Cria um arquivo de fila de espera adicionando "-ESPERA.txt" ao nome do arquivo do voo.
 *            - Lê as informações dos passageiros existentes na fila de espera.
 *            - Verifica se o passageiro já está na fila de espera.
 *            - Se a fila de espera não estiver lotada (menos de 5 passageiros):
 *                - Adiciona o passageiro na fila de espera.
 *                - Escreve as informações atualizadas no arquivo da fila de espera.
 *                - Imprime uma mensagem de aviso.
 *            - Se a fila de espera estiver lotada:
 *                - Imprime uma mensagem de aviso.
 */
void adicionarPassageiroNoVoo(const Passageiro passageiro, const char* vooPath, Passageiro passageiros[], int arraySize) {
    int numPassageiroNoVoo = readFile(vooPath, passageiros, arraySize);

    numPassageiroNoVoo++;

    for (int i = 0; i < numPassageiroNoVoo; i++) {
        if (strcmp(passageiros[i].cpf, passageiro.cpf) == 0) {
            printf("Passageiro já está no voo.\n");
            return;
        }
    }

    if (numPassageiroNoVoo < 10) {
        passageiros[numPassageiroNoVoo] = passageiro;
        writeFile(vooPath, passageiros, numPassageiroNoVoo + 1);
        printf("Passageiro adicionado no VOO com sucesso!\n");
    } else {
        char newFilePath[MAX_STRING];
        const char* additionalText = "-ESPERA.txt";

        strcpy(newFilePath, vooPath);

        char* extension = strstr(newFilePath, ".txt");
        if (extension != NULL) {
            *extension = '\0';
        }
        strcat(newFilePath, additionalText);

        Passageiro listaPassageiros[MAX_PASSAGEIROS];
        int indiceFilaEspera = readFile(newFilePath, listaPassageiros, arraySize);
        int numPassageirosNaFila = indiceFilaEspera;

        int filaSize = sizeof(listaPassageiros) / sizeof(listaPassageiros[0]);

        if (numPassageirosNaFila < 5) {
            // Verifica se o passageiro já está na fila de espera
            for (int i = 0; i < numPassageirosNaFila; i++) {
                if (strcmp(listaPassageiros[i].cpf, passageiro.cpf) == 0) {
                    printf("Passageiro já está na fila de espera.\n");
                    return;
                }
            }

            // Cria uma cópia do passageiro antes de adicioná-lo na fila de espera
            Passageiro passageiroFilaEspera = passageiro;
            listaPassageiros[indiceFilaEspera] = passageiroFilaEspera;
            writeFile(newFilePath, listaPassageiros, numPassageirosNaFila + 1);
            printf("ATENÇÃO VOO LOTADO: Passageiro adicionado à fila de espera!\n");
        } else {
            printf("ATENÇÃO FILA DE ESPERA LOTADA: Tente mais tarde!\n");
        }
    }
}

/**
 * Descrição da Função:
 *    Exclui um passageiro da lista de espera de um voo. Remove o passageiro da lista de espera, atualiza o arquivo da lista de espera e adiciona o passageiro de volta ao voo.
 *
 * Parâmetros:
 *    - passageiro (Passageiro):
 *        O objeto Passageiro a ser excluído da lista de espera.
 *    - voo (char[]):
 *        O nome do voo.
 *    - passageiros (Passageiro[]):
 *        O array de objetos Passageiro contendo os passageiros na lista de espera.
 *    - numPassageiros (int):
 *        O número de passageiros na lista de espera.
 *
 * Retorno:
 *    void
 *
 * Exemplos:
 *    Exemplo 1:
 *        >>> excluirPassageiroFilaEspera(passageiro, voo, passageiros, numPassageiros)
 *
 * Notas:
 *    - A função realiza as seguintes ações:
 *        1. Percorre o array de passageiros na lista de espera.
 *        2. Se encontra o passageiro a ser excluído:
 *            - Move os passageiros seguintes uma posição para trás, sobrescrevendo o passageiro a ser excluído.
 *            - Reduz o número de passageiros na lista de espera.
 *            - Atualiza o arquivo da lista de espera com as informações atualizadas.
 *            - Imprime uma mensagem de aviso.
 *            - Chama a função adicionarPassageiroNoVoo para adicionar o passageiro excluído de volta ao voo.
 *            - Imprime uma mensagem de sucesso.
 *        3. Se não encontra o passageiro a ser excluído, imprime uma mensagem informando que o passageiro não foi encontrado.
 */
void excluirPassageiroFilaEspera(const Passageiro passageiro, const char voo[], Passageiro passageiros[], int *numPassageiros) {
    int i;
    
    for (i = 0; i < *numPassageiros; i++) {
        if (strcmp(passageiros[i].cpf, passageiro.cpf) == 0) {
            int j;
            for (j = i; j < *numPassageiros - 1; j++) {
                passageiros[j] = passageiros[j + 1];
            }
            (*numPassageiros)--;

            char fileName[100];
            strcpy(fileName, voo);
            strcat(fileName, "-ESPERA.txt");
            writeFile(fileName, passageiros, *numPassageiros);
            printf("ATENÇÃO: Passageiro REMOVIDO da Lista de Espera!\n");

            adicionarPassageiroNoVoo(passageiro, voo, passageiros, *numPassageiros);

            printf("Passageiro removido com sucesso.\n");
            return;
        }
    }

    printf("Passageiro não encontrado.\n");
}
