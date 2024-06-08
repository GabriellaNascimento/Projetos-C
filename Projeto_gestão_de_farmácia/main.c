#include <stdio.h>
#include <stdlib.h> //usando system
#include <ctype.h> //usando toupper
#include <string.h> //usando strcmp
#include <locale.h>

struct TpFarma{
    char Nome[21];
    float Preco;
    int QEstoque;
};

typedef struct TpFarma TpFARMA;
TpFARMA RgFarma;

FILE *ArqFarma;

long int Tamanho = sizeof(TpFARMA); //32BYTES -> 4BYTES DE PADDING
//21*sizeof(char)+sizeof(float)+sizeof(int); -> RETORNA 29BYTES -> SEM PADDING

//FUN��O PARA INCLUIR NO ARQUIVO UM NOVO FARMACO
void Incluir(){
    char R;
    ArqFarma = fopen("Farmacos.dat", "a+b");

    do{
        printf("*** Inclus�o ***\n\n");
        int ver = 0;

        //VERIFICAR SE O FARMACO J� EXISTE NO ARQUIVO, CASO N�O, ADICIONA-LO
        ver = 0;
        char Nome[21];
        printf("Nome: ");
        scanf(" %[^\n]s", Nome);
        do{
            fseek(ArqFarma, 0, 0); //MOVE O PONTEIRO PARA O IN�CIO E COM PULO DE 0BYTES
            while(fread(&RgFarma, Tamanho, 1, ArqFarma)){ //LEITURA DE 1 ELEMENTO POR VEZ
                if(strcmp(RgFarma.Nome, Nome) == 0 && RgFarma.Preco > 0){
                    printf("Farmaco j� existente!\n");
                    ver = 1;
                    return;
                }/*else{
                    strcpy(RgFarma.Nome, Nome);
                }*/
            }

        }while(ver);
        strcpy(RgFarma.Nome, Nome);
        do{
            printf("Pre�o: ");
            scanf("%f", &RgFarma.Preco);
            if(RgFarma.Preco < 0)
                printf("Pre�o Inv�lido!\n");
        } while(RgFarma.Preco < 0);

        do{
            printf("Estoque: ");
            scanf("%d", &RgFarma.QEstoque);
            if (RgFarma.QEstoque < 0)
                printf("Estoque Inv�lido!\n");
        } while(RgFarma.QEstoque < 0);

        fseek(ArqFarma, 0, 2); //POSICIONAR O PONTEIRO NO FINAL DO ARQUIVO
        fwrite(&RgFarma, Tamanho, 1, ArqFarma); //ESCREVER AS INFORMA��ES NO ARQUIVO

        printf("\nNoma inclus�o? S/N ");
        scanf(" %c", &R);
        R = toupper(R);
    }while(R != 'N');
    fclose(ArqFarma);
    return 0;
};

//EXCLUS�O L�GICA DE UM FARMACO DO ARQUIVO
//O FARMACO PASSAR� A TER PRE�O = -1
void Excluir(){
    system("cls");
    printf("*** Exclus�o ***\n\n");
    char Farmaco[21];
    fflush(stdin);
    printf("Nome do farmaco que deseja excluir: ");
    scanf(" %[^\n]", Farmaco);

    ArqFarma = fopen("Farmacos.dat", "r+b"); //ARQUIVO DEVE EXISTIR + LEITURA E ALTERA��O DOS DADOS
    fseek(ArqFarma, 0, 0);
    int Achou  = 0;
    while(fread(&RgFarma, Tamanho, 1, ArqFarma)){
        if (strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0){
            Achou = 1;
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: %.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
            fseek(ArqFarma, -Tamanho, 1); //VOLTAR PARA O DADO ENCONTRADO E MODIFICAR O VALOR DO PRE�O
            RgFarma.Preco = -1;
            fwrite(&RgFarma, Tamanho, 1, ArqFarma);
            break;
        }
    }

    if(Achou == 0)
        printf("Registro inexistente!");
    else
        printf("Exclus�o realizada!");

    fclose(ArqFarma);
    return;
}

//FUN��O QUE RETORNA A QUANTIDADE DE REGISTROS DO ARQUIVO
long int TArquivo(){
    fseek(ArqFarma, 0, 2);
    long int R = ftell(ArqFarma)/Tamanho; //FTELL -> DIZ A POSI��O ATUAL DO PONTEIRO DO ARQUIVO
    return R;
}

void Alterar(){
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if(TArquivo() != 0){
        system("cls");
        printf("*** Alterar ***\n\n");
        fseek(ArqFarma, 0, 0);
        printf("Qual farmaco? ");
        char Farmaco[21];
        scanf("%s", Farmaco);
        int Achou = 0;
        do{
            fread(&RgFarma, Tamanho, 1, ArqFarma);
            if(strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0){
                Achou = 1;
                printf("Nome: %s\n", RgFarma.Nome);
                printf("Valor: %.2f\n", RgFarma.Preco);
                printf("Estoque: %d\n", RgFarma.QEstoque);
            }
        }while(!feof(ArqFarma) && (Achou == 0));

        if(Achou == 0)
            printf("Registro inexistente!");
        else{
            do{
                printf("Qual o novo pre�o? \n");
                scanf("%f", &RgFarma.Preco);
                if(RgFarma.Preco < 0)
                    printf("Pre�o inv�lido!\n");
            }while(RgFarma.Preco < 0);
            do{
                printf("Qual a nova quantidade? \n");
                scanf("%d", &RgFarma.QEstoque);
                if (RgFarma.QEstoque < 0)
                    printf("Quantidade inv�lida\n");
            }while(RgFarma.QEstoque < 0);

            fseek(ArqFarma, -Tamanho, 1);
            fwrite(&RgFarma, Tamanho, 1, ArqFarma);
            printf(">>> Altera��o efetuada com sucesso! <<<\n");
        }

        fclose(ArqFarma);
        ArqFarma = fopen("Farmacos.dat", "a+b");
    }else
        printf("Arquivo vazio. N�o existem dados a alterar!");

    return 0;
};

//CONSULTAR OS DADOS DE UM FARMACO, CASO EXISTA
void Consultar(){
    system("cls");
    printf("*** Consultar ***\n\n");
    fseek(ArqFarma, 0, 0);
    printf("Qual farmaco? ");
    char Farmaco[21];
    scanf("%s", Farmaco);
    int Achou = 0;
    ArqFarma - fopen("Farmacos.dat", "r+b");
    do{
        fread(&RgFarma, Tamanho, 1, ArqFarma);
        if(strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0){
            Achou = 1;
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: %.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
        }
    }while(!feof(ArqFarma) && (Achou == 0));

    if(Achou == 0)
        printf("Registro inexistente!");
    fclose(ArqFarma);
    return;
}

//LISTA TODOS OS REGISTROS, EXCLUINDO OS QUE FORAM EXCLU�DOS LOGICAMENTE
void LTodos(){
    system("cls");
    printf("*** Listar todos ***\n\n");
    ArqFarma = fopen("Farmacos.dat", "r+b");

    if(ArqFarma == NULL){
        printf("Erro ao abrir o arquivo de farmacos!\n");
        return;
    }

    fseek(ArqFarma, 0, 0);
    while(fread(&RgFarma, Tamanho, 1, ArqFarma)){
        if(RgFarma.Preco > 0){
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: %.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
            printf("***\n\n");
        }
    }
    fclose(ArqFarma);
    return;
};

int main()
{
    setlocale(LC_ALL, "Portuguese"); //PERMITIR ACENTUA��O
    ArqFarma = fopen("Farmacos.dat", "a+b"); //ABRIR ARQUIVO
    /*modo a+b
    - se n�o existir, ser� criado
    - escrita */
    char opcao;
    do{
        printf("\n\n> > > Pague Pouco < < <\n\n");
        printf("O que deseja fazer? \n\n");
        printf("I - Incluir \n");
        printf("E - Excluir \n");
        printf("A - Alterar \n");
        printf("C - Consultar \n");
        printf("T - Listar Todos \n");
        printf("S - Sair \n\n");
        scanf(" %c", &opcao);
        opcao = toupper(opcao);
        switch (opcao){
            case 'I': Incluir(); break;
            case 'E': Excluir(); break;
            case 'A': Alterar(); break;
            case 'C': Consultar(); break;
            case 'T': LTodos(); break;
            case 'S': break;
            default: printf("Op��o Inv�lida!!"); break;
        }
    }while( opcao != 'S');

    fclose(ArqFarma); //FECHAR ARQUIVO
    return 0;
}
