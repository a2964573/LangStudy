// � ���ڿ��� ���ؼ� ���̻�� Ư�� �ε������� �����ϴ� ���ڿ��� �ǹ��մϴ�. 
// ���� ���, "banana"�� ��� ���̻�� "banana", "anana", "nana", "ana", "na", "a"�Դϴ�.
// ���ڿ� my_string�� is_suffix�� �־��� ��, 
// is_suffix�� my_string�� ���̻��� 1��, �ƴϸ� 0�� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_suffix) {
    int answer = 0;

    int start = 0;
    while(true) {
        if(my_string.length() - start < is_suffix.length()) {
            break;
        }

        if(my_string.compare(start, my_string.length() - start, is_suffix) == 0) {
            answer = 1;
            break;
        }

        start++;
    }

    return answer;
}
  
