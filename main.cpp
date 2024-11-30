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
        bool isBeforeRotationOffset;
        if (pos < rotation_offset)
            isBeforeRotationOffset = true;
        else
            isBeforeRotationOffset = false;

        // Adjust the logical position to the actual position
        pos = getRealPosition(pos);

        if (isBeforeRotationOffset)
            rotation_offset += 1;
        count += 1;

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
        // Update the rotation offset and ensure it is positive
        rotation_offset = (rotation_offset + r) % count;
        if (rotation_offset < 0)
        {
            rotation_offset += count;
        }
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

    // Swap operation: swap the values of two nodes at given positions
    void swap(int i, int j)
    {
        if (i == j)
            return; // If the indices are the same, no swap is needed.

        // Normalize indices considering rotation and handle wrap-around using getRealPosition
        int real_i = getRealPosition(i);
        int real_j = getRealPosition(j);

        // First find the corresponding positions using the splay tree and splay them to the root
        Node *node_i = find(real_i);
        splay(node_i); // Splay the first node to the root

        Node *node_j = find(real_j);
        splay(node_j); // Splay the second node to the root

        // If either node is null (which should not happen in proper usage), do nothing
        if (!node_i || !node_j)
            return;

        // Swap the values of the two nodes
        int temp = node_i->val;
        node_i->val = node_j->val;
        node_j->val = temp;

        // Optionally, re-splay one of the nodes to keep tree balanced
        splay(node_i); // Keep the first node at the root to optimize further accesses
    }

    // Reverse operation: reverse the order of the nodes in the range [i, j]
    void reverse(int i, int j)
    {
        if (count == 0)
            return; // No elements to reverse if the tree is empty

        // Normalize indices considering rotation and wrap around
        i = getRealPosition(i);
        j = getRealPosition(j);

        if (i == j)
            return; // Single element reversal is meaningless

        if (i > j)
        {
            // Wrap around case: Reverse [i, end] and [start, j]
            splay(find(i)); // Make i the root
            if (root->right)
            {
                pushDown(root->right); // Apply pending reversals if any
                root->right->rev ^= 1; // Toggle the reverse flag
            }

            splay(find(j)); // Make j the root
            if (root->right)
            {
                pushDown(root->right); // Apply pending reversals if any
                root->right->rev ^= 1; // Toggle the reverse flag
            }
        }
        else
        {
            // Direct case: Reverse [i, j]
            splay(find(i)); // Splay i to the root
            Node *temp = root->right;
            if (temp)
            {
                splay(findAtRelative(j - i, temp)); // Splay j to be the right child of the root
                if (root->right->left)
                {
                    pushDown(root->right->left); // Apply pending reversals if any
                    root->right->left->rev ^= 1; // Toggle the reverse flag
                }
            }
        }
    }

    // Helper function to find a node at a relative position in a subtree
    Node *findAtRelative(int relPos, Node *start)
    {
        int index = relPos;
        Node *node = start;
        while (node)
        {
            pushDown(node); // Always respect pending operations
            int leftSize = getSize(node->left);
            if (index == leftSize)
            {
                return node;
            }
            else if (index < leftSize)
            {
                node = node->left;
            }
            else
            {
                index -= leftSize + 1;
                node = node->right;
            }
        }
        return nullptr;
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

        for (int i = count - rotation_offset; i < count; i++)
            printf("%d ", result[i]);
        for (int i = 0; i < count - rotation_offset; i++)
            printf("%d ", result[i]);

        printf("\n");

        delete[] result;
    }

    // In-order traversal to output the result
    void inorder(Node *node, int *result, int &index)
    {
        if (!node)
            return;
        pushDown(node); // Ensure the reverse flag is handled
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
