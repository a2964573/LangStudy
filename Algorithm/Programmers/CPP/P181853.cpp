// ������ �̷���� ����Ʈ num_list�� �־����ϴ�. 
// num_list���� ���� ���� 5���� ���� ������������ ���� ����Ʈ�� return�ϵ��� solution �Լ��� �ϼ����ּ���.

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

