#include <iostream>
#include <string>
using namespace std;

class Node
{
    friend class list;

public:
    Node(long long int u)
    {
        val = u;
        this->right = this->left = this->up = this->down = this;
    }
    ~Node()
    {
        right = left = down = up = nullptr;
    }

private:
    Node *right, *left, *down, *up;
    long long int val;
};

class list
{
public:
    list()
    {
        header = new Node(0);
    }

    void printEnd()
    {
        cout << "PrintEnd\n";
        Node *np = header->up;
        while (np != header)
        {
            Node *s = np->left;
            while (s != np)
            {
                cout << '(' << s->val << ',' << np->val << ')' << '\n';
                s = s->left;
            }
            np = np->up;
        }
    }
    void printFront()
    {

        Node *head = header->down;
        cout << "PrintFront\n";
        while (head != header)
        {
            Node *np = head->right;
            while (np != head)
            {
                cout << '(' << np->val << ',' << head->val << ')' << '\n';
                np = np->right;
            }
            head = head->down;
        }
    }
    void bomb()
    {

        long long int x, y;
        cin >> x >> y;
        Node *np;
        np = find(x - 1, y);
        deleteNode(np);

        np = find(x + 1, y);
        deleteNode(np);
        np = find(x, y);
        deleteNode(np);

        np = find(x, y + 1);

        deleteNode(np);

        np = find(x, y - 1);
        deleteNode(np);
    }
    void house()
    {
        long long int x, y;
        cin >> x >> y;
        Node *np = new Node(x);
        insert(np, x, y);
    }

private:
    Node *header;

    void insert(Node *data, long long int x, long long int y)
    {
        Node *row = header->down;
        bool flag = false;
        while (row != header)
        {
            if (row->val == y)
            {
                flag = true;
                break;
            }
            if (row->val > y)
                break;
            row = row->down;
        }

        if (flag)
        {
            Node *np = row->right;

            bool f = true;
            while (np != row)
            {
                if (np->val == x)
                {
                    f = false;
                    break;
                }
                if (np->val > x)
                    break;
                np = np->right;
            }
            if (f)
            {
                data->right = np;
                data->left = np->left;
                (np->left)->right = data;
                np->left = data;
            }
            else
                delete data;
        }

        else
        {
            Node *np = new Node(y);

            (row->up)->down = np;
            np->up = row->up;
            np->down = row;
            row->up = np;

            np->left = np->right = data;
            data->right = data->left = np;
        }
        header->val++;
    }

    Node *find(long long int x, long long int y)
    {
        bool flag = false;
        Node *np = header->down;
        while (np != header)
        {
            if (np->val == y)
            {
                flag = true;
                break;
            }
            if (np->val > y)
                return nullptr;
            np = np->down;
        }

        if (flag)
        {
            Node *n = np->right;

            while (n != np)
            {
                if ((n->val) == x)
                    return n;
                n = n->right;
            }
            return nullptr;
        }
        else
            return nullptr;
    }
    void deleteNode(Node *np)
    {
        if (np != nullptr)
        {
            if (np->right == np->left)
            {
                ((np->right)->up)->down = (np->right)->down;
                ((np->right)->down)->up = (np->right)->up;
                delete np->right;
            }
            else
            {
                (np->right)->left = np->left;
                (np->left)->right = np->right;
            }
            delete np;
            header->val--;
        }
    }
};

int main()
{
    int n;
    string str;
    cin >> n;
    list L;

    while (n--)
    {
        cin >> str;

        if (str == "PrintEnd")
            L.printEnd();
        else if (str == "Bomb")
            L.bomb();
        else if (str == "House")
            L.house();
        else if (str == "PrintFront")
            L.printFront();
    }
}