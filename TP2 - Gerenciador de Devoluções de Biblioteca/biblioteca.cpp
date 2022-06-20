#include "biblioteca.h"
#define MULTA 0.80f


istream& operator>>(istream& is, Data& temp_d)	//Defini��o de como o cin deve ler o tipo "Data"
{
	is >> temp_d.dia;
	is.get();
	is >> temp_d.mes;
	is.get();
	is >> temp_d.ano;

	return is; //L� no padr�o dd/mm/aaaa
}
ostream& operator<<(ostream& os, Data& temp_d)	//Defini��o de como o cout deve exibir o tipo "Data"
{
	cout.fill('0');

	cout.width(2);
	os << temp_d.dia;
	os << "/";
	cout.width(2);
	os << temp_d.mes;
	os << "/";
	os << temp_d.ano;

	return os;	//Exibe no padr�o dd/mm/aaaa
}
int operator-(Data& temp_d1, Data& temp_d2)	//Defini��o de como a subtra��o de dois tipo "Data" s�o feitos. Considera-se que s�o do mesmo ano
{
	int diaMes[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	//N�mero de dias em cada m�s. Considera-se o ano como n�o-bissexto
	int totalDias = 0;	//Total de dias entre as datas 

	for (int i = temp_d2.mes - 1; i < temp_d1.mes - 1; i++)
		totalDias += diaMes[i];

	return (totalDias - temp_d2.dia) + temp_d1.dia;	//	Retorna a quantidades de dias no intervalo apresentado. 
}

float calcMultaTotal(emprestimo temp_emp[], int tam_vet, Data dat_dev)
{
	float multaApurada = 0.0f;	//Total de multa apurado
	for (int i = 0; i < tam_vet; i++)
		multaApurada += calcAtraso(&(temp_emp[i].dataEmprestimo), &dat_dev) * MULTA;	//Acumula as multas do dia

	return multaApurada;
}
void dadosEmprestimo(emprestimo* temp_emp, Data* temp_dat)
{
	cout << fixed;	//Fiz o mesmo dentro da fun��o para garantir, ser�o exibidos dois n�meros ap�s a v�rgula
	cout.precision(2);
	cout.fill(' ');	//Espa�os vazios exibir�o " "

	float multa = calcAtraso(&temp_emp->dataEmprestimo, temp_dat) * MULTA;	//Guarda o valor da multa para o par�metro

	//Exibe os dados em forma de lista
	cout << left;	cout.width(11); cout << temp_emp->idAluno;
					cout.width(6); cout << temp_emp->idLivro;
					cout.width(11); cout << temp_emp->dataEmprestimo;
					cout.width(4); cout << " ->" " R$" << (multa);
					cout << endl;
}
void desenhaTraco(int temp_i)
{
	for (int c = 1; c <= temp_i; c++)	//Desenha um tra�o do tamanho passado no par�metro
		cout << "-";
}

int calcAtraso(Data* dat_emp, Data* dat_devo)
{
	int dif_datas = *dat_devo - *dat_emp, atraso = 0;	//A diferen�a das datas e n�mero de dias de atraso
	for (int i = 0; dif_datas > 3 && i < dif_datas - 3; i++)	//S� incrementa o n�mero de dias de atraso se a diferen�a for maior
		atraso++;												//que 3 dias.

	return atraso;
}