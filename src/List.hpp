//
// Created by 90828 on 2022-02-11.
//

#ifndef NEWEMSYSTEM_LIST_HPP
#define NEWEMSYSTEM_LIST_HPP
#include <cstddef>
#include <iostream>
using namespace std;
template<class T>
struct LNode{   //链表结点类型
    T val;
    LNode *next;
    LNode():val(),next(nullptr){}
    LNode(T &v):val(v),next(nullptr){}
};
template <class T>
class List {
    typedef LNode<T> Node;
    Node *root;
    Node *rear;
    int listSize;
public:
    List(){
        root = new Node();
        rear=root;
        listSize=0;
    }
    ~List(){    //重载析构函数，释放内存
        while(root){
            rear=root->next;
            delete root;
            root=rear;
        }
    }
    size_t size(){  //返回表长
        return this->listSize;
    }
    bool empty(){   //判空
        return this->listSize==0;
    }
    void push_back(T &val){ //插入元素
        Node *t = new Node(val);
        rear->next = t;
        rear=rear->next;
        listSize++;
    }
    template<typename equal>
    T find(T elem,equal e=[](T a,T b){return a==b;}){   //查找元素
        for(Node* p=root->next;p;p=p->next){
            if(e(elem,p->val)) return p->val;
        }
        return T();
    }
    void print(){   //输出
        for(Node *p=root->next;p;p=p->next)
            cout<<p->val<<' ';
    }

    bool count(T elem) {    //判断存在
        for(Node* p=root->next;p;p=p->next){
            if(elem==p->val) return true;
        }
        return false;
    }
    void remove(T elem){    //删除指定元素
        //p为遍历结点的指针，q指向p的前驱结点,保证链表已经初始化
        for(Node* p=root->next,*q=root;p!= nullptr;q=p,p=p->next){
            if(elem==p->val){
                q->next=p->next;//前驱结点的next直接指向后继结点
                if(p->next == nullptr) rear=q;//更新尾部指针
                delete p;//释放空间
                listSize--;//调整链表长度
                return;
            }
        }
    }
};


#endif //NEWEMSYSTEM_LIST_HPP
