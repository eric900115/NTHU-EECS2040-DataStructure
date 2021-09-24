#include <string>
#include <iostream>
#define max(a, b)     \
    {                 \
        a > b ? a : b \
    }
#include "function.h"
#include <stddef.h>
using namespace std;

BaseQueue<char> *q = new BaseQueue<char>[100];
BaseStack<string> s;

int slot[100] = {0}, insert_row = 0, insert_col, insertion_counter;

void insert(int L)
{
    std::cin.tie(0);
    int num, strlen;
    string str;
    cin >> num >> str;

    insertion_counter = insert_row = 0;
    strlen = str.length();

    for (int i = num; i < num + strlen; i++)
        insert_row = max(insert_row, slot[i]);

    for (int i = num; i < num + strlen; i++)
    {
        insert_col = i;
        (q[i]).push(str[insertion_counter]);
        insertion_counter++;
    }

    for (int i = num; i < num + strlen; i++)
        slot[i] = insert_row + 1;
}

string first_row(int L, bool print)
{
    cout << "BOTTOM_ROW\n";

    string str = "";

    for (int i = 0; i < L; i++)
        if (!q[i].empty())
            str += (q[i].front());
        else
            str += "~";

    cout << str << "\n";
    return str;
}
void query(int L)
{

    string str = "", str_comp;
    size_t query_num;

    cin >> str_comp;

    for (int i = 0; i < L; i++)
        if (!q[i].empty())
            str += (q[i].front());
        else
            str += "~";

    query_num = str.find(str_comp);

    if (query_num != std::string::npos)
    {
        int query_start, query_end;
        query_start = query_num;
        query_end = query_num + str_comp.length();

        for (int i = query_start; i < query_end; i++)
        {
            q[i].pop();
            slot[i]--;
        }

        s.push(str_comp);
    }
}
void flush()
{
    cout << "FLUSH\n";

    while (!s.empty())
    {
        cout << s.top() << "\n";
        s.pop();
    }
}
void reset(int L)
{
    for (int i = 0; i < L; i++)
        q[i].~BaseQueue();

    q = new BaseQueue<char>[L];
    while (!s.empty())
        s.pop();

    for (int i = 0; i < L; i++)
        slot[i] = 0;
}

template <class T>
BaseQueue<T>::BaseQueue()
{
    _queue = new T[10000];
    _front = 0;
    _rear = 0;
    capacity = 10000;
}

template <class T>
BaseQueue<T>::~BaseQueue()
{
    delete[] _queue;
}

// Check if the stack is empty
template <class T>
bool BaseQueue<T>::empty()
{
    return _rear == _front;
}

// Return the size of the queue
template <class T>
int BaseQueue<T>::size()
{
    int s;

    if (_front < _rear)
        s = _rear - _front;
    else
        s = capacity - (_front - _rear);
    return s;
}

// Return the front element
template <class T>
T &BaseQueue<T>::front()
{
    return _queue[(_front + 1) % capacity];
}

// Insert a new element at rear
template <class T>
void BaseQueue<T>::push(const T &item)
{
    for (int i = slot[insert_col]; i < insert_row; i++)
    {
        if ((_rear + 1) % capacity == _front)
        {
            int s, q_size;
            T *DoubleQueue = new T[capacity + 3000];

            s = _front;
            q_size = size();
            for (int i = 1; i <= q_size; i++)
                DoubleQueue[i] = _queue[++s % capacity];
            _rear = size();
            _front = 0;
            capacity += 3000;
            delete[] _queue;
            _queue = DoubleQueue;
        }

        _rear = (_rear + 1) % capacity;
        _queue[_rear] = '@';
    }

    if ((_rear + 1) % capacity == _front)
    {
        int s, q_size;
        T *DoubleQueue = new T[capacity + 3000];

        s = _front;
        q_size = size();
        for (int i = 1; i <= q_size; i++)
            DoubleQueue[i] = _queue[++s % capacity];
        _rear = size();
        _front = 0;
        capacity += 3000;
        delete[] _queue;
        _queue = DoubleQueue;
    }

    _rear = (_rear + 1) % capacity;
    _queue[_rear] = item;
}

// Delete one element from front
template <class T>
void BaseQueue<T>::pop()
{
    _front = (_front + 1) % capacity;
}
// Constructor
template <class T>
BaseStack<T>::BaseStack()
{
    _stack = new T[100000];
    _top = -1;
    capacity = 100000;
}

// Destructor
template <class T>
BaseStack<T>::~BaseStack()
{
    delete[] _stack;
}

// Check if the stack is empty
template <class T>
bool BaseStack<T>::empty()
{
    return _top == -1;
}

// Return the size of the stack
template <class T>
int BaseStack<T>::size()
{
    return _top;
}

// Return the top element
template <class T>
T &BaseStack<T>::top()
{
    return _stack[_top];
}

// Insert a new element at top
template <class T>
void BaseStack<T>::push(const T &item)
{
    capacity--;
    _stack[++_top] = item;
    //_stack[_top].shrink_to_fit();
}

// Delete one element from top
template <class T>
void BaseStack<T>::pop()
{
    _top--;
    capacity++;
}
