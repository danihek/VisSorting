#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;

int randomnumber(int mini, int maxi);


int main()
{   
    bool sortowanieBabelkowe = false;
    
    int sbabelkowe = 1;
    int jbabelkowe = 0;
    int ibabelkowe = 0;
    int nubmerOfArraySize = 1000;
    int fastOrNot = 0;
    std::vector<int> numbers;

    float delaySort=0.f;

    sf::Clock clock;
    sf::Clock clockUpdateSortClock;
    sf::RectangleShape background(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::View view1(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Event event;
    
    std::chrono::steady_clock::time_point lastTimeClock = std::chrono::steady_clock::now();
    // ================ INPUT 
    std::cout << "Screen width: " << std::endl;
    std::cin >> SCREEN_WIDTH;
    std::cout << "Screen height: " << std::endl;
    std::cin >> SCREEN_HEIGHT;

    std::cout << "number of things to sort: " << std::endl;
    std::cin >> nubmerOfArraySize;
    std::cout << "slow mode/ normal mode/ set delay?(0/1/2): " << std::endl;
    std::cin >> fastOrNot;
    if(fastOrNot==2)
    {
        std::cout<<"delay in ms: ";
        std::cin>>delaySort;
    }

    background.setPosition(0, 0);
    background.setScale(1, 1);
    background.setFillColor(sf::Color(194, 182, 180));

    srand(time(NULL));
    for (int x = 1; x <= nubmerOfArraySize; x++)
    {
        numbers.push_back(x * SCREEN_HEIGHT / nubmerOfArraySize);
    }

    shuffle(numbers.begin(),numbers.end(),std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "World");

    std::vector<sf::RectangleShape> bars;
    for (int i = 0; i < numbers.size(); i++)
    {
        sf::RectangleShape bar(sf::Vector2f(5, numbers.at(i)));
        bar.setPosition(i, SCREEN_HEIGHT - numbers.at(i));
        bar.setScale(1, 1);
        bar.setFillColor(sf::Color(99, 91, 100));
        bar.setOutlineColor(sf::Color(30, 30, 30));
        bar.setOutlineThickness(1);
        bars.push_back(bar);
    }
    while (window.isOpen())
    {
        window.setView(view1);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!sortowanieBabelkowe)
                sortowanieBabelkowe = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            if (sortowanieBabelkowe)
            {
                sortowanieBabelkowe = false;
                shuffle(numbers.begin(),numbers.end(),std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
                ibabelkowe = 0;
                jbabelkowe = 0;
                sbabelkowe = 1;
            }
        }
        if (sortowanieBabelkowe && sbabelkowe == 1 
        && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-lastTimeClock).count()>delaySort)
        {
            bool isRdy = true;
            if (sbabelkowe == 1)// && clockUpdateSortClock.getElapsedTime().asMilliseconds() - lasttimeUpdateSortClock > 0.1)
            {
                isRdy = false;
                lastTimeClock = std::chrono::steady_clock::now();
                sbabelkowe = 0;
                if (fastOrNot == 1)
                {
                    for (int i = 0; i < numbers.size() - 1 - jbabelkowe; i++)
                    {
                        if (numbers.at(i) > numbers.at(i + 1))
                        {
                            sbabelkowe = 1;
                            ibabelkowe = i;
                            std::swap(numbers.at(i), numbers.at(i + 1));
                        }
                    }
                }
                else
                {
                    if (ibabelkowe<numbers.size()-1-jbabelkowe)
                    {
                        if (numbers.at(ibabelkowe) > numbers.at(ibabelkowe + 1))
                        {
                            std::swap(numbers.at(ibabelkowe), numbers.at(ibabelkowe + 1));
                        }
                            sbabelkowe = 1;
                    }
                    ibabelkowe++;
                    if (ibabelkowe >= numbers.size() - 1 - jbabelkowe)
                    {
                        jbabelkowe++;
                        ibabelkowe = 0;
                    }
                }
            }
        }

        //TODO: fix problem when nubmerOfArraySize>(SCREEN_WIDTH/10)*2
        // bars are not streching to window correctly

        std::vector<sf::RectangleShape> bars;
        if (nubmerOfArraySize>(SCREEN_WIDTH/10)*2)
        {
            for (int i = 0; i < numbers.size(); i++)
            {
                sf::RectangleShape bar(sf::Vector2f(SCREEN_WIDTH / nubmerOfArraySize, numbers.at(i)));
                bar.setPosition(i * (SCREEN_WIDTH / nubmerOfArraySize), SCREEN_HEIGHT - numbers.at(i));
                bar.setScale(1, 1);
                    bar.setFillColor(sf::Color(99, 91, 100));
                if (i==ibabelkowe)
                    bar.setFillColor(sf::Color(214,232,172));
                bar.setOutlineColor(sf::Color(30, 30, 30));
                bar.setOutlineThickness(1);
                bars.push_back(bar);
            }
        }
        else
        {
            for (int i = 0; i < numbers.size(); i++)
            {
                sf::RectangleShape bar(sf::Vector2f(SCREEN_WIDTH / nubmerOfArraySize, numbers.at(i)));
                bar.setPosition(i * (SCREEN_WIDTH / nubmerOfArraySize), SCREEN_HEIGHT - numbers.at(i));
                bar.setScale(1, 1);
                    bar.setFillColor(sf::Color(99, 91, 100));
                if (i==ibabelkowe)
                    bar.setFillColor(sf::Color(214,232,172));
                bar.setOutlineColor(sf::Color(30, 30, 30));
                bar.setOutlineThickness(1);
                bars.push_back(bar);
            }
        }

        window.clear();
        window.setView(view1);
        window.draw(background);

        for (int i = 0; i < bars.size(); i++)
        {
            window.draw(bars.at(i));
        }
        window.display();
    }
    return 0;
}

int randomnumber(int mini, int maxi)
{
    return rand() % (maxi - mini + 1) + mini;
}
