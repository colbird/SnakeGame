#include <snake.h>
#include <food.h>
#include <map.h>
#include <queue.h>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <termios.h>
#include <termios.h>
#include <termios.h>

enum Direction{STOP = 0, UP, RIGHT, DOWN, LEFT};

Direction get_input();
void init_keyboard();

class Game{
private:
    Snake snake;
    Food food;
    Map map;
    Queue queue;
    int score;
    int cut;
    bool gameover;
    bool in;

public:
    Game(){
        int* temp = randPos();
        snake.setHeadx(temp[0]);
        snake.setHeady(temp[1]);
        delete [] temp;
        temp = randPos();
        food.setFood(temp);
        delete [] temp;
        score = 0;
        cut = 0;
        gameover = false;
        in = false;
        map.setMap(food.getFoodx(), food.getFoody(), 'F');
    }
    int* randPos(){
        int* temp = new int[2];
        do{
            temp[0] = std::rand() % 50;
            temp[1] = std::rand() % 30;
        } while(!map.isEmpty(temp[0], temp[1]));

        return temp;
    }
    void drw() const{
        system("clear");
        std::cout << std::setw(21) << "->" <<
        score << "<-" <<std::endl;
        map.mapDisplay();
    }

    void update(){

        // 碰撞检测
        if (map.getMap(snake.getHeadx(), snake.getHeady()) == '#' ||
            (map.getMap(snake.getHeadx(), snake.getHeady()) == 'O' && snake.getStatus()))
            gameover = 1;
        
        // 吃到食物
        if (map.getMap(snake.getHeadx(), snake.getHeady()) == 'F'){
            int* temp = randPos();
            food.setFood(temp);
            delete [] temp;
            snake.lengthAdd();
            map.setMap(food.getFoodx(), food.getFoody(), 'F');
            score++;
        }

        map.setMap(snake.getHeadx(), snake.getHeady(), 'O');
        // 移动过的路线
        if (in && snake.getStatus())
            in = false;
        if (!in){
            queue.push(snake.getHeadx(), snake.getHeady());
            cut++;
            if (!snake.getStatus())
                in = true;
        }
        if (snake.getLength() < cut){
            int* temp = queue.pop();
            map.setMap(temp[0], temp[1], ' ');
            delete [] temp;
            cut--;
        }
        
        // 方向判断
        Direction input = get_input();
        if ((input == LEFT && snake.getStatus() != RIGHT) || 
            (input == RIGHT && snake.getStatus() != LEFT) ||
            (input == UP && snake.getStatus() != DOWN) ||
            (input == DOWN && snake.getStatus() != UP)) {
            snake.setStatus(input);
        }

        switch(snake.getStatus()){
            case UP: snake.up(); break;
            case DOWN: snake.down(); break;
            case LEFT: snake.left(); break;
            case RIGHT: snake.right(); break;
        }
    }

    bool  isGameover() const{
        return gameover;
    }
};

int main(){
    init_keyboard();
    srand(time(0));
    Game game;
    
    while(!game.isGameover()){
        game.update();
        game.drw();
        usleep(100000);
    }
    
    return 0;
}
struct termios original_tattr;
void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_tattr);
}

// 非阻塞键盘输入设置
void init_keyboard() {
    struct termios tattr;
    tcgetattr(STDIN_FILENO, &original_tattr);
    atexit(restore_terminal);
    
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO);  // 关闭行缓冲和回显
    tattr.c_cc[VMIN] = 0;              // 无阻塞读取
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

// 检测键盘输入
Direction get_input() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    
    if (select(1, &fds, NULL, NULL, &tv) > 0) {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        
        // 处理方向键（转义序列）
        if (ch == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) <= 0) return STOP;
            if (read(STDIN_FILENO, &seq[1], 1) <= 0) return STOP;
            
            if (seq[0] == 91) {
                switch(seq[1]) {
                    case 'A': return UP;
                    case 'B': return DOWN;
                    case 'C': return RIGHT;
                    case 'D': return LEFT;
                }
            }
        }
        
        switch(ch) {
            case 'a': return LEFT;
            case 'd': return RIGHT;
            case 'w': return UP;
            case 's': return DOWN;
            case 'q': exit(0);
        }
    }
    return STOP;
}
