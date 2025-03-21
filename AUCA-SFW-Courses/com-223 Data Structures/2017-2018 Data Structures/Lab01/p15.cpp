#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

int main()
{
    cout << "a: ";
    int32_t a; cin >> a;
    
    cout << "b: ";
    int32_t b; cin >> b;
    
    if (a > b)
    {
        swap(a, b);
    }
    
    cout << sizeof(long) << endl;
    
    int64_t s = 0;
    for (int32_t i = a; i <= b; ++i)
    {
        s += i;
    }
    
    cout << "sum(" << a << ", " << b << ") = " << s << endl;
    
    s = int64_t(a + b) * (b - a + 1) / 2;
    
    cout << "sum(" << a << ", " << b << ") = " << s << endl;
    
    
    return 0;
}