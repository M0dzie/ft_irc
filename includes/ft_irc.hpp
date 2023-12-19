/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:54 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/19 13:36:37 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>
# include <sys/socket.h>
# include <netinet/in.h>

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GRAY "\033[0;37m"
# define RESET "\033[0m" 
# define BOLD "\033[1m"

/* ---------- EXECUTING ---------- */
/* ---------- main.cpp ---------- */

/* ---------- User.cpp ---------- */

/* ---------- Server.cpp ---------- */


/* ---------- PARSING ---------- */
/* ---------- errors.cpp ---------- */
void displayErrorMessage(std::string const &msg);

/* ---------- parsing.cpp ---------- */
bool isPortValid(char *argv);

#endif