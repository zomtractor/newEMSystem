//
// Created by 90828 on 2022-02-11.
//

#ifndef NEWEMSYSTEM_ARRAY_HPP
#define NEWEMSYSTEM_ARRAY_HPP

#include <ostream>
#include <cstring>
template<class T>
class Array {
    T *buf;
    int bufSize;
    int ptr;

    template<typename CompareMethod>
    void qsort(int l,int r,CompareMethod compareMethod){    //快速排序
        auto getIndex=[&](int l,int r){ //内部lambda函数，快速排序的主体
            T t=buf[l];//选择buf[l]为枢纽记录
            while(l<r){
                while(l<r && compareMethod(t,buf[r])) r--;
                buf[l]=buf[r];//将比枢纽记录（小）的记录移动到低短
                while(l<r && compareMethod(buf[l],t)) l++;
                buf[r]=buf[l];//将比枢纽记录（大）的记录移动到高端
            }
            buf[l]=t;
            return l;//返回枢纽位置
        };
        if(l>=r) return;
        int index=getIndex(l,r);
        qsort(l,index-1,compareMethod); //对（低）子数组递归排序
        qsort(index+1,r,compareMethod); //对（高）子数组递归排序
    }

public:
    T& operator[](int i){
       return buf[i];
    }
    Array():bufSize(256),ptr(0){buf = new T[256];};
    Array(int bufSize_):bufSize(bufSize_),ptr(bufSize_){buf = new T[bufSize_];}
    ~Array(){delete[] buf;}
    size_t size(){
        return ptr;
    }
    bool empty(){
        return ptr==0;
    }
    void reSize(int size){  //重新调整大写
        T *arr = new T[size];
        int sz=std::min(bufSize,size);  //获取实际大小，若新数组比旧的小则舍弃部分数据
        for(int i=0;i<sz;i++) arr[i]=buf[i];    //拷贝数组信息
        delete[] buf;   //释放原有空间
        buf=arr;
    }

    bool seek(int pos){ //调整数组大小
        if(pos>=bufSize||pos<0) return false;
        ptr=pos;
        return true;
    }
    bool push_back(T val){  //在尾部存入数据
        if(ptr==bufSize) return false;
        buf[ptr++]=val;
        return true;
    }

    int find(T val){    //查找元素
        for(int i=0;i<ptr;i++) if(val==buf[i]) return i;
        return -1;
    }

    template<typename CompareMethod>
    void sort(CompareMethod compareMethod){ //公开的快排入口
        if(size()<1) return;
        int l=0,r=ptr-1;
        return qsort(l,r,compareMethod);
    }
    void erase(int index){  //删除指定下标的元素
        if(index>=ptr||index<0) return;
        buf[index]=buf[--ptr];  //调整数组大小
    }
    void remove(T elem){    //寻找指定元素并删除
        for(int i=0;i<ptr;i++){
            if(buf[i]==elem) erase(i);
        }
    }
    template<typename Condition>
    Array<T> findElemBy(Condition condition){   //根据传入的条件查找元素
        int temp[1024]; //存放符合条件的数组下标的数组
        int p=0;
        for(int i=0;i<ptr;i++){
            if(condition(buf[i])) temp[p++]=i;//将符合条件的下标存入
        }
        Array<T> res(p);    //新建数组，大小为符合条件元素的个数
        for(int i=0;i<p;i++) res[i]=buf[temp[i]];// 将符合条件的元素填入要返回的数组
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Array &array) {
        for(int i=0;i<array.ptr;i++) os<<i<<" ";
        return os;
    }
    Array& operator=(const Array &o){
        delete[] buf;
        ptr=o.ptr;
        buf = new T[ptr];
        memcpy(buf,o.buf,sizeof(T)*ptr);
        return *this;
    }
};


#endif //NEWEMSYSTEM_ARRAY_HPP
