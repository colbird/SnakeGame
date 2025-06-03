#ifndef QUEUE_H
#define QUEUE_H

class Node{
public:
    int* data;
    Node* next;
    Node(int x, int y) : next(nullptr){
        data = new int[2];
        data[0] = x;
        data[1] = y;
    }
};

class Queue{
private:
    Node* real;
    Node* top;

public:
    Queue() : real(nullptr), top(nullptr){}

    ~Queue(){
        while(!isEmpty()){
            int* temp = pop();
            delete [] temp;
        }
    }

    bool isEmpty()const{
        return top == nullptr;
    }

    void push(int x, int y){
        Node* newNode = new Node(x, y);
        if (isEmpty()){
            top = real = newNode;
        }
        else{
            real -> next = newNode;
            real = newNode;
        }
    }

    int* pop(){
        if (isEmpty())
            return nullptr;

        Node* temp = top;
        top = top -> next;
        int* intpArr = temp -> data;

        if (top == nullptr)
            top = real = nullptr;

        delete temp;
        return intpArr;
    }
};

#endif
