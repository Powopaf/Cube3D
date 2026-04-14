/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:35:27 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 11:35:42 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_MLX_INIT "Error: Failed to initialize MLX."
# define ERROR_WINDOW_INIT "Error: Failed to create a window."
# define ERROR_IMAGE_INIT "Error: Failed to create an image."

int	print_error(const char *message);

#endif
