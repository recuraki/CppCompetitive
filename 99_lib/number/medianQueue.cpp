#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T> struct medianQueue{
public:
    multiset<T> qL;
    multiset<T> qR;
    void balanceAll(){
        // 全てをきれいにする
        // 数合わせ
        if(qL.size() == 1 && qR.size() == 0) {}
        else if( (qL.size() + qR.size()) %2 == 0){
            // 偶数なら同じ数にしたい
            while(qL.size() > qR.size()){ // LからRに移す [1,2,3] [4] -> [1,2] [3,4]
                auto ret = qL.begin();
                qR.insert(-*ret);
                qL.erase(ret);
            }
            while(qL.size() < qR.size()){ // RからLに移す [1] [2,3,4] -> [1,2] [3,4]
                auto ret = qR.begin();
                qL.insert(-*ret);
                qR.erase(ret);
            }
        }
        else{
            // 奇数なら [1,2,3] [4,5]にしたい
            while(qL.size() > (qR.size() + 1)){ // LからRに移す [1,2,3,4] [5] -> [1,2,3] [4,5]
                auto ret = qL.begin();
                qR.insert(-*ret);
                qL.erase(ret);
            }
            while( (qL.size()+1) <= qR.size()){ // RからLに移す [1,2] [3,4,5] -> [1,2,3] -> [4,5]
                auto ret = qR.begin();
                qL.insert(-*ret);
                qR.erase(ret);
            }
        }
        // 次は左右のずれをなくしたい もしも、 [1,3] [2,4] then 3<->4 -> [1,2] [3,4]
        if (qR.size() == 0) return;
        while(1){
            auto numL = qL.begin();
            auto numR = qR.begin();
            if(-*numL <= *numR){
                break;
            }
            auto tmpL = *numL, tmpR = *numR;
            qL.erase(numL); qR.erase(numR);
            qL.insert(-tmpR); qR.insert(-tmpL);
        }
    }
    T get(){ // 中央値を求める
        // qLの一番目がほしい値(のマイナスがかかったもの)
        assert(qL.size() > 0);
        return -(*qL.begin());
    }
    T pop(){ // 中央値を取り出し、消す
        assert(qL.size() > 0);
        auto ret = (*qL.begin());
        qL.erase(ret);
        return -(ret);
    }
    void add(T x){ // 新しい値を追加する
        qL.emplace(-x);
        balanceAll();
    }
    void erase(T x){ // 存在する値を消す
        assert(qL.size() > 0);
        auto val = -(*qL.begin());
        if(x <= val){
            auto itr = qL.find(-x);
            assert(itr != qL.end());
            qL.erase(itr);
            balanceAll();
            return;
        }
        assert(qR.count(x) != 0);
        auto itr = qR.find(x);
        assert(itr != qR.end());
        qR.erase(itr);
        balanceAll();
    }
    void dump(){
        cout << "L:";
        for(auto x: qL) cout  << x << " ";
        cout << "\n";
        cout << "R:";
        for(auto x: qR) cout  << x << " ";
        cout << "\n";
    }
};

void medianQueue_sample1(){
    medianQueue<int> mq;
    mq.add(10); // 10
    cout << mq.get() << "\n"; // 10
    mq.add(5); // 5 10
    cout << mq.get() << "\n"; // 5
    mq.add(20); // 5 10 20
    cout << mq.get() << "\n"; // 10
    mq.add(30); // 5 10 20 30
    cout << mq.get() << "\n"; // 10
    mq.add(30); // 5 10 20 30 30
    cout << mq.get() << "\n"; // 20
    mq.erase(5);// 10 20 30 30
    cout << mq.get() << "\n"; // 20
    mq.erase(10);// 20 30 30
    cout << mq.get() << "\n"; //30
}

void medianQueue_sample2(){
    medianQueue<int> mq;
    mq.add(10); // 10
    mq.dump();
    mq.add(10); // 10
    mq.dump();
    cout << mq.get() << "\n"; // 10
    mq.add(10); // 10
    cout << mq.get() << "\n"; // 10
    mq.add(10); // 10
    cout << mq.get() << "\n"; // 10
    mq.add(10); // 10
    cout << mq.get() << "\n"; // 10

    mq.dump();
    mq.erase(10);// 20 30 30
    mq.dump();
    cout << mq.get() << "\n"; //30
    mq.erase(10);// 20 30 30
    cout << mq.get() << "\n"; //30
    mq.erase(10);// 20 30 30
    cout << mq.get() << "\n"; //30
    mq.erase(10);// 20 30 30
    cout << mq.get() << "\n"; //30
    mq.erase(10);// 20 30 30
    cout << mq.get() << "\n"; //30
}

int main(){
    //medianQueue_sample1();
    medianQueue_sample2();
    return 0;
}