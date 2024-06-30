#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int V;
    vector<vector<pair<int, int>>> adj; // undirected graph with edge weights

public:
    Graph(int V)
    {
        this->V = V;
        adj = vector<vector<pair<int, int>>>(V + 1);
    }
    void add_edge(int a, int b, int dist)
    {
        if (a > V || b > V || a <= 0 || b <= 0)
        {
            cout << "Cities out of bound, addition unsuccessful." << endl;
            return;
        }
        adj[a].push_back({b, dist});
        adj[b].push_back({a, dist});
    }
    int find_min_dist(int src, int dest)
    {
        if (src > V || dest > V || src <= 0 || dest <= 0)
            return -1;

        vector<int> vis(V + 1, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, src});

        while (!pq.empty())
        {
            int dist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (node == dest)
                return dist;
            vis[node] = 1;

            for (auto it : adj[node])
            {
                if (!vis[it.first])
                {
                    pq.push({dist + it.second, it.first});
                }
            }
        }
        return -2;
    }
}; 

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input the cities
    int V, E;
    cout << "Please enter no. of cities :" << endl;
    cin >> V;
    Graph network(V);

    cout << "Enter no. of edges/lines between cities :" << endl;
    cin >> E;

    cout << "Enter city1, city2 and dist :" << endl;
    for (int i = 0; i < E; i++)
    {
        int city1, city2, dist;
        cin >> city1 >> city2 >> dist;
        network.add_edge(city1, city2, dist);
    }
    cout << "All cities entered." << endl;

    int q;
    cout << "Enter number of queries." << endl;
    cin >> q;

    while (q--)
    {
        int src, dest;
        cin >> src >> dest;
        int ans = network.find_min_dist(src, dest);
        if (ans == -1)
            cout << "Cities out of Bound." << endl;
        else if (ans == -2)
            cout << "Cities are not connected." << endl;
        else
            cout << "Distance between city " << src << " and " << dest << " is: " << ans << "." << endl;
    }

    return 0;
}
