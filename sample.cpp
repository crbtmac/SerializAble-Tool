#include "seri.h"
#include "seriImpl.impl"
#include <iostream>
using namespace std;



//结构体数据要实现SerializAble接口
//node 实现了SerializAble接口 
struct node: public SerializAble
{
    u8 a;
    u16 b;
    u32 c;
    string d; 
    
    void init() 
    {
        a = 'x', b = 1234, c = 123456;
        char *p = "hello world";
        d = p;
    }
    
    void show()
    {
        cout << a << endl;
        cout << b << endl;    
        cout << c << endl;
        cout << d << endl;
    }
    
    void marshal(Seri &seri)
    {
        seri.add_data(a);
        seri.add_data(b);
        seri.add_data(c);   
        seri.add_data(d);
        seri.commit();
    }
    
    void unmarshal(Seri &seri)
    {
        node b;
        seri.read_data(b.a);
        seri.read_data(b.b);
        seri.read_data(b.c);
        seri.read_data(b.d);
        this->a = b.a;
        this->b = b.b;
        this->c = b.c;
        this->d = b.d;
    }
};

int main() 
{
    //Seri对象 
    Seri s; 
    
    //要序列化的数据 
    node a;
    //序列化 
    cout << "序列化之前的数据:" << endl; 
    a.init();
    a.show();
    a.marshal(s);
    
    
    //反序列化 
    node b;
    cout << "反序列化数据结果:" << endl;
    b.unmarshal(s);
    b.show();
    
    system("pause");
    return 0;    
}
