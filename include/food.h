#ifndef FOOD_H
#define FOOD_H

class Food{
private:
    int foodx;
    int foody;

public:
    Food(){}

    int getFoodx() const{
        return foodx;
    }
    int getFoody() const{
        return foody;
    }
    void setFoodx(int foodx){
        this -> foodx = foodx;
    }

    void setFoody(int foody){
        this -> foody = foody;
    }

    void setFood(int* pos){
        foodx = pos[0];
        foody = pos[1];
    }

};

#endif
