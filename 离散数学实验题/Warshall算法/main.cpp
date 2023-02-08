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

//用结构体来表示二元关系
struct BR
{
    char a;
    char b;
};

class Warshall
{
private:
    char *A; //元素集合
    BR *R;   //关系集合
    int n;   //元素个数
    int m;   //关系个数

    bool **tR; //传递闭包矩阵

public:
    Warshall();
    ~Warshall();

    int find(char c);
    void warshall();
    void translation_output();
};

Warshall::Warshall()
{
    // 初始化集合
    std::cout << "请输入集合 A 中的元素个数(正整数)，按回车键输入下一项：" << std::endl;
    n = GetInt(1, INT_MAX, true);
    A = new char[n];

    std::cout << "请依次输入集合 A 中的" << n << "个元素(形如：a b c d ......这样的格式)，按回车键输入下一项：" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> A[i];
    }

    // 初始化二元关系
    std::cout << "请输入二元关系 R 中的元素个数(正整数)，按回车键输入下一项：" << std::endl;
    m = GetInt(1, INT_MAX, true);
    R = new BR[m];

    std::cout << "请依次输入 R 中的" << m << "个元素，一行是一个元素" << std::endl;
    std::cout << "(形如：" << std::endl;
    std::cout << "a b" << std::endl;
    std::cout << "b c" << std::endl;
    std::cout << "c d" << std::endl;
    std::cout << "......" << std::endl;
    std::cout << "这样的格式)，按回车键输入下一项：" << std::endl;
    for (int i = 0; i < m; i++)
    {
        std::cin >> R[i].a;
        std::cin >> R[i].b;
    }

    // 初始化传递闭包矩阵
    tR = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        tR[i] = new bool[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tR[i][j] = 0;
        }
    }
}

Warshall::~Warshall()
{
    delete[] A;
    delete[] R;
    for (int i = 0; i < n; i++)
    {
        delete[] tR[i];
    }
    delete[] tR;
}

int Warshall::find(char c)
{
    for (int i = 0; i < n; i++)
    {
        if (A[i] == c)
        {
            return i;
        }
    }
    return -1;
}

void Warshall::warshall()
{
    // 从关系集合中获取关系矩阵
    int x, y;
    for (int i = 0; i < m; i++)
    {
        x = find(R[i].a);
        y = find(R[i].b);
        tR[x][y] = 1;
    }

    // Warshall算法计算传递闭包矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tR[j][i] == 1)
            {
                for (int k = 0; k < n; k++)
                {
                    tR[j][k] = bool(tR[j][k] + tR[i][k]); // ?
                }
            }
        }
    }
}

void Warshall::translation_output()
{
    // 输出传递闭包集合形式
    std::cout << std::endl;
    std::cout << "R 的传递闭包(集合形式)为：" << std::endl;
    std::cout << "t(R) = {";
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (tR[i][j] == 1)
            {
                std::cout << "<" << A[i] << "," << A[j] << ">"
                          << ",";
            }
        }
    }
    std::cout << "}" << std::endl;

    // 输出传递闭包矩阵形式
    std::cout << "R 的传递闭包(矩阵形式)为：" << std::endl;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            std::cout << tR[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    Warshall warshall;             // 初始化元素集合、关系集合、传递闭包矩阵
    warshall.warshall();           // 计算传递闭包矩阵
    warshall.translation_output(); // 输出传递闭包矩阵

    return 0;
}