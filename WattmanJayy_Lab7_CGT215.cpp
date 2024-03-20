// WattmanJayy_Lab7_CGT215.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;


int main()
{
    //create window and world with gravity 0,1
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    //create the ball so we have something to bounce
    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 300)); //remember that in SFPhysics we orient from the center
    ball.setRadius(20); //set the size of the ball
    world.AddPhysicsBody(ball); //adds ball to world so it can be affected by the gravity and such

    //create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true); //makes sure that the floor doesn't move
    world.AddPhysicsBody(floor);

    //make the walls and ceiling
    PhysicsRectangle LWall;
    LWall.setSize(Vector2f(20, 600));
    LWall.setCenter(Vector2f(790, 300));
    LWall.setStatic(true);
    world.AddPhysicsBody(LWall);

    PhysicsRectangle RWall;
    RWall.setSize(Vector2f(20, 600));
    RWall.setCenter(Vector2f(10, 300));
    RWall.setStatic(true);
    world.AddPhysicsBody(RWall);

    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) // use an anonymus function with a reference to thudCount
        {
            cout << "thud " << thudCount << endl;
            thudCount++; //increment the thud count
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) 
    {
        //calculate milliseconds since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime); 
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) 
        {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }
        window.clear(Color(0, 0, 0));
        window.draw(ball); 
        window.draw(floor);
        window.draw(LWall);
        window.draw(RWall);
        window.draw(ceiling);
        window.display();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
