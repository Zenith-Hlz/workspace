#include <vector>
#include <algorithm>
#include <stack>
#include <stdio.h>
using namespace std;

struct Point
{
    int x, y;
    bool operator<(const Point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int orientation(const Point &p, const Point &q, const Point &r)
{
    // Cross product calculation for orientation
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;             // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

void triangulate(const vector<Point> &vertices, int n)
{
    vector<int> lower_chain, upper_chain;
    stack<int> st;

    // Sort vertices
    vector<pair<Point, int>> points;
    for (int i = 0; i < n; ++i)
        points.push_back({vertices[i], i});
    sort(points.begin(), points.end());

    // Initialize chains
    for (int i = 0; i < n; ++i)
    {
        if (points[i].second == 0 || points[i].second == n - 1)
            continue;
        if (orientation(points[0].first, points[n - 1].first, points[i].first) == 1)
            upper_chain.push_back(points[i].second);
        else
            lower_chain.push_back(points[i].second);
    }

    st.push(points[0].second);
    st.push(points[1].second);

    for (int i = 2; i < n; ++i)
    {
        int curr = points[i].second;
        bool is_upper = find(upper_chain.begin(), upper_chain.end(), curr) != upper_chain.end();

        if (is_upper != (find(upper_chain.begin(), upper_chain.end(), st.top()) != upper_chain.end()))
        {
            // Different chain: connect all stack elements to `curr`
            while (st.size() > 1)
            {
                int top = st.top();
                st.pop();
                printf("%d %d ", vertices[curr].x, vertices[curr].y);
                printf("%d %d ", vertices[top].x, vertices[top].y);
                printf("%d %d\n", vertices[st.top()].x, vertices[st.top()].y);
            }
            st.pop();
            st.push(points[i - 1].second);
            st.push(curr);
        }
        else
        {
            // Same chain
            int last = st.top();
            st.pop();
            while (!st.empty() && orientation(vertices[curr], vertices[last], vertices[st.top()]) != 2)
            {
                printf("%d %d ", vertices[curr].x, vertices[curr].y);
                printf("%d %d ", vertices[last].x, vertices[last].y);
                printf("%d %d\n", vertices[st.top()].x, vertices[st.top()].y);
                last = st.top();
                st.pop();
            }
            st.push(last);
            st.push(curr);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<Point> vertices(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &vertices[i].x, &vertices[i].y);
    }
    triangulate(vertices, n);
    return 0;
}
