/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/16 19:50:46 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "external.hpp"

Server::Server()
	: _root("./"),
		_autoindex(false),
		_client_max_body_size(1024 * 1024)
{
	this->set_listen(4000, "0.0.0.0");
	this->_index.push_back("index.html");
	this->_error_pages["404"].push_back("404.html");
	return ;
}

Server::Server(const Server &other)
{
	this->_listen = other._listen;
	this->_root = other._root;
	this->_autoindex = other._autoindex;
	this->_client_max_body_size = other._client_max_body_size;
	this->_index = other._index;
	this->_server_name = other._server_name;
	this->_error_pages = other._error_pages;
	this->_routes = other._routes;
	return ;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->_listen = other._listen;
		this->_root = other._root;
		this->_autoindex = other._autoindex;
		this->_client_max_body_size = other._client_max_body_size;
		this->_index = other._index;
		this->_server_name = other._server_name;
		this->_error_pages = other._error_pages;
		this->_routes = other._routes;
	}
	return (*this);
}

Server::~Server(void)
{
	return ;
}

void Server::set_listen(int port, std::string ip)
{
	this->_listen.port = port;
	this->_listen.ip = ip;
}

void Server::set_root(std::string new_val)
{
	this->_root = new_val;
}

void Server::set_autoindex(bool new_val)
{
	this->_autoindex = new_val;
}

void Server::set_client_max_body_size(uint new_val)
{
	this->_client_max_body_size = new_val;
}

void Server::set_index(std::vector<std::string> new_val)
{
	this->_index = new_val;
}

void Server::set_server_name(std::vector<std::string> new_val)
{
	this->_server_name = new_val;
}

void Server::set_error_pages(std::map<std::string,
										std::vector<std::string> > new_val)
{
	this->_error_pages = new_val;
}

void Server::set_routes(std::vector<Route> new_val)
{
	this->_routes = new_val;
}

void Server::add_route(Route new_val)
{
	this->_routes.push_back(new_val);
}

util::Address Server::get_listen() const
{
	return (this->_listen);
}

std::string Server::get_root() const
{
	return (this->_root);
}

bool Server::get_autoindex() const
{
	return (this->_autoindex);
}

uint Server::get_client_max_body_size() const
{
	return (this->_client_max_body_size);
}

std::vector<Route> Server::get_routes() const
{
	return (this->_routes);
}

std::vector<std::string> Server::get_index() const
{
	return (this->_index);
}
std::map<std::string, std::vector<std::string> > Server::get_error_pages() const
{
	return (this->_error_pages);
}

std::vector<std::string> Server::get_server_name() const
{
	return (this->_server_name);
}

	std::vector<Route> _routes;

std::ostream &operator<<(std::ostream &os, Server const &server)
{
	
	std::map<std::string, std::string> col_map = util::get_color_map();

	os << std::endl
		<< std::endl
		<< std::endl;
	os << "Server";
	os << std::endl;
	os << col_map["red"];
	os << "[Address] ";
	os << col_map["green"];
	os << "_listen: ";
	util::Address listen = server.get_listen();
	os << col_map["reset"];
	os << std::endl;
	os << listen.ip;
	os << std::endl;
	os << listen.port;
	os << std::endl;
	os << col_map["red"];
	os << "[string] ";
	os << col_map["green"];
	os << "root: ";
	os << col_map["reset"];
	os << server.get_root();
	os << std::endl;
	os << col_map["red"];
	os << "[uint] ";
	os << col_map["green"];
	os << "client_max_body_size: ";
	os << col_map["reset"];
	os << server.get_client_max_body_size();
	os << std::endl;
	os << col_map["red"];
	os << "[bool] ";
	os << col_map["green"];
	os << "autoindex: ";
	os << col_map["reset"];
	os << server.get_autoindex();
	os << std::endl;
	os << col_map["red"];
	os << "[vector<string>] ";
	os << col_map["green"];
	os << "index: ";
	os << col_map["reset"];
	std::vector<std::string> indexes = server.get_index();
	for (std::vector<std::string>::iterator vec_it = indexes.begin(); vec_it != indexes.end(); ++vec_it)
	{
		os << *vec_it << " ";
	}
	os << std::endl;
	os << col_map["red"];
	os << "[vector<string>] ";
	os << col_map["green"];
	os << "server_name: ";
	os << col_map["reset"];
	std::vector<std::string> server_names = server.get_server_name();
	for (std::vector<std::string>::iterator vec_it = server_names.begin(); vec_it != server_names.end(); ++vec_it)
	{
		os << *vec_it << " ";
	}
	os << std::endl;
	os << col_map["red"];
	os << "[map<string, vector<string>>] ";
	os << col_map["green"];
	os << "error_pages: ";
	os << col_map["reset"];
	os << std::endl;
	std::map<std::string,
				std::vector<std::string> >
		error_pages = server.get_error_pages();
	for (std::map<std::string,
					std::vector<std::string> >::iterator it = error_pages.begin();
			it != error_pages.end();
			++it)
	{
		os << it->first << " ";
		const std::vector<std::string> &values = it->second;
		for (std::vector<std::string>::const_iterator vec_it = values.begin(); vec_it != values.end(); ++vec_it)
		{
			os << *vec_it << " ";
		}
		os << std::endl;
	}
	std::vector<Route> server_routes = server.get_routes();
		for (std::vector<Route>::iterator vec_it = server_routes.begin(); vec_it != server_routes.end(); ++vec_it)
	{
		os << *vec_it;
	}
	os << std::endl
		<< std::endl
		<< std::endl;
	return (os);
}
