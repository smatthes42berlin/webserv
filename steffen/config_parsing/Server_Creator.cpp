/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Creator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server_Creator.hpp"
#include "external.hpp"

Server_Creator::Server_Creator()
{
	return ;
}

Server_Creator::Server_Creator(const Server_Creator &other)
{
	(void)other;
	return ;
}

Server_Creator &Server_Creator::operator=(const Server_Creator &other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

Server_Creator::~Server_Creator(void)
{
	return ;
}

std::vector<Server> Server_Creator::create_servers(std::vector<Server_Parser> server_parser)
{

	std::vector<Server> servers;
	for (std::vector<Server_Parser>::iterator it = server_parser.begin(); it != server_parser.end(); ++it)
	{
		Server new_server;

		new_server.set_autoindex((*it).get_autoindex_handler().get_config_defs());
		new_server.set_client_max_body_size((*it).get_client_max_body_size_handler().get_config_defs());
		new_server.set_error_pages((*it).get_error_page_handler().get_error_pages());
		new_server.set_index((*it).get_index_handler().get_config_defs());
		new_server.set_listen((*it).get_listen_handler().get_config_defs());
		new_server.set_root((*it).get_root_handler().get_config_defs());
		new_server.set_server_name((*it).get_server_name_handler().get_config_defs());
		// create routes array
		new_server.set_routes((*it).);
		servers.push_back(new_server);
	}
	return (servers);
}

std::vector<Location_Parser> _location_parser;

void	create_routes(Server &new_server, Server_Parser &cur_parser)
{
	std::vector<Location_Parser> location_parsers = cur_parser.get_location_parser();
	for (std::vector<Location_Parser>::iterator it = location_parsers.begin(); it != location_parsers.end(); ++it)
	{
		Location new_location;
		new_server.add_route(new_location);

	}
}
