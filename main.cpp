#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

int main() {
    map<string, map<string, int>> indexedWords;

    // BEGIN - Mocked data
    map<string, int> apartamentoIndexes;
    apartamentoIndexes["d1.txt"] = 1;
    apartamentoIndexes["d3.txt"] = 1;
    indexedWords["apartamento"] = apartamentoIndexes;

    map<string, int> casaIndexes;
    casaIndexes["d1.txt"] = 2;
    casaIndexes["d2.txt"] = 1;
    indexedWords["casa"] = casaIndexes;

    map<string, int> emIndexes;
    emIndexes["d2.txt"] = 1;
    indexedWords["em"] = emIndexes;

    map<string, int> entrarIndexes;
    entrarIndexes["d2.txt"] = 1;
    indexedWords["entrar"] = entrarIndexes;

    map<string, int> estaIndexes;
    estaIndexes["d3.txt"] = 1;
    indexedWords["esta"] = estaIndexes;

    map<string, int> ninguemIndexes;
    ninguemIndexes["d1.txt"] = 2;
    ninguemIndexes["d2.txt"] = 1;
    ninguemIndexes["d3.txt"] = 1;
    indexedWords["ninguem"] = ninguemIndexes;

    map<string, int> todosIndexes;
    todosIndexes["d2.txt"] = 2;
    todosIndexes["d3.txt"] = 1;
    indexedWords["todos"] = todosIndexes;

    map<string, int> noIndexes;
    noIndexes["d3.txt"] = 1;
    indexedWords["no"] = noIndexes;

    map<string, int> poremIndexes;
    poremIndexes["d1.txt"] = 1;
    indexedWords["porem"] = poremIndexes;

    map<string, int> quemIndexes;
    quemIndexes["d1.txt"] = 1;
    quemIndexes["d2.txt"] = 2;
    quemIndexes["d3.txt"] = 1;
    indexedWords["quem"] = quemIndexes;

    map<string, int> querIndexes;
    querIndexes["d1.txt"] = 2;
    querIndexes["d2.txt"] = 1;
    indexedWords["quer"] = querIndexes;

    map<string, int> sairamIndexes;
    sairamIndexes["d2.txt"] = 1;
    sairamIndexes["d3.txt"] = 1;
    indexedWords["sairam"] = sairamIndexes;

    map<string, int> tambemIndexes;
    tambemIndexes["d1.txt"] = 1;
    indexedWords["tambem"] = tambemIndexes;
    // END - Mocked data

    // BEGIN - Part 3: Recovery
    string search;
    cout << "Digite sua consulta: ";
    getline(cin, search);

    vector<string> splitSearch;
    split(search, splitSearch, ' ');

    map<string, vector<int>> ocurrencesByFile;

    for (int i = 0; i < splitSearch.size(); i++) {
        string currentWord = splitSearch[i];
        map<string, int> currentWordIndexes = indexedWords[currentWord];

        map<string, int>::iterator currentWordIndexesIterator = currentWordIndexes.begin();
        while (currentWordIndexesIterator != currentWordIndexes.end()) {
            string currentFileAssociated = currentWordIndexesIterator->first;
            int currentWordCount = currentWordIndexesIterator->second;

            bool isFileOnOutput = ocurrencesByFile.find(currentFileAssociated) != ocurrencesByFile.end();
            if (isFileOnOutput) {
                vector<int> appearencesOnCurrentFile = ocurrencesByFile[currentFileAssociated];
                appearencesOnCurrentFile.push_back(currentWordCount);
                ocurrencesByFile[currentFileAssociated] = appearencesOnCurrentFile;
            } else {
                vector<int> appearencesOnCurrentFile{currentWordCount};
                ocurrencesByFile[currentFileAssociated] = appearencesOnCurrentFile;
            }

            currentWordIndexesIterator++;
        }
    }

    map<int, vector<string>> resultingFilesByScore;

    map<string, vector<int>>::iterator ocurrencesByFileIterator = ocurrencesByFile.begin();
    while (ocurrencesByFileIterator != ocurrencesByFile.end()) {
        string currentFileAssociated = ocurrencesByFileIterator->first;
        vector<int> currentOcurrencesList = ocurrencesByFileIterator->second;

        int currentMatchingWordsSize = currentOcurrencesList.size();
        int wordsFromSearchSize = splitSearch.size();
        bool hasAllWordsFromSearch = currentMatchingWordsSize == wordsFromSearchSize;
        if (hasAllWordsFromSearch) {
            int currentFileScore = 0;

            for (int i = 0; i < currentMatchingWordsSize; i++) {
                currentFileScore += currentOcurrencesList[i];
            }

            bool isPositionBeingUsed = resultingFilesByScore.find(currentFileScore) != resultingFilesByScore.end();
            if (isPositionBeingUsed) {
                vector<string> tiedValuesForScore = resultingFilesByScore[currentFileScore];
                tiedValuesForScore.push_back(currentFileAssociated);
                resultingFilesByScore[currentFileScore] = tiedValuesForScore;
            } else {
                vector<string> filesListForCurrentScore{currentFileAssociated};
                resultingFilesByScore[currentFileScore] = filesListForCurrentScore;
            }
        }

        ocurrencesByFileIterator++;
    }

    cout << "Resultado da consulta:" << endl;
    map<int, vector<string>>::reverse_iterator resultingFilesByScoreReverseIterator = resultingFilesByScore.rbegin();
    while (resultingFilesByScoreReverseIterator != resultingFilesByScore.rend()) {
        int currentScore = resultingFilesByScoreReverseIterator->first;
        vector<string> currentFilesList = resultingFilesByScoreReverseIterator->second;

        bool isScoreTied = currentFilesList.size() > 1;

        if (isScoreTied) {
            sort(currentFilesList.begin(), currentFilesList.end());
        }

        for (int j = 0; j < currentFilesList.size(); j++) {
            string currentFile = currentFilesList[j];
            cout << "Arquivo '" << currentFile << "' - " << currentScore << " ocorrências das palavras da consulta." << (isScoreTied ? "[EMPATADO]" : "") << endl;
        }

        resultingFilesByScoreReverseIterator++;
    }
    // END - Part 3: Recovery

    return 0;
}