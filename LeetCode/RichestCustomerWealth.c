int maximumWealth(int **accounts, int accountsSize, int *accountsColSize) {
  int biggestWealth = 0, sum;
  for (int i = 0; i < accountsSize; i++) {
    sum = 0;
    for (int j = 0; j < accountsColSize[i]; j++) {
      sum += accounts[i][j];
    }
    if (biggestWealth < sum)
      biggestWealth = sum;
  }
  return biggestWealth;
}
