/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:30:36 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 13:30:46 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error/error.h"
#include <unistd.h>

int	print_error(const char *message)
{
	write(STDERR_FILENO, message, sizeof(message));
	return (1);
}
