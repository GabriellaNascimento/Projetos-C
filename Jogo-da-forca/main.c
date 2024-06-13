#include <stdio.h>
#include <locale.h> //setlocale
#include <string.h>
#include <stdlib.h> //system("cls")

const int MaxTentativa = 9;

//Converte palavras para maiúsculas
int palavraMaius(char s[], const int tamanho){
    int p;
    for (p = 0; p < tamanho; p++){
        s[p] = toupper(s[p]);
    }
}

//Verifica se a letra ja foi digitada e ignora a tentativa
void letraJaDigitada(char *j, char n, int *i){
    int c = 0;
    for(c; c < 9; c++){
        if(j[c] == n){
            printf("Essa letra já foi digitada! Tente novamente\n\n");
            c = 0;
            break;
        }
    }
    if(c == 0){
        *i = *i - 1;
    }
    return *i;
}

void IniciarJogo(){
    system("cls");

    printf("O jogador 2 terá %d chances de advinhar a palavra escolhida pelo jogador 1.\n\n", MaxTentativa);

    //Variáveis
    char Jogador1[20], Jogador2[20];
    char Palavra[40]; //Palavra a ser advinhada

    //Definindo os dois jogadores
    printf("Digite o nome do jogador 1: ");
    getchar(); //buffer do teclado
    scanf(" %[^\n]s", Jogador1);
    printf("Digite o nome do jogador 2: ");
    getchar();
    scanf(" %[^\n]s", Jogador2);

    //Palavra a ser advinhada
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

    char LetrasDigitadas[40] = ""; //Variável para verificar as letras que já foram digitadas
    int i = 0;
    while(i <= MaxTentativa){
        printf("%s, %d° Letra: ", Jogador2, i+1);

        char letra;
        getchar();
        scanf(" %c", &letra);
        letra = toupper(letra);

        //Verificação se a letra ja foi digitadaTa
        letraJaDigitada(LetrasDigitadas, letra, &i);

        //Salvar a letra digitada
        int tam = strlen(LetrasDigitadas);
        LetrasDigitadas[tam] = letra;
        LetrasDigitadas[tam+1] = '\0';

        //Comparar a letra digitada com a palvra a ser advinhada
        int n;
        for(n = 0; n < strlen(Palavra); n++){
            if(Palavra[n] == letra){
                nova[n] = letra;
            }
        }

        printf("\t%s\n", nova);

        if(strcmp(Palavra, nova) == 0){//Verificar se a palavra já foi advinhada
            printf("Parabéns você adivinhou a palavras em %d tentativas\n", i+1);
            break;
        }else
            printf("Restam %d tentativas!\n", MaxTentativa-i-1);

        if(i == 8){
            char escolha;
            printf("Deseja fazer um chute? (S/N)");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);
            if(escolha == 'S'){
                char chute[40];
                printf("\nQual o seu chute: ");
                scanf(" %[^\n]s", chute);

                palavraMaius(chute, strlen(Palavra));

                if(strcmp(Palavra, chute) == 0)
                    printf("Parabéns, você acertou!\n\n");
                else
                    printf("Palavra errada!\n Você perdeu!\n\n");
            }else
                printf("Você perdeu!");
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
        puts("2 - Sair\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1: IniciarJogo(); break;
            case 2: break;
            default: printf("Opção inválida!\n"); break;
        }
    }while(opcao == 1);
    return 0;
}
