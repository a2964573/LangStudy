// 정수가 담긴 리스트 num_list가 주어질 때, 
// 모든 원소들의 곱이 모든 원소들의 합의 제곱보다 작으면 1을 크면 0을 return하도록 solution 함수를 완성해주세요.

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

