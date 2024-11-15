/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:35:59 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/15 16:47:47 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"

class Location
{
  public:
	Location(void);
	Location(const Location &other);
	Location &operator=(const Location &other);
	virtual ~Location(void);

  private:
	std::string _location;
	std::vector<std::string> _alias;
	std::map<std::string, bool> _allowed_methods;
	std::vector<std::string> _root;
	std::vector<std::string> _index;
	std::map<std::string, std::vector<std::string>> _error_pages;
	std::vector<uint> _client_max_body_size;
	std::vector<bool> _autoindex;
};
