#include <iostream>

void GetNodeEdgeNum(int &NodeNum, int &EdgeNum)
{
    while (true)
    {
        std::cin >> NodeNum >> EdgeNum;
        std::cin.ignore(INT_MAX, '\n');
        if (NodeNum == 0 && EdgeNum == 0)
        {
            exit(1);
        }
        else if (!std::cin ||
                 NodeNum < 2 ||
                 EdgeNum < NodeNum - 1 ||
                 EdgeNum > NodeNum * (NodeNum - 1) / 2)
        {
            std::cout << "输入非法，请重试" << std::endl;
            std::cin.clear();
        }
        else
        {
            break;
        }
    }
}

class Graph
{
private:
    int NodeNum;
    int EdgeNum;
    int *Nodes;   // 顶点集合
    int **Edges;  // 边集合
    int **Matrix; //邻接矩阵

    int MinTotalCost;

public:
    Graph();
    ~Graph();

    void Prim();

    int Find(int *Parent, int Node);               // 查找节点所在集合
    void Union(int *Parent, int Node1, int Node2); // 合并两个集合
    void Kruskal();

    int GetMinTotalCost() const
    {
        return MinTotalCost;
    }
};

Graph::Graph()
{
    // 输入节点数和边数
    std::cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n";
    GetNodeEdgeNum(NodeNum, EdgeNum);

    // 初始化顶点集合和边集合
    Nodes = new int[NodeNum];
    for (int i = 0; i < NodeNum; i++)
    {
        Nodes[i] = i;
    }
    Edges = new int *[EdgeNum];
    for (int i = 0; i < EdgeNum; i++)
    {
        Edges[i] = new int[3];
    }

    // 初始化邻接矩阵
    Matrix = new int *[NodeNum];
    for (int i = 0; i < NodeNum; i++)
    {
        Matrix[i] = new int[NodeNum];
        for (int j = 0; j < NodeNum; j++)
        {
            Matrix[i][j] = INT_MAX;
        }
    }

    // 输入边
    std::cout << "请输入两条边的节点序号以及它们的权值(以空格分隔各个数):\n";
    for (int i = 0; i < EdgeNum; i++)
    {
        // 输入边的起点、终点和权重，确保输入合法
        int StartNode, EndNode, EdgeWeight;
        std::cin >> StartNode >> EndNode >> EdgeWeight;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin ||
            StartNode < 1 ||
            StartNode > NodeNum ||
            EndNode < 1 ||
            EndNode > NodeNum ||
            EdgeWeight < 0)
        {
            std::cout << "输入非法，请重试" << std::endl;
            std::cin.clear();
            i--;
            continue;
        }

        // 边集合赋值
        Edges[i][0] = StartNode;
        Edges[i][1] = EndNode;
        Edges[i][2] = EdgeWeight;

        // 赋值邻接矩阵
        Matrix[StartNode - 1][EndNode - 1] = Matrix[EndNode - 1][StartNode - 1] = EdgeWeight;
    }
}

Graph::~Graph()
{
    // 释放顶点集合
    delete[] Nodes;

    // 释放边集合
    for (int i = 0; i < EdgeNum; i++)
    {
        delete[] Edges[i];
    }
    delete[] Edges;

    // 释放邻接矩阵
    for (int i = 0; i < NodeNum; i++)
    {
        delete[] Matrix[i];
    }
    delete[] Matrix;
}

void Graph::Prim()
{
    std::cout << "【Prim算法求最小生成树】" << std::endl;

    MinTotalCost = 0;

    // 栈，存放已访问节点的下标
    int top = 0;
    int *VisitedNodes = new int[NodeNum];

    // 第一个节点入栈
    VisitedNodes[top++] = 0;

    // 遍历已访问节点的所有边，找到最小边，直到所有节点入栈（已访问）
    while (top < NodeNum)
    {
        int MinEdgeWeight = INT_MAX;
        int r = -1;
        int c = -1;
        for (int i = 0; i < top; i++)
        {
            for (int j = 0; j < NodeNum; j++)
            {
                // 如果边指向已访问节点，跳过
                bool isVisited = false;
                for (int k = 0; k < top; k++)
                {
                    if (VisitedNodes[k] == j)
                    {
                        isVisited = true;
                        break;
                    }
                }

                // 如果该节点未访问过、不是自身、有边连接且边权小于当前最小边权，更新最小边权
                if (!isVisited && VisitedNodes[i] != j && Matrix[VisitedNodes[i]][j] != INT_MAX && Matrix[VisitedNodes[i]][j] < MinEdgeWeight)
                {
                    // 更新最小边的权重
                    MinEdgeWeight = Matrix[VisitedNodes[i]][j];
                    // 更新最小边的起点和终点
                    r = VisitedNodes[i];
                    c = j;
                }
            }
        }

        // 将最小边的终点入栈
        VisitedNodes[top++] = c;
        // 更新最小总代价
        MinTotalCost += MinEdgeWeight;

        std::cout << "最小耗费是:" << r + 1 << "和" << c + 1 << std::endl;
    }

    // 释放栈
    delete[] VisitedNodes;
}

void Graph::Kruskal()
{
    std::cout << "【Kruskal算法求最小生成树】" << std::endl;

    MinTotalCost = 0;

    // 初始化并查集
    int *Parent = new int[NodeNum];
    for (int i = 0; i < NodeNum; i++)
    {
        Parent[i] = i;
    }

    // 按边权从小到大排序
    for (int i = 0; i < EdgeNum; i++)
    {
        for (int j = i + 1; j < EdgeNum; j++)
        {
            if (Edges[i][2] > Edges[j][2])
            {
                int temp = Edges[i][2];
                Edges[i][2] = Edges[j][2];
                Edges[j][2] = temp;
                temp = Edges[i][0];
                Edges[i][0] = Edges[j][0];
                Edges[j][0] = temp;
                temp = Edges[i][1];
                Edges[i][1] = Edges[j][1];
                Edges[j][1] = temp;
            }
        }
    }

    // 遍历所有边，如果边的两个节点不在同一集合中，将两个节点合并到同一集合中
    for (int i = 0; i < EdgeNum; i++)
    {
        int StartNode = Edges[i][0] - 1;
        int EndNode = Edges[i][1] - 1;
        int EdgeWeight = Edges[i][2];

        // 如果两个节点不在同一集合中，将两个节点合并到同一集合中
        if (Find(Parent, StartNode) != Find(Parent, EndNode))
        {
            Union(Parent, StartNode, EndNode);
            MinTotalCost += EdgeWeight;
            std::cout << "最小耗费是:" << StartNode + 1 << "和" << EndNode + 1 << std::endl;
        }
    }

    delete[] Parent;
}

int Graph::Find(int *Parent, int Node)
{
    while (Parent[Node] != Node)
    {
        Node = Parent[Node];
    }
    return Node;
}

void Graph::Union(int *Parent, int Node1, int Node2)
{
    int Parent1 = Find(Parent, Node1);
    int Parent2 = Find(Parent, Node2);
    Parent[Parent1] = Parent2;
}

int main()
{
    // 创建无向图
    Graph graph;

    // Prim算法求最小生成树
    graph.Prim();

    // 输出最小总代价
    std::cout << "最小总代价为：" << graph.GetMinTotalCost() << std::endl;

    // Kruskal算法求最小生成树
    graph.Kruskal();

    // 输出最小总代价
    std::cout << "最小总代价为：" << graph.GetMinTotalCost() << std::endl;

    return 0;
}

// 1 2 20
// 2 3 15
// 3 4 3
// 4 5 17
// 5 6 28
// 6 1 23
// 1 7 1
// 2 7 4
// 3 7 9
// 4 7 16
// 5 7 25
// 6 7 36