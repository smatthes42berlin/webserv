/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:55:07 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/03 18:51:23 by smatthes         ###   ########.fr       */
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

	void set_location_block_str(std::string);
	void set_location(std::string);
	void parse_location_block();

	void assign_handlers();

	void handle_root(std::vector<std::string> &key_val);
	void handle_index(std::vector<std::string> &key_val);
	void handle_error_page(std::vector<std::string> &key_val);
	void handle_client_max_body_size(std::vector<std::string> &key_val);
	void handle_methods(std::vector<std::string> &key_val);
	void handle_autoindex(std::vector<std::string> &key_val);
	void handle_alias(std::vector<std::string> &key_val);

	class EmptyLocationDefinition : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class UnknownKeywordInLocationBlock : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	void print(void);

  private:
	std::string _location_block_str;
	std::string _location;
	std::map<std::string, void (LocationParser::*)(std::vector<std::string> &)> keyword_handlers;
	std::vector<std::string> _root;
	std::vector<std::string> _index;
	std::vector<std::string> _error_page;
	std::vector<std::string> _client_max_body_size;
	std::vector<std::string> _methods;
	std::vector<std::string> _autoindex;
	std::vector<std::string> _alias;
};
