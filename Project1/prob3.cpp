#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// ������ ���� 3 �̻��� �ܾ� ����
vector<string> extractWords(const string& desc) {
    vector<string> words;
    stringstream ss(desc);
    string word;

    while (ss >> word) {
        if (word.length() >= 3) words.push_back(word);
    }
    return words;
}

int main() {
    ifstream infile("shuffled_dict.txt");
    string line, input;

    cout << "�ܾ �Է��ϼ���: ";
    cin >> input;

    while (getline(infile, line)) {
        stringstream ss(line);
        string word, def;
        getline(ss, word, '\t');
        getline(ss, def);

        // �Էµ� �ܾ ��ġ�ϸ� ���
        if (word == input) {
            cout << word << ": " << def << endl;
            vector<string> relatedWords = extractWords(def);
            vector<string> printedWords = {word}; // ��µ� �ܾ ���

            // ���õ� �ܾ� ���� �˻�
            for (const auto& rWord : relatedWords) {
                if (find(printedWords.begin(), printedWords.end(), rWord) == printedWords.end()) {
                    ifstream searchFile("shuffled_dict.txt");
                    string searchLine, searchDef;

                    while (getline(searchFile, searchLine)) {
                        stringstream searchSS(searchLine);
                        string searchWord;
                        getline(searchSS, searchWord, '\t');
                        getline(searchSS, searchDef);

                        if (rWord == searchWord) {
                            cout << searchWord << ": " << searchDef << endl;
                            printedWords.push_back(searchWord); // ����� �ܾ� ���
                            break;
                        }
                    }
                    searchFile.close();
                }
            }
            break; //���� ����
        }
    }
    
    infile.close();
    return 0;
}
