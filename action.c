#include "philosopher.h"

void print_message(t_philosopher *philo, char *str)
{
    pthread_mutex_lock(&philo->data->m_print);
    if (philo->data->is_ok == 1)
    {
        printf ("%lld %d %s\n", get_time() - philo->data->time,
            philo->id + 1, str);
    }
    pthread_mutex_unlock(&philo->data->m_print);
}

void take_forks(t_main *data, int id)
{
    data->philo[id].l_fork = &data->fork[id];
    if (id + 1 >= data->nbr_philo)
        data->philo[id].r_fork = &data->fork[0];
    else
        data->philo[id].r_fork = &data->fork[id + 1];
}

void start_half(t_main *data, int i)
{
    while (i < data->nbr_philo)
    {
        data->philo[i].data = data;
        data->philo[i].id = i;
        data->philo[i].last_eat = data->time;
        data->philo[i].limit_eat = data->time + data->timeToDie;
        data->philo[i].nbr_eat = 0;
        take_forks(data, 1);
        pthread_mutex_init(&data->philo[i].m_eating, NULL);
        pthread_create(&data->philo[i].thread, NULL, philosopher,
            &data->philo[i]);
        i += 2;
    }
    
}

void philo_eat(t_philosopher *philo)
{
    pthread_mutex_init(philo->l_fork, NULL);
    print_message(philo, "has taken a fork");
    pthread_mutex_init(philo->r_fork, NULL);
    print_message(philo, "has taken a fork");
    pthread_mutex_lock(&philo->m_eating);
    print_message(philo, "is eating");
    philo->last_eat = get_time();
    philo->limit_eat = philo->last_eat + philo->data->timeToDie;
    pthread_mutex_unlock(&philo->m_eating);
    ft_usleep(philo->data, philo->data->timeToEat);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
    if (philo->data->nbrEat != -1)
    {
        pthread_mutex_lock(&philo->data->m_eat_count);
        philo->nbr_eat += 1;
        philo->data->eat_count += 1;
        pthread_mutex_unlock(&philo->data->m_eat_count);
    }
}