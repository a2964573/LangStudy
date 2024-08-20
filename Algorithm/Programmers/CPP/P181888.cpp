// 정수 리스트 num_list와 정수 n이 주어질 때, 
// num_list의 첫 번째 원소부터 마지막 원소까지 n개 간격으로 저장되어있는 원소들을 차례로 담은 리스트를 return하도록 solution 함수를 완성해주세요.

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer;
    answer.clear();

	int pos = 0;

	try {
        while(true) {
            answer.push_back(num_list.at(pos));
            pos += n;
        }
	} catch(const std::out_of_range& e) {
        // 아무것도 하지 않음
	}

    return answer;
}

