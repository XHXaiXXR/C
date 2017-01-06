#include<iostream>  
#include<boost\shared_ptr.hpp>  
#include<boost\weak_ptr.hpp>  
  
using namespace boost;  
using namespace std;  
  
  
struct Node  
{  
    boost::shared_ptr<Node> _next;  
    boost::shared_ptr<Node> _prve;  
  
    ~Node()  
    {  
        cout<<"~Node"<<endl;  
    }  
      
};  
  
void test()  
{  
    boost::shared_ptr <Node> s1(new Node);  
    boost::shared_ptr <Node> s2(new Node);  
  
    //我们让s1和s2两个结点连起来  
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