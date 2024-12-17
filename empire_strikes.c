/*
** EPITECH PROJECT, 2024
** Synthese
** File description:
** sc
*/

#include "empire_strikes.h"

void loop_unlock(Roman_t *roman)
{
    lempire_release_fork(roman->right_fork);
    pthread_mutex_unlock(roman->right_fork);
    lempire_release_fork(roman->left_fork);
    pthread_mutex_unlock(roman->left_fork);
}

void *roman_life(void *arg)
{
    Roman_t *roman = (Roman_t *)arg;
    int think_time = 0;

    while (roman->meals_eaten < roman->Nb_eat) {
        if (roman->id % 2 == 0) {
            take_left_fork(roman);
        } else {
            take_right_fork(roman);
        }
        lempire_eat();
        think_time = rand() % 3 + 3;
        usleep(think_time * 1000);
        roman->meals_eaten++;
        loop_unlock(roman);
        lempire_sleep();
        think_time = rand() % 3 + 3;
        usleep(think_time * 1000);
    }
    return NULL;
}

void initialize_and_start_romans(Roman_t *p_data, pthread_mutex_t *forks,
    Roman_t *roman_data, pthread_t *romans)
{
    for (int i = 0; i < p_data->Nb_rom; i++) {
        if (pthread_mutex_init(&forks[i], NULL) != 0) {
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < p_data->Nb_rom; i++) {
        roman_data[i].Nb_rom = p_data->Nb_rom;
        roman_data[i].Nb_eat = p_data->Nb_eat;
        roman_data[i].id = i;
        roman_data[i].meals_eaten = 0;
        roman_data[i].left_fork = &forks[i];
        roman_data[i].right_fork = &forks[(i + 1) % p_data->Nb_rom];
        if (pthread_create(&romans[i], NULL,
            roman_life, &roman_data[i]) != 0) {
            exit(EXIT_FAILURE);
        }
    }
    join_pthread(p_data, romans);
    destroy_pthread(p_data, forks);
}

int data_struct(int ac, char **av, Roman_t *p_data)
{
    p_data->Nb_eat = 0;
    p_data->Nb_rom = 0;
    if (ac != 5) {
        return 1;
    }
    for (int i = 1; i < ac; i += 2) {
        if (strcmp(av[i], "-p") == 0) {
            p_data->Nb_rom = atoi(av[i + 1]);
        }
        if (strcmp(av[i], "-e") == 0) {
            p_data->Nb_eat = atoi(av[i + 1]);
        }
    }
    if (p_data->Nb_rom <= 1 || p_data->Nb_eat <= 0) {
        fprintf(stderr, "nbr_p must be > 1 & nbr_e must be > 0\n");
        return 1;
    }
    return 0;
}

int main(int ac, char **av)
{
    Roman_t data;
    pthread_t *romans = NULL;
    Roman_t *roman_data = NULL;
    pthread_mutex_t *forks = NULL;

    if (data_struct(ac, av, &data) == 1) {
        fprintf(stderr, "Usage: %s -p nbr_p -e nbr_e\n", av[0]);
        return EXIT_FAILURE;
    }
    romans = malloc(sizeof(pthread_t) * data.Nb_rom);
    roman_data = malloc(sizeof(Roman_t) * data.Nb_rom);
    forks = malloc(sizeof(pthread_mutex_t) * data.Nb_rom);
    srand(time(NULL));
    RCFStartup(ac, av);
    initialize_and_start_romans(&data, forks, roman_data, romans);
    RCFCleanup();
    printf("Tous les Romains ont fini de manger.\n");
    return EXIT_SUCCESS;
}
