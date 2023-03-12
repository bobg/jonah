#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

using namespace std;

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_withVector = false;
            m_it = m_end;
        }

        Iterator(vector<ValueType>& v) {
            m_withVector = true;
            m_it = v.begin();
            m_end = v.end();
        }

        ValueType& get_value() const
        {
            return *m_it;
        }

        bool is_valid() const
        {
            if (m_withVector == false) {
                return false;
            }

            if (m_it != m_end) {
                return true;
            }
            else {
                return false;
            }
        }

        void advance()
        {
            m_it++;
        }

      private:
          typename vector<ValueType>::iterator m_it;
          typename vector<ValueType>::iterator m_end;
          bool m_withVector;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        delete_helper(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr) {
            m_root = new Node(key, value);
        }

        Node* insert_node = find_helper_helper(key, m_root);

        if (insert_node->m_key == key) {
            insert_node->m_values.push_back(value);
            return;
        }

        if (insert_node->m_key > key) {
            insert_node->m_left = new Node(key, value);
        }
        else {
            insert_node->m_right = new Node(key, value);
        }
    }

    Iterator find(const KeyType& key) const
    {
        TreeMultimap<KeyType, ValueType>::Iterator it;

        if (m_root == nullptr) {
            return it;
        }

        Node* cur = find_helper(key, m_root);

        if (cur != nullptr) {
            it = Iterator(cur->m_values);
        }

        return it;
    }

  private:
      struct Node {
      public:
          Node(KeyType key, ValueType value) {
              m_left = nullptr;
              m_right = nullptr;
              m_key = key;
              m_values.push_back(value);
          }
          Node* m_left;
          Node* m_right;
          KeyType m_key;
          vector<ValueType> m_values;
      };

      Node* m_root;

      Node* find_helper(const KeyType& key, Node* n) const {
          Node* m = find_helper_helper(key, n);

          if (key != m->m_key) {
              return nullptr;
          }

          return m;
      }

      Node* find_helper_helper(const KeyType& key, Node* n) const {
          if (n->m_key == key) {
              return n;
          }

          if (n->m_key > key) {
              if (n->m_left == nullptr) {
                  return n;
              }
              Node* m = find_helper_helper(key, n->m_left);
              return m;
          }
          else {
              if (n->m_right == nullptr) {
                  return n;
              }
              Node* m = find_helper_helper(key, n->m_right);
              return m;
          }
      }

      void delete_helper(Node* n) {
          if (n != nullptr) {
              delete_helper(n->m_left);
              delete_helper(n->m_right);
              delete n;
          }
      }
};

#endif // TREEMULTIMAP_INCLUDED
