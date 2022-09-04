#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

# define NORMAL  "\x1B[0m"
# define RED  "\x1B[31m"

# define EATING "is eating"
# define ENOUGH_EAT "eat enough"
# define TOOK_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

typedef struct s_data   t_data;

typedef struct s_philo
{
    int             id;
    long            start_time;
    int             enough_meals;
    long            nb_of_meals;
    long            time;
    t_data          *input; 
    pthread_t       thread;
    pthread_mutex_t left_fork;
    pthread_mutex_t *right_fork;

}	t_philo;

typedef struct s_data
{
    int     nb_philos;
    int     time_to_think;
    int     is_dead;
    int     stop_eating;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     must_eat;
    t_philo *philosophers;
    pthread_mutex_t m_eat_enough;
    pthread_mutex_t m_print;
    pthread_mutex_t m_dead;
    pthread_mutex_t m_eat;
}	t_data;

// --- init.c ---- //
int     ft_init_struct(t_data *input, int ac, char **av);
void	ft_init_mutex(t_data *input);
void    ft_init_philos(t_data *input);

// ------ thread.c -------// 
void    ft_create_threads(t_data *input);
void    ft_join_threads(t_data *input);

//------- process.c ------//
void	*ft_monitoring(void *arg);
void    *ft_live(void *arg);

//------- monitoring.c ------//
int     ft_eat_enough(t_philo *one_philo);
int     ft_is_dead(t_data *input);
int     ft_check_meals(t_philo *one_philo);
int     ft_check_death(t_philo *one_philo);

// ----- actions -----//
void    ft_take_forks(t_philo *one_philo);
void    ft_eat(t_philo *one_philo);
void	ft_leave_forks(t_philo *one_philo);
void    ft_sleep(t_philo *one_philo);

// ----- actions_utils.c -----//
void    ft_one_philo(t_philo *one_philo);
void    ft_prioritize(t_philo *one_philo);

// ----- free and quit ----- //
void    ft_exit(char *msg);
void    ft_exit_2(t_data *input, char *msg);

//--- utils.c ---- //
void    ft_print_state(t_philo *one_philo, char *str);
void	ft_clean(t_data *input);
int     ft_atoi(const char *nptr);
int     ft_isdigit(int c);
int     ft_check_input(char **av);
int     ft_strcmp(char *s1, char *s2);

//------ time.c -------//
long long   ft_get_timestamp();
void        ft_usleep(int ms);
#endif