  Node* BSTNearCommAncestor(Node* left, Node* right)
       {
              if (_root == NULL)
              {
                     return NULL;
              }
              Node* cur = _root;
              while (cur)
              {
                     if (cur->_data > left->_data && cur->_data > right->_data)
                     {
                           cur = cur->_left;
                     }
                     else if (cur->_data < left->_data && cur->_data < right->_data)
                     {
                           cur = cur->_right;
                     }
                     else
                     {
                           break;
                     }
              }
              if (cur)
              {
                     return cur;
              }
              return NULL;
       }
