#include <iostream>
using namespace std;

//Registros que armazenam dados sobre o empr�stimo e data
struct Data
{
	int dia, mes, ano;
};
struct emprestimo
{
	Data dataEmprestimo;
	char idAluno[11]{};
	char idLivro[6]{};
	Data dataDevolucao;
};

//Fun��es que definem operadores para os registros criados acima
istream& operator>>(istream&, Data&);	//Define a leitura do cin para o tipo "Data" 
ostream& operator<<(ostream&, Data&);	//Define a exibi��o de "Data" para cout
int operator-(Data&, Data&);			//Define a subtra��o para duas "Datas"

//Fun��es pedidas na quest�o
float calcMultaTotal(emprestimo[], int, Data);	//Calcula multa apurada no dia
void dadosEmprestimo(emprestimo*, Data*);		//Exibe dados de um empr�stimo
void desenhaTraco(int);							//Desenha um tra�o na tela 

//Fun��es opcionais que decidi adicionar
int calcAtraso(Data*, Data*);	//Calcula o atraso entre duas datas, que se define a partir de 3 dias de diferen�a

