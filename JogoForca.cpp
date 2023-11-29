#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

const string PALAVRA_SECRETA = "MELANCIA";
map<char, bool> chutou;
vector<char> chutes_errados;


bool letra_existe(char chute) {
	for (char letra : PALAVRA_SECRETA){
		if (chute == letra) {
			return true;
		}
	}
	return false;
}

bool nao_acertou() {
	for (char letra : PALAVRA_SECRETA) {
		if (!chutou[letra]) {
			return true;
		}
	}
	return false;
}

bool nao_enforcou() {
	return chutes_errados.size() < 5;
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

void imprime_palavra() {
	for (char letra : PALAVRA_SECRETA) {
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

void chuta() {
	cout << "Seu chute: " << endl;
	char chute;
	cin >> chute;

	chutou[chute] = true;

	if (letra_existe(chute)) {
		cout << "voce acertou! seu chute esta na palavra" << endl;
	}
	else
	{
		cout << "voce errou! seu chute nao esta na palavra" << endl;
		chutes_errados.push_back(chute);
	}
	cout << endl;
}

int main()
{
		imprimi_cabecalho();

		while (nao_acertou() && nao_enforcou()) {
			
			imprime__chutes_errados();

			imprime_palavra();

			chuta();
		}
		
		cout << "FIM DE JOGO!" << endl;
		cout << "A palavra secreta era: "<< PALAVRA_SECRETA << endl;
		if (nao_acertou()){
			cout << "Voce perdeu! Tente novamente!" << endl;
		}
		else
		{
			cout << "Parabens! Voce acertou a palavra secreta!" << endl;
		}

}
