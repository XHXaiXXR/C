#include<iostream>  
#include<boost\shared_ptr.hpp>  
#include<boost\weak_ptr.hpp>  
  
using namespace boost;  
using namespace std;  
  
/*��_next��_prve����Ϊ��ָ�룬�������shared_ptr�����Ľڵ�ָ�����ʹ��,�����ԣ�����Ϊ��ָ��Ļ�����������ü���������++���������ü���������1�����Կ����ͷţ�*/
struct Node  
{  
    /*boost::shared_ptr<Node> _next; 
    boost::shared_ptr<Node> _prve;*/  
  
    boost::weak_ptr <Node> _next;//����Ϊ��ָ��  
    boost::weak_ptr <Node> _prve;//����Ϊ��ָ��  
  
  
    ~Node()  
    {  
        cout<<"~Node"<<endl;  
    }  
      
};  
  
void test()  
{  
    boost::shared_ptr <Node> s1(new Node);  
    boost::shared_ptr <Node> s2(new Node);  
  
    //������s1��s2�������������  
    s1->_next = s2;  
    s2->_prve = s1;  
  
    cout<<s1.use_count() <<endl;  
    cout<<s2.use_count() <<endl;  
}  
  
int main()  
{  
    test();  
    system("pause");  
    return 0;  
}  