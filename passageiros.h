#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

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

int readFile(const char* filePath, Passageiro passageiros[], int passageirosCount);
void writeFile(const char* filePath, const Passageiro passageiros[], int numPassageiros);
Passageiro buscarPassageiroPorCpf(Passageiro passageiros[], const char searchTerm[]);
Passageiro buscarPassageiroPorNome(Passageiro passageiros[], const char searchTerm[]);
void adicionarPassageiroNoVoo(Passageiro passageiro, const char* vooPath, Passageiro passageiros[], int arraySize);
void excluirPassageiroFilaEspera(Passageiro passageiro, const char voo[], Passageiro passageiros[], int numPassageiros);
int exibirDadosPassageiros(Passageiro passageiros[], int numPassageiros);

#endif  // PASSAGEIROS_H
