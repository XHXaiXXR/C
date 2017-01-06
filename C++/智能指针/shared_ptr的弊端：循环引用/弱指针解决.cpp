#include<iostream>  
#include<boost\shared_ptr.hpp>  
#include<boost\weak_ptr.hpp>  
  
using namespace boost;  
using namespace std;  
  
/*将_next和_prve声明为弱指针，和外面的shared_ptr声明的节点指针配合使用,很明显，声明为弱指针的话，不会对引用计数器进行++；所以引用计数器都是1；所以可以释放！*/
struct Node  
{  
    /*boost::shared_ptr<Node> _next; 
    boost::shared_ptr<Node> _prve;*/  
  
    boost::weak_ptr <Node> _next;//声明为弱指针  
    boost::weak_ptr <Node> _prve;//声明为弱指针  
  
  
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