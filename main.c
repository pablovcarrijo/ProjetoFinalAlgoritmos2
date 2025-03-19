#include <stdio.h>
#include <stdlib.h>

#define MIN_ALOC 20

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    char cliente_nome[50];
    char cliente_cpf[16];
    char cliente_telefone[17];
    char cliente_email[50];
} Cliente;

typedef struct{
    int pacote_codigo;
    char pacote_destino[50];
    Data pacote_data_ida;
    Data pacote_data_volta;
    float preco;
} Pacote;

typedef struct{
    int reserva_codigo;
    Cliente reserva_cliente;
    Pacote reserva_pacote;
    Data reserva_data;
} Reserva;

int total_pacotes = 0;

void menu(Pacote **v_pacotes);

void escolhaOpcaoCliente();
void escolhaOpcaoPacote(Pacote **v_pacotes);
void escolhaOpcaoReserva();

void listarClientes();
void listarPacotes(Pacote *v_pacotes);
void listarReservas();
void gerarRelatorio();

void cadastrarPacote(Pacote **v_pacotes);
void consultarPacote(Pacote **v_pacotes);
void alterarPacote(Pacote **v_pacotes);
void removerPacote();

void carregarDadosClientes();
void carregarDadosPacotes(Pacote **v_pacotes);

int main(){

    Pacote *v_pacotes = (Pacote*)malloc(MIN_ALOC * sizeof(Pacote));
    carregarDadosPacotes(&v_pacotes);

    menu(&v_pacotes);

    free(v_pacotes);

    return 0;

}

void menu(Pacote **v_pacotes){

    int opc = -1;
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

    switch(opc){
        case 1:
            escolhaOpcaoCliente();
            break;
        case 2:
            escolhaOpcaoPacote(v_pacotes);
            break;
        case 3:
            escolhaOpcaoReserva();
            break;
        case 4:
            listarClientes();
            break;
        case 5:
            listarPacotes(*v_pacotes);
            break;
        case 6:
            listarReservas();
            break;
        case 7:
            gerarRelatorio();
            break;
        case 8:
            exit(0);
            break;
        default:
            printf("Digite novamente\n");
            break;
        
    }
    menu(v_pacotes);

}

//CLIENTES

void carregarDadosClientes(){

}

void escolhaOpcaoCliente(){

}

void listarClientes(){

}

//PACOTES
void carregarDadosPacotes(Pacote **v_pacotes) {
    FILE *p;
    p = fopen("Pacotes.txt", "r");
    if (p == NULL) {
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
                &(*v_pacotes)[total].preco)) != EOF) {
        total++;

        if (total % MIN_ALOC == 0) {
            Pacote *temp = (Pacote *)realloc((*v_pacotes), (total + MIN_ALOC) * sizeof(Pacote));
            if (temp == NULL) {
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

void carregarAlteracaoPacotes(Pacote **v_pacotes){
    FILE *p;
    p = fopen("Pacotes.txt", "w");

    if(p == NULL){
        printf("Erro ao atualizar pacote no banco de dados\n");
        system("pause");
        exit(1);
    }

    for(int i = 0; i < total_pacotes; i++){
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
    escolhaOpcaoPacote(v_pacotes);

}

void escolhaOpcaoPacote(Pacote **v_pacotes){
    int opc = -1;
    printf("===========PACOTES===========\n");
    printf("1 - Cadastrar novo pacote\n");
    printf("2 - Alterar pacote\n");
    printf("3 - Consultar pacote existente\n");
    printf("4 - Remover pacote\n");
    printf("5 - Menu\n");
    scanf("%d%*c", &opc);
    switch(opc){
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
            removerPacote();
            break;
        case 5:
            menu(v_pacotes);
            break;
        default:
            printf("Opcao invalida\n");
    }
    escolhaOpcaoPacote(v_pacotes);
}

void cadastrarPacote(Pacote **v_pacotes) {
    int idTemp, flag;

    printf("\n===============Cadastro de pacotes===============\n");

    if (total_pacotes % MIN_ALOC == 0) {
        Pacote *temp = (Pacote *)realloc(*v_pacotes, (total_pacotes + MIN_ALOC) * sizeof(Pacote));
        if (temp == NULL) {
            printf("Erro ao adicionar mais memoria para pacotes\n");
            exit(1);
        }
        *v_pacotes = temp;
    }

    do {
        flag = 0;
        printf("Digite o id do pacote: ");
        scanf("%d%*c", &idTemp);

        for (int i = 0; i < total_pacotes; i++) {
            if ((*v_pacotes)[i].pacote_codigo == idTemp) {
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
    if (p == NULL) {
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

void alterarPacote(Pacote **v_pacotes){

    int codTemp, flag, index, opc;

    printf("\n===============Alteração de pacote===============\n");

    do{
        flag = 1;
        printf("Digite o codigo do pacote: ");
        scanf("%d%*c", &codTemp);
        for(int i = 0; i < total_pacotes; i++){
            if(codTemp == (*v_pacotes)[i].pacote_codigo){
                flag = 0;
                index = i;
            }
        }
        if (flag == 1) printf("Pacote inexistente, tente novamente....\n");

    } while(flag == 1);

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

    do{
        flag = 0;
        printf("1 - Alterar destino\n");
        printf("2 - Alterar data de ida\n");
        printf("3 - Alterar data de volta\n");
        printf("4 - Alterar valor do pacote\n");
        printf("5 - Cancelar alteracao\n");
        scanf("%d%*c", &opc);
        switch(opc){
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
    } while(flag == 1);

    if(flag == 0){
        printf("Pacote alterado com sucesso...\n");
        carregarAlteracaoPacotes(v_pacotes);
    }

}

void consultarPacote(Pacote **v_pacotes){

    int codTemp, flag, index;

    printf("\n===============Consulta de pacotes===============\n");

    do{
        flag = 1;
        printf("Digite o codigo do pacote: ");
        scanf("%d%*c", &codTemp);
        for(int i = 0; i < total_pacotes; i++){
            if(codTemp == (*v_pacotes)[i].pacote_codigo){
                flag = 0;
                index = i;
            }
        }
        if (flag == 1) printf("Pacote inexistente, tente novamente....\n");

    } while(flag == 1);

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

void removerPacote(){

}

void listarPacotes(Pacote *v_pacotes){

    printf("\n=============Listagem de pacotes================\n");
    for(int i = 0; i < total_pacotes; i++){
        printf("Id: %d\nDestino: %s\nData de chegada: %d/%d/%d\nData de saida: %d/%d/%d\nValor: %.2f\n\n", v_pacotes[i].pacote_codigo,
            v_pacotes[i].pacote_destino,v_pacotes[i].pacote_data_ida.dia, v_pacotes[i].pacote_data_ida.mes,
            v_pacotes[i].pacote_data_ida.ano, v_pacotes[i].pacote_data_volta.dia, v_pacotes[i].pacote_data_volta.mes,
            v_pacotes[i].pacote_data_volta.ano, v_pacotes[i].preco);
    }

}

//RESERVAS 
void listarReservas(){

}

void escolhaOpcaoReserva(){

}

//RELATORIOS
void gerarRelatorio(){

}