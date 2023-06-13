#include <string>
#include <vector>

using namespace std;

size_t split(const string &txt, vector<string> &strs, char ch);

// Retorna verdadeiro se o caractere é uma letra
bool isLetter(char c);

// Verifica se 'c' é maiúscula e trasnforma em minuscula
/* Funciona com a ordem de ASCII, isso é pega a subtrai os valores de 'a' e 'A' e soma com o caractere maiúsculo, retornando o minúsculo correspondente */
char toLowercase(char c);

// Normatização de palavras
string normalizeWord(const string &word);