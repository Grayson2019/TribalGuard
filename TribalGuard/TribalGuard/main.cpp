#include<iostream>

using namespace std;
// 居民数n，仇敌关系数m，部落卫队最大人数maxNum，当前部落卫队人数nowNum，有仇敌关系的x和y
int n, m, maxNum, nowNum, x, y;
// 关系表relationTable，当前部落卫队人数情况soldiersNow，最终部落卫队人数情况soldiersFinal
int relationalTable[100][100],soldiersNow[100],soldiersFinal[100],f[100];

// 回溯法递归函数
void backtracking(int depth)
{
    // 当递归到第n+1层时
    if (depth == n+1)
    {
        if (nowNum > maxNum) // 当前情况的部落卫队人数大于已知的部落卫队人数
        {
            maxNum = nowNum;
            for (int i = 1; i <= n; i++)
                soldiersFinal[i] = soldiersNow[i];
        }
        return;
    }
    // 最优化剪枝，如果当前选好的人加上还没有搜索到的人还小于或等于当前已知的最大值的话，就直接退出，没必要继续搜索了
    if (nowNum + n- depth + 1 <= maxNum) return;
    
    if (!f[depth])
    {
        soldiersNow[depth] = 1;
        nowNum++;
        for (int i = 1; i <= n; i++)//选了一个人，那就把他所有的仇人的f[i]+1
            if (relationalTable[depth][i] == 1)
                f[i]++;//巧妙之处！！！
        backtracking(depth+1);
        // 回溯一步
        for (int i = 1; i <= n; i++)
            if (relationalTable[depth][i] == 1)
                f[i]--;
        nowNum--;
    }
    // 这是当前的人不选的情况，直接搜索下一层
    soldiersNow[depth] = 0;
    backtracking(depth+1);
}

int main()
{
    // 输入居民数n和仇敌关系数m
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        // 存储仇敌关系
        relationalTable[x][y]=1;
        relationalTable[y][x]=1;
    }
    // 回溯法递归函数
    backtracking(1);
    cout << maxNum << "\n";
    for (int i = 1; i <= n; i++)
        cout << soldiersFinal[i] << " ";
    return 0;
}
