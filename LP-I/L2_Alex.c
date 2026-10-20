// Alex Araujo Braca RA: 0030482521020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Registro {
    Data data;          // composição 
    float temperatura;  // temperatura do dia
} Registro;

// Funções prototipos
//[1] Cadastrar registros
int lerQuantidade(); //retorna quantidade valida de dias
int validarData(Data d); // retorna 1(valida) ou 0(invalida)
int lerRegistros(Registro *v, int quantidade); //preenche o vetor 
Data receber_data(); // recebe uma data do usuario e retorna a struct Data preenchida

//[2] Mostrar estatisticas
int indiceMaiorTemperatura(Registro *v); // retorna posição do maior valor
float calcularMedia(Registro *v, int quantidade); //retorna media
float calcularVariancia(Registro *v, int quantidade); // recebe media e calcula variância
float calcularDesvioPadrao(Registro *v, int quantidade); //calcula raiz da variância
int calcularModa(Registro *v, int quantidade); // retorna valor mais frequente (no caso de empate, considere o maior value)    

//[3] Listar abaixo da media
int abaixoMedia(Registro *v, int quantidade, int *indices); //preenche vetor de indices e quantidade 
int mostrarAbaixoMedia(Registro *v, int quantidade, int *indices); //exibe valores com data

//[4] Mostrar dias da semana
int calcularDiaSemana(int dia, int mes, int ano); // retorna número (0 a 6)
char* nomeDiaSemana(int dia); // converte número em string


int main() {
    struct Registro registros[31];
    int qnt_registros=0, menu, indicesAbaixoMedia[31];
    Registro *v;
    // cadastrar registros
    Data data_inicial; 

    v = &registros[0];

    do {
    printf("\nSistema de Monitoramento de Clima e Estatisticas\n");
    printf("[1] Cadastrar registros\n");
    printf("[2] Mostrar estatisticas\n");
    printf("[3] Listar abaixo da media\n");
    printf("[4] Mostrar dias da semana\n");
    printf("[5] Sair\n");
    scanf("%d", &menu);
    

    switch (menu){
    case 1: //[1] Cadastrar registros

        printf("Cadastrar registros\n");
        qnt_registros = lerQuantidade(); //le a quantidade de registros a ser cadastrada
        lerRegistros(registros, qnt_registros); //preenche o vetor

        
    break;

    case 2: //[2] Mostrar estatisticas
        if (qnt_registros == 0) {
            printf("Nenhum registro cadastrado.\n");
            break;
        }
        
        float moda;
        int indiceMaior;
        indiceMaior = indiceMaiorTemperatura(v);
        
        printf("\nEstatisticas\n");

        printf("Maior temperatura: %.2f\n", v[indiceMaior].temperatura);
        printf("Media: %.2f\n", calcularMedia(v, qnt_registros));
        printf("Variancia: %.2f\n", calcularVariancia(v, qnt_registros));
        printf("Desvio Padrao: %.2f\n", calcularDesvioPadrao(v, qnt_registros));
        moda = calcularModa(v, qnt_registros);
        if (moda == -51) {
            printf("Moda: Nao existe moda\n");
        }
        else {
            printf("Moda: %.2f\n", moda);
        }

        
    break;

    case 3: //[3] Listar abaixo da media
    if (qnt_registros == 0) {
            printf("\nNenhum registro cadastrado.\n");
            break;
        }
    
    printf("\nTemperaturas abaixo da media\n");
    int quantidadeAbaixoMedia = abaixoMedia(v, qnt_registros, indicesAbaixoMedia); //preenche vetor de indices e quantidade
    if (quantidadeAbaixoMedia == 0) {
        printf("Nenhuma temperatura abaixo da media.\n");
        break;
    }
    mostrarAbaixoMedia(v, quantidadeAbaixoMedia, indicesAbaixoMedia); //exibe valores com data  
        
    break;

    case 4: //[4] Mostrar dias da semana
    if (qnt_registros == 0) {
            printf("\nNenhum registro cadastrado.\n");
            break;
        }

    printf("\nMostrar dias da semana de cada registro\n");

    for (int i = 0; i < qnt_registros; i++) {
        
        printf("Dia: %d/%d/%d - Dia da semana: %s\n", v[i].data.dia, v[i].data.mes, v[i].data.ano,
             nomeDiaSemana(calcularDiaSemana(v[i].data.dia, v[i].data.mes, v[i].data.ano)));
    }

        
    break;

    case 5: // [5] Sair
    
        printf("\nEncerrando...\n");

    break;

    };
    } while (menu > 0 && menu < 5);

return 0;        
}

// Funções
//[1] Cadastrar registros
int lerQuantidade(){ //retorna quantidade valida de dias
    int qnt_registros;
    
    printf("Digite a quantidade de registros (1-31): ");
    scanf("%d", &qnt_registros);
    if (qnt_registros < 1 || qnt_registros > 31) {
        printf("Quantidade invalida. Digite um valor entre 1 e 31.\n");
        return lerQuantidade(); // Chama a função novamente para obter uma quantidade valida
    }
            
return qnt_registros;
}

Data receber_data(){
    Data data_recebida = {0, 0, 0};    

    printf("\nDia: ");
    scanf("%d", &data_recebida.dia);
    printf("mes: ");
    scanf("%d", &data_recebida.mes);
    printf("Ano: ");
    scanf("%d", &data_recebida.ano);

    return data_recebida;
    };

int validarData(Data d){ // retorna 1(valida) ou 0(invalida)
    if (d.mes < 1 || d.mes > 12 || d.dia < 1 || d.dia > 31 || d.ano < 1) {
        return 0; // Data invalida
    }
    else if ((d.mes == 4 || d.mes == 6 || d.mes == 9 || d.mes == 11) && d.dia > 30) {
        return 0; // Data invalida para meses com 30 dias
    }
    else if (d.mes == 2) {
        int bissexto = (d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0);
        if ((bissexto && d.dia > 29) || (!bissexto && d.dia > 28)) {
            return 0; // Data invalida para fevereiro
        }
    }

    return 1; // Data valida
} 

int lerRegistros(Registro *v, int quantidade){ //preenche o vetor
    Data data_inicial;

    for (int i = 0; i < 31; i++) { // limpa o vetor de registros
        v[i].data.dia = 0; 
        v[i].data.mes = 0;
        v[i].data.ano = 0;
        v[i].temperatura = 0.0;
    }

    do {
        printf("Digite a data inicial dos registros(dd/mm/aaaa): \n");
        data_inicial = receber_data(); //pede a data inicial dos registros
    } while (!validarData(data_inicial)); // verifica se a data e valida
    v[0].data = data_inicial; // preenche a data do primeiro registro com a data inicial


    for (int i = 0; i < quantidade; i++) { 

        // preenche o vetor com as temperaturas
        printf("Digite o registro do dia %d/%d/%d: ", v[i].data.dia, v[i].data.mes, v[i].data.ano);
        scanf("%f", &v[i].temperatura); 
        if (v[i].temperatura < -50 || v[i].temperatura > 60) {
            printf("Temperatura invalida. Digite um valor entre -50 e 60.\n");
            i--; // Decrementa o indice para repetir a leitura do mesmo dia
        }

        // Preenche a data do próximo registro com a data do registro anterior + 1 dia
        if (i < quantidade - 1) { // Verifica se ainda ha registros para preencher  
            v[i + 1].data.dia = v[i].data.dia + 1;
            v[i + 1].data.mes = v[i].data.mes;
            v[i + 1].data.ano = v[i].data.ano;
            // Verifica se a data e valida, caso contrario, ajusta para o próximo mês ou ano
            if (!validarData(v[i + 1].data)) {
                v[i + 1].data.dia = 1; // Reinicia o dia para 1
                v[i + 1].data.mes += 1; // Incrementa o mês
                if (v[i + 1].data.mes > 12) { // Verifica se o mês ultrapassa dezembro
                    v[i + 1].data.mes = 1; // Reinicia o mês para janeiro
                    v[i + 1].data.ano += 1; // Incrementa o ano
                }
            }
        }
    }

    return 0;
}  

//[2] Mostrar estatisticas

int indiceMaiorTemperatura(Registro *v){ // retorna posição do maior valor
    int indiceMaior = 0;
        for (int i = 1; i < 31; i++) {
            if (v[i].temperatura > v[indiceMaior].temperatura) {
                indiceMaior = i;
            }
        }

    return indiceMaior;
} 

float calcularMedia(Registro *v, int quantidade){ //retorna media das temperaturas
    float media = 0;

    for (int i = 0; i < quantidade; i++) {
        media += v[i].temperatura;
    }
    media /= quantidade;

    return media;
} 

float calcularVariancia(Registro *v, int quantidade){ //calcula variância
    float variancia = 0, media;

    media = calcularMedia(v, quantidade); //calcula media
    for (int i = 0; i < quantidade; i++) {
        variancia += (v[i].temperatura - media) * (v[i].temperatura - media);// x - m elevado ao quadrado
    }
    variancia /= quantidade;

    return variancia;
}

float calcularDesvioPadrao(Registro *v, int quantidade){  //calcula raiz da variância
    float desvioPadrao = sqrt(calcularVariancia(v, quantidade));

    return desvioPadrao;
} 

int calcularModa(Registro *v, int quantidade){ //retorna valor mais frequente (no caso de empate, considera o maior valor)
    int moda = 0, aux = 0, maior = 0;

    for (int i = 0; i < quantidade; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if ((int)v[i].temperatura == (int)v[j].temperatura) {
                aux++;
            }
        }
        if (aux > moda) {
            moda = aux;
            maior = (int)v[i].temperatura;
        }
        else if (aux == moda && (int)v[i].temperatura > maior) {
            maior = (int)v[i].temperatura;
        }
        aux = 0;
    }
    if (moda == 0) {
        return -51; // Indica que não ha moda
    }
    return maior;
}

//[3] Listar abaixo da media
int abaixoMedia( Registro *v, int quantidade, int *indices){ //preenche vetor de indices e quantidade
    float media = calcularMedia(v, quantidade);
    int quantidadeAbaixoMedia = 0;

    for (int i = 0; i < 31; i++) { // limpa o vetor de indices
        indices[i] = -1;
    }

    for (int i = 0; i < quantidade; i++) {
        if (v[i].temperatura < media) {
            indices[quantidadeAbaixoMedia] = i;
            quantidadeAbaixoMedia++;
        }
    }

    return quantidadeAbaixoMedia;
}

int mostrarAbaixoMedia(Registro *v, int quantidade, int *indices){ //exibe valores com data
    for (int i = 0; i < quantidade; i++) {
        if (indices[i] != -1) {
            printf("Dia: %d/%d/%d - Temperatura: %.2f\n", v[indices[i]].data.dia, v[indices[i]].data.mes, v[indices[i]].data.ano, v[indices[i]].temperatura);
        }
    }
    return 0;
}

//[4] Mostrar dias da semana
int calcularDiaSemana(int dia, int mes, int ano){ // retorna número (0 a 6)
    int D, M, A, S, dia_da_Semana;

    D = dia;
    M = mes -2; //março é o mês 1, fevereiro é o mês 12 do ano anterior
    if (M <= 0) {
        M += 12;
        ano -= 1;
    }
    A = ano % 100;
    S = ano / 100;

    dia_da_Semana = ((int)(2.6 * M - 0.1) + D + A + (A / 4) + (S / 4) - 2 * S)%7;

    return dia_da_Semana;
}

char* nomeDiaSemana(int dia){ // converte número em string
    char* diasSemana[] = {"Domingo", "Segunda-feira", "Terca-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado"};
    
    return diasSemana[dia];
}






