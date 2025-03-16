# ✈️ Sistema de Reservas Aéreas

O **Sistema de Reservas Aéreas** é um programa desenvolvido em C/C++ para gerenciar reservas de passagens aéreas, passageiros e filas de espera em uma companhia aérea. O sistema permite cadastrar passageiros, gerenciar voos, pesquisar informações e garantir a persistência dos dados em arquivos `.txt`.

---

##  Funcionalidades

-   **Cadastro de Passageiros**: Registre passageiros com informações como CPF, nome, endereço, telefone, número da passagem, número da poltrona e número do voo.
-   **Gestão de Voos**: Gerencie voos disponíveis (ex: BH-RIO, BH-SP, BH-BRASÍLIA).
-   **Fila de Espera**: Inclua passageiros em uma fila de espera caso o voo esteja lotado.
-   **Pesquisa de Passageiros**: Pesquise passageiros por CPF ou nome.
-   **Exclusão de Passageiros**: Remova passageiros de um voo e automaticamente promova passageiros da fila de espera.
-   **Persistência de Dados**: Salve todos os dados em arquivos `.txt` para garantir a persistência.
-   **Validação de Dados**: Validação de dados de entrada, como CPF, número de voo e número de poltrona.
-   **Tratamento de Erros**: Tratamento de erros para situações inesperadas, como arquivos não encontrados ou entradas inválidas.

---

## ️ Tecnologias Utilizadas

-   **Linguagem**: C/C++
-   **Persistência de Dados**: Arquivos `.txt`
-   **Compilador**: GCC (GNU Compiler Collection)

---

##  Como Compilar e Executar o Projeto

1.  **Clone o Repositório**:

    ```bash
    git clone [https://github.com/seu-usuario/sistema-reservas-aereas.git](https://github.com/seu-usuario/sistema-reservas-aereas.git)
    ```

2.  **Navegue até o Diretório do Projeto**:

    ```bash
    cd sistema-reservas-aereas
    ```

3.  **Compile o Projeto**:

    ```bash
    g++ main.cpp passageiros.c -o sistema_reservas
    ```

4.  **Execute o Sistema**:

    ```bash
    ./sistema_reservas
    ```

---

##  Funcionalidades do Sistema

### Menu Principal

O sistema apresenta um menu com as seguintes opções:

-   Mostrar Lista de Passageiros: Exibe a lista completa de passageiros de um voo.
-   Pesquisar Passageiro por CPF: Busca um passageiro pelo CPF.
-   Pesquisar Passageiro por Nome: Busca um passageiro pelo nome.
-   Cadastrar Passageiro: Adiciona um novo passageiro a um voo ou à fila de espera.
-   Excluir Passageiro: Remove um passageiro de um voo e promove passageiros da fila de espera.
-   Mostrar Fila de Espera: Exibe a fila de espera de um voo.

---

##  Arquivos de Dados

-   `BH-RIO.txt`: Lista de passageiros do voo BH-RIO.
-   `BH-RIO-ESPERA.txt`: Fila de espera do voo BH-RIO.
-   `BH-SP.txt`: Lista de passageiros do voo BH-SP.
-   `BH-SP-ESPERA.txt`: Fila de espera do voo BH-SP.
-   `BH-BRASILIA.txt`: Lista de passageiros do voo BH-BRASÍLIA.
-   `BH-BRASILIA-ESPERA.txt`: Fila de espera do voo BH-BRASÍLIA.

---

##  Equipe

-   Wilken Henrique Moreira

---

##  Licença

Este projeto é licenciado sob a Licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.

---

##  Contribuição

Contribuições são sempre bem-vindas! Sinta-se à vontade para abrir uma issue ou enviar um pull request.

---

##  Notas Adicionais

-   Este projeto foi desenvolvido para fins educacionais e demonstra os conceitos básicos de gerenciamento de reservas aéreas em C/C++.
-   A persistência de dados é feita por meio de arquivos `.txt` simples, o que pode não ser adequado para sistemas de produção com grande volume de dados.