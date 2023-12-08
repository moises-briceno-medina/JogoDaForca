#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cctype> // Para a função toupper
#include <algorithm> // Para a função transform

using namespace std;

string palavra_secreta;
int tentativas = 5;
map<char, bool> chutou;
vector<char> chutes_errados;
vector<char> chutes_feitos;


bool letra_existe(char chute) {
	for (char letra : palavra_secreta){
		if (chute == letra) {
			return true;
		}
	}
	return false;
}

bool nao_acertou() {
	for (char letra : palavra_secreta) {
		if (!chutou[letra]) {
			return true;
		}
	}
	return false;
}

bool nao_enforcou() {
	return chutes_errados.size() < tentativas;
}

void imprimi_cabecalho() {
	cout << "*************************" << endl;
	cout << "***   JOGO DA FORCA   ***" << endl;
	cout << "*************************" << endl;
	cout << endl;
}

void imprime__chutes_errados() {
	cout << "Chutes errados: ";
	for (char letras : chutes_errados) {
		cout << letras << " ";
	}
	cout << endl;
}

void imprime_tentativas() {
	
	cout << "Voce tem mais " << tentativas - chutes_errados.size() << " tentativas " << endl;
}

void imprime_palavra() {
	for (char letra : palavra_secreta) {
		if (chutou[letra]) {
			cout << letra << " ";
		}
		else
		{
			cout << "_ ";
		}
	}
	cout << endl;
}

bool letra_ja_chutada(char letra) {
	for (char letra_chutes_feitos : chutes_feitos) {
		if (letra == letra_chutes_feitos) {
			return true;
		}
	}
	return false;
}


void chuta() {
	cout << "Seu chute: " << endl;
	char chute;
	cin >> chute;
	chute = toupper(chute);

	chutou[chute] = true;

	if (letra_ja_chutada(chute))
	{
		cout << "Voce ja chutou essa letra antes." << endl;
	}
	else
	{
		if (letra_existe(chute)) {
			cout << "voce acertou! seu chute esta na palavra" << endl;
		}
		else
		{
			cout << "voce errou! seu chute nao esta na palavra" << endl;
			chutes_errados.push_back(chute);
		}
	}
	chutes_feitos.push_back(chute);
	cout << endl;
}

vector<string> le_arquivo() {
	ifstream arquivo;
	arquivo.open("palavrasJogoForca.txt");

	if (arquivo.is_open()) {
		int quantidade_palavras;
		arquivo >> quantidade_palavras;


		vector<string> palavras_do_arquivo;

		for (int i = 0; i < quantidade_palavras; i++) {
			string palavra_lida;
			arquivo >> palavra_lida;
			palavras_do_arquivo.push_back(palavra_lida);
		}

		arquivo.close();
		return palavras_do_arquivo;
	}
	else {
		cout << "Nao foi possivel acessar o banco de palavras." << endl;
		exit(0);
	}
}

 void sorteia_palavra() {
	vector<string> palavras = le_arquivo();
	
	srand(time(NULL));
	int indice_sorteado = rand() % palavras.size();

	palavra_secreta = palavras[indice_sorteado];
}

 void salva_arquivo(vector<string> nova_lista){
	 ofstream arquivo;
	 arquivo.open("palavrasJogoForca.txt");
		 if (arquivo.is_open()) {
			 arquivo << nova_lista.size() << endl;

			 for (string palavra : nova_lista) {
				 arquivo << palavra << endl;
			 }
			 arquivo.close();
		 }
		 else
		 {
			 cout << "Não foi possivel acessar o banco de palavras." << endl;
			 exit(0);
		 }
 }

 bool ehPalavraComposta(string palavra_composta) {
	 for (char letra : palavra_composta) {
		 if (letra == ' ' || letra == '-') {
			 return true;
		 }
	 }
	 return false;
 }

 void add_palavra() {
	 bool palavra_adicionada = false;
	 cout << "Nao adicione palavras compostas ou com espaco!!!" << endl;
	 cout << "Digite a nova palavra: " << endl;
	 do
	 {
		 string nova_palavra;
		 cin >> nova_palavra;

		 if (ehPalavraComposta)
		 {
			 cout << "A palavra nao pode ser composta ou ter espaco" << endl;
			 cout << "Digite a nova palavra: " << endl;
		 }
		 else
		 {
			 // Convertendo toda a string para maiúsculas
			 transform(nova_palavra.begin(), nova_palavra.end(), nova_palavra.begin(), toupper);

			 vector<string> lista_palavras = le_arquivo();
			 lista_palavras.push_back(nova_palavra);

			 salva_arquivo(lista_palavras);
			 palavra_adicionada = true;
		 }

	 } while (palavra_adicionada == false);
 }

int main(){
		
	le_arquivo();
	sorteia_palavra();

	imprimi_cabecalho();

	while (nao_acertou() && nao_enforcou()) {
			
		imprime__chutes_errados();

		imprime_palavra();
		imprime_tentativas();
		

		chuta();
	}
		
	cout << "FIM DE JOGO!" << endl;
	cout << "A palavra secreta era: "<< palavra_secreta << endl;
	if (nao_acertou()){
		cout << "Voce perdeu! Tente novamente!" << endl;
	}
	else
	{
		cout << "Parabens! Voce acertou a palavra secreta!" << endl;
		cout << "Voce deseja adicionar uma nova palavra ao jogo? (S/N)"<< endl;
		char resposta;
		cin >> resposta;
		resposta = toupper(resposta);
			if (resposta == 'S') {
				add_palavra();
			}
	}
}