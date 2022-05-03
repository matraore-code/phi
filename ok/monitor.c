
#include "philo.h"

int	monitor_eat(t_main *status)
{
	pthread_mutex_lock(&status->m_eat_count);
	if (status->eat_count >= status->nbr_philo * status->nbrEat
		&& status->nbrEat != -1)
	{
		pthread_mutex_lock(&status->m_good);
		status->good = 0;
		pthread_mutex_unlock(&status->m_good);
		pthread_mutex_unlock(&status->m_eat_count);
		return (1);
	}
	pthread_mutex_unlock(&status->m_eat_count);
	return (0);
}

int	monitor_life(t_main *status, int i)
{
	if (get_time() > status->philos[i].limit_eat)
	{
		pthread_mutex_lock(&status->m_print);
		pthread_mutex_lock(&status->m_good);
		status->good = 0;
		pthread_mutex_unlock(&status->m_good);
		printf("%lld %d died\n", get_time() - status->time, i + 1);
		pthread_mutex_unlock(&status->m_print);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_main		*status;
	int			i;

	status = (t_main *)arg;
	while (1)
	{
		i = -1;
		while (++i < status->nbr_philo)
		{
			pthread_mutex_lock(&status->philos[i].m_eating);
			if (monitor_life(status, i) || monitor_eat(status))
			{
				pthread_mutex_unlock(&status->philos[i].m_eating);
				return (NULL);
			}
			pthread_mutex_unlock(&status->philos[i].m_eating);
		}
		usleep(100);
	}
}
