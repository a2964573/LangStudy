// ���� ����Ʈ num_list�� ���� n�� �־��� ��, 
// num_list�� ù ��° ���Һ��� ������ ���ұ��� n�� �������� ����Ǿ��ִ� ���ҵ��� ���ʷ� ���� ����Ʈ�� return�ϵ��� solution �Լ��� �ϼ����ּ���.

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer;
    answer.clear();

	int pos = 0;

	try {
        while(true) {
            answer.push_back(num_list.at(pos));
            pos += n;
        }
	} catch(const std::out_of_range& e) {
        // �ƹ��͵� ���� ����
	}

    return answer;
}

