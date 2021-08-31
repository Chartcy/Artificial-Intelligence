#include <iostream>
using namespace std;

void site(char monkey, char box)
{
    cout << "SITE(monkey," << monkey << ")" << endl;
    cout << "SITE(box," << box << ")" << endl;
}
void state(int on, int hold)
{
    if (on == 0)
        cout << "!ON" << endl;
    else
        cout << "ON" << endl;
    if (hold == 0)
        cout << "!HOLD" << endl;
    else
        cout << "HOLD" << endl;
}

void PRO(char monkey, char box, char banana, int on, int hold)
{
    if (monkey != box)
    {
        cout << "----------------------GOTO(" << monkey << "," << box << ")----------------------" << endl;
        monkey = box;
		site(monkey, box);
        state(on, hold);
        cout << endl;
    }
    if (monkey != banana && monkey == box)
    {
        cout << "----------------------PUSH(" << monkey << "," << banana << ")----------------------" << endl;
        monkey = banana;
		site(monkey, banana);
        state(on, hold);
        cout << endl;
    }
    if (monkey == banana && on == 0)
    {
        cout << "----------------------CLIMBBOX----------------------" << endl;
		site(monkey, banana);
        on =1;
        state(on, hold);
        cout << endl;
    }
    if (monkey == banana && on == 1 && hold == 0)
    {
        cout << "----------------------GRASP----------------------" << endl;
		site(monkey, banana);
		hold =1;
        state(on, hold);
        cout << endl;
    }
}

int main()
{
    char monkey, box, banana;
    int on = 0, hold = 0;
    cout << "猴子的位置：";
    cin >> monkey;
    cout << "箱子的位置：";
    cin >> box;
    cout << "香蕉的位置：";
    cin >> banana;
    cout << endl;
	site(monkey, box);
    state(on, hold);
    cout << endl;
    PRO(monkey, box, banana, on, hold);
    return 0;
}
