#include <fstream>
using namespace std;
struct Produto
{
	char nome[30];
	float preco;
	float quant;
};

void menu();
void pedir(Produto*, ifstream&, ofstream&);					//Função que lê um arquivo texto contendo o pedido e gera o recibo e as condições forem atendidas
Produto* adicionar(Produto*, int&);							//Função que adiciona um novo elemento ao estoque. Caso não haja espaço, aloca dinâmicamente memória e retorna um novo endereço
Produto* excluir(Produto*, int&);							//Função que remove um elemento do estoque. Aloca dinâmicamente um bloco menor de memória e retorna o endereço desse
void listar(Produto*, const int*);							//Lista os elementos presentes no estoque

//Considerando criar função pra alocar blocos de memoria para o tipo Produto
void linha(int, char = '-');
int buscaProduto(const char*, const Produto*, const int);	//Função que retorna a posição de um produto (nome) no vetor de produtos. -1 indica que o nome não existe no vetor
int numProd(Produto*, const int*);							//Retorna o número de produtos existentes no estoque
int pot(int, int);											//Calcula uma potência. Uso exclusivo para calcular novos blocos de memória dinâmicamente alocada

