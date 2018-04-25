//
// Created by ernesto on 13/01/18.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<pair<int, int>  > > adj;
int n, m, u, v, c;

int start, finish;

int dijikstra() {
    priority_queue<pair<int, int> > vertex;
    vector<bool> visited(n, false);
    vertex.push(make_pair(0, start));

    while (not vertex.empty()) {
        pair<int, int> proc = vertex.top();
        vertex.pop();

        if (visited[proc.second])
            continue;

        visited[proc.second] = true;

        if (proc.second == finish)
            return -proc.first;


        for (int i = 0; i < adj[proc.second].size(); i++) {
            if (!visited[i]) {
                vertex.push(make_pair(
                        proc.first - adj[proc.second][i].second, adj[proc.second][i].first));
            }
        }
    }
    return -1;
}

int main() {
    while (cin >> n >> m) {
        adj = vector<vector<pair<int, int> > >(n, vector<pair<int, int> >());
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> c;
            adj[u].push_back(make_pair(v, c));
        }

        cin >> start >> finish;

        int d = dijikstra();

        if (d > 0)
            cout << d << endl;
        else
            cout << "no path from " << start << " to " << finish << endl;
    }
}
