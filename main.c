#include "philosopher.h"

void  *philosopher(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    while (1)
    {
        if (philo->data->nbrEat != -1
            && philo->nbr_eat == philo->data->nbrEat)
            return (NULL);
        if (verification_data(philo->data))
            return (NULL);
        philo_eat(philo);
        if (verification_data(philo->data))
            return (NULL);
        print_message(philo, "is sleeping");
        ft_usleep(philo->data, philo->data->timeToSleep);
        if (verification_data(philo->data))
            return (NULL);
        print_message(philo, "is thinking");
    }
}

void ft_free(t_main *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_philo)
        pthread_detach(data->philo[i].thread);
    free(data->philo);
    while (++i < data->nbr_philo)
        pthread_mutex_destroy(&data->fork[i]);
    free(data->fork);
}

int new_philosopher(t_main *data)
{
    int i;

    data->eat_count = 0;
    data->philo = malloc(sizeof(t_philosopher) * data->nbr_philo);
    data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
    pthread_mutex_init(&data->m_print, NULL);
    i = -1;
    while (++i < data->nbr_philo)
        pthread_mutex_init(&data->fork[i], NULL);
    pthread_mutex_init(&data->m_is_ok, NULL);
    pthread_mutex_init(&data->m_eat_count, NULL);
    data->time = get_time();
    //printf("%lld \n", data->time);
    start_half(data, 1);
    printf("%lld \n", data->time);
    // ft_usleep(data, 10);
    // start_half(data, 1);
    // pthread_create(&data->controlor, NULL, controlor, data);
    // pthread_join(data->controlor, NULL);
    // ft_free(data);
    return (0);
}


int verification_data(t_main *data)
{
    if (!(data->nbr_philo > 0))
        return (1);
    if (!(data->timeToDie > 0))
        return (1);
    if (!(data->timeToEat> 0))
        return (1);
    if (!(data->timeToSleep > 0))
        return (1);
    if (!(data->nbrEat > 0) && data->nbrEat != -1)
        return (1);
    return (0);
}

int main (int argc, char const *argv[])
{
    t_main  data;

    if (argc > 4 && argc <= 6)
    {
        data.nbr_philo = ft_atoi(argv[1]);
        data.timeToDie = ft_atoi(argv[2]);
        data.timeToEat = ft_atoi(argv[3]);
        data.timeToSleep = ft_atoi(argv[4]);
        data.nbrEat = -1;
        if (argc == 6)
            data.nbrEat = ft_atoi(argv[5]);
        if (verification_data(&data))
        {
            write(STDERR_FILENO, "Erreur de donnee\n", ft_strlen("Erreur de donnee\n"));
            return (1);
        }
        data.is_ok = 1;
        new_philosopher(&data);
        // printf("%d\n", data.nbr_philo);
        // printf("%d\n", data.timeToDie);
        // printf("%d\n", data.timeToEat);
        // printf("%d\n", data.timeToSleep);

    }
    else
    {
        write(STDERR_FILENO, "Erreur de donnee\n", ft_strlen("Erreur de donnee\n"));
        return (1);
    }
    return (0);
}