#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

struct Request
{
    int id;       // 请求编号
    int people;   // 人数
    int arrive;   // 到达时间
    int duration; // 就餐时长
};

struct Table
{
    int id;                  // 餐桌编号
    vector<Request> ongoing; // 当前正在就餐的请求
};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<Table> tables(N);
    for (int i = 0; i < N; ++i)
    {
        tables[i] = {i + 1, {}}; // 初始化每张餐桌: 编号从1开始，无请求
    }

    vector<Request> requests(M);
    for (int i = 0; i < M; ++i)
    {
        int P, S, L;
        cin >> P >> S >> L;
        requests[i] = {i, P, S, L};
    }

    // 按到达时间排序，若时间相同按人数排序，人数相同按输入顺序排序
    sort(requests.begin(), requests.end(), [](const Request &a, const Request &b)
         {
        if (a.arrive != b.arrive) return a.arrive < b.arrive;
        if (a.people != b.people) return a.people > b.people;
        return a.id < b.id; });

    vector<int> tableUsage(N, 0); // 每张餐桌的累计人数
    queue<Request> waitingQueue;  // 等待队列

    for (const auto &req : requests)
    {
        // 处理当前时间点之前完成的请求
        for (auto &table : tables)
        {
            // 遍历餐桌上的请求，找到已完成的请求
            auto it = remove_if(table.ongoing.begin(), table.ongoing.end(),
                                [&](const Request &r)
                                {
                                    if (r.arrive + r.duration <= req.arrive)
                                    {
                                        // 减去已完成请求的人数
                                        tableUsage[table.id - 1] -= r.people;
                                        return true; // 标记为删除
                                    }
                                    return false; // 保留尚未完成的请求
                                });

            // 删除已完成的请求
            table.ongoing.erase(it, table.ongoing.end());
        }

        // 将当前请求放入等待队列
        waitingQueue.push(req);

        while (!waitingQueue.empty())
        {
            Request current = waitingQueue.front();
            bool assigned = false;

            // 查找可用餐桌
            sort(tables.begin(), tables.end(), [](const Table &a, const Table &b)
                 {
                     int remainingA = 4 - accumulate(a.ongoing.begin(), a.ongoing.end(), 0,
                                                     [](int sum, const Request &r)
                                                     { return sum + r.people; });
                     int remainingB = 4 - accumulate(b.ongoing.begin(), b.ongoing.end(), 0,
                                                     [](int sum, const Request &r)
                                                     { return sum + r.people; });

                     if (remainingA != remainingB)
                         return remainingA < remainingB; // 优先选择剩余空位更少的餐桌
                     return a.id < b.id;                 // 如果剩余空位相同，选择编号较小的
                 });

            for (auto &table : tables)
            {
                int remainingCapacity = 4 - accumulate(table.ongoing.begin(), table.ongoing.end(), 0,
                                                       [](int sum, const Request &r)
                                                       { return sum + r.people; });
                if (remainingCapacity >= current.people)
                {
                    // 安排座位
                    current.arrive = req.arrive;
                    table.ongoing.push_back(current);
                    tableUsage[table.id - 1] += current.people;
                    assigned = true;
                    break;
                }
            }

            if (assigned)
            {
                waitingQueue.pop(); // 当前请求已处理
            }
            else
            {
                break; // 无法安排，等待下一轮处理
            }
        }
    }

    // 处理等待队列中剩余的请求
    int currentTime = requests.back().arrive;
    while (!waitingQueue.empty())
    {
        // 找到所有的结束时间和当前队列中的最早到达时间
        vector<int> timePoints;
        for (const auto &table : tables)
        {
            for (const auto &r : table.ongoing)
            {
                timePoints.push_back(r.arrive + r.duration);
            }
        }

        // Create a temporary vector from the queue to iterate over
        vector<Request> tempQueue;
        while (!waitingQueue.empty())
        {
            tempQueue.push_back(waitingQueue.front());
            waitingQueue.pop();
        }

        for (const auto &req : tempQueue)
        {
            timePoints.push_back(req.arrive);
            waitingQueue.push(req); // Push back into the queue
        }

        // 找到下一时间点
        currentTime = *min_element(timePoints.begin(), timePoints.end());

        // 清理在当前时间完成的请求
        for (auto &table : tables)
        {
            auto it = remove_if(table.ongoing.begin(), table.ongoing.end(),
                                [&](const Request &r)
                                {
                                    if (r.arrive + r.duration <= currentTime)
                                    {
                                        tableUsage[table.id - 1] -= r.people;
                                        return true;
                                    }
                                    return false;
                                });
            table.ongoing.erase(it, table.ongoing.end());
        }

        // 尝试安排等待队列中的请求
        while (!waitingQueue.empty())
        {
            Request current = waitingQueue.front();
            if (current.arrive > currentTime)
                break;

            bool assigned = false;
            sort(tables.begin(), tables.end(), [](const Table &a, const Table &b)
                 {
                     int remainingA = 4 - accumulate(a.ongoing.begin(), a.ongoing.end(), 0,
                                                     [](int sum, const Request &r)
                                                     { return sum + r.people; });
                     int remainingB = 4 - accumulate(b.ongoing.begin(), b.ongoing.end(), 0,
                                                     [](int sum, const Request &r)
                                                     { return sum + r.people; });

                     if (remainingA != remainingB)
                         return remainingA < remainingB;
                     return a.id < b.id; });

            for (auto &table : tables)
            {
                int remainingCapacity = 4 - accumulate(table.ongoing.begin(), table.ongoing.end(), 0,
                                                       [](int sum, const Request &r)
                                                       { return sum + r.people; });
                if (remainingCapacity >= current.people)
                {
                    table.ongoing.push_back(current);
                    tableUsage[table.id - 1] += current.people;
                    assigned = true;
                    break;
                }
            }

            if (assigned)
            {
                waitingQueue.pop();
            }
            else
            {
                break;
            }
        }
    }

    // 输出每张餐桌的最终使用情况
    for (int i = 0; i < N; ++i)
    {
        cout << tableUsage[i] << (i == N - 1 ? "\n" : " ");
    }

    return 0;
}
