#include "philo.h"

int	mtn(void)
{
	struct timeval	mtntv;
	int				ms;

	gettimeofday(&mtntv, NULL);
	ms = (int)((mtntv.tv_usec / 1000) + (mtntv.tv_sec * 1000));
	return (ms);
}
