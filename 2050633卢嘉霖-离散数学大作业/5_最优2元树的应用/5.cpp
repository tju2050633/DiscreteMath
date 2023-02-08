#include <iostream>

/* 输入一定范围内的整数 */
int GetInt(int low = INT_MIN, int high = INT_MAX, bool clear = true)
{
    int number;
    while (true)
    {
        std::cin >> number;
        if (!std::cin || number < low || number > high)
        {
            std::cout << "输入非法，请重新输入!" << std::endl;
            std::cin.clear();
            if (clear)
                std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            break;
        }
    }
    return number;
}

struct Node
{
    int weight;
    Node *parent;
    Node *l_child;
    Node *r_child;

    Node(int weight, Node *parent = nullptr, Node *l_child = nullptr, Node *r_child = nullptr)
        : weight(weight), parent(parent), l_child(l_child), r_child(r_child) {}
};

class HuffmanTree
{
public:
    HuffmanTree(int *array, int n);
    ~HuffmanTree();

    void ConstructTree();
    void PrintCode();

private:
    Node *root;
    int n;
    Node **leaf;

    void DeleteSubTree(Node *node);
    void _print_code(Node *node);
};

HuffmanTree::HuffmanTree(int *array, int n)
{
    // 初始化根节点
    root = nullptr;

    // 初始化叶子节点
    this->n = n;
    leaf = new Node *[n];
    for (int i = 0; i < n; i++)
    {
        leaf[i] = new Node(array[i]);
    }

    // 构造哈夫曼树
    ConstructTree();
}

HuffmanTree::~HuffmanTree()
{
    // 删除哈夫曼树
    DeleteSubTree(root);

    // 删除叶子节点
    delete[] leaf;
}

void HuffmanTree::DeleteSubTree(Node *node)
{
    if (node == nullptr)
        return;
    DeleteSubTree(node->l_child);
    DeleteSubTree(node->r_child);
    delete node;
}

void HuffmanTree::ConstructTree()
{
    // 构造哈夫曼树
    for (int i = 0; i < n - 1; i++)
    {
        // 找到权值最小的两个节点
        int min1 = INT_MAX, min2 = INT_MAX;
        int index1 = -1, index2 = -1;
        for (int j = 0; j < n; j++)
        {
            if (leaf[j] != nullptr)
            {
                if (leaf[j]->weight < min1)
                {
                    min2 = min1;
                    index2 = index1;
                    min1 = leaf[j]->weight;
                    index1 = j;
                }
                else if (leaf[j]->weight < min2)
                {
                    min2 = leaf[j]->weight;
                    index2 = j;
                }
            }
        }

        // 构造新节点
        Node *new_node = new Node(min1 + min2, nullptr, leaf[index1], leaf[index2]);
        leaf[index1]->parent = new_node;
        leaf[index2]->parent = new_node;
        leaf[index1] = new_node;
        leaf[index2] = nullptr;
    }

    // 找到根节点
    for (int i = 0; i < n; i++)
    {
        if (leaf[i] != nullptr)
        {
            root = leaf[i];
            break;
        }
    }
}

void HuffmanTree::PrintCode()
{
    _print_code(root);
}

void HuffmanTree::_print_code(Node *node)
{
    if (node == nullptr)
        return;
    if (node->l_child == nullptr && node->r_child == nullptr)
    {
        // 找到叶子节点
        std::cout << node->weight << ":  ";
        Node *p = node;
        std::string code = "";
        while (p->parent != nullptr)
        {
            if (p->parent->l_child == p)
                code = "0" + code;
            else
                code = "1" + code;
            p = p->parent;
        }
        std::cout << code << std::endl;
        return;
    }
    else
    {
        _print_code(node->l_child);
        _print_code(node->r_child);
    }
}

int main()
{
    // 输入叶子节点的个数，以及每个叶子节点的权值
    std::cout << "输入节点个数:";
    int n = GetInt(1, INT_MAX);

    int *array = new int[n];
    std::cout << "输入节点:";
    for (int i = 0; i < n; i++)
    {
        array[i] = GetInt();
    }

    // 构造哈夫曼树，并打印哈夫曼编码
    HuffmanTree tree(array, n);
    tree.PrintCode();

    // 释放内存
    delete[] array;

    return 0;
}