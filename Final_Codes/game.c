#include "game.h"
#include "utility.h"
#include "menu_scene.h"

static ALLEGRO_DISPLAY* gameDisplay;
static ALLEGRO_TIMER* gameTimer;
static ALLEGRO_TIMER* gameTick;
static ALLEGRO_EVENT_QUEUE* event_queue;
static ALLEGRO_EVENT event;

bool keyState[ALLEGRO_KEY_MAX] = { false };  // Array to track the state of each key
ALLEGRO_MOUSE_STATE mouseState;

Scene current_scene;

void change_scene(Scene next_scene) {
    game_log("Change scene from %s to %s",
        current_scene.name ? current_scene.name : "NULL",
        next_scene.name ? next_scene.name : "NULL");
    if (current_scene.destroy)
        (*current_scene.destroy)();
    if (gameTimer == NULL)
        game_abort("NULL gameTimer timer!!!");
    if (gameTick == NULL)
        game_abort("NULL gameTick timer!!!");
    al_stop_timer(gameTimer);
    al_stop_timer(gameTick);
    current_scene = next_scene;
    if (current_scene.init)
        current_scene.init();
    if (gameTimer == NULL) {
        game_abort("NULL gameTimer timer!!!");
    }
    if (gameTick == NULL) {
        game_abort("NULL gameTick timer!!!");
    }
    al_set_timer_count(gameTimer, 0);
    al_set_timer_count(gameTick, 0);
    al_start_timer(gameTimer);
    al_start_timer(gameTick);
}

// Initialize Game Property
void initGame(void){
    // Initialize Allegro
    if (!al_init())
        game_abort("failed to initialize allegro");
    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
    if (!al_install_audio())
        game_abort("failed to initialize audio add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    if(!al_init_image_addon())
        game_abort("couldn't initialize image addon\n");
    
    game_log("Initialized Allegro");
    
    // Create Game Display
    gameDisplay = al_create_display(SCREEN_W, SCREEN_H);
    if (!gameDisplay)
        game_abort("failed to create display");
    // Set Window Title
    al_set_window_title(gameDisplay, GAME_TITLE);
    
    game_log("Initialized Window Display");
    
    //Set event queue
    event_queue = al_create_event_queue();
    if(!event_queue)
        game_abort("failed to create event queue");
    // Set Game Timer
    gameTimer = al_create_timer(1.0f / FPS);
    if (!gameTimer)
        game_abort("failed to create game timer");
    gameTick = al_create_timer(1.0f / FPS);
    if(!gameTick)
        game_abort("failed to create game tick timer");
    
    // Register Event
    al_register_event_source(event_queue, al_get_display_event_source(gameDisplay));
    al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(gameTick));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    game_log("Initialized Event Queue and Source");

    // Initialize Utility
    init_Util();
    
    // Start the timer
    al_start_timer(gameTimer);
    al_start_timer(gameTick);

    // Create the current scene
    change_scene(create_menu_scene());
    game_log("Scene %s created, initializing ... ", current_scene.name);
}

// Destroy resources if the game done
void terminate(void){
    // Destroy Utility
    destroy_init();

    al_destroy_display(gameDisplay);
    al_destroy_timer(gameTimer);
    al_destroy_timer(gameTick);
    al_destroy_event_queue(event_queue);
}

// Game Event Loop
void start_loop(void){
    bool gameDone = false;
    bool redraw = false;

    while(!gameDone){ // Will loop until the program exitd
        
        // Get Allegro Event
        al_wait_for_event(event_queue, &event);

        switch(event.type)
        {
            // Close the game
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_log("Window close button pressed");
                gameDone = true;
                break;
            
            // Timer for update & draw
            case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == gameTimer)
                    redraw = true;
                break;
            
            // If keyboard key pressed
            case ALLEGRO_EVENT_KEY_DOWN:
                game_log("Key %d down", event.keyboard.keycode);
                keyState[event.keyboard.keycode] = true;
                break;
            
            // Unpressed the keyboard key
            case ALLEGRO_EVENT_KEY_UP:
                game_log("Key %d up", event.keyboard.keycode);
                keyState[event.keyboard.keycode] = false;
                break;
        }
        
        // Get Mouse State
        al_get_mouse_state(&mouseState);

        // Early break if game done
        if(gameDone)
            break;
        
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            // Clear the template
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            // Update
            current_scene.update();

            // Draw
            current_scene.draw();
            
            // Flip the display
            al_flip_display();
            
            redraw = false;
        }
    }
    
    return;
}


void startGame(void){
    
    game_log("Initializing Game ...");
    initGame();

    game_log("Start Game Event Loop");
    start_loop();
    
    game_log("Terminating ...");
    terminate();
    
    return;
}


