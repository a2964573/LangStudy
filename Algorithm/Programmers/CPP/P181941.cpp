// ���ڵ��� ����ִ� �迭 arr�� �־����ϴ�. 
// arr�� ���ҵ��� ������� �̾� ���� ���ڿ��� return �ϴ� solution�Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

string solution(vector<string> arr) {
    string answer = "";

	for(string ele : arr) {
		answer.append(ele);
	}

    return answer;
}

