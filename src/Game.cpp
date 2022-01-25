#include "pch.h"
#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
    this->updatedRes = false;
}

void Game::initWindow()
{
    this->gfx.loadFromFile("Config/graphics.ini");

    if (this->gfx.fullscreen)
        this->window = std::make_shared<sf::RenderWindow>(this->gfx.resolution, this->gfx.title, sf::Style::Fullscreen, this->gfx.contextSettings);
    else
        this->window = std::make_shared<sf::RenderWindow>(this->gfx.resolution, this->gfx.title, sf::Style::Default, this->gfx.contextSettings);

    this->gfx.setIcon(this->window);
    this->window->setFramerateLimit(this->gfx.framerateLimit);

    ShowWindow(this->window->getSystemHandle(), SW_MAXIMIZE);
}

void Game::initStates()
{
    this->stateData.window = this->window;
    this->stateData.dt = &this->dt;
    this->stateData.states = &this->states;
    this->stateData.gfx = &this->gfx;

    this->states.push(new MainMenuState(&stateData));
}

void Game::updateResolution()
{      
    this->states.top()->updateResolution();
}   

void Game::updateEvents()
{
    while (window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->states.top()->endState();
            this->endApplication();
            break;
        case sf::Event::KeyPressed:
            switch (this->event.key.code)
            {
            case sf::Keyboard::Key::F11:               
                if (this->gfx.fullscreen) //If fullscreen we set it to false and also update the window
                {                   
                    this->window->create(this->gfx.resolution, this->gfx.title, sf::Style::Default, gfx.contextSettings);
                    this->updateResolution();

                    this->gfx.setIcon(this->window);
                    this->window->setVerticalSyncEnabled(this->gfx.verticalSync);
                    this->window->setFramerateLimit(this->gfx.framerateLimit);

                    ShowWindow(this->window->getSystemHandle(), SW_MAXIMIZE);
                    this->gfx.fullscreen = false;
                }
                else //If !fullscreen we set it to true and also update the window
                {
                    this->window->create(gfx.resolution, this->gfx.title, sf::Style::Fullscreen, gfx.contextSettings);
                    this->updateResolution();
                    this->gfx.setIcon(this->window);
                    this->window->setVerticalSyncEnabled(this->gfx.verticalSync);
                    this->window->setFramerateLimit(this->gfx.framerateLimit);
                    this->gfx.fullscreen = true;
                }
                break;
            }
            break;
        }
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication()
{
    this->gfx.saveToFile("Config/graphics.ini");
    this->window->close();
}

void Game::update()
{
    this->updateEvents();
    
    this->updateDt();

    if (!this->states.empty())
    {
       if(true)
       {
          this->states.top()->update();
          //If the state requests to be ended it does
          if (this->states.top()->getQuit())
          {
            //Saving the updatedRes variable before we delete it
            this->updatedRes = this->states.top()->getUpdatedRes();

            //Deleting the state
            this->states.top()->endState(); 
            delete this->states.top();
            this->states.pop();

            //If the resolution was updated in the last state the new state gets notified of it
            if (this->updatedRes)
            {
                this->states.top()->updateResolution();
                this->updatedRes = false;
            }
          }
        }
    }
    else
    {
        this->endApplication();
    }
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    //Deleting the remaining states
    while (!this->states.empty())
    {
        this->states.top()->saveSettings();
        delete states.top();
        this->states.pop();
    }
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
