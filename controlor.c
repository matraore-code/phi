#include "philosopher.h"

int controlor_eat(t_main *data)
{
    pthread_mutex_lock(&data->m_eat_count);
    if(data->eat_count >= data->nbr_philo * data->nbrEat
        && data->nbrEat != -1)
    {
        pthread_mutex_lock(&data->m_is_ok);
        data->is_ok = 0;
        pthread_mutex_unlock(&data->m_is_ok);
        pthread_mutex_unlock(&data->m_eat_count);
        return (-1);
    }
    return (0);
}

int controlor_life(t_main *data, int i)
{
    if (get_time() > data->philo[i].limit_eat)
    {
        pthread_mutex_lock(&data->m_print);
        pthread_mutex_lock(&data->m_is_ok);
        data->is_ok = 0;
        pthread_mutex_unlock(&data->m_is_ok);
        printf("%lld %d died", get_time() - data->time, i + 1);
        pthread_mutex_unlock(&data->m_print);
        return (-1);
    }
    return (0);
}

void *controlor(void *arg)
{
    t_main *data;
    int i;

    data = (t_main *)arg;
    while (1)
    {
        i = -1;
        while (++i < data->nbr_philo)
        {
            pthread_mutex_lock(&data->philo[i].m_eating);
            if (controlor_life(data, i) || controlor_eat(data))
            {
                pthread_mutex_unlock(&data->philo[i].m_eating);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philo[i].m_eating);
        }
        usleep(100);
    }
}