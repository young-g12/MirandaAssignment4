#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "mappy_A5.h"
#include "SpriteGrabber.h"

struct Hero
{
    float x;
    float y;

    int frame;
};

int main()
{
    // Initialize Allegro
    al_init();
    al_init_image_addon();
    al_install_keyboard();

    // Create display
    ALLEGRO_DISPLAY* display =
        al_create_display(800, 600);

    if (!display)
        return -1;

    // Create event queue
    ALLEGRO_EVENT_QUEUE* queue =
        al_create_event_queue();

    // Create timer
    ALLEGRO_TIMER* timer =
        al_create_timer(1.0 / 60.0);

    // Register event sources
    al_register_event_source(
        queue,
        al_get_display_event_source(display));

    al_register_event_source(
        queue,
        al_get_timer_event_source(timer));

    al_register_event_source(
        queue,
        al_get_keyboard_event_source());

    al_start_timer(timer);

    // Load sprite sheet
    SpriteGrabber grabber;

    if (!grabber.load("Images/rabbitsheet.png"))
    {
        return -1;
    }

    char mapFile[] = "Images/map1.fmp";

    if (MapLoad(mapFile, 1))
    {
        return -1;
    }

    // Load animation frames
    ALLEGRO_BITMAP* rabbitFrames[4];

    rabbitFrames[0] = grabber.grabImage(0, 0, 48, 32);
    rabbitFrames[1] = grabber.grabImage(48, 0, 48, 32);
    rabbitFrames[2] = grabber.grabImage(96, 0, 48, 32);
    rabbitFrames[3] = grabber.grabImage(144, 0, 48, 32);

    // Create hero
    Hero hero;

    hero.x = 64;
    hero.y = 64;
    hero.frame = 0;

    int animationCounter = 0;
    int mapX = 0;
    int mapY = 0;

    bool keys[4] =
    {
        false, // up
        false, // down
        false, // left
        false, // right
    };

    bool gameOver = false;

    while (!gameOver)
    {
        ALLEGRO_EVENT ev;

        while (al_get_next_event(queue, &ev))
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                gameOver = true;
            }

            if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    keys[0] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    keys[1] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    keys[2] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    keys[3] = true;
                    break;
                }
            }

            if (ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    keys[0] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    keys[1] = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                    keys[2] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    keys[3] = false;
                    break;
                }
            }
        }

        // Move hero
        float speed = 3.0f;

        bool moving = false;

        if (keys[0])
        {
            hero.y -= speed;
            moving = true;
        }

        if (keys[1])
        {
            hero.y += speed;
            moving = true;
        }

        if (keys[2])
        {
            hero.x -= speed;
            moving = true;
        }

        if (keys[3])
        {
            hero.x += speed;
            moving = true;
        }

        // Animate while moving
        if (moving)
        {
            animationCounter++;

            if (animationCounter > 10)
            {
                hero.frame++;

                if (hero.frame > 3)
                {
                    hero.frame = 0;
                }

                animationCounter = 0;
            }
        }

        MapUpdateAnims();

        // Draw
        MapDrawBG(
            mapX,
            mapY,
            0,
            0,
            799,
            599);

        al_draw_bitmap(
            rabbitFrames[hero.frame],
            hero.x,
            hero.y,
            0);

        al_flip_display();
    }

    
    for (int i = 0; i < 4; i++)
    {
        al_destroy_bitmap(rabbitFrames[i]);
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}