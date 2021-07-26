#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <string>
#include "Config.h"
#include "Driver.h"

#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
#define _CRTDBG_MAP_ALLOC

int error(const std::string &message);

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	const ALLEGRO_COLOR clearColor = al_map_rgb(255, 69, 103);

	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_EVENT_QUEUE *eventQueue = nullptr;
	ALLEGRO_TIMER *timer = nullptr;

	bool redraw = true;

	if (!al_init())
		return error("Failed to initialize Allegro 5!");

	if (!al_init_image_addon())
		return error("Failed to initialize Allegro 5 image addon!");
	
	if(!al_init_primitives_addon())
		return error("Failed to initialize Allegro 5 primitives addon!");

	if (!al_init_font_addon())
		return error("Failed to initialize Allegro 5 font addon!");

	if (!al_init_ttf_addon())
		return error("Failed to initialize Allegro 5 ttf addon!");

	display = al_create_display(Config::displayWidth, Config::displayHeight);
	if (!display)
		return error("Failed to create Allegro 5 display!");

	eventQueue = al_create_event_queue();
	if (!eventQueue)
		return error("Failed to create Allegro 5 event queue!");

	timer = al_create_timer(1.0 / Config::fps);
	if (!timer)
		return error("Failed to create Allegro 5 timer!");

	if (!al_install_keyboard())
		return error("Failed to install Allegro 5 keyboard!");

	if (!al_install_mouse())
		return error("Failed to install Allegro 5 mouse!");

	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());

	Driver driver;

	al_start_timer(timer);

	while (!driver.isDone())
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			driver.updateOnTick();

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			driver.updateOnMouseAxes(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			driver.updateOnMousePress(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			driver.updateOnMouseRelease(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			driver.updateOnKeyPress(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			driver.updateOnKeyRelease(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			driver.updateOnDisplayClose();
		}

		if (redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;

			al_clear_to_color(clearColor);
			driver.render();
			al_flip_display();
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);

	return 0;
}

int error(const std::string &message)
{
	std::cerr << message << std::endl;
	return 1;
}