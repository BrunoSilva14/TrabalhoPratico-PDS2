#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
using namespace std;

int AMOUNT_FILES = 30;

int main()
{
    // BEGIN - Part 1: Collection
    map<string, string> indexedFiles;
    for (int i = 1; i <= AMOUNT_FILES; i++)
    {
        char currentWord[100];
        FILE* file;
        string fileName = "d" + to_string(i);
        fileName = fileName + ".txt";
        string filePath="./documentos/" + fileName;
        file = fopen(filePath.c_str(), "r+");
        if (file == NULL)
        {
            cout << "Could not open this file" << endl;
            continue;
        }
        string fileContent = "";
        while (fscanf(file, "%s", currentWord) != EOF)
        {
            fileContent= fileContent + currentWord + " ";
        }
        indexedFiles[fileName] = fileContent;
    }
    // END - Part 1: Collection
    
    // BEGIN - Part 2: Indexing
    map<string, map<string, int>> indexedWords;

    for (auto entry : indexedFiles) {
        string file = entry.first;
        string words = entry.second;

        vector<string> splitWords;
        split(words, splitWords, ' ');

        for(auto word : splitWords){
            string normalizedWord = normalizeWord(word);
            indexedWords[normalizedWord][file]++;
        }
    }
    // END - Part 2: Indexing

    // BEGIN - Part 3: Recovery
    string search;
    cout << "Digite sua consulta: ";
    getline(cin, search);

    vector<string> splitSearch;
    split(search, splitSearch, ' ');

    map<string, vector<int>> ocurrencesByFile;

    for (int i = 0; i < splitSearch.size(); i++) {
        string currentNormalizedWord = normalizeWord(splitSearch[i]);
        map<string, int> currentWordIndexes = indexedWords[currentNormalizedWord];

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