// ������ ��� ����Ʈ num_list�� �־����ϴ�. 
// num_list�� Ȧ���� ������� �̾� ���� ���� ¦���� ������� �̾� ���� ���� ���� return�ϵ��� solution �Լ��� �ϼ����ּ���.

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int getDigit(vector<int> arr)
{
    int digit = 1;
    int pos;
    for(pos = 1; pos < arr.size(); pos++) {
        digit *= 10;
    }

    return digit;
}

int solution(vector<int> num_list) {
    int answer = 0;
    int digit  = 0;

    vector<vector<int>> arr(2);

    for(int num : num_list) {
        if(num % 2 == 0) {
            arr[0].push_back(num);
        } else {
            arr[1].push_back(num);
        }
    }

    for(const auto& list : arr) {
        digit = getDigit(list);
        for(int num : list) {
            answer += num * digit;
            digit /= 10;
        }
    }

    return answer;
}

