class LRUCache {
public:
    // Front = new, Back = old
    list<pair<int, int>> queue;
    unordered_map<int, list<pair<int, int>>::iterator> mp;
    int cap;
    LRUCache(int capacity) {
        mp.clear();
        cap = capacity;
    }

    int get(int key) {
        // 存在しない場合は何もしない
        if(mp.count(key) == 0) return -1;
        // 存在するはずなので、イテレータを返す
        auto cur = mp[key]; // iter
        int ans = cur->second;
        queue.erase(cur);
        queue.push_front({key, ans});
        mp[key] = queue.begin();
        return ans;
    }

    void put(int key, int value) {
        if(mp.count(key) == 1){
            auto cur = mp[key];
            queue.erase(cur);
        }
        queue.push_front({key, value});
        mp[key] = queue.begin();
        if(mp.size() > cap) {
            // 削除処理
            auto &[k, v] = *(--queue.end());
            mp.erase(k);
            queue.pop_back();
        }
    }
};
