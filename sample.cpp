#include "seri.h"
#include "seriImpl.impl"
#include <iostream>
using namespace std;



//�ṹ������Ҫʵ��SerializAble�ӿ�
//node ʵ����SerializAble�ӿ� 
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
    //Seri���� 
    Seri s; 
    
    //Ҫ���л������� 
    node a;
    //���л� 
    cout << "���л�֮ǰ������:" << endl; 
    a.init();
    a.show();
    a.marshal(s);
    
    
    //�����л� 
    node b;
    cout << "�����л����ݽ��:" << endl;
    b.unmarshal(s);
    b.show();
    
    system("pause");
    return 0;    
}
