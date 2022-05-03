#include "philosopher.h"

void    ft_usleep(t_main *data, int stop_ms)
{
    long long end_ms;

    end_ms = get_time() + stop_ms;
    while (get_time() < end_ms)
    {
        pthread_mutex_lock(&data->m_is_ok);
        if (data->is_ok != 1)
        {
            pthread_mutex_unlock(&data->m_is_ok);
            return ;
        }
        pthread_mutex_unlock(&data->m_is_ok);
        usleep(100);
    }
}

int is_it_ok(t_main *data)
{
    pthread_mutex_lock(&data->m_is_ok);
    if (!data->is_ok)
    {
        pthread_mutex_unlock(&data->m_is_ok);
        return (1);
    }
    pthread_mutex_unlock(&data->m_is_ok);
    return (0);
}
