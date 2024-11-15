/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive_Alias.hpp"
#include "Directive_Allowed_Methods.hpp"
#include "Directive_Client_Max_Body_Size.hpp"
#include "Directive_Error_Page.hpp"
#include "Directive_Index.hpp"
#include "Directive_Root.hpp"
#include "Directive_Autoindex.hpp"
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
	void handle_allowed_methods(std::vector<std::string> &key_val);
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
		UnknownKeywordInLocationBlock(std::string _keyword_name);
		virtual ~UnknownKeywordInLocationBlock() throw();
		virtual const char *what() const throw();

		private:
		std::string _keyword_name;
		mutable std::string _msg;
	};

	void print(void);

  private:
	Directive_Root _root_handler;
	Directive_Alias _alias_handler;
	Directive_Index _index_handler;
	Directive_Error_Page _error_page_handler;
	Directive_Client_Max_Body_Size _client_max_body_size_handler;
	Directive_Allowed_Methods _allowed_methods_handler;
	Directive_Autoindex _autoindex_handler;
	std::string _location_block_str;
	std::string _location;
	std::map<std::string,
				void (LocationParser::*)(std::vector<std::string> &)>
		keyword_handlers;
};
