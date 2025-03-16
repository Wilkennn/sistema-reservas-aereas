#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>

// DEFINING CONSTANTS
#define MAX_STRING 255
#define MAX_PASSAGEIROS 10

struct Passageiro {
  char cpf[MAX_STRING];
  char nome[MAX_STRING];
  char endereco[MAX_STRING];
  char telefone[MAX_STRING];
  char numPassagem[MAX_STRING];
  char numPoltrona[MAX_STRING];
  char numVoo[MAX_STRING];
  char horario[MAX_STRING];
};

int readFile(std::string filePath, Passageiro passageiros[], int passageirosCount) {
    FILE* file = fopen(filePath.c_str(), "r");

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
                strcpy(passageiros[passageirosCount].cpf, value);
            } else if (strcmp(key, "Nome") == 0) {
                strncpy(passageiros[passageirosCount].nome, value, MAX_STRING - 1);
            } else if (strcmp(key, "Endereço") == 0) {
                strncpy(passageiros[passageirosCount].endereco, value, MAX_STRING - 1);
            } else if (strcmp(key, "Telefone") == 0) {
                strncpy(passageiros[passageirosCount].telefone, value, MAX_STRING - 1);
            } else if (strcmp(key, "Número da Passagem") == 0) {
                strncpy(passageiros[passageirosCount].numPassagem, value, MAX_STRING - 1);
            } else if (strcmp(key, "Número da Poltrona") == 0) {
                strncpy(passageiros[passageirosCount].numPoltrona, value, MAX_STRING - 1);
            } else if (strcmp(key, "Número do Voo") == 0) {
                strncpy(passageiros[passageirosCount].numVoo, value, MAX_STRING - 1);
            } else if (strcmp(key, "Horário") == 0) {
                strncpy(passageiros[passageirosCount].horario, value, MAX_STRING - 1);
            }
        }
    }

    fclose(file);

    return passageirosCount;
}

void writeFile(const std::string& filePath, const Passageiro passageiros[], int numPassageiros) {
    FILE* file = fopen(filePath.c_str(), "w");

    if (file == nullptr) {
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

Passageiro buscarPassageiroPorCpf(Passageiro passageiros[], char searchTerm[]) {

  if (passageiros && !(searchTerm[0] == '\0')) {
    for (int i = 0; i < MAX_PASSAGEIROS; i++) {
      if (strcmp(passageiros[i].cpf, searchTerm) == 0) {
        return passageiros[i];
      }
    }
  }

  Passageiro passageiroDefault;
  memset(&passageiroDefault, 0, sizeof(Passageiro));
  return passageiroDefault;
}

Passageiro buscarPassageiroPorNome(Passageiro passageiros[], char searchTerm[]) {

  if (passageiros && !(searchTerm[0] == '\0')) {
    for (int i = 0; i < MAX_PASSAGEIROS; i++) {
      if (strcmp(passageiros[i].nome, searchTerm) == 0) {
        return passageiros[i];
      }
    }
  }

  Passageiro passageiroDefault;
  memset(&passageiroDefault, 0, sizeof(Passageiro));
  return passageiroDefault;
}

void adicionarPassageiroNoVoo(Passageiro passageiro, std::string vooPath, Passageiro passageiros[], int arraySize) {
  
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

    std::strcpy(newFilePath, vooPath.c_str());

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
      writeFile(newFilePath, listaPassageiros, numPassageirosNaFila);
      printf("ATENÇÃO VOO LOTADO: Passageiro adicionado à fila de espera!\n");
    } else {
      printf("ATENÇÃO FILA DE ESPERA LOTADA: Tente mais tarde!\n");
    }
  }
}

void excluirPassageiroFilaEspera(Passageiro passageiro, char voo[], Passageiro passageiros[], int numPassageiros) {

  for (int i = 0; i < numPassageiros; i++) {
    if (strcmp(passageiros[i].cpf, passageiro.cpf) == 0) {
      for (int j = i; j < numPassageiros - 1; j++) {
        passageiros[j] = passageiros[j + 1];
      }
      numPassageiros--;

      writeFile(strcat(voo, "-ESPERA.txt"), passageiros, numPassageiros);
      printf("ATENÇÃO: Passageiro REMOVIDO da Lista de Espera!\n");

      adicionarPassageiroNoVoo(passageiro, voo, passageiros, numPassageiros);

      printf("Passageiro removido com sucesso.\n");
      return;
    }
  }

  printf("Passageiro não encontrado.\n");
}

void exibirDadosPassageiros(Passageiro passageiro, int numPassageiros) {
  for (int i = 0; i < numPassageiros; i++) {
    std::cout << "\nCPF: " << passageiro.cpf << std::endl;
    std::cout << "Nome: " << passageiro.nome << std::endl;
    std::cout << "Endereco: " << passageiro.endereco << std::endl;
    std::cout << "Telefone: " << passageiro.telefone << std::endl;
    std::cout << "Número da Passagem: " << passageiro.numPassagem << std::endl;
    std::cout << "Número da Poltrona: " << passageiro.numPoltrona << std::endl;
    std::cout << "Número do Voo: " << passageiro.numVoo << std::endl;
    std::cout << "Horário: " << passageiro.horario << std::endl;
  }
}



int main() {
  
  int option;

  std::string voo;
  std::cout << "Digite 'BH-RIO' para ir para o Rio, 'BH-SP' para São Paulo e 'BH-BRA' para Brasília: ";
  std::cin >> voo;

  std::string filePath = voo + ".txt";

  while(option == 0){
    std::cout << "========== MENU ==========" << std::endl;
    std::cout << "1. Adicionar passageiro no voo" << std::endl;
    std::cout << "2. Mostrar a lista completa dos passageiros de um determinado voo" << std::endl;
    std::cout << "3. Excluir passageiro da fila de espera" << std::endl;
    std::cout << "4. Buscar passageiro por nome" << std::endl;
    std::cout << "5. Buscar passageiro por CPF" << std::endl;
    std::cout << "6. Listar passageiros fila de espera do voo" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "Digite sua opção: ";
    std::cin >> option;

    std::cin.ignore();

    switch (option) {
      case 1: {
         Passageiro passageiros [MAX_PASSAGEIROS];
        readFile(filePath, passageiros, MAX_PASSAGEIROS);
        
        Passageiro passageiro;
        
        std::cout << "Digite o CPF do passageiro: ";
        std::cin.getline(passageiro.cpf, MAX_PASSAGEIROS);
        std::cout << "Digite o nome do passageiro: ";
        std::cin.getline(passageiro.nome, MAX_PASSAGEIROS);
        std::cout << "Digite o endereço do passageiro: ";
        std::cin.getline(passageiro.endereco, MAX_PASSAGEIROS);
        std::cout << "Digite o telefone do passageiro: ";
        std::cin.getline(passageiro.telefone, MAX_PASSAGEIROS);
        std::cout << "Digite o número da passagem: ";
        std::cin.getline(passageiro.numPassagem, MAX_PASSAGEIROS);
        std::cout << "Digite o número da poltrona: ";
        std::cin.getline(passageiro.numPoltrona, MAX_PASSAGEIROS);
        std::cout << "Digite o número do voo: ";
        std::cin.getline(passageiro.numVoo, MAX_PASSAGEIROS);
        std::cout << "Digite o horário do voo: ";
        std::cin.getline(passageiro.horario, MAX_PASSAGEIROS);

        adicionarPassageiroNoVoo(passageiro, filePath, passageiros,MAX_PASSAGEIROS);
        
        break;
      }
      case 2: {
         Passageiro passageiros[MAX_PASSAGEIROS];

         readFile(filePath, passageiros, MAX_PASSAGEIROS);

         for (int i = 0; i < MAX_PASSAGEIROS; i++) {
          if (strcmp(passageiros[i].cpf, "\0") == 0) { break; }
          std::cout << "\nCPF: " << passageiros[i].cpf << std::endl;
          std::cout << "Nome: " << passageiros[i].nome << std::endl;
          std::cout << "Endereco: " << passageiros[i].endereco << std::endl;
          std::cout << "Telefone: " << passageiros[i].telefone << std::endl;
          std::cout << "Número da Passagem: " << passageiros[i].numPassagem << std::endl;
          std::cout << "Número da Poltrona: " << passageiros[i].numPoltrona << std::endl;
          std::cout << "Número do Voo: " << passageiros[i].numVoo << std::endl;
          std::cout << "Horário: " << passageiros[i].horario << std::endl;
        }

        break;
      }
      case 3: {
        Passageiro passageiros[MAX_PASSAGEIROS];
        Passageiro passageiro;
    
        char newFilePath[MAX_STRING];
        const char* additionalText = "-ESPERA.txt";
    
        std::strcpy(newFilePath, filePath.c_str());
        
        char* extension = std::strstr(newFilePath, ".txt");
        if (extension != nullptr) {
            *extension = '\0';
        }
        
        std::strcat(newFilePath, additionalText);
    
        readFile(newFilePath, passageiros, MAX_PASSAGEIROS);
    
        char cpf[MAX_STRING];
    
        std::cout << "Digite seu CPF: ";
        std::cin >> cpf;
    
        passageiro = buscarPassageiroPorCpf(passageiros, cpf);
    
        excluirPassageiroFilaEspera(passageiro, newFilePath, passageiros, MAX_PASSAGEIROS);
        
        break;
      }
      case 4: {

        Passageiro passageiro;
        Passageiro passageiros[MAX_PASSAGEIROS];

        readFile(filePath, passageiros, MAX_PASSAGEIROS);

        char cpf[MAX_STRING];
    
        std::cout << "Digite seu CPF: ";
        std::cin >> cpf;
        
        passageiro = buscarPassageiroPorNome(passageiros, cpf);

        exibirDadosPassageiros(passageiro, 1);
        
        break;

      }
      case 5: {
        Passageiro passageiro;
        Passageiro passageiros[MAX_PASSAGEIROS];

        readFile(filePath, passageiros, MAX_PASSAGEIROS);

        char cpf[MAX_STRING];
    
        std::cout << "Digite seu CPF: ";
        std::cin >> cpf;
        
        passageiro = buscarPassageiroPorCpf(passageiros, cpf);

        exibirDadosPassageiros(passageiro, 1);
        
        break;
      }
      case 6: {

        char newFilePath[MAX_STRING];
        const char* additionalText = "-ESPERA.txt";
    
        std::strcpy(newFilePath, filePath.c_str());
        
        char* extension = std::strstr(newFilePath, ".txt");
        if (extension != nullptr) {
            *extension = '\0';
        }
        
        std::strcat(newFilePath, additionalText);
         Passageiro passageiros[MAX_PASSAGEIROS];

         int numpassageiros = readFile(newFilePath, passageiros, MAX_PASSAGEIROS);

         if (strcmp(passageiros[0].cpf, "\0") == 0) { break; }

         for (int i = 0; i < numpassageiros; i++) {
          if (strcmp(passageiros[0].cpf, "\0") == 0) { break; }
          std::cout << "\nCPF: " << passageiros[i].cpf << std::endl;
          std::cout << "Nome: " << passageiros[i].nome << std::endl;
          std::cout << "Endereco: " << passageiros[i].endereco << std::endl;
          std::cout << "Telefone: " << passageiros[i].telefone << std::endl;
          std::cout << "Número da Passagem: " << passageiros[i].numPassagem << std::endl;
          std::cout << "Número da Poltrona: " << passageiros[i].numPoltrona << std::endl;
          std::cout << "Número do Voo: " << passageiros[i].numVoo << std::endl;
          std::cout << "Horário: " << passageiros[i].horario << std::endl;
        }

        break;
      }
    }

    std::cout << std::endl;
  }

  return 0;
  
}
