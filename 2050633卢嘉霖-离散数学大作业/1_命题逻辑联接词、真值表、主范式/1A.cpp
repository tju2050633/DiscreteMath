#include <iostream>
using namespace std;

void Welcome()
{
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        欢迎进入逻辑运算程序       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl
         << endl;
}

int GetInt(char c)
{
    int i = -1;
    cout << "\n  请输入" << c << "的值（0或1）,以回车结束:";
    cin >> i;
    if (i != 0 && i != 1 || !cin)
    {
        cout << "\n  " << c << "的值输入有误,请重新输入!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        return GetInt(c);
    }

    cin.ignore(INT_MAX, '\n'); //防止读入第一个数字后方的输入影响下面输入
    return i;
}

bool isContinue()
{
    bool flag;
    char s;
    cout << "\n是否继续？（y/n）:";
    cin >> s;

    if (s == 'y' || s == 'n')
    {
        if (s == 'y')
        {
            flag = true; //继续
        }
        else
        {
            printf("欢迎下次再次使用!\n"); //退出
            flag = false;
        }
    }
    else
    {
        printf("输入错误,请重新输入!\n"); //错误校验
        return isContinue();
    }
    cin.ignore(INT_MAX, '\n'); //防止读入第一个字母后方的输入影响下面输入
    return flag;
}

int main()
{
    Welcome(); //标语

    int a[4];
    int P, Q;

    while (true)
    {
        P = GetInt('P');
        Q = GetInt('Q');

        a[0] = P && Q;                     //与运算
        a[1] = P || Q;                     //或运算
        a[2] = (!P) || Q;                  //蕴含运算，将其转化为与或非形式
        a[3] = ((!P) || Q) && ((!Q) || P); //等值运算，将其转化为与或非形式

        cout << "\n\n  合取:\n       P/\\Q = " << a[0] << endl; //输出结果
        cout << "  析取:\n       P\\/Q = " << a[1] << endl;
        cout << "  条件:\n       P->Q = " << a[2] << endl;
        cout << "  双条件:\n       P<->Q = " << a[3] << endl;

        if (!isContinue())
        {
            break;
        }
    }

    return 0;
}