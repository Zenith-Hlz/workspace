#include <cstdio>

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
    int count;           // This tracks the number of dancers in the tree

    // The constructor initializes the root node and the rotation offset
    SplayTree() : root(nullptr), rotation_offset(0), count(0) {}

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

    // Rotation operation: rotate node node up to the position of its parent p
    void rotate(Node *node)
    {
        Node *p = node->parent;
        Node *g = p ? p->parent : nullptr;

        // Rotate the node up to the position of its parent
        if (node == p->left)
        {
            p->left = node->right;
            if (node->right)
                node->right->parent = p;
            node->right = p;
        }
        else
        {
            p->right = node->left;
            if (node->left)
                node->left->parent = p;
            node->left = p;
        }

        p->parent = node;
        node->parent = g;

        // Update the grandparent's child pointer
        if (g)
        {
            if (g->left == p)
                g->left = node;
            else
                g->right = node;
        }

        update(p);
        update(node);
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
        count += 1;
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
            pushDown(node); // Push down the reverse flag

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
    void rotate(int r)
    {
        // Update the rotation offset
        rotation_offset = (rotation_offset + r) % count;
    }

    // Get the actual position of the node
    int getRealPosition(int pos)
    {
        if (count == 0)
            return 0; // Avoid division/modulus by zero

        // Adjust the position based on the rotation offset
        if (pos - rotation_offset == count)
            return count;
        return (pos - rotation_offset + count) % count;
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
        int n = count; // Total number of nodes
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
            Node *l = node->left;
            Node *r = node->right;

            // Swap children
            node->left = r;
            node->right = l;

            // Propagate reverse flag
            if (l)
                l->rev ^= 1;
            if (r)
                r->rev ^= 1;

            // Clear the flag
            node->rev = 0;
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
        scanf(" %c", &operation); // Add a space before %c to consume the newline character

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
            tree.rotate(x);
        }
        else if (operation == 'F')
        {
            scanf("%d %d", &x, &y);
            tree.reverse(x, y);
        }
    }

    // Output the final result
    tree.print();

    return 0;
}
