
#include "philo.h"

int	check_good(t_main *status)
{
	pthread_mutex_lock(&status->m_good);
	if (!status->good)
	{
		pthread_mutex_unlock(&status->m_good);
		return (1);
	}
	pthread_mutex_unlock(&status->m_good);
	return (0);
}
