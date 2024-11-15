/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:42:13 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "LocationParser.hpp"
#include "Directive_Client_Max_Body_Size.hpp"
#include "Directive_Error_Page.hpp"
#include "Directive_Index.hpp"
#include "Directive_Root.hpp"
#include "Directive_Autoindex.hpp"
#include "Directive_Listen.hpp"
#include "Directive_Server_Name.hpp"
#include "external.hpp"
#include "util.hpp"

class ServerParser
{
  public:
	ServerParser(std::string server_str);
	ServerParser(const ServerParser &other);
	ServerParser &operator=(const ServerParser &other);
	virtual ~ServerParser(void);

	void parse_server_block(void);
	void handle_location_strings(void);
	void handle_server_directive_str(void);

	int extract_location_block(std::string &remaining_server_block);
	std::string get_location(std::string remaining_server_block,
								int index_start_location_block,
								int &index_opening_bracket_location_block);
	void get_location_string(std::string src_str, std::string &res_location);
	void parse_location_string(std::string location,
								std::string remaining_server_block,
								int index_opening_bracket_location_block,
								int index_closing_bracket_location_block);
	void assign_handlers();

	void handle_root(std::vector<std::string> &key_val);
	void handle_index(std::vector<std::string> &key_val);
	void handle_error_page(std::vector<std::string> &key_val);
	void handle_client_max_body_size(std::vector<std::string> &key_val);
	void handle_autoindex(std::vector<std::string> &key_val);
	void handle_listen(std::vector<std::string> &key_val);
	void handle_server_name(std::vector<std::string> &key_val);

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

	class UnknownKeywordInServerBlock : public std::exception
	{
		public:
		UnknownKeywordInServerBlock(std::string _keyword_name);
		virtual ~UnknownKeywordInServerBlock() throw();
		virtual const char *what() const throw();

		private:
		std::string _keyword_name;
		mutable std::string _msg;
	};

  private:
	std::string _server_str;
	std::string _keywords_str;
	std::vector<LocationParser> _location_parser;
	std::map<std::string,
				void (ServerParser::*)(std::vector<std::string> &)>
		keyword_handlers;
	Directive_Root _root_handler;
	Directive_Index _index_handler;
	Directive_Error_Page _error_page_handler;
	Directive_Client_Max_Body_Size _client_max_body_size_handler;
	Directive_Autoindex _autoindex_handler;
	Directive_Listen _listen_handler;
	Directive_Server_Name _server_name_handler;
};
