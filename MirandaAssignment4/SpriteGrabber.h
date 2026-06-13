#pragma once

#include <allegro5/allegro.h>

class SpriteGrabber
{
private:
    ALLEGRO_BITMAP* spriteSheet;

public:
    SpriteGrabber();

    bool load(const char* filename);

    ALLEGRO_BITMAP* grabImage(
        int x,
        int y,
        int width,
        int height);
};