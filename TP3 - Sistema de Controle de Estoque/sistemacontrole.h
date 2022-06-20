#include <fstream>
using namespace std;
struct Produto
{
	char nome[30];
	float preco;
	float quant;
};

void menu();
void pedir(Produto*, ifstream&, ofstream&);					//Fun��o que l� um arquivo texto contendo o pedido e gera o recibo e as condi��es forem atendidas
Produto* adicionar(Produto*, int&);							//Fun��o que adiciona um novo elemento ao estoque. Caso n�o haja espa�o, aloca din�micamente mem�ria e retorna um novo endere�o
Produto* excluir(Produto*, int&);							//Fun��o que remove um elemento do estoque. Aloca din�micamente um bloco menor de mem�ria e retorna o endere�o desse
void listar(Produto*, const int*);							//Lista os elementos presentes no estoque

//Considerando criar fun��o pra alocar blocos de memoria para o tipo Produto
void linha(int, char = '-');
int buscaProduto(const char*, const Produto*, const int);	//Fun��o que retorna a posi��o de um produto (nome) no vetor de produtos. -1 indica que o nome n�o existe no vetor
int numProd(Produto*, const int*);							//Retorna o n�mero de produtos existentes no estoque
int pot(int, int);											//Calcula uma pot�ncia. Uso exclusivo para calcular novos blocos de mem�ria din�micamente alocada

