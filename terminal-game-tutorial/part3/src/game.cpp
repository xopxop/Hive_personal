#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "game.h"
#include "ObjectField.h"

WINDOW* wnd;

struct {
	vec2i pos;
	char disp_char;
} player;

ObjectField starts;

int init(void)
{
	wnd = initscr();
	cbreak();
	noecho();
	clear();
	refresh();

	keypad(wnd, true);

	nodelay(wnd, true);

	curs_set(0);

	if (!has_colors()) {
		endwin();
		std::cout << "ERROR: Terminal does not support color." << std::endl;
		exit(1);
	}

	start_color();

	attron(A_BOLD);
	box(wnd, 0, 0);
	attroff(A_BOLD);

	// init_pair(1, COLOR_BLACK, COLOR_CYAN);
	// wbkgd(wnd, COLOR_PAIR(1));

	return 0;
}

void run(void)
{
	uint_fast16_t maxx, maxy;
	getmaxyx(wnd, maxy, maxx);
	rect game_area = { {0, 0} , {maxx, maxy} };
	starts.setBounds(game_area);


	player.disp_char = '0';
	player.pos = {10, 5};
	int in_char;
	bool exit_requested = false;
	while(1)
	{
		in_char = wgetch(wnd);
		mvaddch(player.pos.y, player.pos.x, ' ');
		
		starts.update();
		for(auto s : starts.getData())
		{
			mvaddch(s.getPos().y, s.getPos().x, ' ');
		}

		for(auto s : starts.getData())
		{
			mvaddch(s.getPos().y, s.getPos().x, '*');
		}


		switch(in_char) {
			case 'q':
				exit_requested = true;
				break;
			case KEY_UP:
			case 'w':
				player.pos.y -= 1;
				break;
			case KEY_DOWN:
			case 's':
				player.pos.y += 1;
				break;
			case KEY_LEFT:
			case 'a':
				player.pos.x -= 1;
				break;
			case KEY_RIGHT:
			case 'd':
				player.pos.x += 1;
				break;
			default:
				break;
		}
		mvaddch(player.pos.y, player.pos.x, player.disp_char);
		refresh();
		if (exit_requested) break;
		usleep(10000);
	}
}

void close(void)
{
	endwin();
}
