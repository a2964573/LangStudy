// � ���ڿ��� ���ؼ� ���λ�� Ư�� �ε��������� ���ڿ��� �ǹ��մϴ�. 
// ���� ���, "banana"�� ��� ���λ�� "b", "ba", "ban", "bana", "banan", "banana"�Դϴ�.
// ���ڿ� my_string�� is_prefix�� �־��� ��, 
// is_prefix�� my_string�� ���λ��� 1��, 
// �ƴϸ� 0�� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_prefix) {
    int answer = 0;

    if(my_string.compare(0, is_prefix.length(), is_prefix) == 0) {
        answer = 1;
    }

    return answer;
}

