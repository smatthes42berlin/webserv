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
	: _location_block_str(location_block_str), _location("")
{
	this->assign_handlers();
	return ;
}

LocationParser::LocationParser(const LocationParser &other)
{
	(void)other;
	return ;
}

LocationParser &LocationParser::operator=(const LocationParser &other)
{
	if (this != &other)
	{
		;
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
	this->keyword_handlers["methods"] = &LocationParser::handle_methods;
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
			throw UnknownKeywordInLocationBlock();
	}
	// split at ' '
	// check first word as keyword
	// handle rest as args of keyword
}

void LocationParser::handle_root(std::vector<std::string> &key_val)
{
	std::cout << "handle root" << std::endl;
	if (this->_root.size() > 0)
		throw DuplicateIdentifier();
	if (key_val.size() != 2)
		throw InvalidNumberOfArguments();
	if (this->_alias.size() > 0)
		throw AliasNotAllowedWithRoot();
	this->_root.push_back(key_val[1]);
}
void LocationParser::handle_index(std::vector<std::string> &key_val)
{
	std::cout << "handle index" << std::endl;
	if (key_val.size() < 2)
		throw InvalidNumberOfArguments();
	util::vector_append_from_index(this->_index, key_val, 1);
}
void LocationParser::handle_error_page(std::vector<std::string> &key_val)
{
	(void)key_val;
	std::cout << "handle error_page" << std::endl;
}
void LocationParser::handle_client_max_body_size(std::vector<std::string> &key_val)
{
	(void)key_val;
	std::cout << "handle client_max_body_size" << std::endl;
}
void LocationParser::handle_methods(std::vector<std::string> &key_val)
{
	(void)key_val;
	std::cout << "handle methods" << std::endl;
}
void LocationParser::handle_autoindex(std::vector<std::string> &key_val)
{
	(void)key_val;
	std::cout << "handle autoindex" << std::endl;
}
void LocationParser::handle_alias(std::vector<std::string> &key_val)
{
	std::cout << "handle alias" << std::endl;
	if (this->_alias.size() > 0)
		throw DuplicateIdentifier();
	if (key_val.size() != 2)
		throw InvalidNumberOfArguments();
	if (this->_root.size() > 0)
		throw AliasNotAllowedWithRoot();
	this->_alias.push_back(key_val[1]);
}

const char *LocationParser::EmptyLocationDefinition::what() const throw()
{
	return ("The location block does not contain any directives!\n");
}

const char *LocationParser::UnknownKeywordInLocationBlock::what() const throw()
{
	return ("There was an unknown keyword encountered inside a location block!\n");
}

const char *LocationParser::DuplicateIdentifier::what() const throw()
{
	return ("A keyword allowing only one definition has been defined twice inside a location block!\n");
}

const char *LocationParser::InvalidNumberOfArguments::what() const throw()
{
	return ("An invalid number of arguments has been provided for a keyword inside a location block!\n");
}

const char *LocationParser::AliasNotAllowedWithRoot::what() const throw()
{
	return ("Either the root or alias keyword can be defined inside a location block,not both!\n");
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
