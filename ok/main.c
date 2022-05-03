

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->status->nbrEat != -1
			&& philo->nbr_eat == philo->status->nbrEat)
			return (NULL);
		if (check_good(philo->status))
			return (NULL);
		philo_eat(philo);
		if (check_good(philo->status))
			return (NULL);
		print_message(philo, "is sleeping");
		ft_usleep(philo->status, philo->status->timeToSleep);
		if (check_good(philo->status))
			return (NULL);
		print_message(philo, "is thinking");
	}
}

void	ft_clear(t_main *status)
{
	int	i;

	i = -1;
	while (++i < status->nbr_philo)
		pthread_detach(status->philos[i].thread);
	free(status->philos);
	while (++i < status->nbr_philo)
		pthread_mutex_destroy(&status->forks[i]);
	free(status->forks);
}

int	create_philo(t_main *status)
{
	int	i;

	status->eat_count = 0;
	status->philos = malloc(sizeof(t_philo) * status->nbr_philo);
	status->forks = malloc(sizeof(pthread_mutex_t) * status->nbr_philo);
	pthread_mutex_init(&status->m_print, NULL);
	i = -1;
	while (++i < status->nbr_philo)
		pthread_mutex_init(&status->forks[i], NULL);
	pthread_mutex_init(&status->m_good, NULL);
	pthread_mutex_init(&status->m_eat_count, NULL);
	status->time = get_time();
	start_half(status, 0);
	ft_usleep(status, 10);
	start_half(status, 1);
	pthread_create(&status->monitor, NULL, monitor, status);
	pthread_join(status->monitor, NULL);
	ft_clear(status);
	return (0);
}

int	check_inputs(t_main *status)
{
	if (!(status->nbr_philo > 0))
		return (1);
	if (!(status->timeToEat > 0))
		return (1);
	if (!(status->timeToSleep > 0))
		return (1);
	if (!(status->timeToDie > 0))
		return (1);
	if (!(status->nbrEat > 0) && status->nbrEat != -1)
		return (1);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_main		status;

	if (argc > 4 && argc <= 6)
	{
		status.nbr_philo = ft_atoi(argv[1]);
		status.timeToDie = ft_atoi(argv[2]);
		status.timeToEat = ft_atoi(argv[3]);
		status.timeToSleep = ft_atoi(argv[4]);
		status.nbrEat = -1;
		if (argc == 6)
			status.nbrEat = ft_atoi(argv[5]);
		if (check_inputs(&status))
		{
			write(STDERR_FILENO, "Error inputs\n", ft_strlen("Error inputs\n"));
			return (1);
		}
		status.good = 1;
		create_philo(&status);
	}
	else
	{
		write(STDERR_FILENO, "Error inputs\n", ft_strlen("Error inputs\n"));
		return (1);
	}
	return (0);
}
