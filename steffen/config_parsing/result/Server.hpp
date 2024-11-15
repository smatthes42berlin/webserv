/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:42:13 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/15 17:51:46 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Location.hpp"
#include "external.hpp"
#include "util.hpp"

class Server
{
  public:
	Server(void);
	Server(const Server &other);
	std::vector<std::string> _config_defs;
	Server &operator=(const Server &other);
	virtual ~Server(void);

	void set_listen(std::vector<util::Address> new_val);
	void set_routes(std::vector<Location> new_val);
	void add_route(Location new_val);
	void set_root(std::vector<std::string> new_val);
	void set_index(std::vector<std::string> new_val);
	void set_error_pages(std::map<std::string,
		std::vector<std::string>> new_val);
	void set_client_max_body_size(std::vector<uint> new_val);
	void set_autoindex(std::vector<bool> new_val);
	void set_server_name(std::vector<std::string> new_val);

	std::vector<util::Address> &get_listen();
	std::vector<Location> &get_routes();
	std::vector<std::string> &get_root();
	std::vector<std::string> &get_index();
	std::map<std::string, std::vector<std::string>> &get_error_pages();
	std::vector<uint> &get_client_max_body_size();
	std::vector<bool> &get_autoindex();
	std::vector<std::string> &get_server_name();

  private:
	std::vector<util::Address> _listen;
	std::vector<Location> _routes;
	std::vector<std::string> _root;
	std::vector<std::string> _index;
	std::map<std::string, std::vector<std::string>> _error_pages;
	std::vector<uint> _client_max_body_size;
	std::vector<bool> _autoindex;
	std::vector<std::string> _server_name;
};
