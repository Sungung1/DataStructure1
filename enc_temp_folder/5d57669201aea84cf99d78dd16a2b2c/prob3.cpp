#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// 설명에서 길이 3 이상의 단어 추출
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

    cout << "단어를 입력하세요: ";
    cin >> input;

    while (getline(infile, line)) {
        stringstream ss(line);
        string word, def;
        getline(ss, word, '\t');
        getline(ss, def);

        // 입력된 단어가 일치하면 출력
        if (word == input) {
            cout << word << ": " << def << endl;
            vector<string> relatedWords = extractWords(def);
            vector<string> printedWords = {word}; // 출력된 단어를 기록

            // 관련된 단어들을 사전에서 검색
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
                            printedWords.push_back(searchWord); // 출력한 단어 기록
                            break; // 단어를 찾았으면 더 이상 반복할 필요 없음
                        }
                    }
                    searchFile.close();
                }
            }
            break; // 처음 입력된 단어를 찾았으니 루프 종료
        }
    }
    
    infile.close();
    return 0;
}
