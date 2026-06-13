#include "SpriteGrabber.h"
#include <allegro5/allegro_image.h>

SpriteGrabber::SpriteGrabber()
{
    spriteSheet = nullptr;
}

bool SpriteGrabber::load(const char* filename)
{
    spriteSheet = al_load_bitmap(filename);

    if (!spriteSheet)
        return false;

    return true;
}

ALLEGRO_BITMAP* SpriteGrabber::grabImage(
    int x,
    int y,
    int width,
    int height)
{
    return al_create_sub_bitmap(
        spriteSheet,
        x,
        y,
        width,
        height);
}