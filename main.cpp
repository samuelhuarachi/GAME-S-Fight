#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <array>
#include <iterator>
#include <cmath>
#include <tuple>
#include <vector>
#include "Bullet.h"
#include "Fleet.h"
#include "LeftSector.h"
#include "MiddleSector.h"
#include "ProgressBar.h"

using namespace std;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
#define KEY_SEEN     1
#define KEY_RELEASED 2



bool is_pressing_the_key(int key) {
    if (key) {
        return true;
    }
    return false;
}

int main()
{
    ALLEGRO_DISPLAY* display;

    if(!al_init())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro couldnt initialize",NULL,NULL);

    if(!al_install_keyboard())
        printf("couldn't initialize keyboard\n");

    /*if(!al_install_mouse())
        printf("couldn't initialize mouse\n"); */


    al_init_primitives_addon();
    al_install_audio();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    al_init_acodec_addon();

    ALLEGRO_FONT* font;

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(800,600);
    if(!display)
        al_show_native_message_box(NULL,NULL,NULL,"Couldnt create Screen",NULL,NULL);


    ALLEGRO_EVENT_QUEUE* queue;
    int FPS = 60;

    ALLEGRO_TIMER* timer;
    timer = al_create_timer(1.0 / FPS);
    queue = al_create_event_queue();
    font = al_create_builtin_font();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    //al_register_event_source(queue, al_get_mouse_event_source());

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    unsigned char key[ALLEGRO_KEY_MAX];

    if(!al_init_image_addon())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro image addon couldnt initialize",NULL,NULL);


    bool abc = false;
    bool mb1 = false;

    int pos_x = 1;
    int pos_y = 1;

    bool exit_game = false;
    memset(key, 0, sizeof(key));

    double last_time = al_get_time();
    double delta_time;

    Fleet fleet(398, 590);
    LeftSector left_sector;
    MiddleSector middle_sector;
    ProgressBar progress_bar;

    vector<Bullet> bullets;

    while(!exit_game) {
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER: // Holding some keyboard key
            {
                delta_time = al_get_time() - last_time;
                last_time = al_get_time();

                if (fleet.shipCount() > 0) {
                    fleet.update(
                        is_pressing_the_key(key[ALLEGRO_KEY_A]),
                        is_pressing_the_key(key[ALLEGRO_KEY_D]),
                        delta_time
                    );

                    left_sector.update(delta_time);
                    middle_sector.update(delta_time, fleet);

                    for (Bullet& bullet : bullets) {
                        bullet.update(delta_time);
                    }

                    left_sector.damageFleet(fleet);
                    middle_sector.damageFleet(fleet);

                    middle_sector.collide(bullets);

                    int destroyed = left_sector.collide(bullets);
                    int ships = progress_bar.addDestructions(destroyed);
                    for (int i = 0; i < ships; ++i)
                        fleet.addShip();

                    bullets.erase(
                        remove_if(
                            bullets.begin(),
                            bullets.end(),
                            [](const Bullet& bullet) {
                                return !bullet.isActive();
                            }
                        ),
                        bullets.end()
                    );
                }


                for(int i = 0; i < ALLEGRO_KEY_MAX; i++) {
                    key[i] &= KEY_SEEN;
                }


                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN: // Key down
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP: // Key up
                if(key[ALLEGRO_KEY_A]) {
                }
                if(key[ALLEGRO_KEY_ESCAPE]) {
                    exit_game = true;
                }

                if (key[ALLEGRO_KEY_SPACE]) {
                    if (fleet.shipCount() == 0) {
                        fleet.reset();
                        left_sector.reset();
                        middle_sector.reset();
                        progress_bar.reset();
                        bullets.clear();
                    } else {
                        fleet.shoot(bullets);
                    }
                }

                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit_game = true;
                break;
            /*case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;
                break;*/

        }


        fleet.draw();

        for (Bullet& bullet : bullets) {
            bullet.draw();
        }

        left_sector.draw();
        middle_sector.draw();

        progress_bar.draw();

        al_draw_line(
            237, 0,
            237, 600,
            al_map_rgb(255, 255, 255),
            2
        );

        al_draw_line(
            307, 0,
            307, 600,
            al_map_rgb(255, 255, 255),
            2
        );

        al_draw_line(
            489, 0,
            489, 600,
            al_map_rgb(255, 255, 255),
            2
        );

        al_draw_line(
            559, 0,
            559, 600,
            al_map_rgb(255, 255, 255),
            2
        );

        if (fleet.shipCount() == 0) {
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                400, 260,
                ALLEGRO_ALIGN_CENTRE,
                "GAME OVER"
            );
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                400, 280,
                ALLEGRO_ALIGN_CENTRE,
                "press space para reiniciar o jogo"
            );
        }



        al_flip_display();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}
