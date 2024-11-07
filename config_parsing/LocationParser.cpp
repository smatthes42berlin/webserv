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

LocationParser::LocationParser() : _location_block_str(""), _location("")
{
	this->assign_handlers();
	return ;
}

LocationParser::LocationParser(std::string location_block_str) : _location_block_str(location_block_str),
	_location("")
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
	std::cout << "handle error_page" << std::endl;
	if (key_val.size() < 3)
		throw InvalidNumberOfArguments();
	if (!this->check_error_codes(key_val))
		throw InvalidErrorCodeFormat();
	for (std::vector<std::string>::const_iterator it = key_val.begin()
		+ 1; it != key_val.end() - 1; ++it)
	{
		this->_error_pages[*it].push_back(key_val.back());
	}
}

bool LocationParser::check_error_codes(std::vector<std::string> &key_val)
{
	int		num;
	bool	valid;

	valid = true;
	std::vector<std::string>::iterator it_key_val;
	for (it_key_val = key_val.begin() + 1; it_key_val != key_val.end()
		- 1; it_key_val++)
	{
		if (!util::is_digits_only(*it_key_val))
			valid = false;
		num = atoi((*it_key_val).c_str());
		if (num < 300 || num > 599)
			valid = false;
		if (!valid)
			break ;
	}
	return (valid);
}
void LocationParser::handle_client_max_body_size(std::vector<std::string> &key_val)
{
	uint	size_in_bytes;

	std::cout << "handle client_max_body_size" << std::endl;
	if (this->_client_max_body_size.size() > 0)
		throw DuplicateIdentifier();
	if (key_val.size() != 2)
		throw InvalidNumberOfArguments();
	if (!this->check_body_size_format(key_val[1], size_in_bytes))
		throw InvalidClientMaxBodySizeFormat();
	this->_client_max_body_size.push_back(size_in_bytes);
}

bool LocationParser::check_body_size_format(std::string size_str,
	uint &size_in_bytes)
{
	char	last_char;
	int		size_int;

	std::string num_str;
	last_char = size_str[size_str.size() - 1];
	if (isdigit(last_char))
	{
		num_str = size_str;
	}
	else
	{
		if (last_char != 'M' && last_char != 'm' && last_char != 'K'
			&& last_char != 'k' && last_char != 'G' && last_char != 'g')
			return (false);
		num_str = size_str.substr(0, size_str.length() - 1);
	}
	if (!util::is_digits_only(num_str))
		return (false);
	size_int = atoi(num_str.c_str());
	if(size_int == -1)
		return false;
	if (last_char == 'g' || last_char == 'G')
	{
		if (size_int > 2)
			return (false);
		size_in_bytes = size_int * 1024 * 1024 * 1024;
	}
	else if (last_char == 'm' || last_char == 'M')
	{
		if (size_int > 2048)
			return (false);
		size_in_bytes = size_int * 1024 * 1024;
	}
	else if (last_char == 'k' || last_char == 'K')
	{
		if (size_int > 2097152)
			return (false);
		size_in_bytes = size_int * 1024;
	}
	else
	{
		if (size_int == INT_MAX)
			return (false);
		size_in_bytes = size_int;
	}
	return (true);
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

const char *LocationParser::InvalidErrorCodeFormat::what() const throw()
{
	return ("The provided error codes for the error_page keyword must be only numbers between 300 and 599!\n");
}

const char *LocationParser::InvalidClientMaxBodySizeFormat::what() const throw()
{
	return ("The provided argument for client_max_body is in the wrong format or the maximum value of 2GB is exceded!\n");
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
