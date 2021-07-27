//
// Created by Kylian Lee on 2021/07/23.
//

#include <iostream>
#include <vector>
#define INF 2100000000

using namespace std;

vector<vector<int>> adj;
vector<int> cost;

void Dijkstra1(int src, int cities);
int Dijkstra2(int src, int dest, int cities);

int main(){
  int cities, roads, party_city;
  cin >> cities >> roads >> party_city;
  cost.resize(cities + 1, INF);      //  allocating and initialize cost array
  adj.resize(cities + 1);
  for (int i = 0; i <= cities; ++i) {   //  allocating adjacent matrix
    adj[i].resize(cities, INF);
  }
  for (int i = 0; i < roads; ++i) {   //  initialize adjacent matrix
    int src, dest, weight;
    cin >> src >> dest >>weight;
    adj[src][dest] = weight;
  }
  Dijkstra1(party_city, cities);
  for (int i = 1; i <= cities; ++i) {
    cout << i << " : " << cost[i] << endl;
  }
  for (int i = 1; i <= cities; ++i) {
    if(i == party_city)
      continue;
    cost[i] += Dijkstra2(i, party_city, cities);
  }
  int answer = 0;
  for (int i = 1; i <= cities; ++i) {
    if(cost[i] > answer)
      answer = cost[i];
  }
  for (int i = 1; i <= cities; ++i) {
    cout << i << " : " << cost[i] << endl;
  }
  cout << answer << endl;
}

void Dijkstra1(int src, int cities){
  cost[src] = 0;    //  set source city cost 0
  vector<bool> visited_city(cities + 1, false);
  int min, min_idx;
  int loop = cities;
  while(loop--){
    min = INF;
    for(int i = 1; i <= cities; i++){   //  find city to take minimum cost of cities
      if(!visited_city[i] && cost[i] < min) {  //  unvisited && min cost
        min = cost[i];
        min_idx = i;
      }
    }
    for (int i = 1; i <= cities; ++i) {
      if(cost[i] > (cost[min_idx] + adj[min_idx][i]))
        cost[i] = cost[min_idx] + adj[min_idx][i];
    }
    visited_city[min_idx] = true;
  }
}

int Dijkstra2(int src, int dest, int cities){
  vector<int> cost2(cities + 1, INF);
  cost2[src] = 0;
  vector<bool> visited_city(cities + 1, false);
  int min, min_idx;
  int loop = cities;
  while(loop--){
    min = INF;
    for(int i = 1; i <= cities; i++){   //  find city to take minimum cost of cities
      if(!visited_city[i] && cost2[i] < min) {  //  unvisited && min cost
        min = cost2[i];
        min_idx = i;
      }
    }
    for (int i = 1; i <= cities; ++i) {
      if(cost2[i] > (cost2[min_idx] + adj[min_idx][i]))
        cost2[i] = cost2[min_idx] + adj[min_idx][i];
    }
    visited_city[min_idx] = true;
    if(min_idx == dest)
      break;
  }
  return cost2[dest];
}