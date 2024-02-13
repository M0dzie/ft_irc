/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_messages.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:45:25 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:02:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/Client.hpp"

void displayRPL(int RPLCode, Client const &client) {
    switch(RPLCode) {
        case RPL_WELCOME:
            sendMessage(client.getFD(), ":localhost 001 " + client.getNickname() + " :Welcome to your IRC Network!");
            break;
        case RPL_MOTDSTART:
            sendMessage(client.getFD(), ":localhost 375 " + client.getNickname() + " :- ft_irc Message of the day - ");
            break;
        case RPL_MOTD:
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :                                          ");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  ███████╗████████╗    ██╗██████╗  ██████╗");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  ██╔════╝╚══██╔══╝    ██║██╔══██╗██╔════╝");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  █████╗     ██║       ██║██████╔╝██║     ");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  ██╔══╝     ██║       ██║██╔══██╗██║     ");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  ██║        ██║       ██║██║  ██║╚██████╗");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :  ╚═╝        ╚═╝       ╚═╝╚═╝  ╚═╝ ╚═════╝");
            sendMessage(client.getFD(), ":localhost 372 " + client.getNickname() + " :                                          ");
            break;
        case RPL_ENDOFMOTD:
            sendMessage(client.getFD(), ":localhost 376 " + client.getNickname() + " :End of /MOTD command.");
            break;
            
        default:
            break;
    }
}

void displayChannelRPL(int RPLCode, Client const &client, Channel &channel) {
    switch(RPLCode) {
        case RPL_NOTOPIC:
            sendMessage(client.getFD(), ":localhost 331 " + client.getNickname() + " " + channel.getName() + " :No topic is set");
            break;
        case RPL_TOPIC:
            sendMessage(client.getFD(), ":localhost 332 " + client.getNickname() + " " + channel.getName() + " :" + channel.getTopic());
            break;
        case RPL_NAMREPLY:
            sendMessage(client.getFD(), ":localhost 353 " + client.getNickname() + " = " + channel.getName() + " :" + channel.getClientList());
            break;
        case RPL_ENDOFNAMES:
            sendMessage(client.getFD(), ":localhost 366 " + client.getNickname() + " " + channel.getName() + " :End of /NAMES list");
            break;
        case RPL_CHANNELMODEIS:
            sendMessage(client.getFD(), ":localhost 324 " + client.getNickname() + " " + channel.getName() + channel.getModes());
            break;

        default:
            break;
    }
}