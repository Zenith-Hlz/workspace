union node
{
    struct
    {
        union node *left;
        union node *right;
    } interval;
    double data[2];
};

int main()
{
    return 0;
}