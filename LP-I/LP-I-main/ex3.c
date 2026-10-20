// Exercicio 3
//Alex Araújo Braca RA: 0030482521020
//Arthur Pereira da Silva RA:  0030482521042

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Data{
    unsigned char dia;
    unsigned char mes;
    unsigned short int ano;
} Data;

typedef struct Reserva{
    int codigo;
    char cliente[51];
    char destino[31];
    Data dataViagem;
    char status; //P ou N
} Reserva;

typedef struct Resumo{
    char destino[31];
    int qnt;
} Resumo;

int main(){
    Reserva reserva[10];
    int menu,qntReservas = 0, i=0, anoFiltro, mesFiltro, totalUnicos = 0, encontrado = 0;
    Resumo resumo[10];

do {
printf("\n1 - Cadastrar Reservas\n");
printf("2 - Exibir Reservas\n");
printf("3 - Exibir apenas reservas pagas\n");
printf("4 - Filtro por data\n");
printf("5 - Resumo por destino\n");
printf("0 - Sair\n");
scanf("%d", &menu);
switch (menu)
{
    case 1:
        // Cadastro
        printf("Qual a quantidade de Reservas: ");
        scanf("%d", &qntReservas);

        for (int i = 0; i < qntReservas; i++) {
            printf("Codigo: ");
            scanf("%d", &reserva[i].codigo);
            while (getchar() != '\n'); 

            printf("Digite o Nome do Cliente: ");
            fgets(reserva[i].cliente, 51, stdin);
            // Remover o \n manualmente ;C
            for (int j = 0; j < 51; j++) {
                if (reserva[i].cliente[j] == '\n') {
                    reserva[i].cliente[j] = '\0';
                    break;
                }
            }

            printf("Digite o Destino do Cliente: ");
            fgets(reserva[i].destino, 31, stdin);
            //limpa
            for (int j = 0; j < 31; j++) {
                if (reserva[i].destino[j] == '\n') {
                    reserva[i].destino[j] = '\0';
                    break;
                }
            }

            printf("Digite a Data da Viagem (DD MM AAAA): ");
            scanf(" %hhu %hhu %hu", 
                &reserva[i].dataViagem.dia, 
                &reserva[i].dataViagem.mes, 
                &reserva[i].dataViagem.ano);
            while (getchar() != '\n'); 

            printf("Insira o Status da Reserva(P ou N): ");
            scanf(" %c", &reserva[i].status);
            while (getchar() != '\n'); 
        }
    break;

    case 2:
        // Exibição de Reservas
        printf("%-6s | %-20s | %-15s | %-10s | %s\n", "COD", "CLIENTE", "DESTINO", "DATA", "STATUS");
        for (int i=0; i < qntReservas; i++) {
            printf("%-6d | %-20.20s | %-15.15s | %02hhu/%02hhu/%-5u | %c\n", //-1.1s para regularizar os espaços
            reserva[i].codigo, 
            reserva[i].cliente, 
            reserva[i].destino, 
            reserva[i].dataViagem.dia, 
            reserva[i].dataViagem.mes, 
            reserva[i].dataViagem.ano,
            reserva[i].status);
        } 
    break;

    case 3:
        // Filtro: Reservas Pagas
        printf("Reservas Pagas:\n");
        for (int i=0; i < qntReservas; i++) {
            if (reserva[i].status == 'P') {
                printf("%-6d | %-20.20s | %-15.15s | %02hhu/%02hhu/%-5u\n",
                reserva[i].codigo,
                reserva[i].cliente,
                reserva[i].destino,
                reserva[i].dataViagem.dia,
                reserva[i].dataViagem.mes,
                reserva[i].dataViagem.ano);
            }
        }
    break;

    case 4:
    // Filtro: Por Data
        printf("Digite a Data da Viagem (MM AAAA): ");
            scanf(" %i %i",  
                &mesFiltro, 
                &anoFiltro);

        printf("Reservas para a data %2i/%2i:\n", mesFiltro, anoFiltro);

        for (int i=0; i < qntReservas; i++) {
            if (reserva[i].dataViagem.mes == mesFiltro && reserva[i].dataViagem.ano == anoFiltro){
                printf("%-6d | %-20.20s | %-15.15s | %c\n",
                reserva[i].codigo,
                reserva[i].cliente,
                reserva[i].destino,
                reserva[i].status);
            }
        }
        break;

    case 5:
        // Resumo por Destino
        for (int i = 0; i < qntReservas; i++) {
            encontrado = 0;

            for (int j = 0; j < totalUnicos; j++) {
                if (strcmp(reserva[i].destino, resumo[j].destino) == 0) {
                    resumo[j].qnt++;
                    encontrado = 1; 
                    break;
                }
            }

            if (!encontrado) {
                strcpy(resumo[totalUnicos].destino, reserva[i].destino);
                resumo[totalUnicos].qnt = 1;
                totalUnicos++; 
            }
        }

        printf("Destino | Quantidade\n");

        for (int i=0; i < totalUnicos; i++) {
            printf("%s: %d\n",
            resumo[i].destino,
            resumo[i].qnt);
        }
    break;
   }
  }while (menu !=0);
}

