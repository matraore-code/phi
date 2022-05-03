
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_eat;
	long long		limit_eat;
	int				nbr_eat;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_main	*status;
}	t_philo;

typedef struct s_main
{
	int				nbr_philo;
	int				timeToDie;
	int				timeToEat;
	int				timeToSleep;
	int				nbrEat;
	int				good;
	int				eat_count;
	pthread_mutex_t	m_eat_count;
	pthread_mutex_t	m_good;
	long long		time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
}	t_main;

typedef struct s_args
{
	t_main	*status;
	t_philo	*philo;
}	t_args;

int			ft_strlen(const char *str);
int			ft_atoi(const char *str);
int			check_good(t_main *status);
long long	get_time(void);
void		*philosopher(void *arg);
void		start_half(t_main *status, int i);
void		ft_usleep(t_main *status, int stop_ms);
void		ft_putnbr_fd(int n, int fd);
void		print_message(t_philo *philo, char *str);
void		philo_eat(t_philo *philo);
void		*monitor(void *arg);

#endif
