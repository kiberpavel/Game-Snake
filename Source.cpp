#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>

using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 4;



class Snake
{
public:
    int x, y;
    //движение змейки
    void Motion() {
        if (dir == 0) y += 1;
        if (dir == 1) x -= 1;
        if (dir == 2) x += 1;
        if (dir == 3) y -= 1;
    }
    //функция нажатия кнопок, с помощью которых происходит движение змейки
    void Keys() {
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
    }
    //функция с помощью которой происходи движение за картой
    void Walls() {
        if (x > N) x = 0;
        if (x < 0) x = N;
        if (y > M) y = 0;
        if (y < 0) y = M;
    }

}  s[300];


class Fruit
{
public:
    int x, y;

    //задает координаты для фрукта
    void New() {
        x = rand() % N;
        y = rand() % M;
    }

} f;





void Tick()
{

    for (int i = num;i > 0;--i)//задание размера змейкки,единство всех её частей
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }

      s->Motion();

    if ((s[0].x == f.x) && (s[0].y == f.y))//если координаты змеи и фрукта совпадают,то происходит его поедания и увеличение длинны змеи
    {
        num++;
        f.New();
    }

    for (int i = 1;i < num;i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;//рестарт змеи при условии что она пойдет в противоположную сторону

    s->Walls();
}
void menu(RenderWindow& window) {
    //загрузка изображений для меню
    Texture menuTexture1, menuTexture3, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/snake2.jpg");
    //создание спрайтов для этих изображений
    Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    //задание координат для размещения кнопок меню
    menu1.setPosition(80, 30);
    menu3.setPosition(100, 90);

    //////////////////// МЕНЮ //////////////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;

        if (IntRect(80, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то начинается игра
            if (menuNum == 3) { window.close(); isMenu = false; }//если нажал на вторую кнопку,то выходишь из игры

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu3);

        window.display();
    }
    ////////////////////////////////////////////////////
}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");
    menu(window);//вызов меню

    //загрузка и воспроизведение музыки
    Music fruit;
    fruit.openFromFile("sounds/m.ogg");
    fruit.play();
    fruit.setLoop(true);

    //загрузка изображений
    Texture t1, t2, t3;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/image.png");
    t3.loadFromFile("images/apple.png");

    //создание спрайтов для этих изображений
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;//простой класс, предназначенный для измерения времени
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 5;

    while (window.isOpen())
    {
        //движение змейки и ее рестарт
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;//закрытие приложения
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        s->Keys();

        if (timer > delay) { timer = 0; Tick(); }

        ////// ОТРИСОВКА  ///////
        window.clear();

        //отрисовка карты
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        //отрисовка змеи
        for (int i = 0;i < num;i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);

        }

        //отрисовка фрукта
        sprite3.setPosition(f.x * size, f.y * size);  window.draw(sprite3);

        window.display();

    }
         /////////////////////////
    return 0;
}
