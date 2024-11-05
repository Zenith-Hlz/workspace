#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    bool isReflex; // Indicates if this point is a reflex vertex
    bool chain = 0;

    bool operator<(const Point &other) const
    {
        return x < other.x;
    }
};

vector<Point> points;                                  // Store polygon points
vector<tuple<int, int, int, int, int, int>> triangles; // Store the triangles

// Cross product to determine orientation of three points
int crossProduct(const Point &A, const Point &B, const Point &C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

void classifyChain(int n)
{
    // Find the iterators to the minimum and maximum element based on x value
    auto min_iter = std::min_element(points.begin(), points.end());
    int min_index = std::distance(points.begin(), min_iter);

    auto max_iter = std::max_element(points.begin(), points.end());
    int max_index = std::distance(points.begin(), max_iter);

    if (min_index <= max_index)
    {
        // Points from min_index to max_index are on the upper chain
        for (int i = min_index; i <= max_index; ++i)
        {
            points[i].chain = 1;
        }
    }
    else
    {
        // Polygon wraps around: min_index to end and begin to max_index form the upper chain
        for (int i = min_index; i < n; ++i)
        {
            points[i].chain = 1;
        }
        for (int i = 0; i <= max_index; ++i)
        {
            points[i].chain = 1;
        }
    }
}

// Generate triangles based on the stack's reflex chain
void addTriangle(const Point &a, const Point &b, const Point &c)
{
    triangles.emplace_back(a.x, a.y, b.x, b.y, c.x, c.y);
}

void triangulateXMonotonePolygon(int n)
{
    stack<Point> S;

    sort(points.begin(), points.end());

    for (int i = 0; i < n; ++i)
    {
        Point &curr = points[i];

        // Case 1: Different chain
        if (!S.empty() && S.top().chain != curr.chain)
        {
            Point t = S.top();
            while (S.size() > 1)
            {
                Point prev = S.top();
                S.pop();
                addTriangle(S.top(), prev, curr);
            }
            S.pop();
            S.push(t);
            S.push(curr);
        }
        else
        {
            // Case 2: Same chain
            while (S.size() >= 2)
            {
                Point top1 = S.top();
                S.pop();
                Point top2 = S.top();

                // Determine if we need to add a diagonal
                if (crossProduct(top2, top1, curr) <= 0)
                {
                    addTriangle(top2, top1, curr);
                }
                else
                {
                    S.push(top1);
                    break;
                }
            }
            S.push(curr);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    points.resize(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    classifyChain(n);
    triangulateXMonotonePolygon(n);

    // Output triangles
    for (const auto &[x1, y1, x2, y2, x3, y3] : triangles)
    {
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
    }

    return 0;
}
