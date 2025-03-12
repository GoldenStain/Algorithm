class Solution {
    public:
        string simplifyPath(string path) {
            std::vector<std::string> stk;
            // 有些输入不以/结尾，导致我们需要特判，我们在此给他手动加上一个
            path.append("/");
            std::string ans = "/";
            ans.reserve(path.size());
            size_t pos = path.find("/");
            while(pos != std::string::npos && pos < path.size()) {
                while(path[pos] == '/')
                    pos++;
                size_t next_pos = path.find("/", pos);
                std::string now_str = path.substr(pos, next_pos - pos);
                // 如果为空，说明最后只剩下若干/，没有意义
                if (now_str.empty())
                    break;
                // 上级目录
                if (now_str == "..") {
                    if (stk.size())
                        stk.pop_back();
                }
                else if (now_str == ".") {
                    // do nothing
                }
                else 
                    stk.push_back(now_str);
                pos = next_pos;
            }
            for (auto si: stk) {
                ans.append(si);
                ans+="/";
            }
            // 删去最后一个多余的ans，但是要保证此时ans不是只有一个/
            if (ans.size() > 1)
                ans.erase(ans.size() - 1, 1);
            return ans;
        }
    };