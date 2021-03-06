/***************************************************************************
*   $MCI Módulo de implementação: Módulo Matriz
*
*   Arquivo gerado:              MATRIZ.h
*   Letras identificadoras:      MAT
*
*   Projeto: Disciplina INF1301
*   Departamento: DI/PUC-Rio
*   Autores: avc - Antônio Chaves
*            jpp - João Pedro Paiva
			 pc	 - Pedro Costa
*
*   $HA Histórico de evolução:
*       Versão  Autor   Data        Observações
*       1.00    avc     25/08/2019  Início do desenvolvimento (protótipos de 
*                                   funções)
*       2.00    jpp     29/08/2019  Continuação do desenvolvimento (tpNoMatriz, 
*                                   tpMatriz, MAT_cria e MAT_criaNo)
*       3.00    jpp     03/09/2019  Continuação do desenvolvimento 
*                                   (MAT_vaiPara e MAT_destroi)
*       4.00    jpp     04/09/2019  Uniformização da interface das funções e
*                                   das condições de retorno, comentários no
*                                   código
*		5.00	pc		07/09/2019	Correção de erros e adptação à mudanças no módulo de definição.
*       6.00    pc      08/09/2019  Correção da destrução
*       7.00    jpp     22/09/2019  AE e AS
*       8.00    jpp     24/09/2019  Matriz_cria nova
*		8.01	pc		06/10/2019	Correção de erros
*
***************************************************************************/

#include "MATRIZ.h"
#include <stdlib.h>

/***********************************************************************
*
*   $TC Tipo de dados:
*       MAT Descritor do nó da matriz.
*
*
*   $ED Descrição do tipo:
*       Descreve a organização do nó.
*
***********************************************************************/

typedef struct tgNoMatriz
{

	struct tgNoMatriz* pNoCima;
	/* Ponteiro para nó de cima
		*
		*$EED Assertivas estruturais
		*    */

	struct tgNoMatriz* pNoEsquerda;
	/* Ponteiro para nó da esquerda
			   *
			   *$EED Assertivas estruturais
			   *    */

	void* Elemento;
	/* Elemento contido no nó */

	struct tgNoMatriz* pNoDireita;
	/* Ponteiro para nó da direita
			   *
			   *$EED Assertivas estruturais
			   *    */

	struct tgNoMatriz* pNoBaixo;
	/* Ponteiro para nó de baixo
			   *
			   *$EED Assertivas estruturais
			   *    */

} tpNoMatriz;


/***********************************************************************
*
*   $TC Tipo de dados:
*       ARV Descritor da cabeça de uma matriz.
*
*
*   $ED Descrição do tipo:
*       A cabeça da matriz é o ponto de acesso para uma determinada
*       matriz.
*       Por intermédio da referência para o nó corrente e dos
*       ponteiros
*       adjascentes pode-se navegar a matriz sem necessitar de uma
*       pilha.
*
***********************************************************************/

typedef struct tgMatriz
{

    tpNoMatriz *pNoPrimeiro;
    /* Ponteiro para a o primeiro nó da matriz, escolhido arbitrariamente */

    tpNoMatriz *pNoCorr;
    /* Ponteiro para o nó corrente da matriz */

    void (*destruirElemento)(void *elemento);
    /* Ponteiro para a função de destrução de um elemento */
    
} tpMatriz;

/***** Protótipos das funções encapsuladas no módulo *****/

   static tpNoMatriz *MAT_criaNo(void);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************
*
*	$FC Função: MAT Criar um nó da matriz
*
****************************************************/
tpNoMatriz *MAT_criaNo(void)
{
    tpNoMatriz *NoMatrizCriado;

    NoMatrizCriado = (tpNoMatriz*) malloc(sizeof(tpNoMatriz));

    if (NoMatrizCriado == NULL)
        return NULL;

    NoMatrizCriado->Elemento = NULL;
    NoMatrizCriado->pNoBaixo = NULL;
    NoMatrizCriado->pNoCima = NULL;
    NoMatrizCriado->pNoDireita = NULL;
    NoMatrizCriado->pNoEsquerda = NULL;

    return NoMatrizCriado;
}

/*******************************************************
*
*	$FC Função: MAT Nó corrente da Matriz se torna o nó
*       Acima do nó corrente atual.
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoNaoExiste
*
********************************************************/
MAT_tpCondRet MAT_vaiParaCima(MAT_tppMatriz CabecaDaMatriz)
{
	if (CabecaDaMatriz->pNoCorr->pNoCima == NULL) /* Não existe nó nesta direção */
		return MAT_CondRetNoNaoExiste; /* Retorna condição de falha na movimentação do nó corrente */

	CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoCorr->pNoCima; /* Movimenta nó corrente na direção indicada */
	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */

}

/*******************************************************
*
*	$FC Função: MAT Nó corrente da Matriz se torna o nó
*       à Esquerda do nó corrente atual.
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoNaoExiste
*
********************************************************/
MAT_tpCondRet MAT_vaiParaEsquerda(MAT_tppMatriz CabecaDaMatriz)
{
	if (CabecaDaMatriz->pNoCorr->pNoEsquerda == NULL) /* Não existe nó nesta direção */
		return MAT_CondRetNoNaoExiste; /* Retorna condição de falha na movimentação do nó corrente */

	CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoCorr->pNoEsquerda; /* Movimenta nó corrente na direção indicada */
	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */

}

/*******************************************************
*
*	$FC Função: MAT Nó corrente da Matriz se torna o nó
*       à Direita do nó corrente atual.
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoNaoExiste
*
********************************************************/
MAT_tpCondRet MAT_vaiParaDireita(MAT_tppMatriz CabecaDaMatriz)
{
	if (CabecaDaMatriz->pNoCorr->pNoDireita == NULL) /* Não existe nó nesta direção */
		return MAT_CondRetNoNaoExiste; /* Retorna condição de falha na movimentação do nó corrente */

	CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoCorr->pNoDireita; /* Movimenta nó corrente na direção indicada */
	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */

}

/*******************************************************
*
*	$FC Função: MAT Nó corrente da Matriz se torna o nó
*       Abaixo do nó corrente atual.
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoNaoExiste
*
********************************************************/
MAT_tpCondRet MAT_vaiParaBaixo(MAT_tppMatriz CabecaDaMatriz)
{
	if (CabecaDaMatriz->pNoCorr->pNoBaixo == NULL) /* Não existe nó nesta direção */
		return MAT_CondRetNoNaoExiste; /* Retorna condição de falha na movimentação do nó corrente */

	CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoCorr->pNoBaixo; /* Movimenta nó corrente na direção indicada */
	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */

}

/*******************************************************
*
*	$FC Função:
*       MAT Coloca nó corrente na mesma posição do primeiro nó.
*
*
*	$AE Assertivas de entrada esperadas:
*		Cabeça da matriz != NULL.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
*
*	$AS Assertivas de saída esperadas:
*       Nó corrente está na mesma posição que o primeiro nó.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
********************************************************/
MAT_tpCondRet MAT_resetNoCorrente(MAT_tppMatriz CabecaDaMatriz)
{
	CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoPrimeiro;

	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */
}

/***************************************************
*
*   $FC Função:
*       MAT Adiciona uma coluna à matriz.
*
*
*	$AE Assertivas de entrada esperadas:
*       Cabeça da Matriz != NULL.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
*
*	$AS Assertivas de saída esperadas:
*       Coluna foi adicionada à matriz.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
****************************************************/
MAT_tpCondRet MAT_adicionaColuna(MAT_tppMatriz CabecaDaMatriz)
{
	while (CabecaDaMatriz->pNoCorr->pNoDireita) /* Loop para chegar no primeiro nó da última coluna da matriz */
		MAT_vaiParaDireita(CabecaDaMatriz);
	
	/* No bloco de código abaixo o nó corrente percorrerá a última coluna da matriz criando nós à
	direita para gerar uma nova coluna */
	do
	{
		CabecaDaMatriz->pNoCorr->pNoDireita = MAT_criaNo(); /* Cria nó da coluna nova à direita do nó corrente */
		if (!CabecaDaMatriz->pNoCorr->pNoDireita) return MAT_CondRetFaltouMemoria;  /* Nó criado == NULL. Retorna condição de insufuciência de memória */

		CabecaDaMatriz->pNoCorr->pNoDireita->pNoEsquerda = CabecaDaMatriz->pNoCorr; /* Conecta nó da coluna nova ao nó corrente */
		if (CabecaDaMatriz->pNoCorr->pNoCima) /* Se existir nó acima do nó corrente (não é o primeiro nó da coluna) */
		{
			CabecaDaMatriz->pNoCorr->pNoDireita->pNoCima = CabecaDaMatriz->pNoCorr->pNoCima->pNoDireita; /* Conecta o nó da coluna nova ao acima dele */
			CabecaDaMatriz->pNoCorr->pNoCima->pNoDireita->pNoBaixo = CabecaDaMatriz->pNoCorr->pNoDireita; /* Conecta o de cima do novo ao novo */
		}

	} while (MAT_vaiParaBaixo(CabecaDaMatriz) != MAT_CondRetNoNaoExiste); /* Nó corrente desce a coluna. Para somente quando caminhar para o NULL */

	MAT_resetNoCorrente(CabecaDaMatriz); /* Coloca o nó corrente na mesma posição do primeiro nó */

	return MAT_CondRetOK;
}

/***************************************************
*
*   $FC Função:
*       MAT Adiciona uma linha à matriz.
*
*
*	$AE Assertivas de entrada esperadas:
*       Cabeça da Matriz != NULL.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
*
*	$AS Assertivas de saída esperadas:
*       Linha foi adicionada à matriz.
*		Valem as assertivas estruturais da matriz
*       com cabeça.
*
****************************************************/
MAT_tpCondRet MAT_adicionaLinha(MAT_tppMatriz CabecaDaMatriz)
{
	while (CabecaDaMatriz->pNoCorr->pNoBaixo) /* Loop para chegar no primeiro nó da última linha da matriz */
		MAT_vaiParaBaixo(CabecaDaMatriz);

	/* No bloco de código abaixo o nó corrente percorrerá a última linha da matriz criando nós
	abaixo para gerar uma nova linha */

	do
	{
		CabecaDaMatriz->pNoCorr->pNoBaixo = MAT_criaNo(); /* Cria nó da linha nova abaixo do nó corrente atual */

		if (!CabecaDaMatriz->pNoCorr->pNoBaixo) return MAT_CondRetFaltouMemoria; /* Nó criado == NULL. Retorna condição de insufuciência de memória */

		CabecaDaMatriz->pNoCorr->pNoBaixo->pNoCima = CabecaDaMatriz->pNoCorr; /* Conecta nó da linha nova ao nó corrente atual */

		if (CabecaDaMatriz->pNoCorr->pNoEsquerda) /* Se existir nó à esquerda do nó corrente atual (não é o primeiro nó da linha) */
		{
			CabecaDaMatriz->pNoCorr->pNoBaixo->pNoEsquerda = CabecaDaMatriz->pNoCorr->pNoEsquerda->pNoBaixo; /* Conecta o nó da linha nova ao à esquerda dele */
			CabecaDaMatriz->pNoCorr->pNoEsquerda->pNoBaixo->pNoDireita = CabecaDaMatriz->pNoCorr->pNoBaixo; /* Conecta o de à esquerda do novo ao novo */
		}
	} while (MAT_vaiParaDireita(CabecaDaMatriz) != MAT_CondRetNoNaoExiste); /* Nó corrente anda para a direita na linha. Para somente quando caminhar para o NULL */

	MAT_resetNoCorrente(CabecaDaMatriz); /* Coloca o nó corrente na mesma posição do primeiro nó */

	return MAT_CondRetOK;
}

/***************************************************
*
*   $FC Função: MAT Criar a estrutura da matriz,
*       criando os nós com a MAT_criaNo() e os
*       interconectando.
*
*  $EP Par�metros
*       $P LinhasEColunas - O parâmetro que que passará o número de linhas e colunas da matriz.
*           Este parâmetro é passado por valor.
*       $P MatrizCriada - O parâmetro que receberá o ponteiro para a cabeça da matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetFaltouMemoria
*
****************************************************/
MAT_tpCondRet MAT_cria(char Linhas, char Colunas, void (*destruirElemento)(void *elemento), MAT_tppMatriz *MatrizCriada)
{
	tpNoMatriz* PrimeiroNo;

	PrimeiroNo = MAT_criaNo(); /* Cria primeiro nó da Matriz */
	if (!PrimeiroNo) return MAT_CondRetFaltouMemoria; /* Primeiro Nó == NULL */


	(*MatrizCriada) = (MAT_tppMatriz)malloc(sizeof(tpMatriz)); /* Malloca cabeça da matriz */
	if (!(*MatrizCriada)) return MAT_CondRetFaltouMemoria; /* Cabeça da Matriz == NULL, Retorna condição de insufuciência de memória */

	(*MatrizCriada)->pNoPrimeiro = PrimeiroNo;

	(*MatrizCriada)->pNoCorr = PrimeiroNo; /* Primeiro nó e nó corrente são o mesmo nó */

	(*MatrizCriada)->destruirElemento = destruirElemento;

	while (--Colunas) /* Cria primeira linha da matriz a partir do primeiro nó.
	Subtrai primeiro porque um nó (o primeiro) está feito */
		if (MAT_adicionaColuna((*MatrizCriada)) == MAT_CondRetFaltouMemoria) return MAT_CondRetFaltouMemoria;
	/* Cada chamada cria uma coluna nova na matriz. Já que só há um nó na matriz,
	cada chamada da função só cria novos nós à direita do primeiro, formando a primeira linha */

	while (--Linhas) /* Cria as linhas da matriz extendendo a primeira linha.
	Subtrai primeiro porque uma linha (a primeira) está feita */

		if (MAT_adicionaLinha((*MatrizCriada)) == MAT_CondRetFaltouMemoria) return MAT_CondRetFaltouMemoria;
	/* Cada chamada cria uma linha nova na matriz. */

	(*MatrizCriada)->destruirElemento = destruirElemento;

	return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */
}

/***************************************************
*
*	$FC Função: MAT Destruir matriz linha por linha.
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoNaoExiste
*
****************************************************/
void MAT_destroi(MAT_tppMatriz CabecaDaMatriz)
{
    tpNoMatriz *PrimeiroNoDaLinhaDeBaixo;

    do
    {
        PrimeiroNoDaLinhaDeBaixo = CabecaDaMatriz->pNoPrimeiro->pNoBaixo; /* Guarda primeiro nó da linha de baixo para deletar a linha seguinte */
        CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoPrimeiro->pNoDireita; /* Nó corrente é o nó à direita do primeiro nó da matriz */
        do
        {
            CabecaDaMatriz->destruirElemento(CabecaDaMatriz->pNoPrimeiro->Elemento); /* Libera o ponteiro do elemento */
            free(CabecaDaMatriz->pNoPrimeiro); /* Libera primeiro nó da matriz */
            if (CabecaDaMatriz->pNoCorr == NULL) /* Liberou o último nó desta linha da matriz */
                break; /* Segue para próxima linha da matriz */
            CabecaDaMatriz->pNoPrimeiro = CabecaDaMatriz->pNoCorr; /* Primeiro nó da matriz é o mesmo que o corrente */
            CabecaDaMatriz->pNoCorr = CabecaDaMatriz->pNoCorr->pNoDireita; /* Nó corrente é o nó à direita do primeiro nó da matriz */
        } while (1); /* Para sempre */

        CabecaDaMatriz->pNoPrimeiro = PrimeiroNoDaLinhaDeBaixo; /* Primeiro nó da matriz se torna o primeiro nó da linha de baixo */
    } while (PrimeiroNoDaLinhaDeBaixo != NULL); /* Se a condição for quebrada, então liberou a última linha da matriz */

    free(CabecaDaMatriz); /* Libera cabeça da matriz */
}

/*******************************************************
*
*	$FC Função: MAT Inserir elemento no nó corrente da
*       matriz
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a matriz.
*           Este parâmetro é passado por referência.
*       $P elemento - O parâmetro que passará o ponteiro para o elemento a ser incoporado no nó corrente.
*           Este parâmetro é passado por valor.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoOcupado
*
********************************************************/
MAT_tpCondRet MAT_inserir(MAT_tppMatriz CabecaDaMatriz, void *elemento)
{
    if (CabecaDaMatriz->pNoCorr->Elemento != NULL) /* Nó corrente já possui lista */
        return MAT_CondRetNoOcupado; /* Retorna condição de falha na incorporação da lista no nó corrente */

    CabecaDaMatriz->pNoCorr->Elemento = elemento; /* Incopora ponteiro da lista passado por referência no nó corrente */

    return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */

}

/*******************************************************
*
*	$FC Função: MAT Obtém o elemento do nó corrente da matriz
*
*   $EP Parâmetros
*       $P CabecaDaMatriz - O parâmetro que receberá o ponteiro para a cabeça da matriz.
*           Este parâmetro é passado por referência.
*       $P elem - O parâmetro que receberá o ponteiro para o elemento a ser obtida.
*           Este parâmetro é passado por referência.
*
*   $FV Valor retornado
*       MAT_CondRetOK
*       MAT_CondRetNoVazio
*
********************************************************/
MAT_tpCondRet MAT_obterElemento(MAT_tppMatriz CabecaDaMatriz, void **elemento)
{
    if (CabecaDaMatriz->pNoCorr->Elemento == NULL) /* Nó corrente não possui lista */
        return MAT_CondRetNoVazio; /* Retorna condição de falha na obtenção da lista incorporada no nó corrente */

    *elemento = CabecaDaMatriz->pNoCorr->Elemento; /* Passa, por referência, o ponteiro da lista incorporado no nó corrente */

    return MAT_CondRetOK; /* Retorna condição de teste bem sucedido */
}