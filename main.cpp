#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int N, M;

struct SplayTree
{
    struct Node
    {
        int val, size;
        int rev; // A flag used for lazy propagation to indicate if the subtree needs to be reversed.
        Node *left, *right, *parent;

        // The constructor initializes the node with a specific value
        Node(int v) : val(v), size(1), rev(0), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;
    int rotation_offset; // This tracks the overall rotation of the circle

    // The constructor initializes the root node and the rotation offset
    SplayTree() : root(nullptr), rotation_offset(0) {}

    int getIndex(Node *node)
    {
        if (!node)
            return 0;
        int index = getSize(node->left); // Size of the left subtree
        while (node->parent)
        {
            if (node == node->parent->right)
                index += getSize(node->parent->left) + 1; // Add parent's left size + 1
            node = node->parent;
        }
        return index;
    }

    // Update the size of the current node
    void update(Node *node)
    {
        if (node)
        {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

    // Get the size of the node
    int getSize(Node *node)
    {
        return node ? node->size : 0;
    }

    // Rotation operation: rotate node x up to the position of its parent y
    void rotate(Node *x)
    {
        Node *y = x->parent;
        Node *z = y->parent;

        // If x is the left child of y, move x's right subtree to y's left
        if (x == y->left)
        {
            y->left = x->right;
            if (x->right)
                x->right->parent = y;
            x->right = y;
        }
        else // If x is the right child of y
        {
            y->right = x->left;
            if (x->left)
                x->left->parent = y;
            x->left = y;
        }

        y->parent = x;
        x->parent = z;

        // If z is not null (i.e., y is not the root)
        if (z)
        {
            if (z->left == y)
                z->left = x;
            else
                z->right = x;
        }

        update(y);
        update(x);
    }

    // Splay operation: splay the node x to the root of the tree
    void splay(Node *x)
    {
        // Continue until x becomes the root (i.e., x has no parent)
        while (x->parent)
        {
            Node *p = x->parent;
            Node *g = p->parent;

            // If p is the root
            if (!g)
            {
                rotate(x); // Perform a single rotation
            }
            else if ((x == p->left) == (p == g->left)) // If x and p are both left or both right children
            {
                // Perform a rotation on p (zig-zig or zag-zag case)
                rotate(p);
                rotate(x);
            }
            else // If x and p are on opposite sides (one is a left child, the other is a right child)
            {
                // Perform a rotation on x (zig-zag or zag-zig case)
                rotate(x);
                rotate(x);
            }
        }

        root = x;
    }

    // Find operation: find and return the node with a specific value
    Node *find(int pos)
    {
        Node *node = root;
        while (node)
        {
            int leftSize = getSize(node->left);
            if (pos == leftSize)
                return node;
            else if (pos < leftSize)
                node = node->left;
            else
            {
                pos -= leftSize + 1;
                node = node->right;
            }
        }
        return nullptr;
    }

    // Insert operation: insert a new node with a specific value at a given position
    void insert(int value, int pos)
    {
        // Adjust the logical position to the actual position
        pos = getRealPosition(pos);

        // If the tree is empty, create a new node as the root
        if (!root)
        {
            root = new Node(value);
            return;
        }

        // Find the position to insert the new node
        Node *node = root;
        while (true)
        {
            int leftSize = getSize(node->left);
            // If the position is less than or equal to the size of the left subtree
            if (pos <= leftSize)
            {
                if (!node->left)
                {
                    node->left = new Node(value);
                    node->left->parent = node;
                    splay(node->left);
                    break;
                }
                node = node->left;
            }
            // If the position is greater than the size of the left subtree
            else
            {
                pos -= leftSize + 1;
                if (!node->right)
                {
                    node->right = new Node(value);
                    node->right->parent = node;
                    splay(node->right);
                    break;
                }
                node = node->right;
            }
        }
    }

    // Rotate all dancers
    void rotateAll(int r)
    {
        // Update the rotation offset
        rotation_offset = (rotation_offset + r) % getSize(root);
    }

    // Get the actual position of the node
    int getRealPosition(int pos)
    {
        int n = getSize(root);
        if (n == 0)
            return 0; // Avoid division/modulus by zero

        // Adjust the position based on the rotation offset
        return (pos - rotation_offset + n) % n;
    }

    // Swap operation：swap the values of two nodes
    void swap(int i, int j)
    {
        // First find the corresponding positions using the splay tree
        Node *node_i = find(getRealPosition(i));
        Node *node_j = find(getRealPosition(j));
        if (node_i && node_j)
        {
            // Swap the values of the two nodes
            int temp = node_i->val;
            node_i->val = node_j->val;
            node_j->val = temp;
        }
    }

    void reverse(int i, int j)
    {
        int n = getSize(root); // Total number of nodes
        if (n == 0)
            return;

        // Adjust for real positions considering rotation offset
        i = getRealPosition(i);
        j = getRealPosition(j);

        if (i > j)
        {
            // If i > j, reverse from i to n-1, and then 0 to j
            reverse(i, n - 1);
            reverse(0, j);
        }
        else
        {
            // Find the [i, j] range in the splay tree
            Node *left = nullptr, *middle = nullptr, *right = nullptr;

            // Split the tree into three parts: [0, i-1], [i, j], and [j+1, n-1]
            split(root, i, left, middle);
            split(middle, j - i + 1, middle, right);

            // Toggle the reverse flag for the middle part
            if (middle)
                middle->rev ^= 1;

            // Merge the parts back together
            root = merge(merge(left, middle), right);
        }
    }

    // Helper function: split the tree into two parts at position `pos`
    // Result: `left` contains [0, pos-1], `right` contains [pos, n-1]
    void split(Node *node, int pos, Node *&left, Node *&right)
    {
        if (!node)
        {
            left = right = nullptr;
            return;
        }

        splay(find(pos)); // Splay the node at `pos` to the root
        if (!root)
            return;
        if (pos <= getSize(node->left))
        {
            right = node;
            left = node->left;
            if (left)
                left->parent = nullptr;
            right->left = nullptr;
            update(right);
        }
        else
        {
            left = node;
            right = node->right;
            if (right)
                right->parent = nullptr;
            left->right = nullptr;
            update(left);
        }
    }

    // Helper function: merge two trees `left` and `right`
    Node *merge(Node *left, Node *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        // Splay the largest node of the left tree
        Node *maxLeft = left;
        while (maxLeft->right)
            maxLeft = maxLeft->right;
        splay(maxLeft);

        // Attach the right tree to the left tree
        maxLeft->right = right;
        right->parent = maxLeft;
        update(maxLeft);
        return maxLeft;
    }

    // Helper function: push down the reverse flag to child nodes
    void pushDown(Node *node)
    {
        if (node && node->rev)
        {
            // Swap the left and right children
            swap(getIndex(node->left), getIndex(node->right));
            if (node->left)
                node->left->rev ^= 1;
            if (node->right)
                node->right->rev ^= 1;
            node->rev = 0; // Clear the reverse flag
        }
    }

    // Print the final dancers
    void print()
    {
        // Use a dynamic array to store the result
        int *result = new int[N]; // Use maximum space
        int index = 0;

        inorder(root, result, index);

        for (int i = 0; i < index; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");

        delete[] result; // Free memory
    }

    // In-order traversal to output the result
    void inorder(Node *node, int *result, int &index)
    {
        if (!node)
            return;
        inorder(node->left, result, index);
        result[index++] = node->val;
        inorder(node->right, result, index);
    }
};

int main()
{
    scanf("%d %d", &N, &M);

    SplayTree tree;

    // Process operations
    for (int i = 0; i < M; ++i)
    {
        char operation;
        int x, y;
        scanf("%c", &operation);
        if (operation == 'I')
        {
            scanf("%d %d", &x, &y);
            tree.insert(x, y);
        }
        else if (operation == 'S')
        {
            scanf("%d %d", &x, &y);
            tree.swap(x, y);
        }
        else if (operation == 'R')
        {
            scanf("%d", &x);
            tree.rotateAll(x);
        }
        else if (operation == 'F')
        {
            scanf("%d %d", &x, &y);
            tree.reverse(x, y);
        }
    }

    printf("%d\n", tree.getSize(tree.root));
    // Output the final result
    tree.print();

    return 0;
}

/*
## 题目描述
在苏格兰舞会上，人们会围圈跳舞，并由主持人带领进行着队形变换。舞会期间，不断会有新人加入。主持人确定所有变换之后，希望预先知道，一曲终了时的队形将会如何。

人们在舞圈里的位置，自正门处逆时针从 0 开始这个编号，从最初至终的舞圈开始，反复做下列四种队形变换：

* **I x p**: 代号为整数 x 的舞者，加入到舞圈中 p-1 号与 p 号舞者之间，编号取作 p，原 p 至 n-1 号舞者的编号各自加一，其中 0 ≤ p ≤ n，n为当前的舞者总数。特别地，如果 p = n，则 x 将插到 n-1 号与 0 号之间，编号取作 n，原先舞者的编号均保持不变；如果 p = 0，则 x 将插到 0 号与 n-1 号之间，编号取作 0，原先的所有舞者编号各自加一；

* **S i j**: i 号舞者与 j 号交换位置。0 ≤ i,j < n；

* **R r**: 舞圈整体顺时针旋转 r 次，r ∈ Z，舞者的编号（在模 n 意义下）各自增加 r 个单位。当然，若 r < 0，则相当于逆时针旋转，所有编号减少一个单位；

* **F i j**: i 至 j 号舞者整体区间翻转，0 ≤ i,j < n。这里的区间是就循环意义而言的，以 n = 7 为例，若舞者代号依次为 a,b,c,d,e,f,g，则在做过 F14 翻转后，代号序列将转成 a,e,d,c,b,f,g；而在做过 F41 翻转后，代号序列将转成 f,e,c,d,b,a,g。

## 输入格式
第一行有两个正整数：N 为最终的舞者总数，M 为队形变换的总次数。接下来的 M 行，按照上述格式逐一列出各次变换。S,R,F 操作保证当时的舞圈不空，i,j 总是当前舞圈中的合法位置。

## 输出格式
仅一行，按最终次序逐个列出舞者代号。

## 输入样例

```plain
5 20
I 4399 0
I 1024 1
R -1
S 0 1
I 7777 1
R 20
S 1 2
F 2 0
F 0 1
F 1 0
I 1111 0
I 2048 4
S 1 3
R -3
F 0 2
F 3 0
S 0 0
S 1 4
F 3 2
R 2
```

## 输出样例

```plain
1024 4399 7777 2048 1111
```

## 限制

1 ≤ N ≤ M ≤ 500,000, x, r 不超出 int 数据类型能表示的范围

时间: 1.5 sec

空间: 256 MB

## 提示

第2，3点提示对复杂度没有实质性的影响，不必须按这两点思路解题。

- 伸展树(splay)
- 思考如何在 O(1) 时间内完成 R 操作
- 思考如何避免对树的 split/merge 操作
*/