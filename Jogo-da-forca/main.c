#include <stdio.h>
#include <locale.h> //setlocale
#include <string.h>
#include <stdlib.h> //system("cls")

const int MaxTentativa = 9;

//Converte palavras para maiúsculas
void palavraMaius(char s[], const int tamanho){
    int p;
    for (p = 0; p < tamanho; p++){
        s[p] = toupper(s[p]);
    }
}

void IniciarJogo(){
    system("cls");

    printf("O jogador 2 terá %d chances de advinhar a palavra escolhida pelo jogador 1.\n\n", MaxTentativa);

    //Definindo os dois jogadores
    char Jogador1[20], Jogador2[20];
    printf("Digite o nome do jogador 1: ");
    getchar(); //buffer do teclado
    scanf(" %[^\n]s", Jogador1);
    printf("Digite o nome do jogador 2: ");
    getchar();
    scanf(" %[^\n]s", Jogador2);

    //Palavra a ser advinhada
    char Palavra[40];
    printf("\n%s, qual a palavra a ser advinhada? ", Jogador1);
    scanf(" %[^\n]s", Palavra);

    //Criando nova string para exibir o resultado, string de verificação
    int quantCar = strlen(Palavra);
    char nova[quantCar];

    //Converter a palavra para maiúsculas para facilitar a verificação
    //Inicializando a string de verificação
    int p;
    for (p = 0; p < strlen(Palavra); p++){
        Palavra[p] = toupper(Palavra[p]);
        nova[p] = '_';
    }
    nova[p] = '\0'; //Garantir que a string seja finalizada corretamente -> correção de erro

    system("cls");

    int i = 0;
    while(i <= MaxTentativa){
        printf("%s, %d° Letra: ", Jogador2, i+1);
        char letra;
        getchar();
        scanf(" %c", &letra);
        letra = toupper(letra);

        //Comparar a letra digitada com a palvra a ser advinhada
        int n;
        for(n = 0; n < strlen(Palavra); n++){
            if(Palavra[n] == letra){
                nova[n] = letra;
            }
        }
        printf("\t%s", nova);
        puts("");

        if(strcmp(Palavra, nova) == 0){
            printf("Parabéns você adivinhou a palavras em %d tentativas\n", i+1);
            break;
        }else
            printf("Restam %d tentativas!\n", MaxTentativa-i-1);

        if(i == 8){
            char chute[40];
            printf("Qual o seu chute: ");
            scanf(" %[^\n]s", chute);
            palavraMaius(chute, strlen(Palavra));
            if(strcmp(Palavra, chute) == 0)
                printf("Parabéns, você acertou!\n");
            else
                printf("Palavra errada!\n");
            break;
        }

        puts("\n");
        i++;
    }
};

int main()
{
    setlocale(LC_ALL, "Portuguese"); //Acentuações
    system("cls"); //Limpar tela

    int opcao;
    do{
        puts("\tJOGO DA FORCA");
        puts("1 - Iniciar jogo");
        puts("2 - Sair");

        scanf("%d", &opcao);

        switch(opcao){
            case 1: IniciarJogo(); break;
            case 2: break;
            default: printf("Opção inválida!\n"); break;
        }
    }while(opcao == 1);
    return 0;
}
