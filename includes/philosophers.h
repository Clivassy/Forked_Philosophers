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
# define GREEN  "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE  "\x1B[34m"
# define MAGENTA  "\x1B[35m"
# define CYAN  "\x1B[36m"
# define WHITE  "\x1B[37m"

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

# define IS_ALIVE 0
# define IS_DEAD 1
# define ENOUGH_MEALS 0
# define END -1
# define FAILURE 2

# define EATING "is eating"
# define ENOUGH_EAT "eat enough"
# define TOOK_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

// errors.c //

typedef struct s_data   t_data;

typedef struct s_philo
{
    int             id;
    long    start_time;
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
    int is_over;
    int is_dead;
}	t_data;

//--- init.c ---- //
int     ft_init_struct(t_data *input, int ac, char **av);
void    ft_init_philos(t_data *input);

//free and quit 
void    ft_exit(t_data *input, char *msg);

// thread.c 
void    ft_create_threads(t_data *input);
void	ft_init_mutex(t_data *input);
void    ft_join_threads(t_data *input);

// process.c
void    *ft_live(void *arg);

// actions
void    ft_sleep(t_philo *one_philo);
void   ft_take_forks(t_philo *one_philo);
void	ft_leave_forks(t_philo *one_philo);
void    ft_eat(t_philo *one_philo);
void    ft_print_state(t_philo *one_philo, char *str);

//--- utils.c ---- //
int     ft_atoi(const char *nptr);
int     ft_isdigit(int c);
int     ft_check_input(char **av);
int     ft_strcmp(char *s1, char *s2);

//------ time.c -------//
long long    ft_get_timestamp();
void	ft_usleep(int ms);
//void	ft_monitoring(t_data *input);

int	ft_eat_enough(t_philo *one_philo);
int     ft_sleep_and_think(t_philo *one_philo);

void	*ft_monitoring(void *arg);

long long	ft_time_diff(long long time_start, long long time_end);
void	ft_wait_2(long long time, t_data *input);
int	ft_check_death(t_philo *one_philo);
int	ft_check_meals(t_philo *one_philo);
int	    ft_is_dead(t_data *input);
void	ft_clean(t_data *input);
#endif