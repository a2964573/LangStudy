// ������ ��� ����Ʈ num_list�� �־��� ��, 
// ��� ���ҵ��� ���� ��� ���ҵ��� ���� �������� ������ 1�� ũ�� 0�� return�ϵ��� solution �Լ��� �ϼ����ּ���.

#include <string>
#include <vector>

using namespace std;

int solution(vector<int> num_list) {
	int answer = 0;
	int square = 0;
	int mulsum = 1;

	int pos;
	for(pos = 0; pos < num_list.size(); pos++) {
		square += num_list[pos];
		mulsum *= num_list[pos];
	}
	square *= square;

	if(mulsum < square) {
		answer = 1;
	}

    return answer;
}

