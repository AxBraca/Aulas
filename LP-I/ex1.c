// Exercicio 1
//Alex Araújo Braca RA: 0030482521020
//Arthur Pereira da Silva RA:  0030482521042

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){

    char frase[200], palavra[46] = "", palavraMaior[46] = "";
    int  c=0, j = 0,qntPalavras = 0, qntMaiusculas = 0, qntAO = 0;

    printf("Digite uma frase: ");
    fgets(frase,200,stdin);
   
// total de palavras
     for(int i = 0; i < strlen(frase); i++){
        if(frase[i]== ' ' || frase[i] == '\n'){
            qntPalavras++;
        }
// Palavras iniciadas com maiuscula
         if(isupper(frase[i]) ){
            if (i == 0 || frase[i-1] == ' '){
                qntMaiusculas++;   
            }
        }
    }
    printf("Total de palavras: %i\n", qntPalavras);
    printf("Palavras iniciadas com maiuscula: %i\n", qntMaiusculas);

// Maior palavra
    for (int i = 0; i < strlen(frase); i++){

        while(isalpha(frase[i]) && frase[i] != ' '){
            palavra[j] = frase[i];
            j++;
            i++;
        }
        j = 0;
        if (strlen(palavra) > strlen(palavraMaior)){
            strcpy(palavraMaior, palavra);    
        }
       
        while (palavra[c] != '\0' ) {   
                palavra[c] = '\0';
                c++;
            }
            c = 0;
    }
    printf("Maior palavra: %s\n", palavraMaior);

//Ocorrencia da palavra "AO"
    for (int i = 1; i < strlen(frase); i++){
        if (toupper(frase[i]) == 'O' && toupper(frase[i-1]) == 'A'){
             qntAO++; 
        }
    }
    printf("Ocorrencias da palavra 'AO': %i\n", qntAO);
}
