// TrabArvoreSequencial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define TAM 10000

typedef struct TipoNodo {
	 int ind;
     int numero;
	 int fb;
     TipoNodo *esquerda, *direita;   
}TNodo;

//==============================================================================
	// DADOS
int indInseri = 0;
int contNoFolha = 0;

//==============================================================================
//==============================================================================

void inicializaVetor(TNodo **vet){
	for(int i = 0; i < (TAM/4); i++){
		// Posição filho a Direita
		((*vet)[i]).direita = &(*vet)[((2*i)+2)];
		((*vet)[i]).direita->ind = ((2*i)+1);
		((*vet)[i]).direita->numero = -1;
		((*vet)[i]).direita->fb = 0;

		//// Posição filho a Esquerda
		((*vet)[i]).esquerda = &(*vet)[((2*i)+1)];
		((*vet)[i]).esquerda->ind = ((2*i)+2);
		((*vet)[i]).esquerda->numero = -1;
		((*vet)[i]).esquerda->fb = 0;

		((*vet)[i]).numero = -1;
		((*vet)[i]).fb = 0;
		(*vet)[i].ind = i;
		printf("Vetor indice %d = %d \n",i, (*vet)[i] );
	}
	system("cls");// LIMPA TELA
}
//==============================================================================
	//ARVORE
void insereNodo(TNodo **r, int numero){
   (*r)->numero = numero;
   (*r)->fb = 0;
   //Obs, os indices de direita e esquerda foram definidos na inicialização do vetor.
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

	if ((*r)->numero == -1)   {  
          insereNodo(&(*r),valor); 
          *status = true;
    }else  
		if (valor == (*r)->numero){ 
             printf ("ELEMENTO JA FOI INSERIDO!!! %d \n", valor); 
             //system ("PAUSE");
          }
          else
			  if (valor < (*r)->numero){ 
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
                        } //switch
                  }//if
               } //if
               else { 
				   adicionaNo(&(*r)->direita, valor, &(*status)); 
                    if (*status == true){ 
						switch ((*r)->fb)    {   
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


void gotoxy(int coluna, int linha) { 
        COORD point; 
        point.X = coluna; point.Y = linha; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}

void exibe(TNodo *r, int linha, int coluna, int variacao){
	if (r->numero != -1){
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
int altura(TNodo **n){
	if(((*n)->numero == -1))
       return 0;
   else
       return 1 + maior(altura(&(*n)->esquerda), altura(&(*n)->direita));
}

//Calculo do Nível de Um Nó
int busca(TNodo *r, int k, int nivel) {
	if (r->numero == -1|| r->numero == k)
       return nivel;
    if (r->numero > k)
		return busca( r->esquerda, k, (nivel+1)	);
    else
		return busca( r->direita, k, (nivel+1)	);
}

/*
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
*/

// Verifica Se Arvore esta Perfeitamente Balanceada
void qtdNo(TNodo *r, int *qtd) {
	if (r != NULL){
		(*qtd)++;
		if(r->direita->numero != -1){
			qtdNo(&(*r->direita),&(*qtd));
		}
		if(r->esquerda->numero != -1){
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
	if(((*r)->numero!= -1)){
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
	if(r->numero != -1){
        printf("\t %d - ", r->numero);
		exibirPreOrdem(r->esquerda);
		exibirPreOrdem(r->direita);
     }
}

void exibirEmOrdem(TNodo *r){
	if(r->numero != -1){
		exibirEmOrdem(r->esquerda);
		printf("\t %d - ", r->numero);
		exibirEmOrdem(r->direita);
    }
}

void exibirPosOrdem(TNodo *r){
	if(r->numero != -1){
		exibirPosOrdem(r->esquerda);
		exibirPosOrdem(r->direita);
		printf("\t %d - ", r->numero);
    }
}

void exibirDecrescente(TNodo *r){    
	if(r->numero != -1){
		exibirDecrescente(r->direita);
		printf("\t %d - ", r->numero);
		exibirDecrescente(r->esquerda);
    }
}

//==============================================================================
	//FUNÇÕES DE APRESENTAÇÃO E CONTROLE DO PROGRAMA
int menu(TNodo **vetArvore){
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
        printf(" 0 - Sair\n\n");
        printf("=========================\n");
        scanf("%d",&opcao);
        printf("\n");
        
        switch (opcao){
               case 1:
                    do{
				       num = 0;
		               system("cls");// LIMPA TELA
                       printf("\nInforme o Numero:");
					   scanf("%d",&num);
                       indInseri++;
                       printf("\nInserir outro Numero? s/n");
                       fflush(stdin);scanf("%c",&repete);
                       printf("\n\n");
					   adicionaNo(&(vetArvore[0]), num, &status);
                    }while((repete == 's')||(repete == 'S'));
					break;
               case 2:
					system("cls");// LIMPA TELA
					printf("\nA Altura da Arvore é: %d \n\n", (altura(&(vetArvore[0]))-1));
                    break;
               case 3:
				    num = 0;
                    system("cls");// LIMPA TELA
					printf("---------- Calcula Nivel de Determinado NO ----------\n\n");
					printf("Informe o valor do no: ");
					scanf("%d",&num);
					printf("\nA Nivel da Arvore eh: %d \n\n", busca((vetArvore[0]),num,0));
					break;
               case 4:
				    verificaArvorePerfBalanceada(&(vetArvore[0]));
                    break;
               case 5:
				    status = true;
                    status = verificaArvoreEstritBinaria(&(vetArvore[0]), &status);
					if(status == true){
						printf("\n\n Arvore Estritamente Binaria! \n\n");
					}else{
						printf("\n\n Arvore Nao eh Estritamente Binaria! \n\n");
					}
                    break;
			   case 6:
                    //Imprimir os elementos utilizando Pre-ordem
				    system("cls");// LIMPA TELA
					exibirPreOrdem((vetArvore[0]));
                    break;
			   case 7:
                    //Imprimir os elementos utilizando Em-ordem
					system("cls");// LIMPA TELA
				    exibirEmOrdem((vetArvore[0]));
                    break;
			   case 8:
				    //Imprimir os elementos utilizando Pos-ordem
					system("cls");// LIMPA TELA
				    exibirPosOrdem((vetArvore[0]));
                    break;
			   case 9:
                    exibirDecrescente((vetArvore[0]));
                    break;
			   case 10:
                    exibeNodo((vetArvore[0]));
					printf("\n\n");
					//system("pause");
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
	TNodo *vetArvore;
	int opcao = 0;
	vetArvore = (TNodo*) malloc(TAM *sizeof(TNodo));
    inicializaVetor(&vetArvore);
    do{
       system("cls");// LIMPA TELA
       opcao = menu(&vetArvore);
       printf("\n\n\n");       
    }while(opcao != 0);
	return 0;
}


