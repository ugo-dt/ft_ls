/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:07:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/22 12:04:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#define NSEC_PER_SEC 1000000000

/** \fn struct timespec timespec_normalise(struct timespec ts)
 *  \brief Normalises a timespec structure.
 *
 * Returns a normalised version of a timespec structure, according to the
 * following rules:
 *
 * 1) If tv_nsec is >=1,000,000,00 or <=-1,000,000,000, flatten the surplus
 *    nanoseconds into the tv_sec field.
 *
 * 2) If tv_nsec is negative, decrement tv_sec and roll tv_nsec up to represent
 *    the same value attainable by ADDING nanoseconds to tv_sec.
 */
struct timespec timespec_normalise(struct timespec ts)
{
	while (ts.tv_nsec >= NSEC_PER_SEC)
	{
		++(ts.tv_sec);
		ts.tv_nsec -= NSEC_PER_SEC;
	}

	while (ts.tv_nsec <= -NSEC_PER_SEC)
	{
		--(ts.tv_sec);
		ts.tv_nsec += NSEC_PER_SEC;
	}

	if (ts.tv_nsec < 0)
	{
		/* Negative nanoseconds isn't valid according to POSIX.
		 * Decrement tv_sec and roll tv_nsec over.
		 */

		--(ts.tv_sec);
		ts.tv_nsec = (NSEC_PER_SEC + ts.tv_nsec);
	}

	return ts;
}

/** \fn int timespec_cmp(struct timespec ts1, struct timespec ts2)
 *  \brief Returns (1, 0, -1) if ts1 is (greater than, equal to, less than) to ts2.
 */
int timespec_cmp(struct timespec ts1, struct timespec ts2)
{
	ts1 = timespec_normalise(ts1);
	ts2 = timespec_normalise(ts2);

	if (ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec == ts2.tv_nsec)
	{
		return 0;
	}
	else if ((ts1.tv_sec > ts2.tv_sec) || (ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec > ts2.tv_nsec))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
