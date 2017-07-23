      Node* _NearCommAncestor(Node* root, Node* node1, Node* node2)
       {
              if (root == NULL)
              {
                     return NULL;
              }
              Node* left = _NearCommAncestor(root->_left, node1, node2);
              Node* right = _NearCommAncestor(root->_right, node1, node2);
              if (left && right)
              {
                     return root;
              }
              if (root == node1)
              {
                     return node1;
              }
              if (root == node2)
              {
                     return node2;
              }
              if (left == NULL && right)
              {
                     return right;
              }
              if (right == NULL && left)
              {
                     return left;
              }
       }
       Node* NearCommAncestor(Node* node1, Node* node2)
       {
              return _NearCommAncestor(_root, node1, node2);
       }
