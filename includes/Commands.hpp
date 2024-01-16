/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:15 by msapin            #+#    #+#             */
/*   Updated: 2024/01/16 17:08:07 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "ft_irc.hpp"

void	sendMessage(int clientFd, std::string msg);

class Commands {

	private:
		Commands(void);
		std::string _name;
		std::map< std::string, std::vector< std::string > > _mapArguments;

	public:
		Commands(std::string line);
		~Commands(void);

		void executeCommand();
};
#endif
