// ���ڿ� my_string�� ���� �迭 index_list�� �Ű������� �־����ϴ�. 
// my_string�� index_list�� ���ҵ鿡 �ش��ϴ� �ε����� ���ڵ��� ������� �̾� ���� ���ڿ��� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

string solution(string my_string, vector<int> index_list) {
    string answer = "";

    int pos;
    for(pos = 0; pos < index_list.size(); pos++) {
        answer.push_back(my_string.at(index_list.at(pos)));
    }

    return answer;
}

