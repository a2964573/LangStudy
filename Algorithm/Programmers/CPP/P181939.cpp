// 연산 ?는 두 정수에 대한 연산으로 두 정수를 붙여서 쓴 값을 반환합니다. 예를 들면 다음과 같습니다.
// 12 ? 3 = 123
// 3 ? 12 = 312
// 양의 정수 a와 b가 주어졌을 때, a ? b와 b ? a 중 더 큰 값을 return 하는 solution 함수를 완성해 주세요.
// 단, a ? b와 b ? a가 같다면 a ? b를 return 합니다.

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

