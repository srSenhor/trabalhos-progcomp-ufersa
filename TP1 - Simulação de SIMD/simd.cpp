#include "simd.h"

/* - - - - - - - Fun��o que armazena as opera��es em um �nico int movendo bits - - - - - - - - - - - - */

int armazena(unsigned char primeiroNum, unsigned char segundoNum, unsigned char terceiroNum, unsigned char quartoNum)
{
	// As opera��es a seguir guardam os par�metros, organizando seus bits para que caibam num mesmo int.
	int operando = primeiroNum << 8;
	operando = (operando | segundoNum) << 8;
	operando = (operando | terceiroNum) << 8;
	operando = (operando | quartoNum);
	return operando; // Retorna um int com todos os par�metros da fun��o juntos, um seguido do outro na vis�o bin�ria.
}

/* - - - - - - - Fun��es que retornam determinado n�mero (8 bits) da posi��o de um int - - - - - - - - */

unsigned char primeiro(int primeiroNum)
{
	return primeiroNum >> 24; //Retorna o primeiro n�mero do argumento vindo da fun��o armazena().
}

unsigned char segundo(int segundoNum)
{
	return segundoNum << 8 >> 24; //Retorna o segundo n�mero do argumento vindo da fun��o armazena().
}

unsigned char terceiro(int terceiroNum)
{
	return terceiroNum << 16 >> 24; //Retorna o terceiro n�mero do argumento vindo da fun��o armazena().
}

unsigned char quarto(int quartoNum)
{
	return quartoNum << 24 >> 24; //Retorna o quarto n�mero do argumento vindo da fun��o armazena().
}

/* - - - - - - - Fun��es que realizam as opera��es de soma e multiplica��o sobre dois inteiros - - - - */

int soma(int operando1, int operando2)
{
	int firstSoma = primeiro(operando1) + primeiro(operando2);	//Soma dos primeiros n�meros dos operandos
	int secondSoma = segundo(operando1) + segundo(operando2);	//Soma dos segundos n�meros dos operandos
	int thirdSoma = terceiro(operando1) + terceiro(operando2);	//Soma dos terceiros n�meros dos operandos
	int fourthSoma = quarto(operando1) + quarto(operando2);		//Soma dos quartos n�meros dos operandos
	return armazena(firstSoma, secondSoma, thirdSoma, fourthSoma); //Armazena as opera��es em um inteiro
}

int mult(int operando1, int operando2)
{
	int firstMult = primeiro(operando1) * primeiro(operando2);	//Produto dos primeiros n�meros dos operandos
	int secondMult = segundo(operando1) * segundo(operando2);	//Produto dos segundos n�meros dos operandos
	int thirdMult = terceiro(operando1) * terceiro(operando2);	//Produto dos terceiros n�meros dos operandos
	int fourthMult = quarto(operando1) * quarto(operando2);		//Produto dos quartos n�meros dos operandos
	return armazena(firstMult, secondMult, thirdMult, fourthMult); //Armazena as opera��es em um inteiro

}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
