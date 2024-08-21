// 양의 정수 n이 매개변수로 주어질 때, 
// n이 홀수라면 n 이하의 홀수인 모든 양의 정수의 합을 return 하고 
// n이 짝수라면 n 이하의 짝수인 모든 양의 정수의 제곱의 합을 return 하는 solution 함수를 작성해 주세요.

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

