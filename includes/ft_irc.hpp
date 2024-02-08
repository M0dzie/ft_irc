/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:54 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/08 17:12:57 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>
# include <algorithm>
# include <map>
# include <vector>
# include <poll.h>
# include <signal.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>

# include "Server.hpp"
# include "Client.hpp"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GRAY "\033[0;37m"
# define DEFAULT "\033[0;39m"
# define RESET "\033[0m" 
# define BOLD "\033[1m"
# define ERROR RED BOLD "Error: " RESET

# define USERLEN 18

void displayErrorMessage(std::string const &msg);
void displayMessage(int from, std::string message);

#endif