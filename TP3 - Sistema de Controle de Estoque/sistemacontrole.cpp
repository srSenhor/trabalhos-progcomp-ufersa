#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "sistemacontrole.h"
using namespace std;

void menu()														//Função que desenha o menu
{
	cout << "Sistema de Controle\n";
	linha(19, '=');
	cout << "(P)edir\n"
		"(A)dicionar\n"
		"(E)xcluir\n"
		"(L)istar\n"
		"(S)air\n";
	linha(19, '=');
	cout << "Opcao: [_]\b\b";
}

void pedir(Produto* estoque, ifstream& fin, ofstream& fout)
{
	cout << "Pedir\n";
	linha(5);

	cout << "Arquivo: ";
	char arquivo[20]{};	//Arquivo que vai ser aberto
	cin >> arquivo;
	cin.get();			//Descartando '\n' do buffer

	fin.open(arquivo);
	if (!fin.is_open())
		cout << "\nO arquivo \"" << arquivo << "\" nao foi encontrado!\n";
	else
	{
		int pedido_tam = 0;
		char descarte;
		while (fin.get(descarte))
			if (descarte == '\n')	//Lendo o número total de linhas do arquivo - 1 (por causa do eof)
				pedido_tam++;
		--pedido_tam;				//Tirando uma linha do cabeçalho
		fin.close();


		fin.open(arquivo);

		Produto* pedido = new Produto[pedido_tam]{};	//Alocando um bloco com a quantidade de linhas do pedido
		char nome_pedido[30]{};

		while (!((descarte = fin.get()) == '-' && (descarte = fin.get()) == '\n'))	//Descartando o cabeçalho
			continue;
		while (fin >> nome_pedido)	//Lê o nome do produto...
		{

			float quantidade;
			fin >> quantidade;		//...e a quantidade em seguida

			bool achou_palavra = false;	//Booleano que marca se a palavra foi achada ou não
			int cont = 0;
			nome_pedido[cont] = toupper(nome_pedido[cont]);		//Torna a primeira letra da palavra maiúscula...
			++cont;

			while (nome_pedido[cont])
			{
				nome_pedido[cont] = tolower(nome_pedido[cont]);	//...e o resto da palavra minúscula
				++cont;
			}
			for (int j = 0; j < pedido_tam && achou_palavra == false; ++j)
				if (!strcmp(nome_pedido, pedido[j].nome))	//Se o produto já tiver sido lido...
				{
					pedido[j].quant += quantidade;			//...atualiza quantidade
					achou_palavra = true;
				}
				else if (pedido[j].nome[0] <= 0)			//Senão...
				{
					strcpy(pedido[j].nome, nome_pedido);	//...adiciona as informações ao registro
					pedido[j].quant = quantidade;
					achou_palavra = true;
				}
		}
		fin.close();

		pedido_tam = numProd(pedido, &pedido_tam);	//Atualizando tamanho para o número de elementos do pedido
		Produto* temp = new Produto[pedido_tam]{};	//Alocando um bloco menor ou igual de memória
		for (int i = 0; i < pedido_tam; ++i)
			temp[i] = pedido[i];
		delete[] pedido;							//Liberando memória de pedido
		pedido = temp;								//Apontando para novo bloco


		int* erros = new int[pedido_tam] {};	//Vetor de possíveis erros que guarda posições dos erros do vetor de pedido
		int pos = 0;							//Posição do produto (nome) no vetor de estoque.
		bool condicao_falha[2]{ false, false };	//Condições que impossibilitam o processo de pedido
		for (int i = 0; i < pedido_tam; i++)
		{
			pos = buscaProduto(pedido[i].nome, estoque, pedido_tam);
			if (pos == -1)							//Se o produto não for encontrado no vetor...
			{
				erros[i] = i - 255;					//Vetor de erros guarda a posição - 255 para destacar dos outros erros
				condicao_falha[0] = true;			//Produto não consta no estoque
			}
			else if (estoque[pos].quant < pedido[i].quant)	//Se a quantidade no estoque for inferior ao do pedido...
			{
				erros[i] = i;								//Vetor de erros guarda a posição
				condicao_falha[1] = true;					//Quantidade pedida maior que a do estoque
			}
			else					//Se esse elemento não apresentar os erros anteriores...
			{
				erros[i] = 255;		//O vetor de erros recebe 255 que o define esse elemento como não sendo um erro
				pedido[i].preco = estoque[pos].preco;
			}
		}
		if (condicao_falha[0] || condicao_falha[1])		//Falha na operação! Exibindo o erro.
		{
			cout << "\nPedido falhou!\n";
			for (int i = 0; i < pedido_tam; i++)
				if (erros[i] < 0)	//Se o erro for a falta do produto no estoque...
				{
					cout << left; cout.width(11); cout << pedido[erros[i] + 255].nome << ": Solicitado = " << pedido[erros[i] + 255].quant << "Kg / "
						"Em estoque = " << 0.00 << "Kg" << endl;
				}
				else if (erros[i] < 255)				//Senão, se o erro é a insuficiência do produto...
				{
					int pos_insuf = buscaProduto(pedido[erros[i]].nome, estoque, pedido_tam);	//Posição do produto do pedido que gerou o erro
					cout << left; cout.width(11); cout << pedido[erros[i]].nome << ": Solicitado = " << pedido[erros[i]].quant << "Kg / "
						"Em estoque = " << estoque[pos_insuf].quant << "Kg" << endl;
				}
		}
		else	//Caso nada resulte em erro...
		{
			int pos_prod = 0;	//Posição do produto do pedido no vetor do estoque.
			for (int i = 0; i < pedido_tam; i++)
			{
				pos_prod = buscaProduto(pedido[i].nome, estoque, pedido_tam);	//Atualizando posição;
				estoque[pos_prod].quant -= pedido[i].quant;						//Deduzindo quantidade pedida do estoque.
			}

			char recibo[20]{};			//Nome do arquivo de pedido com extensão .nfc
			int k = 0;
			for (k; arquivo[k] != '.'; ++k)
				recibo[k] = arquivo[k];	//Adiciona o nome do arquivo até achar o ponto...
			recibo[k] = '.';			//...e depois completa com .nfc
			recibo[k + 1] = 'n';
			recibo[k + 2] = 'f';
			recibo[k + 3] = 'c';


			fout.open(recibo);	//Imprimindo um recibo

			fout << fixed;
			double total = 0.0, desconto = 0.0;

			fout << "Pizzaria Mamute\n";
			fout << "--------------------------------------------------\n";
			for (int i = 0; i < 5; ++i)
			{
				fout.precision(0);
				fout << left; fout.width(11);
				fout << pedido[i].nome << pedido[i].quant;
				fout.precision(2);
				fout.width(4);
				fout << "Kg";
				fout.width(3);
				fout << "a";
				fout.width(5);
				fout << pedido[i].preco;
				fout.width(6);
				fout << "/kg";
				fout.width(4);
				fout << "=";

				fout << "R$" << pedido[i].preco * pedido[i].quant << endl;
				total += pedido[i].preco * pedido[i].quant;
			}
			fout << "--------------------------------------------------\n";
			fout << right;	fout.width(28); fout << "Compra";
			fout.width(4);	fout << "=";
			fout.width(5);	fout << "R$" << total << endl;

			if (total >= 1000.0)
			{
				desconto = total * 0.1;
				total -= desconto;
			}

			fout << right;	fout.width(28); fout << "Desconto";
			fout.width(4);	fout << "=";
			fout.width(5);	fout << "R$" << desconto << endl;

			fout << right;	fout.width(28); fout << "Total";
			fout.width(4);	fout << "=";
			fout.width(5);	fout << "R$" << total << endl;

			fout.close();
			cout << "\nRecibo gerado com sucesso!\n\n";

		}
		delete[] pedido;
		delete[] erros;
	}
}

Produto* adicionar(Produto* estoque, int& tam)
{
	Produto novo{};
	cout << "Adicionar\n";
	linha(9);

	cout << left; cout.width(11);	cout << "Produto" << ": ";
	cin >> novo.nome;
	cout << left; cout.width(11);	cout << "Preco" << ": ";
	cin >> novo.preco;
	cout << left; cout.width(11);	cout << "Quantidade" << ": ";
	cin >> novo.quant;
	cin.get();	//Descartando '\n' do buffer

	int j = 0;									//Variável contadora que vai tratar o nome digitado
	novo.nome[j] = toupper(novo.nome[j]);			//Tratando o nome do produto para se adequar ao padrão
	while (novo.nome[++j])
		novo.nome[j] = tolower(novo.nome[j]);

	bool existe = false;							//Booleano que indica se o produto já existe no vetor
	for (int i = 0; estoque[i].nome[0] && !existe && i < tam; ++i)	
		if (!strcmp(estoque[i].nome, novo.nome))	//Se já existe, atualiza o valor
		{
			estoque[i].preco = novo.preco;
			estoque[i].quant += novo.quant;
			existe = true;
		}

	if (existe == false)							//Se não existir...
	{
		int prods = numProd(estoque, &tam);			//Verifica quantos produtos tem no vetor
		if (prods == tam)							//Se não houver espaço...
		{
			static int num_exp;					//Número de expansões que o vetor passou
			tam += pot(2, num_exp);				//Atualiza o tamanho do vetor

			Produto* temp = new Produto[tam]{};	//Aloca um espaço maior de memória
			for (int i = 0; i < prods; ++i)		//Copia os elementos do bloco menor para o novo
				temp[i] = estoque[i];

			delete[] estoque;					//Libera o bloco de memória anterior
			estoque = temp;						//Aponta para o novo bloco

			num_exp++;							//E incrementa o número de expansões feitas
		}
		estoque[prods] = novo;	//Independente de realocar memória, passa o produto informado ao estoque

	}
	return estoque;	//Retornando o endereço do novo bloco, ou o mesmo bloco, de memória
}

Produto* excluir(Produto* estoque, int& tam)
{
	cout << "Excluir\n";
	linha(7);

	int prods = numProd(estoque, &tam);
	for (int i = 0; i < prods; ++i)		//Mostra as opções para exclusão
		cout << i + 1 << ") " << estoque[i].nome << endl;

	cout << "Numero do produto: ";
	int opcao;
	cin >> opcao;

	cout << "Deseja excluir \"" << estoque[opcao - 1].nome << "\"? (S/N) ";	//Confirmano (ou não) exclusão
	char confirma;
	cin >> confirma;
	cin.get();	//Descartando '\n' do buffer

	if (tolower(confirma) == 's')
	{
		Produto* temp = new Produto[tam - 1]{};	//Aloca um novo bloco com um item a menos
		for (int i = 0; i < (opcao - 1); ++i)	//Copia até a posição do item informado
			temp[i] = estoque[i];
		for (int j = opcao; j < tam; ++j)		//Copia o resto do vetor (fora o item informado)
			temp[j - 1] = estoque[j];

		tam = tam - 1;		//Atualizando o tamanho na função principal
		delete[] estoque;	//Liberando bloco anterior
		estoque = temp;		//E apontando para novo bloco
	}

	return estoque;	//Retorna o endereço do estoque sem o item excluído
}

void listar(Produto* estoque, const int* tam)
{
	cout << fixed;

	cout << "Listagem\n";
	linha(8);

	if (numProd(estoque, tam) == 0)					//Caso o estoque esteja vazio, exibe uma mensagem
		cout << "Nada adicionado ao estoque!\n";
	else											//Caso contrário, exibe os itens do estoque
		for (int i = 0; i < *tam && estoque[i].nome[0]; ++i)
		{
			cout.precision(2);
			cout << left; cout.width(9); cout << estoque[i].nome << " - R$";
			cout << left; cout.width(6); cout << estoque[i].preco << " - ";
			cout.precision(0);
			cout << estoque[i].quant << "kg\n";
		}
}

void linha(int tam_linha, char traco)	//Autoexplicativo....desenha uma linha no tamanho e com o caractere informados
{
	for (int i = 0; i < tam_linha; ++i)
		cout << traco;
	cout << endl;
}

int buscaProduto(const char* prod_busc, const Produto* vet_prod, const int tam)
{
	int posicao = -1;
	for (int i = 0; i < tam && posicao == -1; ++i)	//Buscando a posição do produto no vetor informado...
		if (!strcmp(prod_busc, vet_prod[i].nome))
			posicao = i;

	return posicao;		//Se o produto não foi encontrado, retorna -1
}

int numProd(Produto* estoque, const int* tam)
{
	int cont = 0;
	while (estoque[cont].nome[0] && cont < *tam)	//O número de produtos incrementa enquanto for menor que o tamanho do vetor...
		cont++;										//...e não achar um produto com nome vazio

	return cont;
}

int pot(int num, int exp)	//Função que calcula uma potência. Não queria usar cmath só por uma função...
{
	if (exp == 0)
		return 1;
	else
	{
		int resultado = num;
		for (int i = 0; i < exp - 1; i++)
			resultado *= num;
		return resultado;
	}
}