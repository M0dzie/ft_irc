/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:03:54 by msapin            #+#    #+#             */
/*   Updated: 2024/01/18 18:47:08 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePing(Commands & command) {

	std::string tmpPing = *command.getArgSplit().begin();
	std::string serverName = "ft_irc"; /////////////////////// TEMPORARY

	sendMessage(command.getClient().getFD(), serverName + " PONG " + tmpPing);
	// sendMessage(command.getClient().getFD(), serverName + " PONG " + tmpPing);
	// displayMessage(SERVER, serverName + " PONG " + tmpPing);
}
