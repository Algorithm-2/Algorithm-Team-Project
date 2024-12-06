#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// LPS(Longest Prefix Suffix) �迭 ��� �Լ�
void r_computeLPSArray(const string& pattern, int M, vector<int>& lps) {
    int length = 0; // ���� ���λ�� ���̻��� ����
    lps[0] = 0; // ù ��° ���� �׻� 0
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[length]) { // ������ ���ڰ� ��ġ�ϸ�
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1]; // ���� ��ġ ���̸� ���
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// findOverlap �Լ� ����: LPS �迭�� �Ű������� �޾� ���
int r_findOverlap(const string& text, const string& pattern, int max_length, const vector<int>& lps) {
    int N = text.size();
    int M = pattern.size();

    int i = N - max_length; // �ؽ�Ʈ�� �� ���� ��ġ
    int j = 0; // ������ �� ��ġ

    while (i < N) {
        if (text[i] == pattern[j]) { // ���ڰ� ��ġ�ϸ�
            i++;
            j++;
        }

        if (j == max_length) { // �ִ� ��ħ�� �߰ߵǸ� ��ȯ
            return max_length;
        }
        else if (i < N && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; // LPS ���� ����� �̵�
            }
            else {
                i++;
            }
        }
    }
    return j; // ��ħ ���� ��ȯ
}

// ���� �Լ����� LPS �迭�� �̸� ���
void r_kmpMerge(int pattern_length) {
    ifstream inputFile("reads.txt");
    if (!inputFile) {
        cerr << "reads.txt ���� ���� ����" << endl;
        return;
    }

    vector<string> reads;
    string line;
    while (getline(inputFile, line)) {
        reads.push_back(line); // Read �����͸� ���Ϳ� ����
    }
    inputFile.close();

    // LPS �迭 �̸� ��� (��ħ ���� ����)
    vector<int> lps(pattern_length, 0);
    r_computeLPSArray(reads[0].substr(0, pattern_length), pattern_length, lps);

    string result = reads[0]; // ù ��° read�� ����� �ʱ�ȭ
    reads.erase(reads.begin()); // ù ��° read ����

    while (!reads.empty()) { // ��� read�� ���յ� ������ �ݺ�
        bool merged = false;

        for (auto it = reads.begin(); it != reads.end();) {
            int overlap = r_findOverlap(result, *it, pattern_length, lps);

            if (overlap == pattern_length) { // �ڷ� ����
                result += it->substr(overlap);
                it = reads.erase(it); // ���յ� read ����
                merged = true;
                break;
            }

            overlap = r_findOverlap(*it, result, pattern_length, lps);
            if (overlap == pattern_length) { // ������ ����
                result = it->substr(0, it->size() - overlap) + result;
                it = reads.erase(it); // ���յ� read ����
                merged = true;
                break;
            }

            ++it; // ���� read�� �̵�
        }
        if (!merged) {
            break;
        }
    }

    ofstream resultFile("result.txt");
    resultFile << result;
    resultFile.close();
}

void r_execute_KMP(int pattern_length) {
    clock_t start = clock();
    r_kmpMerge(pattern_length);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "���� �ð�: " << elapsed << "s" << std::endl;
    cout << "result.txt ���� �Ϸ�" << endl;
}