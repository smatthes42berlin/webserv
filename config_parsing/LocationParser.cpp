/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:29:15 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationLocationParser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:54 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/02 13:56:13 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationParser.hpp"
#include "external.hpp"

LocationParser::LocationParser()
	: _location_block_str(""), _location("")
{
	this->assign_handlers();
	return ;
}

LocationParser::LocationParser(std::string location_block_str)
	: _location_block_str(location_block_str),
		_location("")
{
	this->assign_handlers();
	return ;
}

LocationParser::LocationParser(const LocationParser &other)
{
	this->_root_handler = other._root_handler;
	this->_alias_handler = other._alias_handler;
	this->_index_handler = other._index_handler;
	this->_error_page_handler = other._error_page_handler;
	this->_client_max_body_size_handler = other._client_max_body_size_handler;
	this->_allowed_methods_handler = other._allowed_methods_handler;
	this->_autoindex_handler = other._autoindex_handler;
	this->_location_block_str = other._location_block_str;
	this->_location = other._location;
	this->assign_handlers();
	return ;
}

LocationParser &LocationParser::operator=(const LocationParser &other)
{
	if (this != &other)
	{
		this->_root_handler = other._root_handler;
		this->_alias_handler = other._alias_handler;
		this->_index_handler = other._index_handler;
		this->_error_page_handler = other._error_page_handler;
		this->_client_max_body_size_handler = other._client_max_body_size_handler;
		this->_allowed_methods_handler = other._allowed_methods_handler;
		this->_autoindex_handler = other._autoindex_handler;
		this->_location_block_str = other._location_block_str;
		this->_location = other._location;
		this->assign_handlers();
	}
	return (*this);
}

LocationParser::~LocationParser(void)
{
	return ;
}

void LocationParser::assign_handlers()
{
	this->keyword_handlers["root"] = &LocationParser::handle_root;
	this->keyword_handlers["alias"] = &LocationParser::handle_alias;
	this->keyword_handlers["index"] = &LocationParser::handle_index;
	this->keyword_handlers["error_page"] = &LocationParser::handle_error_page;
	this->keyword_handlers["client_max_body_size"] = &LocationParser::handle_client_max_body_size;
	this->keyword_handlers["allowed_methods"] = &LocationParser::handle_allowed_methods;
	this->keyword_handlers["autoindex"] = &LocationParser::handle_autoindex;
}

void LocationParser::set_location_block_str(std::string location_block_str)
{
	this->_location_block_str = location_block_str;
}

void LocationParser::set_location(std::string location)
{
	this->_location = location;
}

void LocationParser::parse_location_block()
{
	std::vector<std::string> key_value_strings;
	std::vector<std::string> key_value_vector;
	if (this->_location_block_str.empty())
		throw EmptyLocationDefinition();
	key_value_strings = util::split(this->_location_block_str, ';');
	std::vector<std::string>::iterator it_key_val;
	for (it_key_val = key_value_strings.begin(); it_key_val != key_value_strings.end(); it_key_val++)
	{
		key_value_vector = util::split(*it_key_val, ' ');
		std::map<std::string,
					void (LocationParser::*)(std::vector<std::string> &)>::iterator it = this->keyword_handlers.find(key_value_vector[0]);
		if (it != this->keyword_handlers.end())
		{
			(this->*(it->second))(key_value_vector);
		}
		else
			throw UnknownKeywordInLocationBlock(key_value_vector[0]);
	}
}

void LocationParser::handle_index(std::vector<std::string> &key_val)
{
	this->_index_handler.check_and_add(key_val);
}
void LocationParser::handle_error_page(std::vector<std::string> &key_val)
{
	this->_error_page_handler.check_and_add(key_val);
}

void LocationParser::handle_client_max_body_size(std::vector<std::string> &key_val)
{
	this->_client_max_body_size_handler.check_and_add(key_val);
}

void LocationParser::handle_allowed_methods(std::vector<std::string> &key_val)
{
	this->_allowed_methods_handler.check_and_add(key_val);
}
void LocationParser::handle_autoindex(std::vector<std::string> &key_val)
{
	this->_autoindex_handler.check_and_add(key_val);
}

void LocationParser::handle_root(std::vector<std::string> &key_val)
{
	this->_root_handler.check_and_add(key_val,
										this->_alias_handler.get_config_defs());
}

void LocationParser::handle_alias(std::vector<std::string> &key_val)
{
	this->_alias_handler.check_and_add(key_val,
										this->_root_handler.get_config_defs());
}

const char *LocationParser::EmptyLocationDefinition::what() const throw()
{
	return ("The location block does not contain any directives!\n");
}

LocationParser::UnknownKeywordInLocationBlock::UnknownKeywordInLocationBlock(std::string keyword_name)
	: _keyword_name(keyword_name)
{
}

LocationParser::UnknownKeywordInLocationBlock::~UnknownKeywordInLocationBlock() throw()
{
}

const char *LocationParser::UnknownKeywordInLocationBlock::what() const throw()
{
	this->_msg = "keyword: ";
	this->_msg += this->_keyword_name;
	this->_msg += "\n";
	this->_msg
		+= "There was an unknown keyword encountered inside a location block!";
	return (this->_msg.c_str());
}

void LocationParser::print(void)
{
	std::cout << std::endl;
	std::cout << "**********************";
	std::cout << std::endl;
	std::cout << "LocationParser" << std::endl;
	std::cout << "Location >>" << this->_location << "<<";
	std::cout << std::endl;
	std::cout << "Block String >>" << this->_location_block_str << "<<";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "**********************";
	std::cout << std::endl;
}
