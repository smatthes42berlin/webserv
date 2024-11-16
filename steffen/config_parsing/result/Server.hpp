/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:42:13 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/16 19:43:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Route.hpp"
#include "external.hpp"
#include "util.hpp"

class Server
{
  public:
	Server(void);
	Server(const Server &other);
	Server &operator=(const Server &other);
	virtual ~Server(void);

	void set_listen(int port, std::string ip);
	void set_root(std::string new_val);
	void set_autoindex(bool new_val);
	void set_client_max_body_size(uint new_val);
	void set_index(std::vector<std::string> new_val);
	void set_server_name(std::vector<std::string> new_val);
	void set_error_pages(std::map<std::string,
									std::vector<std::string> > new_val);	
	void set_routes(std::vector<Route> new_val);
	void add_route(Route new_val);

	util::Address get_listen() const;
	std::string get_root() const;
	bool get_autoindex() const;
	uint get_client_max_body_size() const;
	std::vector<std::string> get_index() const;
	std::vector<std::string> get_server_name() const;
	std::map<std::string, std::vector<std::string> > get_error_pages() const;
	std::vector<Route> get_routes() const;

  private:
	util::Address _listen;
	std::string _root;
	bool _autoindex;
	uint _client_max_body_size;
	std::vector<std::string> _index;
	std::vector<std::string> _server_name;
	std::map<std::string, std::vector<std::string> > _error_pages;
	std::vector<Route> _routes;
};

std::ostream &operator<<(std::ostream &os, Server const &server);

