// TrabArvore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define TAM 10010

typedef struct TipoNodo {
     int numero;
	 int fb;
     TipoNodo *esquerda, *direita;   
}TNodo;

void adicionaNo(TNodo **pai, int valor, bool *status);
//==============================================================================
	// DADOS
int indInseri = 0;
TNodo *raiz;
int *vetNum;

//==============================================================================
	// Bubble Sort
int verificarMaior(int p, int p2){
    int i, maior = 0;
    if(p > p2)
        maior = p;
    else
        maior = p2;
 
    for(i = 0; i < maior;i++){
          if(p > p2)
              return 0;
          else if(p < p2) 
              return 1;
          else if((i+1) == maior && p == p2 )
              return 0;
          
    }
}

void swapbubble( int i ){
     int aux;
     aux = vetNum[i];
     vetNum[i] = vetNum[i+1];
     vetNum[i+1] = aux; 
}

void bubbleSort(int qtd){ // qtd é a quantidade de numeros inseridos no vetor 
     int i, p = 0 , p2 = 0;
     int trocou;
     do{
         qtd--;
         trocou = 0;
         for(i = 0; i < qtd; i++){
			 p = vetNum[i];
			 p2 = vetNum[i+1];
             if(verificarMaior(  p, p2  ) == 0){
                   swapbubble( i);
                   trocou = 1;     
             }
         }
     }while(trocou);    
}

void escreverVetor( int n){
	system("cls");// LIMPA TELA
    for(int i = 0; i < n;i++){
             printf("vet[%d] vale %d \n", i, vetNum[i]);        
    }     
}

//==============================================================================
	// VETORNUM
int inseriNum(int indInseri){
     printf("\nInforme o Numero:");
     scanf("%d",&vetNum[indInseri]);
	 return vetNum[indInseri];
}

void inicializaVetorNum(int **vetNum){
	for(int i = 0; i < TAM; i++){
		(*vetNum)[i] = 0;
		printf("Vetor indice %d = %d \n",i, (*vetNum)[i] );
	}
	system("cls");// LIMPA TELA
}

void exibeVetorNum(int **vetNum){

}
void insere1000NumNoVetor(int **vetNum){
	for(int i = 0; i < 10000; i++){
		(*vetNum)[i] = rand();
		printf("Vetor indice %d = %d \n",i, (*vetNum)[i] );
		indInseri++;
	}
	system("cls");// LIMPA TELA
}
void insereVetorNaArvore(int *vetNum, TNodo **raiz){
	bool status = false;
	for(int i = 0; i < 10000; i++){
		adicionaNo(&(*raiz), (vetNum)[i], &status);
	}
}

//==============================================================================
	//ARVORE
void inicializaArvore(TNodo **raiz){
     *raiz = NULL;     
}

void insereNodo(TNodo **r, int numero){
   TNodo *novo = (TNodo *)malloc(sizeof(TNodo));
   novo->numero = numero;
   novo->esquerda = NULL;
   novo->direita = NULL;
   novo->fb = 0;
   *r = novo;
}

void rotacaoDireita(TNodo **nodoA, bool *status){
     
     TNodo *nodoB, *nodoC; 
     
	 nodoB = (*nodoA)->esquerda; 
          
	 if (nodoB->fb == -1)   { // rotação simples                 
		 (*nodoA)->esquerda = nodoB->direita; 
		 nodoB->direita = (*nodoA); 
		 (*nodoA)->fb = 0; 
         (*nodoA) = nodoB;
		 //&(*raiz) = nodoB;
     } //if
     else {  // rotação dupla  
		 if((nodoB->direita != NULL)){
			 nodoC = nodoB->direita;
			 
			 nodoB->direita = nodoC->esquerda;
			 nodoC->esquerda = nodoB;
			 (*nodoA)->esquerda = nodoC;

			 (*nodoA)->esquerda = nodoC->direita;
			 nodoC->direita = (*nodoA);
			
			 if (nodoC->fb == -1){ 
				 (*nodoA)->fb = 1; 
			 }//if
			 else (*nodoA)->fb = 0; 
	                 
			 if (nodoC->fb == 1){ 
				 nodoB->fb = -1; 
			 }//if
			 else nodoB->fb = 0; 
	         
			 (*nodoA) = nodoC; 
		 }
     } //if else
     
	 (*nodoA)->fb = 0; 
     *status = false;
}
     
void rotacaoEsquerda(TNodo **nodoA, bool *status){
     
   TNodo * nodoB = NULL, * nodoC = NULL; 
   nodoC = (TNodo *)malloc(sizeof(TNodo)); 
   nodoB = (TNodo *)malloc(sizeof(TNodo)); 

   nodoB = (*nodoA)->direita; 
   
   if (nodoB->fb == 1)  { // rotação simples 
	   (*nodoA)->direita = nodoB->esquerda; 
	   nodoB->esquerda = (*nodoA); 
	   (*nodoA)->fb = 0; 
       (*nodoA) = nodoB; 
   } //if
   else { // rotação dupla 
	   if(nodoB->esquerda != NULL){
		   nodoC = nodoB->esquerda;
		   nodoB->esquerda = nodoC->direita;
		   (*nodoA)->direita = nodoC;
		   nodoC->direita = nodoB;

		   (*nodoA)->direita = nodoC->esquerda;
		   nodoC->esquerda = (*nodoA);
		   if (nodoC->fb == 1) {
				  (*nodoA)->fb = -1; 
		   }//if
		   else (*nodoA)->fb = 0; 
		      
		   if (nodoC->fb == -1){ 
		 	  nodoB->fb = 1; 
		   }//if
		   else nodoB->fb = 0; 
		      
		   (*nodoA) = nodoC; 
	    }
   }//if else
    
   (*nodoA)->fb = 0; 
   *status = false; 
}


void adicionaNo(TNodo **r, int valor, bool *status){
    if((*r) == NULL)   {  
          insereNodo(&(*r),valor); 
          *status = true;
	}else{  
		if(valor == (*r)->numero){ 
             printf ("ELEMENTO JA FOI INSERIDO!!! %d \n", valor); 
		}else{
			if(valor < (*r)->numero){ 
				adicionaNo(&(*r)->esquerda, valor, &(*status)); 
                if (*status == true){ 
					switch ((*r)->fb){
						case 1 : 
							  (*r)->fb = 0; 
							  status = false; 
							  break; 
						case 0 : 
							  (*r)->fb = -1; 
							  break; 
                        case -1 : 
							  rotacaoDireita(&(*r), &(*status)); 
							  break;
					}
                }
			}else{ 
				adicionaNo(&(*r)->direita, valor, &(*status)); 
                if (*status == true){ 
					switch ((*r)->fb){   
						case -1 : 
							(*r)->fb = 0; 
							status = false; 
							break; 
						case 0 : 
							(*r)->fb = 1; 
							break; 
                        case 1 : 
							rotacaoEsquerda(&(*r), &(*status)); 
							break;     
					}
				}
            }
		}
	}
}


void gotoxy(int coluna, int linha) { 
        COORD point; 
        point.X = coluna; point.Y = linha; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}

void exibe(TNodo *r, int linha, int coluna, int variacao){
     if (r != NULL){
       if ((linha < 25) && (coluna <= 80) && (coluna > 0)){    
           gotoxy(coluna,linha);
		   printf("<%d>",r->numero);
           variacao = variacao /2;
           exibe(r->esquerda,linha+2,coluna-variacao, variacao);
           exibe(r->direita, linha+2,coluna+variacao, variacao);      
        }
     }    
}

void exibeNodo(TNodo *r){
     system("CLS");
     printf("\t\t\t====| Arvore Binaria |====");
     exibe(r,2,40,40);     
}

//Calculo da Altura de Um Nó
int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}
int altura(TNodo *n){
   if((n == NULL))
       return 0;
   else
       return 1 + maior(altura(n->esquerda), altura(n->direita));
}

//Calculo do Nível de Um Nó
int busca(TNodo *r, int k, int nivel) {
	if (r == NULL || r->numero == k)
       return nivel;
    if (r->numero > k)
		return busca( r->esquerda, k, (nivel+1)	);
    else
		return busca( r->direita, k, (nivel+1)	);
}

//Verificação Balanceamento
int CalculoBalanceamento(int a, int b){
	return (b - a);
}

int fbNodo(TNodo *n){
	if((n == NULL)){
       return 0;
	}else{
		return CalculoBalanceamento(altura(n->esquerda), altura(n->direita));
	}
}

void atribuiFB(TNodo *n){
	int altEsq = 0;
	int altDir = 0;
	if((n != NULL)){
		altEsq = altura(n->esquerda);
		altDir = altura(n->direita);
		n->fb = fbNodo(n);
		printf("\n\n No: %d  --- FB: %d  --- altDir: %d  ---  altEsq: %d", n->numero, n->fb, altDir, altEsq);
		atribuiFB(n->esquerda);
		atribuiFB(n->direita);
	}
}
// Verifica Se Arvore esta Perfeitamente Balanceada
void qtdNo(TNodo *r, int *qtd) {
	if (r != NULL){
		(*qtd)++;
		if(r->direita != NULL){
			qtdNo(&(*r->direita),&(*qtd));
		}
		if(r->esquerda != NULL){
			qtdNo(&(*r->esquerda),&(*qtd));
		}
	}
}

void verificaArvorePerfBalanceada(TNodo **r){

	int qtdNoDireita = 0;
	int qtdNoEsquerda = 0;

	qtdNo((*r)->direita, &qtdNoDireita);
	qtdNo((*r)->esquerda, &qtdNoEsquerda);

	if((qtdNoDireita - qtdNoEsquerda == 1)||(qtdNoDireita - qtdNoEsquerda == -1)||(qtdNoDireita - qtdNoEsquerda == 0)){
		printf("Arvore Perfeitamente Balanceada");
	}else{
		printf("Arvore Nao Esta Perfeitamente Balanceada!");
	}
}
bool verificaArvoreEstritBinaria(TNodo **r, bool *status){
	if(((*r)!= NULL)){
		if(((!(*r)->direita)&&((*r)->esquerda)) || ((*r)->direita)&&(!(*r)->esquerda)){
			(*status) = false;
		}else{
			verificaArvoreEstritBinaria(&(*r)->direita, &(*status));
			verificaArvoreEstritBinaria(&(*r)->esquerda,&(*status));
		}
	}
	return *status;
}
//==============================================================================
	//Exibição Dos Nós da Arvore
void exibirPreOrdem(TNodo *r){
     if(r != NULL){
        printf("\t %d - ", r->numero);
		exibirPreOrdem(r->esquerda);
		exibirPreOrdem(r->direita);
     }
}

void exibirEmOrdem(TNodo *r){
    if(r != NULL){
		exibirEmOrdem(r->esquerda);
		printf("\t %d - ", r->numero);
		exibirEmOrdem(r->direita);
    }
}

void exibirPosOrdem(TNodo *r){
    if(r != NULL){
		exibirPosOrdem(r->esquerda);
		exibirPosOrdem(r->direita);
		printf("\t %d - ", r->numero);
    }
}

void exibirDecrescente(TNodo *r){    
    if(r != NULL){
		exibirDecrescente(r->direita);
		printf("\t %d - ", r->numero);
		exibirDecrescente(r->esquerda);
    }
}

//==============================================================================
	//FUNÇÕES DE APRESENTAÇÃO E CONTROLE DO PROGRAMA
int menu(TNodo **raiz){
    int opcao = 0, num = 0, fb = 0, auxpag = 0;
	bool status = false;
    char repete;
	clock_t endBubble = NULL,  startBubble = NULL;
	clock_t endEmOrdem = NULL, startEmOrdem = NULL;
	double respBubble = 0.0, respArvore = 0.0;
    
    do{
		system("cls");// LIMPA TELA
        printf("==========MENU==========\n");
        printf(" 1 - Add Novo No\n 2 - Calcular Altura\n 3 - Calcular Nivel de Determinado No\n");
		printf(" 4 - Verificar se a arvore esta perfeitamente balanceada\n");
		printf(" 5 - Verificar se a arvore eh estritamente binaria\n");
		printf(" 6 - Imprimir os elementos utilizando Pre-ordem\n");
		printf(" 7 - Imprimir os elementos utilizando Em-ordem\n");
		printf(" 8 - Imprimir os elementos utilizando Pos-ordem\n");
		printf(" 9 - Imprimir os elementos na ordem decrescente\n");
		printf("10 - Imprimir Arvore\n");
		printf("11 - Ordenar vetor com BubbleSort\n");
        printf(" 0 - Sair\n\n");
        printf("=========================\n");
        scanf("%d",&opcao);
        printf("\n");
        
        switch (opcao){
               case 1:
                    do{
					   num = 0;
					   system("cls");// LIMPA TELA
                       num = inseriNum(indInseri);
                       indInseri++;
                       printf("\nInserir outro Numero? s/n");
                       fflush(stdin);scanf("%c",&repete);
                       printf("\n\n");
					   
					   adicionaNo(&(*raiz), num, &status);
					   //atribuiFB((*raiz));
					   
                    }while((repete == 's')||(repete == 'S'));
                    break;
               case 2:
					system("cls");// LIMPA TELA
					printf("\nA Altura da Arvore é: %d \n\n", altura(*raiz)-1);
                    break;
               case 3:
				    num = 0;
                    system("cls");// LIMPA TELA
					printf("---------- Calcula Nivel de Determinado NO ----------\n\n");
					printf("Informe o valor do no: ");
					scanf("%d",&num);
					printf("\nA Nivel da Arvore é: %d \n\n", busca(*raiz,num,0));
					break;
               case 4:
				    verificaArvorePerfBalanceada(&(*raiz));
                    break;
               case 5:
				    status = true;
                    status = verificaArvoreEstritBinaria(&(*raiz), &status);
					if(status == true){
						printf("\n\n Arvore Estritamente Binaria! \n\n");
					}else{
						printf("\n\n Arvore Nao eh Estritamente Binaria! \n\n");
					}
                    break;

			   case 6:
                    //Imprimir os elementos utilizando Pre-ordem
				    system("cls");// LIMPA TELA
					exibirPreOrdem(*raiz);
                    break;
			   case 7:
                    //Imprimir os elementos utilizando Em-ordem
					system("cls");// LIMPA TELA
				    exibirEmOrdem(*raiz);
                    break;
			   case 8:
				    //Imprimir os elementos utilizando Pos-ordem
					system("cls");// LIMPA TELA
				    exibirPosOrdem(*raiz);
                    break;
			   case 9:
                    exibirDecrescente(*raiz);
                    break;
			   case 10:
                    exibeNodo((*raiz));
					printf("\n\n");
					//system("pause");
					system("cls");// LIMPA TELA
                    break;
				case 11:
					startEmOrdem = clock();
					exibirEmOrdem(*raiz);
					endEmOrdem = clock();
					respArvore = 1000*(double)(endEmOrdem-startEmOrdem)/(double)(CLOCKS_PER_SEC);
					
					system("cls");// LIMPA TELA
					printf("AGUARDE ... .. .\n");
					startBubble = clock();
                    bubbleSort(indInseri); // Ordena o Vetor
					endBubble = clock();
					respBubble = 1000*(double)(endBubble-startBubble)/(double)(CLOCKS_PER_SEC);
					
					system("cls");// LIMPA TELA
					printf("Tempo gasto para exibir arvore em ordem Crescente: %4.2f min \n\n", (respArvore/60000));
					printf("Tempo gasto para ordenar com BubbleSort: %4.2f min\n\n", (respBubble/60000));
					//escreverVetor(indInseri);
					system("cls");// LIMPA TELA
                    break;
               default:
                       break;
        }
    }while((opcao<0)||(opcao >5));
    return opcao;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int opcao = 0;
	vetNum = (int*) malloc(TAM *sizeof(int));
	inicializaVetorNum(&vetNum);
	inicializaArvore(&raiz);
	insere1000NumNoVetor(&vetNum);
	insereVetorNaArvore(vetNum, &raiz);
    
    do{
	   system("cls");// LIMPA TELA
       opcao = menu(&raiz);
       printf("\n\n\n");       
    }while(opcao != 0);
    
//    exibeNodo(raiz);
//    system("PAUSE");
	return 0;
}
