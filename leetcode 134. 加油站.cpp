class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int start = 0, n = gas.size();
    while (start < n) {
      int sumGas = 0, sumCost = 0, cnt = 0;
      while (cnt < n) {
        int j = (start + cnt) % n;
        sumGas += gas[j];
        sumCost += cost[j];
        if (sumCost > sumGas) {
          break;
        }
        cnt++;
      }
      if (cnt == n)
        return start;
      start = start + cnt + 1;
    }
    return -1;
  }
};

// Better solution

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size(), minPos = -1, minValue = INT_MAX, sum = 0;
    for (int i = 0; i < n; i++) {
      sum += gas[i] - cost[i];
      if (sum < minValue) {
        minValue = sum;
        minPos = i;
      }
    }
    return (sum < 0) ? -1 : (minPos + 1) % n;
  }
};