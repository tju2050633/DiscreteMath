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

class RelationMatrix
{
private:
    int _dimension;
    bool **_matrix;

public:
    RelationMatrix();
    ~RelationMatrix();

    void ReflexiveClosure() const;  // 求自反闭包
    void SymmetricClosure() const;  // 求对称闭包
    void TransitiveClosure() const; // 求传递闭包
};

RelationMatrix::RelationMatrix()
{
    // 输入矩阵的行数和列数
    std::cout << "请输入矩阵的行列数:";
    _dimension = GetInt(1);

    // 为矩阵分配内存
    _matrix = new bool *[_dimension];
    for (int i = 0; i < _dimension; i++)
    {
        _matrix[i] = new bool[_dimension];
    }

    // 输入矩阵的元素
    std::cout << "\n请输入关系矩阵:\n";
    for (int i = 0; i < _dimension; i++)
    {
        std::cout << std::endl;
        std::cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
        for (int j = 0; j < _dimension; j++)
        {
            _matrix[i][j] = GetInt(0, 1, false);
        }
        // GetInt不再输入一个数字就清空缓冲区，而是读完一行再清空
        std::cin.ignore(INT_MAX, '\n');
    }
}

RelationMatrix::~RelationMatrix()
{
    // 释放矩阵的内存
    for (int i = 0; i < _dimension; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

void RelationMatrix::ReflexiveClosure() const
{
    std::cout << "所求关系矩阵为:\n";

    for (int i = 0; i < _dimension; i++)
    {
        for (int j = 0; j < _dimension; j++)
        {
            if (i == j) // 对称闭包元素为1的额外情况：对角线元素为1
                std::cout << "1";
            else
                std::cout << _matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void RelationMatrix::SymmetricClosure() const
{
    std::cout << "所求关系矩阵为:\n";

    for (int i = 0; i < _dimension; i++)
    {
        for (int j = 0; j < _dimension; j++)
        {
            if (_matrix[j][i] == 1) // 对称闭包元素为1的额外情况：对称位置为1
                std::cout << "1";
            else
                std::cout << _matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void RelationMatrix::TransitiveClosure() const
{
    std::cout << "所求关系矩阵为:\n";

    // 传递闭包的矩阵,初始化为原矩阵
    bool temp_matrix[_dimension][_dimension];
    for (int i = 0; i < _dimension; i++)
    {
        for (int j = 0; j < _dimension; j++)
        {
            temp_matrix[i][j] = _matrix[i][j];
        }
    }

    // 通过Warshall算法求传递闭包
    for (int j = 0; j < _dimension; j++)
    {
        for (int i = 0; i < _dimension; i++)
        {
            // 对每个元素遍历
            // 若该元素为1，则i->j有关系，此时检查j->k是否有关系，若有则i->k有关系
            if (temp_matrix[i][j] == 1)
            {
                for (int k = 0; k < _dimension; k++)
                {
                    if (temp_matrix[j][k] == 1)
                    {
                        temp_matrix[i][k] = 1;
                    }
                }
            }
        }
    }

    // 输出传递闭包
    for (int i = 0; i < _dimension; i++)
    {
        for (int j = 0; j < _dimension; j++)
        {
            std::cout << temp_matrix[i][j];
        }
        std::cout << std::endl;
    }
}

int main()
{
    RelationMatrix matrix;

    while (true)
    {
        std::cout << "\n输入对应序号选择算法\n1:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
        int option = GetInt(1, 4);

        switch (option)
        {
        case 1:
            matrix.ReflexiveClosure();
            break;
        case 2:
            matrix.TransitiveClosure();
            break;
        case 3:
            matrix.SymmetricClosure();
            break;
        case 4:
            return 0;
        }
    }

    return 0;
}