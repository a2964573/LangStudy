// ���� n�� k�� �־����� ��, 
// 1 �̻� n������ ���� �߿��� k�� ����� ������������ ������ �迭�� return �ϴ� solution �Լ��� �ϼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int k) {
    vector<int> answer;
    answer.clear();

    int pos;
    for(pos = k; pos <= n; pos += k) {
        answer.push_back(pos);
    }

    return answer;
}

