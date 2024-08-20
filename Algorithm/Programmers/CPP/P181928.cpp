// 정수가 담긴 리스트 num_list가 주어집니다. 
// num_list의 홀수만 순서대로 이어 붙인 수와 짝수만 순서대로 이어 붙인 수의 합을 return하도록 solution 함수를 완성해주세요.

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

