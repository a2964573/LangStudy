// ���̰� ���� ���ڿ� �迭 my_strings�� ������ ���� �迭 parts�� �Ű������� �־����ϴ�. 
// parts[i]�� [s, e] ���·�, my_string[i]�� �ε��� s���� �ε��� e������ �κ� ���ڿ��� �ǹ��մϴ�. 
// �� my_strings�� ������ parts�� �ش��ϴ� �κ� ���ڿ��� ������� �̾� ���� ���ڿ��� return �ϴ� solution �Լ��� �ۼ��� �ּ���.

#include <string>
#include <vector>

using namespace std;

string solution(vector<string> my_strings, vector<vector<int>> parts) {
    string answer = "";

    int pos;
    int limit;
    if(parts.size() > my_strings.size()) {
        limit = my_strings.size();
    } else {
        limit = parts.size();
    }

    for(pos = 0; pos < limit; pos++) {
        answer.insert(answer.length(), my_strings[pos].substr(parts[pos][0], parts[pos][1] - parts[pos][0] + 1));
    }

    return answer;
}

