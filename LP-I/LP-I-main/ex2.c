// Exercicio 2
//Alex Araújo Braca RA: 0030482521020
//Arthur Pereira da Silva RA:  0030482521042

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){

int n = 0, j;
char nome[30][20];
for (int i = 0; i < 30; i++){
    for (int k = 0; k < 20; k++){
        nome[i][k] = '\0';
    }
}

//Recebe o numero de nomes
printf("Digite o numero de nomes: \n");
scanf("%d", &n);
fflush(stdin);
if (n > 30){
    printf("Limite de nomes excedido. Tente novamente.\n");
    return 0;
}
    
//Recebe nomes max 30
int i=0;
printf("Digite os nomes: \n");
while (i <= n){
    fflush(stdin);
    gets(nome[i]);
    // nome[i][strlen(nome[i]) - 1] = '\0';
    fflush(stdin);
    i++;
}
//Estamos confiando que você não vai digitar a primeitra letra minuscula

//Imprime os nomes em ordem alfabetica

 j = n;
 while (j >= 0){
      for(int i = n; i >=0 ; i--){
       if (nome[i][0] < nome[i-1][0]){
         char aux[20];
         strcpy(aux, nome[i]);
         strcpy(nome[i], nome[i-1]);
         strcpy(nome[i-1], aux);
       }
       else if (nome[i][0] == nome[i-1][0]){
         if (nome[i][1] < nome[i-1][1]){
         char aux[20];
         strcpy(aux, nome[i]);
         strcpy(nome[i], nome[i-1]);
         strcpy(nome[i-1], aux);
         }
       }
     };
     j--;    
 }

printf("Ordenacao Alfabetica\n");
for (int i = 0; i <= n; i++){
    printf("%s\n",nome[i]);
}

// por tamanho 
j = n;
while (j >= 0){
    for(int i = n; i >=0 ; i--){
       if (strlen(nome[i]) < strlen(nome[i-1])){
         char aux[20];
         strcpy(aux, nome[i]);
         strcpy(nome[i], nome[i-1]);
         strcpy(nome[i-1], aux);
        }
    };
    j--;
}

printf("Ordenacao por tamanho\n");
for (int i = 0; i <= n; i++){
    printf("%s\n",nome[i]);
}
}

