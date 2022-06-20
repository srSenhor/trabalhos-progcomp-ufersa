#include "simd.h"

/* - - - - - - - Função que armazena as operações em um único int movendo bits - - - - - - - - - - - - */

int armazena(unsigned char primeiroNum, unsigned char segundoNum, unsigned char terceiroNum, unsigned char quartoNum)
{
	// As operações a seguir guardam os parâmetros, organizando seus bits para que caibam num mesmo int.
	int operando = primeiroNum << 8;
	operando = (operando | segundoNum) << 8;
	operando = (operando | terceiroNum) << 8;
	operando = (operando | quartoNum);
	return operando; // Retorna um int com todos os parâmetros da função juntos, um seguido do outro na visão binária.
}

/* - - - - - - - Funções que retornam determinado número (8 bits) da posição de um int - - - - - - - - */

unsigned char primeiro(int primeiroNum)
{
	return primeiroNum >> 24; //Retorna o primeiro número do argumento vindo da função armazena().
}

unsigned char segundo(int segundoNum)
{
	return segundoNum << 8 >> 24; //Retorna o segundo número do argumento vindo da função armazena().
}

unsigned char terceiro(int terceiroNum)
{
	return terceiroNum << 16 >> 24; //Retorna o terceiro número do argumento vindo da função armazena().
}

unsigned char quarto(int quartoNum)
{
	return quartoNum << 24 >> 24; //Retorna o quarto número do argumento vindo da função armazena().
}

/* - - - - - - - Funções que realizam as operações de soma e multiplicação sobre dois inteiros - - - - */

int soma(int operando1, int operando2)
{
	int firstSoma = primeiro(operando1) + primeiro(operando2);	//Soma dos primeiros números dos operandos
	int secondSoma = segundo(operando1) + segundo(operando2);	//Soma dos segundos números dos operandos
	int thirdSoma = terceiro(operando1) + terceiro(operando2);	//Soma dos terceiros números dos operandos
	int fourthSoma = quarto(operando1) + quarto(operando2);		//Soma dos quartos números dos operandos
	return armazena(firstSoma, secondSoma, thirdSoma, fourthSoma); //Armazena as operações em um inteiro
}

int mult(int operando1, int operando2)
{
	int firstMult = primeiro(operando1) * primeiro(operando2);	//Produto dos primeiros números dos operandos
	int secondMult = segundo(operando1) * segundo(operando2);	//Produto dos segundos números dos operandos
	int thirdMult = terceiro(operando1) * terceiro(operando2);	//Produto dos terceiros números dos operandos
	int fourthMult = quarto(operando1) * quarto(operando2);		//Produto dos quartos números dos operandos
	return armazena(firstMult, secondMult, thirdMult, fourthMult); //Armazena as operações em um inteiro

}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
