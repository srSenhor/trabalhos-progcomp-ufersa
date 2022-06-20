#include "cripto.h"
#include <random>
using namespace std;

long long codificar(int operacao_inalterada) 
{
	//Usei a mesma implementa��o do "random" feita no video, se mostrou mais agrad�vel que rand e srand.
	random_device seed_numeroRandom;
	mt19937 numeroRandom(seed_numeroRandom());
	uniform_int_distribution<int> faixa_numeroRandom(0, 31);

	long long operacao_codificada = long long(operacao_inalterada);
	
	//Sorteando e guardando os bits que ser�o alterados
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

	/* - - - - - - - V�rios "if"s que mudam os bits nas posi��es sorteadas - - - - - - - - - - - - - - - - */

	//Usei v�rios "if..else"s por que minha implementa��o do for precisaria de vetor, que n�o domino e nem sei se pode usar
	if (testarBit(operacao_codificada, bit_alterado1)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado1);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado1);
	}

	if (testarBit(operacao_codificada, bit_alterado2)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado2);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado2);
	}

	if (testarBit(operacao_codificada, bit_alterado3)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado3);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado3);
	}

	if (testarBit(operacao_codificada, bit_alterado4)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado4);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado4);
	}

	if (testarBit(operacao_codificada, bit_alterado5)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado5);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado5);
	}

	if (testarBit(operacao_codificada, bit_alterado6)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_codificada = desligarBit(operacao_codificada, bit_alterado6);
	}
	else
	{
		operacao_codificada = ligarBit(operacao_codificada, bit_alterado6);
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	//Deslocando a opera��o codificada e juntando com a cadeia de bits alterados, totalizando 64 bits
	operacao_codificada = operacao_codificada << 32;
	operacao_codificada = (operacao_codificada | bits_alterados);
	return operacao_codificada;
}

int decodificar(long long operacao_codificada)
{
	//Separando a opera��o codificada das posi��es que foram alteradas
	int operacao_decodificada = operacao_codificada >> 32, bits_alterados = operacao_codificada;
	bits_alterados = bits_alterados >> 2;

	/* - - - - - - - - V�rios "if"s que mudam a opera��o que foi codificada para seu formato original- - - - - -*/

	//Usei v�rios "if..else"s por que minha implementa��o do for precisaria de vetor, que n�o domino e nem sei se pode usar
	if (testarBit(operacao_decodificada, bits_alterados >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 5 >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 5 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 5 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 10 >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 10 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 10 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 15 >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 15 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 15 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 20 >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 20 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 20 >> 25);
	}

	if (testarBit(operacao_decodificada, bits_alterados << 25 >> 25)) //Desligando/ligando bit na posi��o sorteada.
	{
		operacao_decodificada = desligarBit(operacao_decodificada, bits_alterados << 25 >> 25);
	}
	else
	{
		operacao_decodificada = ligarBit(operacao_decodificada, bits_alterados << 25 >> 25);
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	return operacao_decodificada; // Retornando a opera��o decodificada
}



int ligarBit(int operacao_a_alterar, int posicaoBit)
{
	int ligaBit = 1 << posicaoBit; //M�scara que mover� 1 bit para a posi��o indicad
	operacao_a_alterar = operacao_a_alterar | ligaBit; //Torna um bit 0 em 1
	return operacao_a_alterar;
}

int desligarBit(int operacao_a_alterar, int posicaoBit)
{
	int desligaBit = 1 << posicaoBit; //M�scara que mover� 1 bit para a posi��o indicada
	operacao_a_alterar = operacao_a_alterar & ~(desligaBit); //Torna um bit 1 em 0
	return operacao_a_alterar;
}

bool testarBit(int operacao_a_alterar, int posicaoBit)
{	
	int testaBit = 1 << posicaoBit; //M�scara que testar� o bit da posi��o indicada
	if (operacao_a_alterar & testaBit) //Se estiver ligado, retorna verdadeiro
	{
		return 1;
	}
	else //Se n�o, falso
	{
		return 0;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */