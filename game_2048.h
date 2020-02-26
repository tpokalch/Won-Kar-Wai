/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:45:57 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:38:16 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GAME_2048_H
# define __GAME_2048_H

# include <ncurses.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef MAP_SIDE_SIZE
#  define MAP_SIDE_SIZE 4
# endif
# if MAP_SIDE_SIZE < 3 || MAP_SIDE_SIZE > 12
#  warning "MAP_SIDE_SIZE is cooked best in range of [3 .. 12]"
# endif
# define MAP_PADDING 0.20f
# define INTER_TILE_GAP 0.0f
# define TILE_SIDE_SIZE ((1.0f - (MAP_PADDING * 2.0f)) / (double)MAP_SIDE_SIZE)
# define TILE_RANDOM_VALUE() (rand() % 5 == 0 ? 4 : 2)
# define RANDOM_IDX() (rand() % MAP_SIDE_SIZE)
# define INITIALIZED_TILES 2
# define UNUSED(x) ((void)(x))

# define SET_STATE(_ctx_2048, _state) (_ctx_2048)->state = (_state)
# define GET_STATE(_ctx_2048) ((_ctx_2048)->state)

enum			e_const
{
	WIN_VALUE = 2048,
};

typedef	enum	e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}				t_dir;

typedef enum	e_win_state
{
	GAME_STATE_START,
	GAME_STATE_IN_PROGRESS,
	GAME_STATE_PAUSED,
	GAME_STATE_FINISHED,
	GAME_STATE_EXIT,
	GAME_STATE_MAX,
}				t_win_state;

typedef struct	s_2048_tile_win
{
	unsigned long long	*value;
	WINDOW				*win;
	int					pos_x;
	int					pos_y;
	int					height;
	int					width;
}				t_2048_tile_win;

typedef struct	s_2048_map
{
	unsigned long long **tiles;
}				t_2048_map;

typedef struct	s_screen
{
	int		width;
	int		height;
}				t_screen;

struct s_2048;

typedef void	(*t_update_fn)(struct s_2048 *, int);
typedef void	(*t_render_fn)(struct s_2048 *);
typedef void	(*t_resize_fn)(struct s_2048 *);
typedef unsigned long long t_ull;
typedef WINDOW	t_window;

typedef struct	s_2048
{
	t_screen		screen;
	t_2048_map		map;
	t_2048_tile_win	map_tiles[MAP_SIDE_SIZE][MAP_SIDE_SIZE];
	bool			keep_playing;
	bool			player_won;
	t_win_state		state;
	void			*state_priv[GAME_STATE_MAX];
	t_update_fn		update_fns[GAME_STATE_MAX];
	t_render_fn		render_fns[GAME_STATE_MAX];
	t_resize_fn		resize_fns[GAME_STATE_MAX];
	t_ull			score;
}				t_2048;

void			resize_2048(t_2048 *ctx_2048);
t_ull			**swipe(t_ull **arr, t_dir direction);
int				movement(t_ull **arr, t_dir direction);

void			tile_set_position(t_2048_tile_win *tile, t_screen *scr,
									int x, int y);
void			tile_init_window(t_2048_tile_win *tile);
void			tile_resize_window(t_2048_tile_win *tile);
void			tile_render(t_2048_tile_win *tile);

void			map_init(t_2048_map *map);
void			map_add_random_value(t_2048_map *map);
bool			map_has_empty_tiles(t_2048_map *map);

bool			has_won(t_2048 *ctx);
bool			has_lost(t_2048 *ctx);

void			set_state_functions(t_2048 *ctx);

void			state_start_update(t_2048 *ctx, int ch);
void			state_start_render(t_2048 *ctx);
void			state_in_progress_update(t_2048 *ctx, int ch);
void			state_in_progress_render(t_2048 *ctx);
void			state_paused_update(t_2048 *ctx, int ch);
void			state_paused_render(t_2048 *ctx);
void			state_finished_update(t_2048 *ctx, int ch);
void			state_finished_render(t_2048 *ctx);
void			state_exit_update(t_2048 *ctx, int ch);
void			state_exit_render(t_2048 *ctx);

void			init_grid(t_2048 *ctx);
void			render_layout(t_2048 *ctx);

int				next_num(int leftof, t_ull *s);
int				first_zero(int *a);
void			swap_line(t_ull *line);
t_ull			*compress_line(t_ull *a);
t_ull			*add_line_left(t_ull *line, int leftof);
t_ull			*move_line(t_ull *a, t_dir swp);
int				next_num_ar(int leftof, int cln, t_ull **line);

#endif
