/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:55:07 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/02 15:01:15 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"

class LocationParser
{
  public:
	LocationParser();
	LocationParser(std::string _location_block_str);
	LocationParser(const LocationParser &other);
	LocationParser &operator=(const LocationParser &other);
	virtual ~LocationParser(void);

	void parse_location_block();

	void set_location_block_str(std::string);
	void set_location(std::string);

  private:
	std::string _location_block_str;
	std::string _location;
	std::vector<std::string> _root;
	std::vector<std::string> _index;
	std::vector<std::string> _error_page;
	std::vector<std::string> _client_max_body_size;
	std::vector<std::string> _methods;
	std::vector<std::string> _autoindex;
	std::vector<std::string> _alias;
};
