/*
** EPITECH PROJECT, 2024
** Synthese
** File description:
** sc
*/

#include "empire_strikes.h"

void join_pthread(Roman_t *p_data, pthread_t *romans)
{
    for (int i = 0; i < p_data->Nb_rom; i++) {
        if (pthread_join(romans[i], NULL) != 0) {
            exit(EXIT_FAILURE);
        }
    }
}

void destroy_pthread(Roman_t *p_data, pthread_mutex_t *forks)
{
    for (int i = 0; i < p_data->Nb_rom; i++) {
        if (pthread_mutex_destroy(&forks[i]) != 0) {
            exit(EXIT_FAILURE);
        }
    }
}

void take_right_fork(Roman_t *roman)
{
    int think_time = 0;

    pthread_mutex_lock(roman->right_fork);
    lempire_take_fork(roman->right_fork);
    lempire_think();
    think_time = rand() % 3 + 3;
    usleep(think_time * 1000);
    pthread_mutex_lock(roman->left_fork);
    lempire_take_fork(roman->left_fork);
}

void take_left_fork(Roman_t *roman)
{
    int think_time = 0;

    pthread_mutex_lock(roman->left_fork);
    lempire_take_fork(roman->left_fork);
    lempire_think();
    think_time = rand() % 3 + 3;
    usleep(think_time * 1000);
    pthread_mutex_lock(roman->right_fork);
    lempire_take_fork(roman->right_fork);
}
