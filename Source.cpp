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
    //�������� ������
    void Motion() {
        if (dir == 0) y += 1;
        if (dir == 1) x -= 1;
        if (dir == 2) x += 1;
        if (dir == 3) y -= 1;
    }
    //������� ������� ������, � ������� ������� ���������� �������� ������
    void Keys() {
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
    }
    //������� � ������� ������� ��������� �������� �� ������
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

    //������ ���������� ��� ������
    void New() {
        x = rand() % N;
        y = rand() % M;
    }

} f;





void Tick()
{

    for (int i = num;i > 0;--i)//������� ������� �������,�������� ���� � ������
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }

      s->Motion();

    if ((s[0].x == f.x) && (s[0].y == f.y))//���� ���������� ���� � ������ ���������,�� ���������� ��� �������� � ���������� ������ ����
    {
        num++;
        f.New();
    }

    for (int i = 1;i < num;i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;//������� ���� ��� ������� ��� ��� ������ � ��������������� �������

    s->Walls();
}
void menu(RenderWindow& window) {
    //�������� ����������� ��� ����
    Texture menuTexture1, menuTexture3, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/snake2.jpg");
    //�������� �������� ��� ���� �����������
    Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    //������� ��������� ��� ���������� ������ ����
    menu1.setPosition(80, 30);
    menu3.setPosition(100, 90);

    //////////////////// ���� //////////////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;

        if (IntRect(80, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ���������� ����
            if (menuNum == 3) { window.close(); isMenu = false; }//���� ����� �� ������ ������,�� �������� �� ����

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
    menu(window);//����� ����

    //�������� � ��������������� ������
    Music fruit;
    fruit.openFromFile("sounds/m.ogg");
    fruit.play();
    fruit.setLoop(true);

    //�������� �����������
    Texture t1, t2, t3;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/image.png");
    t3.loadFromFile("images/apple.png");

    //�������� �������� ��� ���� �����������
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;//������� �����, ��������������� ��� ��������� �������
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 5;

    while (window.isOpen())
    {
        //�������� ������ � �� �������
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;//�������� ����������
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        s->Keys();

        if (timer > delay) { timer = 0; Tick(); }

        ////// ���������  ///////
        window.clear();

        //��������� �����
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        //��������� ����
        for (int i = 0;i < num;i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);

        }

        //��������� ������
        sprite3.setPosition(f.x * size, f.y * size);  window.draw(sprite3);

        window.display();

    }
         /////////////////////////
    return 0;
}
