#include <iostream>
using namespace std;

//Registros que armazenam dados sobre o empréstimo e data
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

//Funções que definem operadores para os registros criados acima
istream& operator>>(istream&, Data&);	//Define a leitura do cin para o tipo "Data" 
ostream& operator<<(ostream&, Data&);	//Define a exibição de "Data" para cout
int operator-(Data&, Data&);			//Define a subtração para duas "Datas"

//Funções pedidas na questão
float calcMultaTotal(emprestimo[], int, Data);	//Calcula multa apurada no dia
void dadosEmprestimo(emprestimo*, Data*);		//Exibe dados de um empréstimo
void desenhaTraco(int);							//Desenha um traço na tela 

//Funções opcionais que decidi adicionar
int calcAtraso(Data*, Data*);	//Calcula o atraso entre duas datas, que se define a partir de 3 dias de diferença

