class Solution {
    public:
        string convert(string s, int numRows) {
            if (numRows == 1)
                return s;
            std::vector<std::string> mat(numRows);
            int line_num = 0, dir = 1;
            for(int i = 0; i < s.size(); i++) {
                mat[line_num].push_back(s[i]);
                line_num += dir;
                if(line_num < 0 || line_num >= numRows) {
                    dir = -dir;
                    line_num = line_num < 0 ? 1 : numRows - 2;
                }
            }
            for(int i = 1; i < numRows; i++)
                mat[0] += mat[i];
            return mat[0];
        }
    };