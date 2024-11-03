/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:45:11 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/03 17:35:39 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "LocationParser.hpp"
#include "external.hpp"
#include "util.hpp"

class ServerParser
{
  public:
	ServerParser(std::string server_str);
	ServerParser(const ServerParser &other);
	ServerParser &operator=(const ServerParser &other);
	virtual ~ServerParser(void);

	void parse_server_block();
	void handle_location_strings();
	int extract_location_block(std::string &remaining_server_block);
	std::string get_location(std::string remaining_server_block,
								int index_start_location_block,
								int &index_opening_bracket_location_block);
	void get_location_string(std::string src_str, std::string &res_location);
	void parse_location_string(std::string location,
											std::string remaining_server_block,
											int index_opening_bracket_location_block,
											int index_closing_bracket_location_block);

	class OpeningBracketForLocationBlockNotFound : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class ClosingBracketForLocationBlockNotFound : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class NestingWithinLocationBlockNotSupported : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class NoOpeningBracketInsideLocationBlock : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class NoLocationDefinedInsideLocationBlock : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

  private:
	std::string _server_str;
	std::string _keywords_str;
	std::vector<LocationParser> _location_parser;
	std::vector<std::string> _listen;
	std::vector<std::string> _root;
	std::vector<std::string> _index;
	std::vector<std::string> _server_name;
	std::vector<std::string> _error_page;
	std::vector<std::string> _client_max_body_size;
	std::vector<std::string> _autoindex;
};
