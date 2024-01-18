/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:24 by msapin            #+#    #+#             */
/*   Updated: 2024/01/18 18:23:26 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePass(Commands & command) {

	std::string password = *(command.getArgSplit().begin());

    Client & tmpClient = command.getClient();

    tmpClient.setPassword(password);
    if (password == command.getServer().getPassword())
	{
        // std::cout << "PASSWORD Valid" << std::endl;
        tmpClient.setPassValidate(true);
	}
    else
    {
        // std::cout << "PASSWORD Invalid" << std::endl;
        tmpClient.setPassValidate(false);
    }
}
