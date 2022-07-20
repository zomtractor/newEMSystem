//
// Created by 90828 on 2022-02-13.
//

#ifndef NEWEMSYSTEM_HASHSET_HPP
#define NEWEMSYSTEM_HASHSET_HPP
#include "List.hpp"
#include "Array.hpp"
template <class T>
class HashSet {
    static const int HASH_MOD = 61; //散列表基础长度
    List<T> buf[HASH_MOD]; //存放链地址的数组
    hash<T> hashCode;   //计算对象哈希值的模板
    int totalSize;//哈希表元素个数
    int getHashAddress(T elem){
        //cout<<"elem's hash is "<<hashCode(elem)<<",after mod "<<hashCode(elem)%HASH_MOD<<endl;
        return abs(int(hashCode(elem)))%HASH_MOD;
    }
public:
    HashSet() {
        totalSize=0;
    }

    void insert(T elem){    //添加元素
        if(count(elem)) return; //如果元素已存在则返回
        int index= getHashAddress(elem); //由哈希值求余计算散列位置
        buf[index].push_back(elem); //对应的链表插入元素
        totalSize++;
    }
    void remove(T elem){    //删除元素
        int index= getHashAddress(elem);
        buf[index].remove(elem);
        totalSize--;
    }
    bool count(T elem){     //判断元素是否存在
        int index= getHashAddress(elem);
        return buf[index].count(elem);
    }

    template<typename equal>
    T find(T elem,equal e=[](T a,T b){return a==b;}){   //查找元素，equal为条件类型
        int index= getHashAddress(elem);
        return buf[index].find(elem,e);
    }
    size_t size(){
        return totalSize;
    }
    bool empty(){
        return totalSize==0;
    }

};


#endif //NEWEMSYSTEM_HASHSET_HPP
