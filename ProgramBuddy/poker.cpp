
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// 将牌面转换为数值
int convertToValue(string card)
{
    if (card == "A")
        return 1;
    else if (card == "J")
        return 11;
    else if (card == "Q")
        return 12;
    else if (card == "K")
        return 13;
    else
        return stoi(card); // 将字符串转换为整数
}

bool isStraight(vector<int> &values)
{
    // 对数值进行排序
    sort(values.begin(), values.end());

    // 检查是否是 Q,K,A
    if (values[0] == 1 && values[1] == 12 && values[2] == 13)
    {
        return true;
    }

    // 检查是否是 K,A,2
    if (values[0] == 1 && values[1] == 2 && values[2] == 13)
    {
        return true;
    }

    // 判断是否连续
    return (values[1] == values[0] + 1 && values[2] == values[1] + 1);
}

int main()
{
    string card1, card2, card3;

    // 读入三张牌
    cin >> card1;
    cin >> card2;
    cin >> card3;

    // 转换为数值
    vector<int> values;
    values.push_back(convertToValue(card1));
    values.push_back(convertToValue(card2));
    values.push_back(convertToValue(card3));

    // 判断并输出结果
    if (isStraight(values))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}