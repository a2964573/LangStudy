// ���� ���� n�� �Ű������� �־��� ��, 
// n�� Ȧ����� n ������ Ȧ���� ��� ���� ������ ���� return �ϰ� 
// n�� ¦����� n ������ ¦���� ��� ���� ������ ������ ���� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
	int num;

	if(n % 2 == 1) {
		for(num = 1; num <= n; num += 2) {
			answer += num;
		}
	} else {
		for(num = 2; num <= n; num += 2) {
			answer += num * num;
		}
	}

    return answer;
}

