// ���� ?�� �� ������ ���� �������� �� ������ �ٿ��� �� ���� ��ȯ�մϴ�. ���� ��� ������ �����ϴ�.
// 12 ? 3 = 123
// 3 ? 12 = 312
// ���� ���� a�� b�� �־����� ��, a ? b�� 2 * a * b �� �� ū ���� return�ϴ� solution �Լ��� �ϼ��� �ּ���.
// ��, a ? b�� 2 * a * b�� ������ a ? b�� return �մϴ�.

#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int answer = 0;

	string str;
	str.append(std::to_string(a));
	str.append(std::to_string(b));

	answer = std::stoi(str);

	if(answer < (a << 1) * b) {
		answer = (a << 1 ) * b;
	}

    return answer;
}

