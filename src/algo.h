void markDirection(char direction, char *path, int *pathLength) {
  if (direction == 'L') {
    path[(*pathLength)++] = 'L';
  } else if (direction == 'R') {
    path[(*pathLength)++] = 'R';
  } else if (direction == 'S') {
    path[(*pathLength)++] = 'S';
  } else if (direction == 'B') {
    path[(*pathLength)++] = 'B';
  }
}

void optimizePath(char *path, int *pathLength, bool isRHW) {
  int newPathLength = 0;
  if (isRHW) { // using RHW
    for (int i = 0; i < *pathLength; i++) {
      if (path[i] == 'R' && path[i + 1] == 'B' && path[i + 2] == 'S') {
        path[newPathLength++] = 'L';
        i += 2;
      } else if (path[i] == 'R' && path[i + 1] == 'B' && path[i + 2] == 'R') {
        path[newPathLength++] = 'S';
        i += 2;
      } else if (path[i] == 'S' && path[i + 1] == 'R' && path[i + 2] == 'R') {
        path[newPathLength++] = 'B';
        i += 2;
      } else if (path[i] == 'R' && path[i + 1] == 'B' && path[i + 2] == 'L') {
        path[newPathLength++] = 'S';
        i += 2;
      } else if (path[i] == 'S' && path[i + 1] == 'B' && path[i + 2] == 'R') {
        path[newPathLength++] = 'L';
        i += 2;
      } else if (path[i] == 'L' && path[i + 1] == 'B' && path[i + 2] == 'S') {
        path[newPathLength++] = 'R';
        i += 2;
      } else {
        path[newPathLength++] = path[i];
      }
    }
  } else { // using LHW
    for (int i = 0; i < *pathLength; i++) {
      if (path[i] == 'L' && path[i + 1] == 'B' && path[i + 2] == 'L') {
        path[newPathLength++] = 'S';
        i += 2;
      } else if (path[i] == 'L' && path[i + 1] == 'B' && path[i + 2] == 'R') {
        path[newPathLength++] = 'B';
        i += 2;
      } else if (path[i] == 'R' && path[i + 1] == 'B' && path[i + 2] == 'L') {
        path[newPathLength++] = 'B';
        i += 2;
      } else if (path[i] == 'R' && path[i + 1] == 'B' && path[i + 2] == 'R') {
        path[newPathLength++] = 'S';
        i += 2;
      } else if (path[i] == 'S' && path[i + 1] == 'B' && path[i + 2] == 'S') {
        path[newPathLength++] = 'B';
        i += 2;
      } else if (path[i] == 'L' && path[i + 1] == 'B' && path[i + 2] == 'S') {
        path[newPathLength++] = 'R';
        i += 2;
      } else {
        path[newPathLength++] = path[i];
      }
    }
  }
  *pathLength = newPathLength;
}
