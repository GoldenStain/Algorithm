class RandomizedSet {
public:
    RandomizedSet() {
        srand(time(NULL));
    }
    
    bool insert(int val) {
        if (dict.find(val) != dict.end())
            return false;
        dict[val] = arr.size();
        arr.emplace_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!dict.count(val))
            return false;
        int k = dict[val];
        int last = arr.back();
        arr[k] = last;
        dict[last] = k;
        arr.pop_back();
        dict.erase(val);
        return true;
    }
    
    int getRandom() {
        int k = rand() % arr.size();
        return arr[k];
    }
private:
    std::vector<int> arr;
    std::unordered_map<int, int> dict;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */