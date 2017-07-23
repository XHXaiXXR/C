  void GetNodePath(Node* root,const Node*& node, vector<Node*>& v, const bool& flag)
       {
              if (root == NULL || flag == true)
              {
                     //空?节??点??或??者?是??已??经-找??到??node节??点??的??情??况?下?无T需??继??续?递?Y归??了??
                     return;
              }
              GetNodePath(root->_left, node, v,flag);
              GetNodePath(root->_right, node, v,flag);
              if (root == node || flag == true)
              {
                     //找??到??这a个?节??点??或??者?是??已??经-找??到??这a个?节??点??路??径?上??的??其?他?节??点??需??要?a添???加??到??路??径?中D
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
