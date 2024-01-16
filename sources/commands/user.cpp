/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/01/16 17:08:37 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

// void	executeUser(std::vector<std::string> commandLine, int fd) {
void	executeUser(Commands & command) {
	
	(void)command;

	std::cout << "Execute JOIN" << std::endl;
	// std::vector<std::string>::iterator itChannel = commandLine.begin();
	// std::string command = *itChannel;
	// std::string userName = *(++itChannel);

	// // sendMessage(fd, "USER " + userName + " 0 * :realname");		// don't send but update username
	// // check if not already connected and all arg valid, password, username, nickname
	// // loginClient(userName, fd);
	// sendMessage(fd, ":localhost 376 " + userName + ":" + userName + "connected!");
}
