#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MIN_ALOC 20
int contAtualCliente = 10;
int contAux = MIN_ALOC;
int total_pacotes = 0;
int cont = 0;
int cont1 = 10;

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    char cliente_nome[50];
    char cliente_cpf[16];
    char cliente_telefone[17];
    char cliente_email[50];
} Cliente;

typedef struct
{
    int pacote_codigo;
    char pacote_destino[50];
    Data pacote_data_ida;
    Data pacote_data_volta;
    float preco;
} Pacote;

typedef struct
{
    int reserva_codigo;
    char reserva_cliente_cpf[16];
    int reserva_pacote_codigo;
    Data reserva_data;
} Reserva;

void menu(Pacote **v_pacotes, Cliente **v_Clientes, Reserva **v_reserva);

// CLIENTES===============================================================
void carregarDadosClientes(Cliente **v_Clientes);
void carregarAlteracaoClientes(Cliente **v_Clientes);

void escolhaOpcaoCliente(Cliente **v_Clientes, Reserva **v_reserva);

void cadastroCliente(Cliente **v_Clientes);
void alteraCliente(Cliente **v_Clientes);
void consultaCliente(Cliente **v_Clientes);
void listarClientes(Cliente *v_Clientes);
void removerCliente(Cliente **v_Clientes, Reserva **v_reserva);

// PACOTES===============================================================
void carregarDadosPacotes(Pacote **v_pacotes);
void carregarAlteracaoPacotes(Pacote **v_pacotes);

void escolhaOpcaoPacote(Pacote **v_pacotes, Reserva **v_reserva);

void cadastrarPacote(Pacote **v_pacotes);
void consultarPacote(Pacote **v_pacotes);
void alterarPacote(Pacote **v_pacotes);
void listarPacotes(Pacote *v_pacotes);
void removerPacote(Pacote **v_pacotes, Reserva **v_reserva);

// RESERVA===============================================================

void carregarReservasPrevias(Reserva **v_reserva);
void salvarReservas(Reserva **v_reserva);
void expandirMemoria(Reserva **v_reserva);
void menu(Pacote **v_pacotes, Cliente **v_Clientes, Reserva **v_reserva);
void escolhaReserva(Reserva **v_reserva, Pacote **v_pacotes, Cliente **v_Clientes);
void cadastraReserva(Reserva **v_reserva, Pacote **v_pacotes, Cliente **v_Clientes);
void alteraReserva(Reserva **v_reserva);
void alteraCodigoReserva(Reserva **v_reserva);
void alteraDataReserva(Reserva **v_reserva);
void alteraCpfReserva(Reserva **v_reserva);
void alteraCodigoPacoteReserva(Reserva **v_reserva);
void listarReservas(Reserva *v_reserva);
void removeReserva(Reserva **v_reserva);
// void gerarRelatorio();

//===============================================================

int main()
{
    Pacote *v_pacotes = (Pacote *)malloc(MIN_ALOC * sizeof(Pacote));
    Cliente *v_Clientes = (Cliente *)malloc(contAux * sizeof(Cliente));
    Reserva *v_reserva = (Reserva *)calloc(10, sizeof(Reserva));

    if (v_reserva == NULL)
    {
        printf("Erro ao alocar memoria\n");
        system("pause");
        exit(1);
    }
    else if(v_Clientes == NULL){
        printf("Erro ao alocar memoria\n");
        system("pause");
        exit(1);
    }
    else if(v_pacotes == NULL){
        printf("Erro ao alocar memoria\n");
        system("pause");
        exit(1);
    }

    carregarDadosPacotes(&v_pacotes);
    carregarDadosClientes(&v_Clientes);
    carregarReservasPrevias(&v_reserva);

    menu(&v_pacotes, &v_Clientes, &v_reserva);

    free(v_pacotes);
    free(v_Clientes);
    free(v_reserva);

    return 0;
}

void menu(Pacote **v_pacotes, Cliente **v_Clientes, Reserva **v_reserva)
{
    bool sair = false;
    int opc = -1;
    while(!sair){
        printf("===============MENU================\n");
        printf("Digite uma opcao: \n");
        printf("1 - Cadastrar, alterar, consultar ou remover clientes\n");
        printf("2 - Cadastrar, alterar, consultar ou remover pacotes de viagens\n");
        printf("3 - Cadastrar, alterar ou remover reservas\n");
        printf("4 - Listar dados de todos os clientes\n");
        printf("5 - Listar dados de todos os pacotes de viagens\n");
        printf("6 - Listar todos os dados de todas as reservas\n");
        printf("7 - Gerar relatorio\n");
        printf("8 - Sair do programa\n");
        scanf("%d%*c", &opc);

        switch (opc)
        {
        case 1:
            escolhaOpcaoCliente(v_Clientes, v_reserva);
            break;
        case 2:
            escolhaOpcaoPacote(v_pacotes, v_reserva);
            break;
        case 3:
            escolhaReserva(v_reserva, v_pacotes, v_Clientes);
            break;
        case 4:
            listarClientes(*v_Clientes);
            break;
        case 5:
            listarPacotes(*v_pacotes);
            break;
        case 6:
            listarReservas(*v_reserva);
            break;
        case 7:
            gerarRelatorio();
            break;
        case 8:
            sair = true;
            break;
        default:
            printf("Digite novamente\n");
            break;
        }
    }
}

// CLIENTES===============================================================

void carregarDadosClientes(Cliente **v_Clientes)
{
    FILE *p;
    p = fopen("Clientes.txt", "r");

    if (p == NULL)
    {
        printf("Erro ao abrir o arquivo...\n");
        system("pause");
        exit(1);
    }
    int atual = 0;
    while (fscanf(p, "%49[^\n]\n%15[^\n]\n%18[^\n]\n%49[^\n]\n", (*v_Clientes)[atual].cliente_nome,
                  (*v_Clientes)[atual].cliente_cpf, (*v_Clientes)[atual].cliente_telefone,
                  (*v_Clientes)[atual].cliente_email) != EOF)
    {
        atual++;
        if (atual % contAux == 0)
        {
            Cliente *temp = (Cliente *)realloc(*v_Clientes, (contAux + 10) * sizeof(Cliente));
            if (temp == NULL)
            {
                printf("Erro ao alocar mais memória em Clientes...\n");
                system("pause");
                exit(1);
            }
            *v_Clientes = temp;
        }
    }
    contAtualCliente = atual;
    fclose(p);
}

void carregarAlteracaoClientes(Cliente **v_Clientes)
{
    FILE *p;
    p = fopen("Clientes.txt", "w");

    if (p == NULL)
    {
        printf("Erro ao atualizar Clientes no banco de dados...\n");
        system("pause");
        exit(1);
    }

    for (int i = 0; i < contAtualCliente; i++)
    {
        fprintf(p, "%s\n%s\n%s\n%s\n", (*v_Clientes)[i].cliente_nome,
                (*v_Clientes)[i].cliente_cpf,
                (*v_Clientes)[i].cliente_telefone,
                (*v_Clientes)[i].cliente_email);
    }
    fclose(p);
}

void escolhaOpcaoCliente(Cliente **v_Clientes, Reserva **v_reserva)
{
    int opc1;

    bool sair = false;

    do{
        printf("=======CLIENTES=======\n");
        printf("Digite uma opção: \n");
        printf("1 - Cadastrar um cliente\n");
        printf("2 - Alterar um cliente\n");
        printf("3 - Consultar um cliente\n");
        printf("4 - Remover um cliente\n");
        printf("5 - Menu\n");
        scanf("%d%*c", &opc1);

        switch (opc1)
        {
        case 1:
            cadastroCliente(v_Clientes);
            break;
        case 2:
            alteraCliente(v_Clientes);
            break;
        case 3:
            consultaCliente(v_Clientes);
            break;
        case 4:
            removerCliente(v_Clientes, v_reserva);
            break;
        case 5:
            sair = true;
            break;
        default:
            printf("Digite novamente...\n");
            break;
        }
    } while(!sair);
}

void cadastroCliente(Cliente **v_Clientes)
{
    bool existe;
    char cpfTemp[16];

    FILE *p;
    p = fopen("Clientes.txt", "a");

    if (p == NULL)
    {
        printf("Erro ao abrir o arquivo...\n");
        system("pause");
        exit(1);
    }

    printf("====CADASTRO DE CLIENTES====\n");

    if (contAtualCliente % contAux == 0)
    {
        Cliente *temp = realloc(*v_Clientes, (contAux + 10) * sizeof(Cliente));
        if (temp == NULL)
        {
            printf("Erro ao adicionar memória em Clientes...\n");
            system("pause");
            exit(1);
        }
        *v_Clientes = temp;
    }

    printf("Nome do cliente: \n");
    gets((*v_Clientes)[contAtualCliente].cliente_nome);

    do
    {
        existe = false;
        printf("CPF do cliente: \n");
        gets(cpfTemp);
        for (int i = 0; i < contAtualCliente; i++)
        {
            if (strcmp(cpfTemp, (*v_Clientes)[i].cliente_cpf) == 0)
            {
                existe = true;
                printf("Cliente já cadastrado...tente novamente\n");
            }
        }
    } while (existe == true);

    strcpy((*v_Clientes)[contAtualCliente].cliente_cpf, cpfTemp);

    printf("Telefone do cliente: \n");
    gets((*v_Clientes)[contAtualCliente].cliente_telefone);

    printf("Email do cliente: \n");
    gets((*v_Clientes)[contAtualCliente].cliente_email);

    fprintf(p, "%s\n%s\n%s\n%s\n", (*v_Clientes)[contAtualCliente].cliente_nome,
            (*v_Clientes)[contAtualCliente].cliente_cpf,
            (*v_Clientes)[contAtualCliente].cliente_telefone,
            (*v_Clientes)[contAtualCliente].cliente_email);

    contAtualCliente++;
    fclose(p);
    printf("Cadastro concluído...\n");
}

void alteraCliente(Cliente **v_Clientes)
{
    int opc1_2;
    bool existe = false;
    char cpf_alteracao[50];

    printf("====ALTERAÇÃO DE CLIENTES====\n");
    do
    {
        existe = false;
        printf("Deseja alterar dados de qual cliente? \n");
        gets(cpf_alteracao);
        for (int i = 0; i < contAtualCliente; i++)
        {
            if (strcmp((*v_Clientes)[i].cliente_cpf, cpf_alteracao) == 0)
            {
                existe = true;
                printf("Deseja alterar qual informação do cliente?\n");
                printf("1 - Nome\n");
                printf("2 - CPF\n");
                printf("3 - Telefone\n");
                printf("4 - Email\n");
                scanf("%d%*c", &opc1_2);
                switch (opc1_2)
                {
                case 1:
                    printf("==ALTERAÇÃO DO NOME DO CLIENTE==\n");
                    printf("Digite o novo nome: \n");
                    gets((*v_Clientes)[i].cliente_nome);
                    printf("Novo nome: %s\n", (*v_Clientes)[i].cliente_nome);
                    carregarAlteracaoClientes(v_Clientes);
                    break;

                case 2:
                    printf("==ALTERAÇÃO DO CPF DO CLIENTE==\n");
                    printf("Digite o novo cpf: \n");
                    gets((*v_Clientes)[i].cliente_cpf);
                    printf("Novo CPF: %s\n", (*v_Clientes)[i].cliente_cpf);
                    carregarAlteracaoClientes(v_Clientes);
                    break;

                case 3:
                    printf("==ALTERAÇÃO DO TELEFONE DO CLIENTE==\n");
                    printf("Digite o novo telefone: \n");
                    gets((*v_Clientes)[i].cliente_telefone);
                    printf("Novo telefone: %s\n", (*v_Clientes)[i].cliente_telefone);
                    carregarAlteracaoClientes(v_Clientes);
                    break;

                case 4:
                    printf("==ALTERAÇÃO DO EMAIL DO CLIENTE==\n");
                    printf("Digite o novo email: \n");
                    gets((*v_Clientes)[i].cliente_email);
                    printf("Novo email: %s\n", (*v_Clientes)[i].cliente_email);
                    carregarAlteracaoClientes(v_Clientes);
                    break;
                }
            }
        }
        if (existe == false)
        {
            printf("Não há nenhum cliente cadastrado com esse cpf...tente novamente\n");
        }
    } while (existe == false);
}

void consultaCliente(Cliente **v_Clientes)
{
    char cpf_alteracao[50];
    bool existe = false;

    printf("====CONSULTA DE CLIENTES====\n");
    do
    {
        existe = false;
        printf("Deseja consultar dados de qual cliente? \n");
        gets(cpf_alteracao);
        for (int i = 0; i < contAtualCliente; i++)
        {
            if (strcmp((*v_Clientes)[i].cliente_cpf, cpf_alteracao) == 0)
            {
                existe = true;
                printf("Nome: %s\nCPF: %s\nTelefone: %s\nEmail: %s\n", (*v_Clientes)[i].cliente_nome,
                       (*v_Clientes)[i].cliente_cpf,
                       (*v_Clientes)[i].cliente_telefone,
                       (*v_Clientes)[i].cliente_email);
            }
        }
        if (existe == false)
        {
            printf("Não há nenhum cliente cadastrado com esse cpf...tente novamente\n");
        }
    } while (existe == false);
}

void removerCliente (Cliente **v_Clientes, Reserva **v_reserva){

    char cpf_alteracao[50];
    bool existe = false;
    int index;

    printf ("=======REMOÇÃO DE CLIENTES=======\n");

    do{
        existe = false;
        printf("Deseja remover qual cliente? \n");
        gets(cpf_alteracao);

        for (int i = 0; i < contAtualCliente; i++){
            if (strcmp((*v_Clientes)[i].cliente_cpf, cpf_alteracao) == 0){
                existe = true;
                index = i;
            }
        }
        if(existe == false){
            printf ("CPF não cadastrado...tente novamente\n");
        }
    }while (existe == false);


    existe = false;
    for(int i = 0; i < cont; i++){
        if(strcmp((*v_Clientes)[index].cliente_cpf, (*v_reserva)[i].reserva_cliente_cpf) == 0){
            printf("Cliente possui uma reserva, exclua sua reserva antes...\n");
            existe = true;
        }
    }

    if(existe == false){
        strcpy((*v_Clientes)[index].cliente_cpf, (*v_Clientes)[--contAtualCliente].cliente_cpf);
        carregarAlteracaoClientes(v_Clientes);
        printf("Cliente removido com sucesso...\n");
    }
}


void listarClientes(Cliente *v_Clientes)
{

    printf("=======LISTA DE REGISTRO DE CLIENTES=======\n");
    for (int i = 0; i < contAtualCliente; i++)
    {
        printf("Cliente %d\n", i + 1);
        printf("Nome: %s\n", v_Clientes[i].cliente_nome);
        printf("CPF: %s\n", v_Clientes[i].cliente_cpf);
        printf("Telefone: %s\n", v_Clientes[i].cliente_telefone);
        printf("Email: %s\n\n", v_Clientes[i].cliente_email);
    }
}

// PACOTES================================================================
void carregarDadosPacotes(Pacote **v_pacotes)
{
    FILE *p;
    p = fopen("Pacotes.txt", "r");
    if (p == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    int total = 0;
    while ((fscanf(p, "%d,%49[^,],%d,%d,%d,%d,%d,%d,%f\n",
                   &(*v_pacotes)[total].pacote_codigo,
                   (*v_pacotes)[total].pacote_destino,
                   &(*v_pacotes)[total].pacote_data_ida.dia,
                   &(*v_pacotes)[total].pacote_data_ida.mes,
                   &(*v_pacotes)[total].pacote_data_ida.ano,
                   &(*v_pacotes)[total].pacote_data_volta.dia,
                   &(*v_pacotes)[total].pacote_data_volta.mes,
                   &(*v_pacotes)[total].pacote_data_volta.ano,
                   &(*v_pacotes)[total].preco)) != EOF)
    {
        total++;

        if (total % MIN_ALOC == 0)
        {
            Pacote *temp = (Pacote *)realloc((*v_pacotes), (total + MIN_ALOC) * sizeof(Pacote));
            if (temp == NULL)
            {
                printf("Erro ao alocar mais memoria para pacotes\n");
                fclose(p);
                exit(1);
            }
            *v_pacotes = temp;
        }
    }

    total_pacotes = total;
    fclose(p);
}

void carregarAlteracaoPacotes(Pacote **v_pacotes)
{
    FILE *p;
    p = fopen("Pacotes.txt", "w");

    if (p == NULL)
    {
        printf("Erro ao atualizar pacote no banco de dados\n");
        system("pause");
        exit(1);
    }

    for (int i = 0; i < total_pacotes; i++)
    {
        fprintf(p, "%d,%s,%d,%d,%d,%d,%d,%d,%.2f\n",
                (*v_pacotes)[i].pacote_codigo,
                (*v_pacotes)[i].pacote_destino,
                (*v_pacotes)[i].pacote_data_ida.dia,
                (*v_pacotes)[i].pacote_data_ida.mes,
                (*v_pacotes)[i].pacote_data_ida.ano,
                (*v_pacotes)[i].pacote_data_volta.dia,
                (*v_pacotes)[i].pacote_data_volta.mes,
                (*v_pacotes)[i].pacote_data_volta.ano,
                (*v_pacotes)[i].preco);
    }

    fclose(p);
}

void escolhaOpcaoPacote(Pacote **v_pacotes, Reserva **v_reserva)
{
    int opc = -1;
    bool sair = false;
    while(!sair){
        printf("===========PACOTES===========\n");
        printf("1 - Cadastrar novo pacote\n");
        printf("2 - Alterar pacote\n");
        printf("3 - Consultar pacote existente\n");
        printf("4 - Remover pacote\n");
        printf("5 - Menu\n");
        scanf("%d%*c", &opc);
        switch (opc)
        {
        case 1:
            cadastrarPacote(v_pacotes);
            break;
        case 2:
            alterarPacote(v_pacotes);
            break;
        case 3:
            consultarPacote(v_pacotes);
            break;
        case 4:
            removerPacote(v_pacotes, v_reserva);
            break;
        case 5:
            sair = true;
            break;
        default:
            printf("Opcao invalida\n");
        }
    }
}

void cadastrarPacote(Pacote **v_pacotes)
{
    int idTemp, flag;

    printf("\n===============Cadastro de pacotes===============\n");

    if (total_pacotes % MIN_ALOC == 0)
    {
        Pacote *temp = (Pacote *)realloc(*v_pacotes, (total_pacotes + MIN_ALOC) * sizeof(Pacote));
        if (temp == NULL)
        {
            printf("Erro ao adicionar mais memoria para pacotes\n");
            exit(1);
        }
        *v_pacotes = temp;
    }

    do
    {
        flag = 0;
        printf("Digite o id do pacote: ");
        scanf("%d%*c", &idTemp);

        for (int i = 0; i < total_pacotes; i++)
        {
            if ((*v_pacotes)[i].pacote_codigo == idTemp)
            {
                flag = 1;
                printf("Erro, pacote com id ja existente, tente novamente...\n");
            }
        }
    } while (flag == 1);

    (*v_pacotes)[total_pacotes].pacote_codigo = idTemp;

    printf("Digite o destino do pacote: ");
    gets((*v_pacotes)[total_pacotes].pacote_destino);

    printf("Data de ida: \n");
    printf("Digite a data (dd/MM/yyyy): ");
    scanf("%d%*c%d%*c%d%*c", &(*v_pacotes)[total_pacotes].pacote_data_ida.dia,
          &(*v_pacotes)[total_pacotes].pacote_data_ida.mes,
          &(*v_pacotes)[total_pacotes].pacote_data_ida.ano);

    printf("Data de volta: \n");
    printf("Digite a data (dd/MM/yyyy): ");
    scanf("%d%*c%d%*c%d%*c", &(*v_pacotes)[total_pacotes].pacote_data_volta.dia,
          &(*v_pacotes)[total_pacotes].pacote_data_volta.mes,
          &(*v_pacotes)[total_pacotes].pacote_data_volta.ano);

    printf("Digite o valor do pacote: R$");
    scanf("%f", &(*v_pacotes)[total_pacotes].preco);

    FILE *p;
    p = fopen("Pacotes.txt", "a");
    if (p == NULL)
    {
        printf("Erro ao salvar no arquivo Pacotes.txt\n");
        exit(1);
    }

    fprintf(p, "%d,%s,%d,%d,%d,%d,%d,%d,%.2f\n",
            (*v_pacotes)[total_pacotes].pacote_codigo,
            (*v_pacotes)[total_pacotes].pacote_destino,
            (*v_pacotes)[total_pacotes].pacote_data_ida.dia,
            (*v_pacotes)[total_pacotes].pacote_data_ida.mes,
            (*v_pacotes)[total_pacotes].pacote_data_ida.ano,
            (*v_pacotes)[total_pacotes].pacote_data_volta.dia,
            (*v_pacotes)[total_pacotes].pacote_data_volta.mes,
            (*v_pacotes)[total_pacotes].pacote_data_volta.ano,
            (*v_pacotes)[total_pacotes].preco);

    total_pacotes++;
    fclose(p);

    printf("Pacote cadastrado com sucesso!\n");
}

void alterarPacote(Pacote **v_pacotes)
{

    int codTemp, flag, index, opc;

    printf("\n===============Alteração de pacote===============\n");

    do
    {
        flag = 1;
        printf("Digite o codigo do pacote: ");
        scanf("%d%*c", &codTemp);
        for (int i = 0; i < total_pacotes; i++)
        {
            if (codTemp == (*v_pacotes)[i].pacote_codigo)
            {
                flag = 0;
                index = i;
            }
        }
        if (flag == 1)
            printf("Pacote inexistente, tente novamente....\n");

    } while (flag == 1);

    printf("Pacote encontrado: \n");
    printf("\nPacote encontrado: \n");
    printf("Codigo: %d\nDestino: %s\nData de ida: %d/%d/%d\nData de volta: %d/%d/%d\nValor: R$%.2f\n\n",
           (*v_pacotes)[index].pacote_codigo,
           (*v_pacotes)[index].pacote_destino,
           (*v_pacotes)[index].pacote_data_ida.dia,
           (*v_pacotes)[index].pacote_data_ida.mes,
           (*v_pacotes)[index].pacote_data_ida.ano,
           (*v_pacotes)[index].pacote_data_volta.dia,
           (*v_pacotes)[index].pacote_data_volta.mes,
           (*v_pacotes)[index].pacote_data_volta.ano,
           (*v_pacotes)[index].preco);

    do
    {
        flag = 0;
        printf("1 - Alterar destino\n");
        printf("2 - Alterar data de ida\n");
        printf("3 - Alterar data de volta\n");
        printf("4 - Alterar valor do pacote\n");
        printf("5 - Cancelar alteracao\n");
        scanf("%d%*c", &opc);
        switch (opc)
        {
        case 1:
            printf("Digite o novo destino: ");
            gets((*v_pacotes)[index].pacote_destino);
            break;
        case 2:
            printf("Digite a nova data de ida (dd/MM/yyyy): ");
            scanf("%d%*c%d%*c%d%*c",
                  &(*v_pacotes)[index].pacote_data_ida.dia,
                  &(*v_pacotes)[index].pacote_data_ida.mes,
                  &(*v_pacotes)[index].pacote_data_ida.ano);
            break;
        case 3:
            printf("Digite a nova data de volta (dd/MM/yyyy): ");
            scanf("%d%*c%d%*c%d%*c",
                  &(*v_pacotes)[index].pacote_data_volta.dia,
                  &(*v_pacotes)[index].pacote_data_volta.mes,
                  &(*v_pacotes)[index].pacote_data_volta.ano);
            break;
        case 4:
            printf("Digite o novo valor do pacote: ");
            scanf("%f%*c", &(*v_pacotes)[index].preco);
            break;
        case 5:
            printf("Processo cancelado...\n");
            flag = -1;
            break;
        default:
            printf("Opcao invalida, tente novamente...");
            flag = 1;
            break;
        }
    } while (flag == 1);

    if (flag == 0)
    {
        printf("Pacote alterado com sucesso...\n");
        carregarAlteracaoPacotes(v_pacotes);
    }
}

void consultarPacote(Pacote **v_pacotes)
{

    int codTemp, flag, index;

    printf("\n===============Consulta de pacotes===============\n");

    do
    {
        flag = 1;
        printf("Digite o codigo do pacote: ");
        scanf("%d%*c", &codTemp);
        for (int i = 0; i < total_pacotes; i++)
        {
            if (codTemp == (*v_pacotes)[i].pacote_codigo)
            {
                flag = 0;
                index = i;
            }
        }
        if (flag == 1)
            printf("Pacote inexistente, tente novamente....\n");

    } while (flag == 1);

    printf("\nPacote encontrado: \n");
    printf("Codigo: %d\nDestino: %s\nData de ida: %d/%d/%d\nData de volta: %d/%d/%d\nValor: R$%.2f\n\n",
           (*v_pacotes)[index].pacote_codigo,
           (*v_pacotes)[index].pacote_destino,
           (*v_pacotes)[index].pacote_data_ida.dia,
           (*v_pacotes)[index].pacote_data_ida.mes,
           (*v_pacotes)[index].pacote_data_ida.ano,
           (*v_pacotes)[index].pacote_data_volta.dia,
           (*v_pacotes)[index].pacote_data_volta.mes,
           (*v_pacotes)[index].pacote_data_volta.ano,
           (*v_pacotes)[index].preco);
}

void listarPacotes(Pacote *v_pacotes)
{

    printf("\n=============Listagem de pacotes================\n");
    for (int i = 0; i < total_pacotes; i++)
    {
        printf("Id: %d\nDestino: %s\nData de chegada: %d/%d/%d\nData de saida: %d/%d/%d\nValor: %.2f\n\n", v_pacotes[i].pacote_codigo,
               v_pacotes[i].pacote_destino, v_pacotes[i].pacote_data_ida.dia, v_pacotes[i].pacote_data_ida.mes,
               v_pacotes[i].pacote_data_ida.ano, v_pacotes[i].pacote_data_volta.dia, v_pacotes[i].pacote_data_volta.mes,
               v_pacotes[i].pacote_data_volta.ano, v_pacotes[i].preco);
    }
}

void removerPacote(Pacote **v_pacotes, Reserva **v_reserva)
{
    int idTemp;
    int flag;
    int index;

    do{
        flag = 0;
        printf("Digite o id do pacote: ");
        scanf("%d%*c", &idTemp);
        
        for(int i = 0; i < total_pacotes; i++){
            if((*v_pacotes)[i].pacote_codigo == idTemp){
                flag = 1;
                index = i;
                break;
            }
        }
        if(flag == 0) printf("Pacote inexistente, tente novamente...\n");
    } while(flag == 0);

    for(int i = 0; i < cont; i++){
        if((*v_pacotes)[index].pacote_codigo == (*v_reserva)[i].reserva_codigo){
            printf("Pacote cadastrado em uma reserva, exclua a reserva para excluir o pacote...\n");
            flag = 0;
            break;
        }  
    }

    if(flag == 1){
        (*v_pacotes)[index] = (*v_pacotes)[--total_pacotes];
        printf("Pacote removido com sucesso...\n");
        carregarAlteracaoPacotes(v_pacotes);
    }

}
// RESERVAS

void escolhaReserva(Reserva **v_reserva, Pacote **v_pacotes, Cliente **v_Clientes)
{

    int opc = -1;
    bool sair = false;

    while(!sair){
        printf("===============RESERVAS================\n");
        printf("1 - Cadastrar Reservas\n");
        printf("2 - Alterar Reservas\n");
        printf("3 - Remover Reservas\n");
        printf("4 - Voltar ao Menu\n");
        printf("=======================================\n");

        scanf("%d%*c", &opc);

        switch (opc)
        {
        case 1:
            cadastraReserva(v_reserva, v_pacotes, v_Clientes);
            break;
        case 2:
            alteraReserva(v_reserva);
            break;
        case 3:
            removeReserva(v_reserva);
            break;
        case 4:
            sair = true;
            break;
        default:
            printf("Digite novamente\n");
            break;
        }
    }

}

void carregarReservasPrevias(Reserva **v_reserva)
{

    FILE *arq = fopen("Reservas.txt", "r");
    if (arq == NULL)
    {
        printf("Arquivo não encontrado. Criando um novo...\n");
        return;
    }

    cont = 0;
    while (fscanf(arq, "%d %d/%d/%d %s %d",
                  &(*v_reserva)[cont].reserva_codigo,
                  &(*v_reserva)[cont].reserva_data.dia,
                  &(*v_reserva)[cont].reserva_data.mes,
                  &(*v_reserva)[cont].reserva_data.ano,
                  (*v_reserva)[cont].reserva_cliente_cpf,
                  &(*v_reserva)[cont].reserva_pacote_codigo) == 6)
    {

        cont++;
        if (cont >= cont1)
        {
            expandirMemoria(v_reserva);
        }
    }

    fclose(arq);
}

void salvarReservas(Reserva **v_reserva)
{
    FILE *arq = fopen("Reservas.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < cont; i++)
    {
        fprintf(arq, "%d %d/%d/%d %s %d\n",
                (*v_reserva)[i].reserva_codigo,
                (*v_reserva)[i].reserva_data.dia,
                (*v_reserva)[i].reserva_data.mes,
                (*v_reserva)[i].reserva_data.ano,
                (*v_reserva)[i].reserva_cliente_cpf,
                (*v_reserva)[i].reserva_pacote_codigo);
    }

    fclose(arq);
    printf("Alterações salvas no arquivo!\n");
}

void expandirMemoria(Reserva **v_reserva)
{
    cont1 += 10;
    Reserva *temp = (Reserva *)realloc((*v_reserva), cont1 * sizeof(Reserva));
    if (temp == NULL)
    {
        printf("Erro ao alocar mais memória.\n");
        exit(1);
    }
    (*v_reserva) = temp;
}

void cadastraReserva(Reserva **v_reserva, Pacote **v_pacotes, Cliente **v_Clientes)
{
    if (cont >= cont1)
    {
        expandirMemoria(v_reserva);
    }

    int cod_temp, dia_temp, mes_temp, ano_temp, cod_pac_temp, flag = 1, v;
    char cpf_temp[16];

    printf("===============Comecando cadastro de Reserva================\n");

    do
    {
        flag = 1;
        printf("Digite o codigo da reserva: ");
        scanf("%d%*c", &cod_temp);

        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == cod_temp)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Codigo ja existe, digite novamente\n");
        }

    } while (flag == 0);

    (*v_reserva)[cont].reserva_codigo = cod_temp;

    flag = 1;

    // DATA DO CADASTRO DO PACOTE==========================================
    do
    {
        flag = 1;
        printf("Digite a data da reserva: ");
        scanf("%d/%d/%d%*c", &dia_temp, &mes_temp, &ano_temp);

        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_data.dia == dia_temp && (*v_reserva)[i].reserva_data.mes == mes_temp && (*v_reserva)[i].reserva_data.ano == ano_temp)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            {
                printf("Data ja existe, deseja cadastrar outro pacote nessa data?\n 1 - Sim\t2 - Nao\n");
                scanf("%d%*c", &v);
                if (v == 1)
                {
                    flag = 1;
                }
            }
    } while (flag == 0);

    (*v_reserva)[cont].reserva_data.dia = dia_temp;
    (*v_reserva)[cont].reserva_data.mes = mes_temp;
    (*v_reserva)[cont].reserva_data.ano = ano_temp;

    // VERIRICAÇÕES COM O CPF===============================================
    // VERIFICA SE TEM CLIENTE COM O CPF
    do
    {
        flag = 0;
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf_temp);

        for (int i = 0; i < contAtualCliente; i++)
        {
            if (strcmp((*v_Clientes)[i].cliente_cpf, cpf_temp) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
            printf("Cpf do cliente nao encontrado, tente novamente\n");
    } while (flag == 0);

    // VERIRICA SE JÁ TEM RESERVA COM ESSE CLIENTE
    do
    {
        flag = 1;
        for (int i = 0; i < cont; i++)
        {
            if (strcmp((*v_reserva)[i].reserva_cliente_cpf, cpf_temp) == 0)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Cpf ja tem uma reserva, deseja cadastrar outra?\n 1 - Sim\t2 - Nao\n");
            scanf("%d%*c", &v);
            if (v == 1)
            {
                flag = 1;
            }
        }
    } while (flag == 0);

    strcpy((*v_reserva)[cont].reserva_cliente_cpf, cpf_temp);

    // VERIRICAÇÕES COM O PACOTE===============================================
    // VERIRICA SE EXISTE O ID DO PACOTE
    do
    {
        flag = 1;
        printf("Digite o codigo do pacote: ");
        scanf("%d%*c", &cod_pac_temp);

        for (int i = 0; i < total_pacotes; i++)
        {
            if (cod_pac_temp == (*v_pacotes)[i].pacote_codigo)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1){
            printf("Codigo do pacote inexistente, tente novamente...\n");
        }

    } while (flag == 1);

    // VERIRICA SE O PACOTE JÁ EXISTE NA RESERVA
    do
    {
        flag = 1;
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_pacote_codigo == cod_pac_temp)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Pacote já tem uma reserva, deseja fazer outra??\n 1 - Sim\t2 - Nao\n");
            scanf("%d%*c", &v);
            if (v == 1)
            {
                flag = 1;
            }
        }
    } while (flag == 0);

    (*v_reserva)[cont].reserva_pacote_codigo = cod_pac_temp;

    cont++;
    salvarReservas(v_reserva);

    printf("Reserva cadastrada com sucesso!\n");
}

void alteraReserva(Reserva **v_reserva)
{

    int opc = -1;

    printf("===============Comecando Alteracao================\n");

    printf("1 - Alterar codigo da reserva\n");
    printf("2 - Aleterar data da reserva\n");
    printf("3 - Alterar CPF do cliente que fez essa reserva\n");
    printf("4 - Alterar codigo do pacote dessa reserva\n");

    scanf("%d%*c", &opc);

    switch (opc)
    {
    case 1:
        alteraCodigoReserva(v_reserva);
        break;
    case 2:
        alteraDataReserva(v_reserva);
        break;
    case 3:
        alteraCpfReserva(v_reserva);
        break;
    case 4:
        alteraCodigoPacoteReserva(v_reserva);
        break;
    default:
        printf("Digite novamente\n");
        alteraReserva(v_reserva);
        break;
    }
}

void alteraCodigoReserva(Reserva **v_reserva)
{

    int cod_reserva = -1;
    int flag = 0;
    int x;
    int n_cod;

    printf("===============Comecando Alteracao de Codigo================\n");

    do
    {
        flag = 0;
        printf("Digite o codigo da reserva que quer alterar: \n");
        scanf("%d%*c", &cod_reserva);
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == cod_reserva)
            {
                flag = 1;
                x = i;
                break;
            }
        }

        if (flag == 0)
        {

            printf("Codigo nao achado, digite novamente\n");
        }

    } while (flag == 0);

    do
    {
        flag = 1;
        printf("Digite o novo codigo: \n");
        scanf("%d%*c", &n_cod);
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == n_cod)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {

            printf("Codigo ja existe, digite novamente\n");
        }

    } while (flag == 0);

    (*v_reserva)[x].reserva_codigo = n_cod;

    salvarReservas(v_reserva);

    printf("Codigo alterado com sucesso!\n");
}

void alteraDataReserva(Reserva **v_reserva)
{

    int cod_reserva = -1;
    int flag = 0;
    int x, v;
    int novo_dia, novo_mes, novo_ano;

    printf("===============Comecando Alteracao da Data================\n");

    do
    {
        flag = 0;
        printf("Digite o codigo da reserva que quer alterar: \n");
        scanf("%d%*c", &cod_reserva);
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == cod_reserva)
            {
                flag = 1;
                x = i;
                break;
            }
        }

        if (flag == 0)
        {

            printf("Codigo nao achado, digite novamente\n");
        }

    } while (flag == 0);

    do
    {

        flag = 1;

        printf("Digite a nova data da reserva: ");
        scanf("%d/%d/%d%*c", &novo_dia, &novo_mes, &novo_ano);

        for (int i = 0; i < cont; i++)
        {

            if ((*v_reserva)[i].reserva_data.dia == novo_dia && (*v_reserva)[i].reserva_data.mes == novo_mes && (*v_reserva)[i].reserva_data.ano == novo_ano)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Data ja existe, realmente esta certa?\n 1 - Sim\t2 - Nao\n");
            scanf("%d", &v);
            if (v == 1)
            {
                flag = 1;
            }
        }

    } while (flag == 0);

    (*v_reserva)[x].reserva_data.dia = novo_dia;
    (*v_reserva)[x].reserva_data.mes = novo_mes;
    (*v_reserva)[x].reserva_data.ano = novo_ano;
    salvarReservas(v_reserva);
    printf("Codigo alterado com sucesso!\n");
}

void alteraCpfReserva(Reserva **v_reserva)
{

    int cod_reserva, flag = 0, x, v;
    char novo_cpf[16];
    printf("\n===============Comecando Alteracao do Cpf================\n");

    do
    {
        flag = 0;
        printf("Digite o codigo da reserva que quer alterar: \n");
        scanf("%d%*c", &cod_reserva);
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == cod_reserva)
            {
                flag = 1;
                x = i;
                break;
            }
        }

        if (flag == 0)
        {

            printf("Codigo nao achado, digite novamente\n");
        }

    } while (flag == 0);

    do
    {
        flag = 1;
        printf("Digite o novo Cpf do cliente: ");
        scanf("%s", novo_cpf);

        for (int i = 0; i < cont; i++)
        {

            if (strcmp((*v_reserva)[i].reserva_cliente_cpf, novo_cpf) == 0)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Cpf ja existe, realmente esta certo?\n 1 - Sim\t2 - Nao\n");
            scanf("%d", &v);
            if (v == 1)
            {
                flag = 1;
            }
        }

    } while (flag == 0);

    strcpy((*v_reserva)[x].reserva_cliente_cpf, novo_cpf);
    salvarReservas(v_reserva);
    printf("Codigo alterado com sucesso!\n");
}

void alteraCodigoPacoteReserva(Reserva **v_reserva)
{

    printf("\n===============Comecando Alteracao do Codigo do Pacote================\n");

    int cod_reserva, flag = 0, x;
    int novo_cod_pac, v;

    do
    {
        flag = 0;
        printf("Digite o codigo da reserva que quer alterar: \n");
        scanf("%d%*c", &cod_reserva);
        for (int i = 0; i < cont; i++)
        {
            if ((*v_reserva)[i].reserva_codigo == cod_reserva)
            {
                flag = 1;
                x = i;
                break;
            }
        }

        if (flag == 0)
        {

            printf("Codigo nao achado, digite novamente\n");
        }

    } while (flag == 0);

    do
    {
        flag = 1;
        printf("Digite o novo codigo do pacote: ");
        scanf("%d", &novo_cod_pac);

        for (int i = 0; i < cont; i++)
        {

            if ((*v_reserva)[i].reserva_pacote_codigo == novo_cod_pac)
            {
                flag = 0;
                break;
            }
        }

        if (!flag)
        {
            printf("Esse codigo do pacote ja existe, realmente esta certo?\n 1 - Sim\t2 - Nao\n");
            scanf("%d", &v);
            if (v == 1)
            {
                flag = 1;
            }
        }

    } while (flag == 0);

    (*v_reserva)[x].reserva_pacote_codigo = novo_cod_pac;
    salvarReservas(v_reserva);
    printf("Codigo alterado com sucesso!\n");
}

void removeReserva(Reserva **v_reserva)
{

    int v, flag, cod_reserva, x;

    printf("===============Comecando remocao de Reserva================\n");

    printf("Voce quer remover todas as reservas ou alguma em especifico ?:\n 1 - Todas\t2 - Especifica\n");

    scanf("%d%*c", &v);

    if (v == 1)
    {

        cont = 0;
    }
    else
    {

        printf("===============Removendo Reserva especifica================\n");

        do
        {
            flag = 0;
            printf("Digite o codigo da reserva que voce quer remover: \n");
            scanf("%d%*c", &cod_reserva);
            for (int i = 0; i < cont; i++)
            {
                if ((*v_reserva)[i].reserva_codigo == cod_reserva)
                {
                    flag = 1;
                    x = i;
                    break;
                }
            }

            if (flag == 0)
            {

                printf("Codigo nao achado, digite novamente\n");
            }

        } while (flag == 0);

        for (int i = x; i < cont - 1; i++)
        {

            strcpy((*v_reserva)[i].reserva_cliente_cpf, (*v_reserva)[i + 1].reserva_cliente_cpf);
            (*v_reserva)[i].reserva_codigo = (*v_reserva)[i + 1].reserva_codigo;
            (*v_reserva)[i].reserva_pacote_codigo = (*v_reserva)[i + 1].reserva_pacote_codigo;
            (*v_reserva)[i].reserva_data.dia = (*v_reserva)[i + 1].reserva_data.dia;
            (*v_reserva)[i].reserva_data.mes = (*v_reserva)[i + 1].reserva_data.mes;
            (*v_reserva)[i].reserva_data.ano = (*v_reserva)[i + 1].reserva_data.ano;
        }
        cont--;
    }

    salvarReservas(v_reserva);
    printf("Remocao feita com sucesso!\n");
}

void listarReservas(Reserva *v_reserva)
{
    printf ("==========Reservas==========\n");
    for(int i = 0; i < cont; i++){
        printf("Codigo da reserva: %d\n", v_reserva[i].reserva_codigo);
        printf("Codigo do pacote: %d\n", v_reserva[i].reserva_pacote_codigo);
        printf ("Data em que a reserva foi feita: %d/%d/%d\n",v_reserva[i].reserva_data.dia,v_reserva[i].reserva_data.mes,v_reserva[i].reserva_data.ano);
        printf ("CPF do cliente que fez essa reserva: %s\n",v_reserva[i].reserva_cliente_cpf);
        printf ("============================\n");
    }
}

// RELATORIOS
void gerarRelatorio()
{
}