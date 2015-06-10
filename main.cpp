#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

enum GAME_KEYS
{
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN
};

int key[] = { 0, 0, 0, 0 };

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *background;
ALLEGRO_BITMAP *cabeza;
ALLEGRO_BITMAP *cuerpo;

int playerX = 100;
int playerY = 100;
int direccion = 2;
int score = 1;
int lastX;
int lastY;

int main()
{
    int redraw = 1;

    al_init();
    al_init_image_addon();

    al_install_keyboard();

    display = al_create_display(640, 480);

    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / 60);

    cabeza = al_load_bitmap("sprites/cabeza.png");
    background = al_load_bitmap("background.png");
    cuerpo = al_load_bitmap("sprites/cuerpo.png");


    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    while (1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 1;
        }

        if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 0;
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            if (key[KEY_LEFT]){
                playerX -= 6;
                direccion = 1;
            }

            if (key[KEY_RIGHT]){

                playerX += 6;
                direccion = 2;
            }

            if (key[KEY_UP]){
                playerY -= 6;
                direccion = 3;
            }

            if (key[KEY_DOWN]){
                playerY += 6;
                direccion = 4;
            }




            redraw = 1;
        }





        if(playerX < 0)
            playerX = 0;

        if(playerY < 0)
            playerY = 0;

        if(playerX > 620)
            playerX = 620;

        if(playerY > 470)
            playerY = 470;






    if (redraw)
        {
            al_draw_bitmap(background, 0, 0, 0);



            switch(direccion) {
            case 1:
                al_draw_bitmap(cuerpo, playerX + 20, playerY, 0);
                al_draw_bitmap(cabeza, playerX, playerY, ALLEGRO_FLIP_HORIZONTAL);
                lastX = playerX + 20;
                lastY = playerY;
                break;

            case 2:
                al_draw_bitmap(cuerpo, playerX - 20, playerY, 0);
                al_draw_bitmap(cabeza, playerX, playerY, 0);
                lastX = playerX -20;
                lastY = playerY;
                break;

            case 3:
                al_draw_bitmap(cuerpo, playerX, playerY + 20, 0);
                al_draw_bitmap(cabeza, playerX, playerY, 0);
                lastX = playerX;
                lastY = playerY +20;
                break;

            case 4:
                al_draw_bitmap(cuerpo, playerX, playerY - 20, 0);
                al_draw_bitmap(cabeza, playerX, playerY, 0);
                lastX = playerX;
                lastY = playerY -20;
                break;
             }
             if(score!=0){
        for (int i = 0; i<=score; i++){
                switch(direccion){
                case 1:
                    al_draw_bitmap(cuerpo, lastX + 20, lastY, 0);
                    break;
                case 2:
                    al_draw_bitmap(cuerpo, lastX - 20, lastY, 0);
                }
        }
             }
            al_flip_display();

            redraw = 0;
        }

    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(cabeza);
    al_destroy_bitmap(cuerpo);
    al_destroy_bitmap(background);

    return 0;
}
