#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

#ifndef DEBUG
# define DEBUG 0
#endif

typedef struct philosopher
{
    int id;
    int nbr_eat;
    long long last_eat;
    long long limit_eat;
    pthread_t thread;
    pthread_mutex_t m_eating;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    struct s_main   *data;
}               t_philosopher;

typedef struct s_main
{
    int     nbr_philo;
    int     timeToEat;
    int     timeToSleep;
    int     timeToDie;
    int     nbrEat;
    int     is_ok;
    int     eat_count;
    long long   time;
    pthread_t   controlor;
    pthread_mutex_t m_eat_count;
    pthread_mutex_t m_is_ok;
    pthread_mutex_t *fork;
    pthread_mutex_t m_print;
    pthread_mutex_t m_dead;
    t_philosopher   *philo;
}               t_main;

typedef struct s_args
{
    t_main  *data;
    t_philosopher *philo;
} t_args;



int			ft_strlen(const char *str);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(int fd, int n);
long long   get_time(void);
int is_it_ok(t_main *data);
void    ft_usleep(t_main *data, int stop_ms);
void  *philosopher(void *arg);
int verification_data(t_main *data);
void start_half(t_main *data, int i);
void take_forks(t_main *data, int id);
void print_message(t_philosopher *philo, char *str);
void *controlor(void *arg);
void philo_eat(t_philosopher *philo);








#endif