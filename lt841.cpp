void dfs(int room, vector<vector<int>> &rooms, vector<bool> &vis) {
  vis[room] = true;
  for (auto key : rooms[room]) {
    if (!vis[key]) {
      dfs(key, rooms, vis);
    }
  }
}

bool canVisitAllRooms(vector<vector<int>> &rooms) {
  int n = rooms.size();
  vector<bool> vis(n, false);

  dfs(0, rooms, vis);

  for (auto room : vis) {
    if (!room)
      return false;
  }

  return true;
}