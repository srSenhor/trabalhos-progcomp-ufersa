#include "cripto.h"
#include <random>
using namespace std;

long long codificar(int operacao_inalterada) 
{
	//Usei a mesma implementação do "random" feita no video, se mostrou mais agradável que rand e srand.
	random_device seed_numeroRandom;
	mt19937 numeroRandom(seed_numeroRandom());
	uniform_int_distribution<int> faixa_numeroRandom(0, 31);

	long long operacao_codificada = long long(operacao_inalterada);
	
	//Sorteando e guardando os bits que serão alterados
	int bit_alterado1 = faixa_numeroRandom(numeroRandom);
	int bit_alterado2 = faixa_numeroRandom(numeroRandom);
	int bit_alterado3 = faixa_numeroRandom(numeroRandom);
	int bit_alterado4 = faixa_numeroRandom(numeroRandom);
	int bit_alterado5 = faixa_numeroRandom(numeroRandom);
	int bit_alterado6 = faixa_numeroRandom(numeroRandom);

	//Guardando todos os bits alterados em uma int, com o 00 no final.
	unsigned int bits_alterados = bit_alterado1 << 5;
	bits_alterados = (bits_alterados | bit_alterado2) << 5;
	bits_alterados = (bits_alterados | bit_alterado3) << 5;
	bits_alterados = (bits_alterados | bit_alterado4) << 5;
	bits_alterados = (bits_alterados | bit_alterado5) << 5;
	bits_alterados = (bits_alterados | bit_alterado6) << 2;

	/* - - - - - - - Vários "if"s que mudam os bits nas posições sorteadas - - - - - - - - - - - - - - - - */

	//Usei vários "if..else"s por que minha implementação do for precisaria de vetor, que não domino e nem sei se pode usar
	if (testarBit(operacao_codificada, bit_alterado1)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado1);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado1);
	}

	if (testarBit(operacao_codificada, bit_alterado2)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado2);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado2);
	}

	if (testarBit(operacao_codificada, bit_alterado3)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado3);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado3);
	}

	if (testarBit(operacao_codificada, bit_alterado4)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado4);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado4);
	}

	if (testarBit(operacao_codificada, bit_alterado5)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado5);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado5);
	}

	if (testarBit(operacao_codificada, bit_alterado6)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado6);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado6);
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	//Deslocando a operação codificada e juntando com a cadeia de bits alterados, totalizando 64 bits
	operacao_codificada = operacao_codificada << 32;
	operacao_codificada = (operacao_codificada | bits_alterados);
	return operacao_codificada;
}

int decodificar(long long operacao_codificada)
{
	//Separando a operação codificada das posições que foram alteradas
	int operacao_decodificada = operacao_codificada >> 32, bits_alterados = operacao_codificada;
	bits_alterados = bits_alterados >> 2;

	/* - - - - - - - - Vários "if"s que mudam a operação que foi codificada para seu formato original- - - - - -*/

	//Usei vários "if..else"s por que minha implementação do for precisaria de vetor, que não domino e nem sei se pode usar
	if (testarBit(operacao_decodificada, bits_alterados >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 5 >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 5 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 5 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 10 >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 10 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 10 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 15 >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 15 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 15 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 20 >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 20 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 20 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 25 >> 25)) //Desligando/ligando bit na posição sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 25 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 25 >> 25);
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	return operacao_decodificada; // Retornando a operação decodificada
}



int ligarBit(int operacao_a_alterar, int posicaoBit)
{
	int ligaBit = 1 << posicaoBit; //Máscara que moverá 1 bit para a posição indicad
	operacao_a_alterar = operacao_a_alterar | ligaBit; //Torna um bit 0 em 1
	return operacao_a_alterar;
}

int desligarBit(int operacao_a_alterar, int posicaoBit)
{
	int desligaBit = 1 << posicaoBit; //Máscara que moverá 1 bit para a posição indicada
	operacao_a_alterar = operacao_a_alterar & ~(desligaBit); //Torna um bit 1 em 0
	return operacao_a_alterar;
}

bool testarBit(int operacao_a_alterar, int posicaoBit)
{	
	int testaBit = 1 << posicaoBit; //Máscara que testará o bit da posição indicada
	if (operacao_a_alterar & testaBit) //Se estiver ligado, retorna verdadeiro
	{
		return 1;
	}
	else //Se não, falso
	{
		return 0;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */