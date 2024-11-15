/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Creator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:42:13 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"
#include "Server.hpp"
#include "Server_Parser.hpp"

class Server_Creator
{
  public:
	Server_Creator();
	Server_Creator(const Server_Creator &other);
	Server_Creator &operator=(const Server_Creator &other);
	virtual ~Server_Creator(void);

	std::vector<Server> create_servers(std::vector<Server_Parser> server_parser);

  private:

};
