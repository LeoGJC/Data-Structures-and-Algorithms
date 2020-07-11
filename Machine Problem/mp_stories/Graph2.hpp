#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <queue>

using namespace std;

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  // path.push_back(start);
  // std::list<edgeListIter> edges = incidentEdges(start);
  // string current = start;
  // for (auto it: edges) {
  //   stringstream go1(adjList.at(it).properties_["value"]);
  //   int x = 0;
  //   go1 >> x;
  //   if (it.dest != current) {
  //     stringstream go2(adjList.at(it.dest).properties_["value"]);
  //     int y = 0;
  //     go2 >> y;
  //     if (x + it.weight() < y || y == 0) {
  //       adjList[it.dest].properties_["value"] = x + it.weight();
  //       adjList[it.dest].properties_["previous"] = it;
  //     }
  //     adjList.at(it.dest).properties_.insert({"visited", "yes"});
  //   }
  // }
  unordered_map<std::string, std::string> previous;
  unordered_map<std::string, double> distance;
  unordered_map<std::string, double> visited;
  queue<std::string> priority;
  priority.push(start);
  string current = start;
  for (auto it : vertexMap) {
    distance[it.first] = 0;
    visited[it.first] = 0;
  }
  while(!priority.empty()) {
    current = priority.front();
    //cout << visited[current] << "-------" << endl;
    // if (visited.at(current) == 1) {
    //   continue;
    // }
    priority.pop();
    visited[current] = 1;
    std::list<edgeListIter> go = adjList[current];
    for (auto gogo : go) {
      // if (visited.at(gogo.get().key())) {
      //
      // }
      string location = gogo->get().source().key() == current ? gogo->get().dest().key() : gogo->get().source().key();
      if (visited.at(location) == 0) {
        priority.push(location);
      }
      if ((distance.at(location) == 0 && location != start)|| distance.at(gogo->get().dest().key()) > distance.at(location) + gogo->get().weight()) {
        distance[location] = distance[current] + gogo->get().weight();
        previous[location] = current;
        priority.push(location);
      }
    }

  }
  current = end;
  path.insert(path.begin(), current);
  while (current != start) {
    //cout << "------6" << endl;
    path.insert(path.begin(), previous[current]);
    current = previous[current];
  }
  return path;
}
