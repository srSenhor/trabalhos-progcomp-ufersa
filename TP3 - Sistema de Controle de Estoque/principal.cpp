#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "sistemacontrole.h"

using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;

	fin.open("estoque.bin", ios_base::in | ios_base::binary);	//Abrindo o arquivo de estoque, se existir
	
	int prods_no_estoque = 0;
	Produto * estoque;
	if(!fin.is_open())								//Se não houver um arquivo de estoque...
		estoque = new Produto[prods_no_estoque]{};	//...inicia o vetor vazio
	else	//Senão...
	{
		fin.read((char*)&prods_no_estoque, sizeof(int));	//O primeiro elemento indica quantos itens tem no vetor
		estoque = new Produto[prods_no_estoque]{};
		for (int i = 0; i < prods_no_estoque; ++i)			//Preenche o arquivo de estoque
			fin.read((char*) &estoque[i], sizeof(Produto));
	}

	fin.close();


	menu();
	char opcao;
	while (toupper(opcao = cin.get()) != 'S')
	{
		opcao = toupper(opcao);
		switch (opcao)
		{
		case 'P':
			cin.get();
			system("cls");
			pedir(estoque, fin, fout);
			cout << "\nPressione ENTER para encerrar...\n";
			cin.get();
			system("cls");
			break;
		case 'A':
			cin.get();
			system("cls");
			estoque = adicionar(estoque, prods_no_estoque);
			cout << "\nPressione ENTER para encerrar...\n";
			cin.get();
			system("cls");
			break;
		case 'E':
			cin.get();
			system("cls");
			estoque = excluir(estoque, prods_no_estoque);
			cout << "\nPressione ENTER para encerrar...\n";
			cin.get();
			system("cls");
			break;
		case 'L':
			cin.get();
			system("cls");
			listar(estoque, &prods_no_estoque);
			cout << "\nPressione ENTER para encerrar...\n";
			cin.get();
			system("cls");
			break;
		default:
			cout << "Opcao desconhecida. Pressione ENTER para encerrar...\n";
			cin.get();
			cin.get();
			system("cls");
			break;
		}
		menu();
	}
	
	prods_no_estoque = numProd(estoque, &prods_no_estoque);							//Atualiza o vetor para conter apenas os produtos no estoque
	fout.open("estoque.bin", ios_base::out | ios_base::trunc | ios_base::binary);	//Abre o arquivo para escrita

	fout.write((char*) &prods_no_estoque, sizeof(int));		//Insere o número de produtos no estoque
	for(int i = 0; i < prods_no_estoque; i++)				//Preenche o estoque
		fout.write((char*) &estoque[i], sizeof(Produto));

	fout.close();
	delete [] estoque;
	return 0;
}
