// ���� ?�� �� ������ ���� �������� �� ������ �ٿ��� �� ���� ��ȯ�մϴ�. ���� ��� ������ �����ϴ�.
// 12 ? 3 = 123
// 3 ? 12 = 312
// ���� ���� a�� b�� �־����� ��, a ? b�� b ? a �� �� ū ���� return �ϴ� solution �Լ��� �ϼ��� �ּ���.
// ��, a ? b�� b ? a�� ���ٸ� a ? b�� return �մϴ�.

#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int answer = 0;

	string str_a = std::to_string(a); 
	string str_b = std::to_string(b); 

	answer = max(std::stoi(str_a + str_b), std::stoi(str_b + str_a));

    return answer;
}

