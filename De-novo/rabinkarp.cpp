#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>
using namespace std;

#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

int d = 4;          // ����
int q = 10007;      // ��ⷯ ����� ���� �Ҽ�

// ���ڸ� ���ڷ� ��ȯ
int charToValue(char c) {
    switch (c) {
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
    default: return -1; // �߸��� �Է� ó��
    }
}

// �ؽð� ���
int gethash(const string& read) {
    int hash = 0;
    for (char c : read) {
        hash = (d * hash + charToValue(c)) % q;
    }
    return hash;
}

vector<string> rb_createReadArray() {
    ifstream inputFile("reads.txt");
    vector<string> lines;
    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}

void execute_RabinKarp(int pattern) {
    
    vector<string> lines = rb_createReadArray();
    clock_t start = clock();

    // �ؽ� ���̺� ����
    vector<tuple<int, string, int>> readNhash; // read, read�� ���λ� �ؽð�, read�� ���̻� �ؽð� ����� tuple �迭
    for (int i = 0; i < lines.size(); i++) {
        readNhash.push_back({
            gethash(lines[i].substr(0, pattern)), // read ���λ� �ؽð�
            lines[i], // read
            gethash(lines[i].substr(lines[i].size() - pattern, pattern)) // read ���̻� �ؽð�
            });
    }

    // ù ��° read�� result�� �ʱ�ȭ
    string result = get<1>(readNhash[0]);
    int resultPreHash = get<0>(readNhash[0]);
    int resultSufHash = get<2>(readNhash[0]);

    bool endcheck; // ���� ���࿡�� result�� ����Ǿ����� Ȯ���ϴ� ����
    while (true) {
        endcheck = false;
        for (auto it = readNhash.begin() + 1; it != readNhash.end();) { // �ؽ����̺� �����ִ� ��� read Ž��
            if (resultPreHash == get<2>(*it)) { // result�� ���λ� �ؽð��� read�� ���̻� �ؽð� ������ Ȯ�� (result �տ� read�� �ٴ� ���)
                if (result.substr(0, pattern) == get<1>(*it).substr(get<1>(*it).size() - pattern, pattern)) { // ������ ������ Ȯ��
                    result = get<1>(*it).substr(0, get<1>(*it).size() - pattern) + result; // result �տ� read ���̱�
                    resultPreHash = get<0>(*it); // result �ؽð� ������Ʈ
                    it = readNhash.erase(it); // ���� ��� ���� �� �ݺ��� ����
                    endcheck = true;
                    continue; // ���� �ݺ��ڷ� �̵�
                }
            }
            else if (resultSufHash == get<0>(*it)) { // result�� ���̻� �ؽð��� read�� ���λ� �ؽð� ������ Ȯ�� (result �ڿ� read�� �ٴ� ���)
                if (result.substr(result.size() - pattern, pattern) == get<1>(*it).substr(0, pattern)) { // ������ ������ Ȯ��
                    result = result + get<1>(*it).substr(pattern); // result �ڿ� read ���̱�
                    resultSufHash = get<2>(*it); // result �ؽð� ������Ʈ
                    it = readNhash.erase(it); // ���� ��� ���� �� �ݺ��� ����
                    endcheck = true;
                    continue; // ���� �ݺ��ڷ� �̵�
                }
            }
            ++it; // ������ �������� ������ ���� ��ҷ� �̵�
        }

        if (!endcheck) { // endcheck==false��� ���� ���࿡�� result�� ������� �ʾ����Ƿ� ���̻� �߰��� read�� ���ٴ� ���� �ǹ�
            break;
        }
    }

    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Execution Time: " << duration << " seconds" << endl;

    // ������ ���ڿ��� result.txt�� ����
    ofstream resultFile("result.txt");
    resultFile << result;
    resultFile.close();
}