// ���� �迭 arr�� delete_list�� �ֽ��ϴ�. 
// arr�� ���� �� delete_list�� ���Ҹ� ��� �����ϰ� 
// ���� ���ҵ��� ������ arr�� �ִ� ������ ������ �迭�� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

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

