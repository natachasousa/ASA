/*
 * Program that determines the maximum number of transmissions a given disease can
 * produce in a population, taking into account the interactions among individuals.
 *
 * Alunas: Beatiz Martinho (106835), Natacha Sousa (107413)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int n, m, v1, v2, maxSaltos;
vector<vector<int>> graph;
vector<vector<int>> graphTrans;
vector<int> topologic;
vector<int> IDs;
int t = 0;
int id = 1;

int DFSvisit(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& closureTime) {

    stack<int> s;

    s.push(v);
    while (!s.empty()) {
        int u = s.top();
        if (visited[u] == false) {
            visited[u] = true; 
            t++;
        }

        bool aux = true;
        for (int adj : graph[u]) {
            if (visited[adj] == false) {
                aux = false;
                s.push(adj);
                break;
            }
        }

        if (aux == true) {
            s.pop();
            closureTime[u] = t++;
        }
    }

    return t;
}

void DFSvisit2(int v, vector<vector<int>>& graphTrans, vector<bool>& visited, vector<int>& nodePath) {
    stack<int> s;

    s.push(v);
    while (!s.empty()) {
        int u = s.top();
        if (visited[u] == false) {
            IDs[u] = id;
            visited[u] = true;
        }

        bool aux = true;
        for (int adj : graphTrans[u]) {
            if (visited[adj] == false) {
                s.push(adj);
                visited[adj] = true;
                IDs[adj] = id;
                aux = false;
                break;
            }
 
            if (IDs[u] != IDs[adj]) {
                nodePath[u] = max(nodePath[adj] + 1, nodePath[u]);
            } else {
                nodePath[u] = max(nodePath[adj], nodePath[u]);
            }
        }

        if (aux == true) {
            s.pop();
        }
    }
}

// Depth First Search for transposed graph
void DFS2(vector<vector<int>>& graphTrans, vector<int>& closureTime) {
    vector<bool> visited(n, false);
    vector<int> nodePath(n, 0);
    IDs.resize(n, 0);

    // get topologic order
    vector<int> topologic(n);
    iota(topologic.begin(), topologic.end(), 0);
    sort(topologic.begin(), topologic.end(), [&closureTime](int i, int j) { return closureTime[i] > closureTime[j]; });

    for (int i : topologic) {
        if (visited[i] == false) {
            DFSvisit2(i, graphTrans, visited, nodePath);
            id++;
        }
    }

    maxSaltos = *max_element(nodePath.begin(), nodePath.end());
}

// Depth First Search for graph
vector<int> DFS(vector<vector<int>>& graph) {
    vector<int> closureTime(n, 0);
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        if (visited[i] == false) {
            t = DFSvisit(i, graph, visited, closureTime);
        }
    }
    return closureTime;
}

int main() {

    scanf("%d %d", &n, &m);

    graph.resize(n);
    graphTrans.resize(n);

    // store graph and transposed graph
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &v1, &v2);
        graph[v1 - 1].push_back(v2 - 1);
        graphTrans[v2 - 1].push_back(v1 - 1);
    }

    vector<int> closureTime = DFS(graph);
    DFS2(graphTrans, closureTime);

    printf("%d\n", maxSaltos);

    return 0;
}