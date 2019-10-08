class node {
  constructor(r, c, walls) {
    this.parent = null;
    this.r = r;
    this.c = c;
    this.northWall = walls[0];
    this.eastWall = walls[1];
    this.southWall = walls[2];
    this.westWall = walls[3];
    this.onSolution = false;
    this.explored = false;
  }
  isOrigin() {
    return this.r == 0 && this.c == 0;
  }
}

class Grid {
  constructor() {
    this.items = [];
  }
  addRow(r) {
    this.items.push(r);
  }
  at(r, c) {
    if (r < 0||c < 0||r > this.items.length - 1|| c > this.items[0].length - 1) {
      return null;
    }
    return this.items[r][c];
  }
  isDestination(n) {
    return n.c == this.items[0].length - 1 && n.r == this.items.length - 1;
  }
  northOf(n) {
    return this.at(n.r - 1, n.c);
  }
  eastOf(n) {
    return this.at(n.r, n.c + 1);
  }
  southOf(n) {
    return this.at(n.r + 1, n.c);
  }
  westOf(n) {
    return this.at(n.r, n.c - 1);
  }
}

function bfs() {
  solution = new Grid();
  for (var i = 0; i < grid.length; i++) {
    var t = [];
    for (var j = 0; j < grid[0].length; j++) {
      t.push(new node(i, j, getBits(grid[i][j])));
    }
    solution.addRow(t);
  }
  exploring = solution.at(0, 0);
  exploring.explored = true;
  exploring.parent = "starting";
  var frontier = [];
  while (!solution.isDestination(exploring)) {
    if (solution.northOf(exploring) != null && !exploring.northWall) {
      if (solution.northOf(exploring).parent == null) {
        solution.northOf(exploring).parent = exploring;
        frontier.push(solution.northOf(exploring));
      }
    }
    if (solution.eastOf(exploring) != null && !exploring.eastWall) {
      if (solution.eastOf(exploring).parent == null) {
        solution.eastOf(exploring).parent = exploring;
        frontier.push(solution.eastOf(exploring));
      }
    }
    if (solution.southOf(exploring) != null && !exploring.southWall) {
      if (solution.southOf(exploring).parent == null) {
        solution.southOf(exploring).parent = exploring;
        frontier.push(solution.southOf(exploring));
      }
    }
    if (solution.westOf(exploring) != null && !exploring.westWall) {
      if (solution.westOf(exploring).parent == null) {
        solution.westOf(exploring).parent = exploring;
        frontier.push(solution.westOf(exploring));
      }
    }
    if (frontier.length == 0) {
      break;
    }
    exploring = frontier.pop(0);
  }
  path = [];
  while(exploring != "starting") {
    path.push(exploring);
    exploring.onSolution = true;
    exploring = exploring.parent;
  }
  path = path.reverse();
}