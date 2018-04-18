#include<cstdio>

using namespace std;

class Point {
public:
    int x, y;

    bool operator < (Point P) {
        if(y != b.y)
            return y < b.y;
        else
            return x < b.x;
    }
};

int main()
{
    takeInput();
    findRightmostLowestPoint();

    return 0;
}
