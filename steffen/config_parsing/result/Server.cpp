/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/15 17:52:13 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "external.hpp"

Server::Server()
{
	return ;
}

Server::Server(const Server &other)
{
	(void)other;
	return ;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

Server::~Server(void)
{
	return ;
}

void Server::set_listen(std::vector<util::Address> new_val)
{
	this->_listen = new_val;
}
void Server::set_routes(std::vector<Location> new_val)
{
	this->_routes = new_val;
}

void Server::add_route(Location new_val)
{
	this->_routes.push_back(new_val);
}
void Server::set_root(std::vector<std::string> new_val)
{
	this->_root = new_val;
}
void Server::set_index(std::vector<std::string> new_val)
{
	this->_index = new_val;
}
void Server::set_error_pages(std::map<std::string,
	std::vector<std::string>> new_val)
{
	this->_error_pages = new_val;
}
void Server::set_client_max_body_size(std::vector<uint> new_val)
{
	this->_client_max_body_size = new_val;
}
void Server::set_autoindex(std::vector<bool> new_val)
{
	this->_autoindex = new_val;
}
void Server::set_server_name(std::vector<std::string> new_val)
{
	this->_server_name = new_val;
}

std::vector<util::Address> &Server::get_listen()
{
	return (this->_listen);
}
std::vector<Location> &Server::get_routes()
{
	return (this->_routes);
}
std::vector<std::string> &Server::get_root()
{
	return (this->_root);
}
std::vector<std::string> &Server::get_index()
{
	return (this->_index);
}
std::map<std::string, std::vector<std::string>> &Server::get_error_pages()
{
	return (this->_error_pages);
}
std::vector<uint> &Server::get_client_max_body_size()
{
	return (this->_client_max_body_size);
}
std::vector<bool> &Server::get_autoindex()
{
	return (this->_autoindex);
}
std::vector<std::string> &Server::get_server_name()
{
	return (this->_server_name);
}
