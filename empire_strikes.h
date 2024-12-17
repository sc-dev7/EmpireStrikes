/*
** EPITECH PROJECT, 2024
** Synthese
** File description:
** sc
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "libempire-11/extern.h"

typedef struct {
    int Nb_rom;
    int Nb_eat;
    int id;
    int meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} Roman_t;

void loop_lock(Roman_t *roman);
int parse_arg(int ac, char **av);
void join_pthread(Roman_t *p_data, pthread_t *romans);
void destroy_pthread(Roman_t *p_data, pthread_mutex_t *forks);
void take_left_fork(Roman_t *roman);
void take_right_fork(Roman_t *roman);
