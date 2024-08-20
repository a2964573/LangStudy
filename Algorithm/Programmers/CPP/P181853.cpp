// 정수로 이루어진 리스트 num_list가 주어집니다. 
// num_list에서 가장 작은 5개의 수를 오름차순으로 담은 리스트를 return하도록 solution 함수를 완성해주세요.

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> num_list) {
    vector<int> answer;
    answer.clear();
    
    std::sort(num_list.begin(), num_list.end());
    
    int pos;
    for(pos = 0; pos < num_list.size(); pos++) {
	answer.push_back(num_list.at(pos));
        if(answer.size() >= 5) {
            break;
        }
    }
    
    return answer;
}

