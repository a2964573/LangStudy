// ���� n�� ���ڿ� control�� �־����ϴ�. control�� "w", "a", "s", "d"�� 4���� ���ڷ� �̷���� ������, control�� �տ������� ������� ���ڿ� ���� n�� ���� �ٲߴϴ�.
// "w" : n�� 1 Ŀ���ϴ�.
// "s" : n�� 1 �۾����ϴ�.
// "d" : n�� 10 Ŀ���ϴ�.
// "a" : n�� 10 �۾����ϴ�.
// �� ��Ģ�� ���� n�� �ٲ��� �� ���� �������� ������ n�� ���� return �ϴ� solution �Լ��� �ϼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

int solution(int n, string control) {
    int answer = 0;

    int pos;
    for(pos = 0; pos < control.length(); pos++) {
        switch(control.at(pos)) {
            case 'w':
                n++;
            break;
            case 's':
                n--;
            break;
            case 'd':
                n += 10;
            break;
            case 'a':
                n -= 10;
            break;
        }
    }

    answer = n;

    return answer;
}

