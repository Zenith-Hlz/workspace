#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>

using namespace std;

// Define a structure to store a point's coordinates and identify its chain
struct Point
{
    long long x, y;
    bool chain = 0; // 0 represents upper chain and 1 represents lower chain by default

    // Operator overload for sorting points based on their x-coordinates
    bool operator<(const Point &other) const
    {
        return x < other.x;
    }
};

// Global vectors to store the polygon points and the resulting triangles
vector<Point> points;
vector<tuple<long long, long long, long long, long long, long long, long long>> triangles;

// Function to compute the cross product of vectors AB and AC
long long crossProduct(const Point &A, const Point &B, const Point &C)
{
    long long dx1 = B.x - A.x;
    long long dy1 = B.y - A.y;
    long long dx2 = C.x - A.x;
    long long dy2 = C.y - A.y;

    long long cross_product = dx1 * dy2 - dy1 * dx2;

    return cross_product;
}

// Classify points into upper and lower chains for the given polygon
void classify(long long n)
{
    // Find the iterators to the minimum and maximum element based on x value
    auto min_iter = std::min_element(points.begin(), points.end());
    long long min_index = std::distance(points.begin(), min_iter);

    auto max_iter = std::max_element(points.begin(), points.end());
    long long max_index = std::distance(points.begin(), max_iter);

    // Determine which points are on the lower chain
    if (min_index <= max_index)
    {
        for (long long i = min_index; i <= max_index; ++i)
        {
            points[i].chain = 1;
        }
    }
    else
    {
        for (long long i = min_index; i < n; ++i)
        {
            points[i].chain = 1;
        }
        for (long long i = 0; i <= max_index; ++i)
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

// Triangulate a given x-monotone polygon
void triangulateXMonotonePolygon(long long n)
{
    stack<Point> S; // A stack to manage points during triangulation

    // Sort points by their x-coordinates to prepare for traversal
    sort(points.begin(), points.end());

    // Loop through each point in the sorted array
    for (long long i = 0; i < n; ++i)
    {
        Point &curr = points[i];

        // Case 1: The current point is on a different chain than the stack top
        if (!S.empty() && S.top().chain != curr.chain)
        {
            // Save the stack top
            Point t = S.top();
            while (S.size() > 1)
            {
                Point prev = S.top();
                S.pop();
                addTriangle(S.top(), prev, curr); // Form triangles
            }
            S.pop();
            S.push(t);
            S.push(curr);
        }
        else
        {
            // Case 2: The current point is on the same chain as the stack top
            while (S.size() >= 2)
            {
                Point top1 = S.top();
                S.pop();
                Point top2 = S.top();

                // Check if a valid diagonal can be drawn
                if ((curr.chain && crossProduct(top2, top1, curr) > 0) || (!curr.chain && crossProduct(top2, top1, curr) < 0))
                {
                    addTriangle(top2, top1, curr);
                }
                else
                {
                    S.push(top1);
                    break;
                }
            }
            S.push(curr); // Add current point to the stack
        }
    }
}

int main()
{
    long long n;
    scanf("%lld", &n);

    points.resize(n); // Resize the points vector to hold all input points

    for (long long i = 0; i < n; ++i)
    {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }

    classify(n);                    // Classify points into upper and lower chains
    triangulateXMonotonePolygon(n); // Triangulate the polygon

    // Output triangles
    for (const auto &[x1, y1, x2, y2, x3, y3] : triangles)
    {
        printf("%lld %lld %lld %lld %lld %lld\n", x1, y1, x2, y2, x3, y3);
    }

    return 0;
}
