class Solution {
   public:
    int rand10() {
        while (true) {
            int a = rand7(), b = rand7();
            int res = (a - 1) * 7 + b - 1;
            if (res < 40) {
                return res / 4 + 1;
            }
        }
    }
};

// a little optimization
class Solution {
    public:
     int rand10() {
         while (true) {
             int a = rand7(), b = rand7();
             int res = (a - 1) * 7 + b - 1;
             if (res < 40) {
                 return res / 4 + 1;
             }
             // a -> 9
             b = rand7();
             a = res - 40;
             res = a * 7 + b - 1;
             if (res < 60) {
                 return res / 6 + 1;
             }
             // a -> 3
             b = rand7();
             a = res - 60;
             res = a * 7 + b - 1;
             if (res < 20) {
                 return res / 2 + 1;
             }
             // a -> 1，无法和b组合出rand10了，进入新一轮循环。
         }
     }
 };