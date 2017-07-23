  void GetNodePath(Node* root,const Node*& node, vector<Node*>& v, const bool& flag)
       {
              if (root == NULL || flag == true)
              {
                     //��?��??��??��??��?��??��??��-��??��??node��??��??��??��??��?��?��T��??��??��?��?Y��??��??
                     return;
              }
              GetNodePath(root->_left, node, v,flag);
              GetNodePath(root->_right, node, v,flag);
              if (root == node || flag == true)
              {
                     //��??��??��a��?��??��??��??��?��??��??��-��??��??��a��?��??��??·??��?��??��??��?��?��??��??��??Ҫ?a��???��??��??·??��?��D
                     v.push_back(root);
                     flag = true;
              }
       }
       Node* NearCommAncestor(Node* left, Node* right)
       {
              if (_root == NULL || left == NULL || right == NULL)
              {
                     return;
              }
              vector<Node*> v1;
              GetNodePath(_root, left, v1, false);
              vector<Node*> v2;
              GetNodePath(_root, right, v2, false);
              int i = 0;
              while ((i < v1.size() - 1) && (i < v2.size() - 1))
              {
                     if (v1[i+1] != v2[i+1])
                     {
                           break;
                     }
                     else
                     {
                           ++i;
                     }
              }
              if ((i < v1.size() - 1) && (i < v2.size() - 1))
              {
                     return v1[i];
              }
              return NULL;
       }
