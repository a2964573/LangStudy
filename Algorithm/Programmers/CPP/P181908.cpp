// 어떤 문자열에 대해서 접미사는 특정 인덱스부터 시작하는 문자열을 의미합니다. 
// 예를 들어, "banana"의 모든 접미사는 "banana", "anana", "nana", "ana", "na", "a"입니다.
// 문자열 my_string과 is_suffix가 주어질 때, 
// is_suffix가 my_string의 접미사라면 1을, 아니면 0을 return 하는 solution 함수를 작성해 주세요.

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
  
