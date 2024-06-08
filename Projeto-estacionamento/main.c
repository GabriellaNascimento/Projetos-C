#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

struct RegMoto{
	char Nome[20];
	char Modelo[10];
	char Placa[7];
	char Defeito[50];
	char Status;
	float Preco;
};
typedef struct RegMoto TpRegMoto;

const int quantMotos = 50;
TpRegMoto VZonda[50];

typedef struct TotalDia{
	char Data[15];
	float Valor;
}TpTotalDia;
TpTotalDia Dados;

FILE *Servicos;
FILE *Historico;

long int TamanhoServ = sizeof(TpRegMoto);
long int TamanhoHist = sizeof(TpTotalDia);

int Quant=-1;//Controla o preenchimento do vetor
float total = 0;

void SolicitaServico(){
	system("cls");
	char Sair='S';
	do{
		printf("\n\n >>> Motos Zonda <<< \n\n");
		Quant = Quant+1;
		printf("Qual o nome do cliente? ");
		scanf(" %[^\n]s",VZonda[Quant].Nome);
		printf("Qual o modelo da moto? ");
		scanf(" %[^\n]s",VZonda[Quant].Modelo);

		//EVITAR PLACAS REPETIDAS
		if (Quant != -1) {
			int placaExistente;
			do{
				placaExistente = 0; //assumindo que não existe placa igual
				printf("Qual a placa da moto? ");
				scanf(" %[^\n]s", VZonda[Quant].Placa);
				int i;
				for (i = 0; i < Quant; i++) {
					if (strcmp(VZonda[Quant].Placa, VZonda[i].Placa) == 0) {
						printf("Placa já registrada!\n");
						placaExistente = 1;
						break;
					}
				}
			}while (placaExistente);
		}

		printf("Qual o defeito da moto? ");
		scanf(" %[^\n]s",VZonda[Quant].Defeito);
		VZonda[Quant].Status = '0';
		VZonda[Quant].Preco = 0;

		printf("\n\n Deseja inserir novo servico? S|N ");
		scanf(" %c",&Sair);
		Sair=toupper(Sair);
	}while (Sair!='N');
}

void IniciaServico(){
	system("cls"); //limpa tela no ReplIt
	char P[7];

	printf("Placa da moto para iniciar serviço: ");
	scanf(" %[^\n]s",P);

	int Pos=-1; //posição da moto P no vetor

	//busca da moto para iniciar serviço
	int Cont;
	for (Cont=0; Cont<=Quant; Cont++){
		if (strcmp(VZonda[Cont].Placa,P)==0)
		   Pos=Cont;
	}
	if (Pos==-1)
	   printf("Moto não cadastrada!");
	else{
		printf("\n Cliente %d: %s", Pos+1, VZonda[Pos].Nome);
		printf("\n Modelo: %s", VZonda[Pos].Modelo);
		printf("\n Placa: %s", VZonda[Pos].Placa);
		printf("\n Defeito: %s", VZonda[Pos].Defeito);
		VZonda[Pos].Status='1';
		printf("\n Status: %c",VZonda[Pos].Status);
		if (VZonda[Pos].Preco==0)
		   printf("\n Preco: NAO DEFINIDO");
		else
			printf("\n Preco: %.2f",VZonda[Pos].Preco);
	}
}

void RemoverSolicitacao(){
	system("cls"); //limpa tela no ReplIt
	char P[7];
	printf("Placa da moto para remover solicitação: ");
	scanf(" %[^\n]s",P);
	int Pos = -1;

	//Buscar a placa
	int i;
	for (i = 0; i <= Quant; i++) {
		if (strcmp(VZonda[i].Placa, P) == 0) {
			Pos = i;
			break;
		}
	}
	if(Pos != -1){
		if(VZonda[Pos].Status == '0'){
		int i;
		for (i = Pos; i <= Quant; i++){
			VZonda[i] = VZonda[i + 1];
		}
		Quant--;
		printf("Solicitação removida!\n");
		}else
	 		printf("O serviço ja foi iniciado, nao e possivel remover a solicitacao!\n");
	}else
		printf("Moto não encontrada!\n");
}

void ConsultarSolicitacoes(){
	system("cls"); //limpa tela no ReplIt
	printf("\n\n >>> Motos Zonda <<< \n\n");
	if (Quant == -1)
		printf("Não há serviços cadastrados.");
	else{
		int Cont;
		for (Cont=0; Cont<=Quant; Cont++){
			if(VZonda[Cont].Status == '0'){
				printf("\n Cliente %d: %s", Cont+1, VZonda[Cont].Nome);
				printf("\n Modelo: %s", VZonda[Cont].Modelo);
				printf("\n Placa: %s", VZonda[Cont].Placa);
				printf("\n Defeito: %s", VZonda[Cont].Defeito);
				printf("\n Status: %c",VZonda[Cont].Status);
			    if (VZonda[Cont].Preco==0)
			      printf("\n Preco: NAO DEFINIDO");
			    else
			      printf("\n Preco: %.2f",VZonda[Cont].Preco);
			    printf("\n --------------------- \n\n");
			}
		}
	}
}

void ConcluirServico(){
	system("cls"); //limpa tela no ReplIt
	char P[7];
    float precoFinal;
    //EXIBIR A QUANTIDADE E OS SERVIÇOES INICIADOS
    int c, cont = 0;
	for (c = 0; c <= Quant; c++)
		if (VZonda[c].Status == '1')
			cont++;
	printf("%d serviços iniciados!", cont);
    int j;
    for (j = 0; j <= Quant; j++) {
        if (VZonda[j].Status == '1') {
        	printf("\n");
            printf("\n Cliente: %s", VZonda[j].Nome);
			printf("\n Modelo: %s", VZonda[j].Modelo);
			printf("\n Placa: %s", VZonda[j].Placa);
			printf("\n Defeito: %s", VZonda[j].Defeito);
			printf("\n Status: %c",VZonda[j].Status);
        }
    }
    printf("\nPlaca da moto para concluir serviço: ");
    scanf(" %[^\n]s", P);
    int Pos = -1;
	int i;
    for (i = 0; i <= Quant; i++) {
        if (strcmp(VZonda[i].Placa, P) == 0) {
            Pos = i;
            break;
        }
    }
    if (Pos != -1) {
    	if(VZonda[Pos].Status == '1'){
	        printf("Digite o preço final do serviço: ");
	        scanf("%f", &precoFinal);
	        VZonda[Pos].Preco = precoFinal;
	        VZonda[Pos].Status = '3';
	        total += precoFinal;
	        printf("Serviço concluído com sucesso!\n");
    	} else
    		printf("O servico ainda nao foi iniciado!");
    } else
        printf("Moto não encontrada!\n");
}

void TotalArrecadado(){
	Historico = fopen("historico.dat", "a+b");

	printf("Digite a data atual: ");
	scanf(" %[^\n]s", Dados.Data);
	Dados.Valor = total;

	fseek(Servicos, 0, 2);
	fwrite(&Dados, TamanhoHist, 1, Historico);

	fclose(Historico);
}

void EncerrarExpediente(){
    Servicos = fopen("servicos.dat", "w+b");
	system("cls"); //limpa tela no ReplIt

	printf("\n\n >>> Serviços Realizados <<< \n\n");

    if (Quant == -1) {
        printf("Não há serviços realizados hoje.\n");
    } else {
        int i;
        int todosConcluidos = 1;
        for (i = 0; i <= Quant; i++) {
            if (VZonda[i].Status != '3') {
                todosConcluidos = 0;
                break;
            }
        }
        if (todosConcluidos ){
            for (i = 0; i <= Quant; i++) {
                printf("\n Cliente %d: %s", i + 1, VZonda[i].Nome);
                printf("\n Placa: %s", VZonda[i].Placa);
                printf("\n Preco: %.2f", VZonda[i].Preco);
                printf("\n Status: %c\n",VZonda[i].Status);
            }
            TotalArrecadado();
        } else {
            printf("Ainda existem serviços pendentes.\n");

            // Perguntar se deseja encerrar o expediente com serviços pendentes
            char resposta;
            printf("\nDeseja encerrar o expediente mesmo com serviços pendentes? (S/N): ");
            scanf(" %c", &resposta);
            if (toupper(resposta) == 'S') {
                printf("Expediente encerrado.\n");

                for (i = 0; i <= Quant; i++) {
                printf("\n Cliente %d: %s", i + 1, VZonda[i].Nome);
                printf("\n Placa: %s", VZonda[i].Placa);
                printf("\n Preco: %.2f", VZonda[i].Preco);
                printf("\n Status: %c\n",VZonda[i].Status);
            	}
                TotalArrecadado();

                //Guardar dados em arquivo auxiliar
                fseek(Servicos, 0, 2);
                for (i = 0; i <= Quant; i++) {
		            if (VZonda[i].Status != '3'){
		                fwrite(&VZonda[i], TamanhoServ, 1, Servicos);
		            }
                }
            } else{
                printf("Continuando expediente...\n");
            }
        }
    }
	fclose(Servicos);
}

void HistoricoFinanceiro(){
	system("cls");
	Historico = fopen("historico.dat", "a+b");
	float valorComparacao = 0;
	char melhorData[15];

	printf("\n\n >>> Histórico Financeiro <<< \n\n");

	while (fread(&Dados, TamanhoHist, 1, Historico) == 1) {
		printf("Data: %s\n", Dados.Data);
		printf("Valor: R$%.2f\n", Dados.Valor);
		printf("----------------------------------\n\n");
		if(Dados.Valor > valorComparacao){
			valorComparacao = Dados.Valor;
			strcpy(melhorData, Dados.Data);
		}
	}
	printf("Houve maior venda no dia %s", melhorData);

	fclose(Historico);
}


int main(){
  setlocale(LC_ALL, "Portuguese");

  Servicos = fopen("servicos.dat", "a+b");
  Historico = fopen("historico.dat", "a+b");

  //inicializar o array de registro com os dados guardados no arquivo auxiliar
  int cont = 0;
  while(!feof(Servicos)){
  	fread(&VZonda[cont], TamanhoServ, 1, Servicos);
  	cont ++;
  };
  Quant = cont-2;

  int Opcao;
  system("cls");
  do{
    //Exibicao de menu e leitura da opcao.
	printf("\n\n >>> Motos Zonda <<< \n\n");
	printf("1 - Solicitar Servico \n");
	printf("2 - Iniciar Servico \n");
	printf("3 - Remover Solicitação \n");
	printf("4 - Consultar Solicitacoes \n");
	printf("5 - Concluir Servico \n");
	printf("6 - Encerrar Expediente \n");
	printf("7 - Histórico Financeiro \n");
	printf("8 - Sair \n\n");
	printf("Digite a opcao desejada: ");
	scanf("%d",&Opcao);
    switch (Opcao){
	    case 1: SolicitaServico(); break;
		case 2: IniciaServico(); break;
		case 3: RemoverSolicitacao(); break;
		case 4: ConsultarSolicitacoes(); break;
		case 5: ConcluirServico(); break;
		case 6: EncerrarExpediente(); break;
		case 7: HistoricoFinanceiro(); break;
		case 8: break;}
	}
	while (Opcao!=8);
  fclose(Servicos);
  fclose(Historico);
  return 0;
}
