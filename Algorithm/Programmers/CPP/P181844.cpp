// 정수 배열 arr과 delete_list가 있습니다. 
// arr의 원소 중 delete_list의 원소를 모두 삭제하고 
// 남은 원소들은 기존의 arr에 있던 순서를 유지한 배열을 return 하는 solution 함수를 작성해 주세요.

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<int> delete_list) {
    vector<int> answer;
	vector<bool> checked_list(arr.size());
	std::fill(checked_list.begin(), checked_list.end(), false);

	int pos;
	for(pos = 0; pos < arr.size(); pos++) {
		for(int del : delete_list) {
			if(del == arr[pos]) {
				checked_list[pos] = true;
				break;
			}
		}
	}

	for(pos = 0; pos < checked_list.size(); pos++) {
		if(checked_list[pos]) {
			continue;
		}

		answer.push_back(arr[pos]);
	}

    return answer;
}

