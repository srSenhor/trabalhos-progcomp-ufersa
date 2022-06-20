#include <iostream>
#include "simd.h"
#include "cripto.h"

using namespace std;

int main()
{
	/* - - - - - - Recebendo valore do usuário e os armazenando em variáveis temporárias - - - - - - - - - */

	int valA, valB, valC, valD; //Números nos quais serão realizadas as operações
	int valE, valF, valG, valH; //Números nos quais serão realizadas as operações

	cin >> valA >> valB >> valC >> valD;
	cin >> valE >> valF >> valG >> valH;

	system("cls");

	/* - - - - - - Exibindo os números digitados pelo usuário com espaços preenchidos por "0"s - - - - - - */

	cout.fill('0');

	cout << "[";
	cout.width(3);
	cout << valA << ",";
	cout.width(3);
	cout << valB << ",";
	cout.width(3);
	cout << valC << ",";
	cout.width(3);
	cout << valD << "]\n";

	cout << "[";
	cout.width(3);
	cout << valE << ",";
	cout.width(3);
	cout << valF << ",";
	cout.width(3);
	cout << valG << ",";
	cout.width(3);
	cout << valH << "]\n" << endl;

	/* - - - - - -  Armazenando os valores em "int"s para simulação de instrução SIMD - - - - - - - - - - -*/

	unsigned int operandoA = armazena(valA, valB, valC, valD);
	unsigned int operandoB = armazena(valE, valF, valG, valH);

	cout << "Operadores em 32 bits = " << operandoA << endl;
	cout << "Operadores em 32 bits = " << operandoB << endl << endl;
	
	/* - - - - - -  Realizando as operações de soma e produto sobre as "int"s concatenadas - - - - - - - - */

	unsigned int somaOperandos = soma(operandoA, operandoB);
	unsigned int multOperandos = mult(operandoA, operandoB);
	cout << "Soma em 32 bits = " << somaOperandos << endl;
	cout << "Produto em 32 bits = " << multOperandos << endl << endl;

	/* - - - - - -  Exibindo 4 resultado das operações entre os operandos armazenados nas "int"s - - - - - */

	cout << "[";
	cout.width(3); 
	cout << (somaOperandos >> 24) << ",";
	cout.width(3);
	cout << (somaOperandos << 8 >> 24) << ",";
	cout.width(3);
	cout << (somaOperandos << 16 >> 24) << ",";
	cout.width(3);
	cout << (somaOperandos << 24 >> 24) << "]" << " = Somas\n";

	cout << "[";
	cout.width(3);
	cout << (multOperandos >> 24) << ",";
	cout.width(3);
	cout << (multOperandos << 8 >> 24) << ",";
	cout.width(3);
	cout << (multOperandos << 16 >> 24) << ",";
	cout.width(3);
	cout << (multOperandos << 24 >> 24) << "]" << " = Produtos\n" << endl;

	/* - - - - - -  Encriptando as operações e exibindo o resultado encriptado - - - - - - - - - - - - - - */

	unsigned long long somaCripto = codificar(somaOperandos); //Encriptando as operações
	unsigned long long multCripto = codificar(multOperandos); //Encriptando as operações
	cout << "Soma encriptada em 64 bits = " << somaCripto << endl;
	cout << "Mult encriptada em 64 bits = " << multCripto << endl << endl;

	/* - - Decodificando as operações, exibindo os resultados embaralhados e os bits que foram alterados - */

	unsigned int somaDecode = decodificar(somaCripto); //Variavel guardando a decodificação, que é igual ao estado original
	unsigned int multDecode = decodificar(multCripto); //Variavel guardando a decodificação, que é igual ao estado original

	cout << "Valor codificado = " << (somaCripto >> 32) << "\t";
	cout << "( " << (somaCripto << 32 >> 59) << " " << (somaCripto << 37 >> 59) << " " << (somaCripto << 37 >> 59);
	cout << " " << (somaCripto << 42 >> 59) << " " << (somaCripto << 47 >> 59) << " " << (somaCripto << 52 >> 59) << " )\n";
	cout << "Soma decodificada = " << somaDecode << endl << endl;

	cout << "Valor codificado = " << (multCripto >> 32) << "\t";
	cout << "( " << (multCripto << 32 >> 59) << " " << (multCripto << 37 >> 59) << " " << (multCripto << 37 >> 59);
	cout << " " << (multCripto << 42 >> 59) << " " << (multCripto << 47 >> 59) << " " << (multCripto << 52 >> 59) << " )\n";
	cout << "Mult decodificada = " << multDecode << endl;

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
}