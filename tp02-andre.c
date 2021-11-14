/* TRABALHO PRATICO 02 PROJETO E ANALISE DE ALGORITMOS */
/* UFSCAR - 2020/2 ENPE */
/* ALUNO: ANDRE SILVEIRA SOUSA RA: 628239 CURSO: ENGENHARIA DE COMPUTACAO */

#include <stdio.h>
#include <stdlib.h>

/* O problema da Black Friday pode ser entendido como um problema de agrupamento                */
/* onde eh necessario agrupar valores de um vetor em grupos de 3, sendo que                     */
/* neste grupo, o MENOR valor deve ser o mais caro (maior) possivel, para ter o maior desconto. */
/* Sendo assim, a logica pensada foi em ordenar o vetor em ordem decrescente                    */
/* e a cada terceira posicao (n=2, 5, 8 etc) eh o valor do item que saira de graca              */
/* A orenacao do vetor sera por algoritmo de Merge Sort */

/* ********************* */
/* Prototipos de Funcoes */
/* ********************* */
void mergesort_decrescente (long long int v[], int n);
void divisao (long long int v[], long long int temp[], int esq, int dir);
void conquista (long long int v[], long long int temp[], int esq , int quebra, int dir);

/* ***************************** */
/* Funcao mergesort_decrescente */
/* ***************************** */
/* entradas: um vetor "v" de valores inteiros e um numero inteiro "n" com a quantidade de itens do vetor */
/* saida: o vetor "v" odenado do maior para o menor */
/* ************************** */

void mergesort_decrescente (long long int v[], int n){
    
    /* vetor temporario usado para trocar a posicao dos valores */
    long long int* temp = (long long int*)malloc(sizeof(long long int) * n); 

    divisao(v, temp, 0, n-1);

    //return v;
}

/* ************** */
/* Funcao divisao */
/* ************** */
/* entradas: um vetor "v" de inteiros com os valores de entrada, um vetor "temp" de inteiros editavel */
/* um valor inteiro "esq" correspondente a posicao inicial do vetor a ser dividido */
/* um valor inteiro "dir" correspondente a posicao final do vetor a ser dividido */
/* saida: vetor v ordenado */
/* ************** */

void divisao (long long int v[], long long int temp[], int esq, int dir){
    
    int quebra;

    if(dir>esq){

        /* divide em 2 subvetores a partir da metade */
        quebra = (esq+dir)/2;

        /* divide o subvetor da esquerda ao menor possivel */
        divisao(v, temp, esq, quebra);

        /* divide o subvetor da direita ao menor possivel */
        divisao(v, temp, quebra+1, dir);

        /* caso base: vetor com 1 unidade, ordenado */
        /* vai para o conquistar: une 2 subvetores, ordenando-os */
        conquista(v, temp, esq, quebra+1, dir);
    }
//return v;
}

/* **************** */
/* Funcao conquista */
/* **************** */
/* entradas: um vetor "v" de inteiros com os valores de entrada, um vetor "temp" de inteiros editavel */
/* um valor inteiro "esq" correspondente a posicao do subvetor da esquerda */
/* um valor inteiro "quebra" correspondente a posicao do subvetor da direita*/
/* um valor inteiro "dir" correspondente a ultima posicao do subvetor da direita */
/* saida: vetor v ordenado */
/* **************** */

void conquista (long long int v[], long long int temp[], int esq, int quebra, int dir){
    
    /* definicao de indices moveis para os subvetores */
    /* v1 = vetor da esquerda */
    /* v2 = vetor da direita */
    /* posicao = posicao do MAIOR valor */
    int i_v1 = esq;
    int i_v2 = quebra;
    int i_posicao = esq;

    while(i_v1 <= quebra-1 && i_v2 <= dir){
        
        /* compara se o valor do subvetor da esquerda eh MAIOR que o subvetor da direita */
        /* caso positivo: passa para o proximo valor incrementando os indices */
        if(v[i_v1] > v[i_v2]){
            temp[i_posicao] = v[i_v1]; 
            i_posicao++;
            i_v1++;  
        } 

        /* se o valor do subvetor da esquerda eh MENOR OU IGUAL que o subvetor da direita, acontece a inversao */
        else{ /* so acontece quando todos da esquerda estao ordenados */
            temp[i_posicao] = v[i_v2];
            i_posicao++;
            i_v2++;
        }
    }

    /* copiando os valores para o retorno dos merges */
    /* quando a posicao esta correta (ja ordenado) */
    while(i_v1 <= quebra-1){
        temp[i_posicao] = v[i_v1];
        i_posicao++;
        i_v1++;
    }
    while(i_v2 <= dir){
        temp[i_posicao] = v[i_v2];
        i_posicao++;
        i_v2++;
    }

    /* copiando o vetor temp ordenado para o vetor original*/
    for(int i=esq; i <= dir; i++) v[i] = temp[i];

    //return v;
}



/* *********** */
/* Funcao MAIN */
/* *********** */

int main(){

    /* Ler arquivo de entrada com casos teste */
    FILE *entrada;
    char nomedoarquivo[10];
    scanf("%s",nomedoarquivo);
    entrada=fopen(nomedoarquivo, "r");

    /* variaveis de operacao */
    int posicao;
    long long int qtditens, somadesconto=0;

    /* ********* */
    /* operacoes */
    /* ********* */
    /* le o primeiro int da linha do arquivo (qtd de itens) */
    fscanf(entrada, "%lld\n", &qtditens);

    /* cria um vetor com os valores do arquivo */
    if(qtditens>2){

        long long int vetorentrada[qtditens];

        for(posicao=0; posicao<qtditens; posicao++){
            fscanf(entrada, "%lld", &vetorentrada[posicao]);
        }

        /* ordena decresente */
        mergesort_decrescente(vetorentrada, qtditens);

        /* cada teerceira posicao eh o desconto*/
        for(posicao=2; posicao<qtditens; posicao+=3){
            somadesconto += vetorentrada[posicao];
        }  

        printf("%lld", somadesconto);

        /* atualiza para a proxima linha */
        //fscanf(entrada, "%d", &qtditens);
    }

    fclose(entrada);
    return 0; // fim da funcao MAIN
}