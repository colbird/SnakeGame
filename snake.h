#ifndef SNAKE_H
#define SNAKE_H

class Snake{
private:
    int length;     // 蛇的长度
    int status;     // 蛇的方向状态 0 stop  1 up 2 right 3 down 4 left
    int headx;
    int heady;

public:
    Snake(){
        length = 3; // 初始长度
        status = 0;
    }
    
    int getLength() const{
        return length;
    }

    void lengthAdd(){
        length++;
    }

    int getStatus(){
        return status;
    }

    void setStatus(int status){
        this -> status = status;
    }

    int getHeadx(){
        return headx;
    }

    int getHeady(){
        return heady;
    }

    void setHeadx(int headx){
        this -> headx = headx;
    }

    void setHeady(int heady){
        this -> heady = heady;
    }

    void up(){
        if (heady == 0)
            heady = 29;
        else
            heady--;
    }

    void down(){
        if (heady == 29)
            heady = 0;
        else
            heady++;
    }

    void left(){
        if (headx == 0)
            headx = 49;
        else
            headx--;
    }

    void right(){
        if (headx == 49)
            headx = 0;
        else
            headx++;
    }
};


#endif
