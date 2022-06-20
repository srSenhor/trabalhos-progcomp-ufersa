#include <windows.h>
#include "biblioteca.h"
#define MULTA 0.80f


int main()
{
	cout << fixed;		//Configurando o cout para exibir, de maneira arredondada, duas casas decimais
	cout.precision(2);

	SetConsoleOutputCP(1252);	//Facilitando a visualização para a região do Brasil

	cout << "Qual o número de devoluções para hoje? ";
	int numDevos;				//Quantidade de devoluções que será realizada no dia
	cin >> numDevos;

	emprestimo * DevolucaoDia =	new emprestimo[numDevos] {}; //Vetor dinâmico que guarda o número de devoluções feitas no dia

	cout << "Qual a data de devolução: __/__/____\b\b\b\b\b\b\b\b\b\b";
	Data data_devo;				//Data atual em que serão regitradas as devoluções
	cin >> data_devo;	
	desenhaTraco(45);			//Organizando visualmente
	
	for (int c = 0; c < numDevos; c++)	//Registrando todas as devoluções do dia
	{
		cout << endl;

		cout << left; cout.width(10); cout << "Aluno";
		cout << right; cout << ": ";
		cin >> DevolucaoDia[c].idAluno;

		cout << left; cout.width(10); cout << "Livro";
		cout << right; cout << ": ";
		cin >> DevolucaoDia[c].idLivro;

		cout << left; cout.width(10); cout << "Empréstimo";
		cout << right; cout << ": __/__/____\b\b\b\b\b\b\b\b\b\b";
		cin >> DevolucaoDia[c].dataEmprestimo;
		DevolucaoDia[c].dataDevolucao = data_devo;

		int diasAtraso = calcAtraso(&DevolucaoDia[c].dataEmprestimo, &data_devo); //Guarda os dias de atraso para aquela devolução

		cout << left; cout.width(10); cout << "Atraso";
		cout << right; cout << ": ";
		cout << diasAtraso << " dia(s)" << endl;

		cout << left; cout.width(10); cout << "Multa";
		cout << right; cout << ": ";
		cout << "R$" << (diasAtraso * MULTA);
		
		cout << endl;
		desenhaTraco(35);
	}
	
	desenhaTraco(10);
	cout << endl << endl;


	const char* mesNomes[12]	//Vetor de constantes com o nome dos meses para exibir informações por extenso
	{
		"janeiro", "fevereiro", "março", "abril", "maio", "junho",
		"julho", "agosto", "setembro", "outubro", "novembro", "dezembro",
	};

	//Exibindo informações
	cout << "Resumo do dia " << data_devo.dia << " de " << mesNomes[(data_devo.mes - 1)] << " de " << data_devo.ano << "\n\n";
	for (int i = 0; i < numDevos; i++)	//A exibição mostrará ID do aluno, ID do livro, Data de empréstimo e multa, respectivamente 
		dadosEmprestimo(&DevolucaoDia[i], &data_devo);
	
	//Exibindo o total em multas apurado no dia
	cout << "\nTotal em multas: R$" << (calcMultaTotal(DevolucaoDia, numDevos, data_devo)) << "\n\n";

	desenhaTraco(45);
	cout << endl;

	cout << "Encerrando o programa..." << endl;
	delete[] DevolucaoDia;	//Liberando memória alocada dinâmicamente

	return 0;
}
