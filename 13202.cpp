#include <iostream>
#include <iomanip>
#include <set>
#include <queue>
using namespace std;
int **arr;
int **arr_floyd;
vector<vector<int>> record;
int answer[300];
set<vector<int>> solution;

void findpath(int t, int depth, int target)
{
    if (t == -1)
    {
        vector<int> a;
        for (int i = depth - 2; i >= 0; --i)
        {
            a.push_back(answer[i]);
        }
        a.push_back(target);
        solution.insert(a);

        return;
    }
    int len = record[t].size();
    for (int i = len - 1; i >= 0; --i)
    {
        answer[depth] = record[t][i];
        findpath(record[t][i], depth + 1, target);
    }
}

void path(int n, int v)
{
    int dist[n];
    int path[n];
    priority_queue<pair<int, int>> q;
    vector<vector<string>> path_str(n, vector<string>(0));
    q.push({0, v});

    for (int i = 0; i < n; i++)
    {
        dist[i] = 1000000;
        path[i] = 0;
        record[i].clear();
        if (arr[v][i] < 1000000 && arr[v][i] > 0)
        {
            string str = to_string(v) + "->" + to_string(i);
            path_str[i].push_back(str);
        }
        else
        {
            string str = to_string(v);
            path_str[i].push_back(str);
        }
    }
    record[v].push_back(-1);
    dist[v] = 0;
    path[v] = 1;

    while (!q.empty())
    {
        int length = q.top().first;
        int current = q.top().second;
        q.pop();
        if (length > dist[current])
            continue;
        for (int i = 0; i < n; i++)
        {
            if (arr[current][i] == 0 || arr[current][i] == 1000000)
                continue;
            int node, cost;
            node = i;
            cost = arr[current][node];

            if (dist[node] > dist[current] + cost)
            {
                q.push({length + cost, node});
                dist[node] = dist[current] + cost;
                path[node] = path[current];

                path_str[node].clear();
                for (auto v : path_str[current])
                {
                    string str;
                    str = v + "->" + to_string(node);
                    path_str[node].push_back(str);
                }

                record[i].clear();
                record[i].push_back(current);
            }
            else if (dist[node] == dist[current] + cost)
            {
                path[node] = path[node] + path[current];
                for (auto v : path_str[current])
                {
                    string str;
                    str = v + "->" + to_string(node);
                    path_str[node].push_back(str);
                }
                record[i].push_back(current);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (arr_floyd[v][i] >= 1000000 || v == i)
            continue;

        solution.clear();
        cout << "Path(" << v << "," << i << "):";

        findpath(i, 0, i);

        vector<int> a = *(solution.begin());
        int a_len = a.size();
        for (int i = 0; i < a_len - 1; i++)
        {
            cout << a[i] << "->";
        }
        cout << i << "\n";
        cout << "Difficulty:";
        cout << dist[i] << "\n";
    }
}

int main()
{
    int n;
    cin >> n;

    arr = new int *[n];
    arr_floyd = new int *[n];
    record.resize(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
        arr_floyd[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;
            if (i == j)
                arr_floyd[i][j] = arr[i][j] = 0;
            else if (num == 0)
                arr_floyd[i][j] = arr[i][j] = 1000000;
            else
                arr_floyd[i][j] = arr[i][j] = num;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (arr_floyd[i][k] + arr_floyd[k][j] < arr_floyd[i][j])
                    arr_floyd[i][j] = arr_floyd[i][k] + arr_floyd[k][j];

    for (int i = 0; i < n; i++)
        path(n, i);

    for (int i = 0; i < n; i++)
    {
        double num = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j && arr_floyd[j][i] < 1000000 && arr_floyd[j][i] != 0)
            {
                num = num + 1 / (double)arr_floyd[j][i];
            }
        }
        cout << "Centrality(" << i << "):";
        cout << fixed;
        cout << std::setprecision(3) << num << "\n";
    }
}