/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"
#include "external.hpp"

ServerParser::ServerParser(std::string server_str)
	: _server_str(server_str)
{
	this->assign_handlers();
	return ;
}

ServerParser::ServerParser(const ServerParser &other)
{
	this->assign_handlers();
	(void)other;
	return ;
}

ServerParser &ServerParser::operator=(const ServerParser &other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

ServerParser::~ServerParser(void)
{
	return ;
}

void ServerParser::assign_handlers()
{
	this->keyword_handlers["root"] = &ServerParser::handle_root;
	this->keyword_handlers["index"] = &ServerParser::handle_index;
	this->keyword_handlers["error_page"] = &ServerParser::handle_error_page;
	this->keyword_handlers["client_max_body_size"] = &ServerParser::handle_client_max_body_size;
	this->keyword_handlers["autoindex"] = &ServerParser::handle_autoindex;
	this->keyword_handlers["listen"] = &ServerParser::handle_listen;
	this->keyword_handlers["server_name"] = &ServerParser::handle_server_name;
}

void ServerParser::parse_server_block(void)
{
	this->handle_location_strings();
	this->handle_server_directive_str();
}

void ServerParser::handle_location_strings(void)
{
	std::string remaining_server_block = this->_server_str;
	this->_server_str = "";
	while (remaining_server_block.length() > 0)
	{
		if (this->extract_location_block(remaining_server_block) < 0)
			break ;
	}
}

int ServerParser::extract_location_block(std::string &remaining_server_block)
{
	int	index_start_location_block;
	int	index_opening_bracket_location_block;
	int	index_closing_bracket_location_block;

	index_start_location_block = remaining_server_block.find("location");
	if (index_start_location_block < 0)
	{
		this->_keywords_str += remaining_server_block;
		return (-1);
	}
	std::string location = this->get_location(remaining_server_block,
												index_start_location_block,
												index_opening_bracket_location_block);
	index_closing_bracket_location_block = util::find_matching_closing_bracket_no_nesting(remaining_server_block,
																							index_opening_bracket_location_block);
	if (index_closing_bracket_location_block < 0)
		throw ClosingBracketForLocationBlockNotFound();
	this->parse_location_string(location, remaining_server_block,
			index_opening_bracket_location_block,
			index_closing_bracket_location_block);
	this->_keywords_str += remaining_server_block.substr(0,
															index_start_location_block);
	remaining_server_block = remaining_server_block.substr(index_closing_bracket_location_block
			+ 1);
	return (1);
}

void ServerParser::parse_location_string(std::string location,
											std::string remaining_server_block,
											int index_opening_bracket_location_block,
											int index_closing_bracket_location_block)
{
	LocationParser	location_parser;

	std::string location_block_str;
	location_parser.set_location(location);
	location_block_str = remaining_server_block.substr(index_opening_bracket_location_block
			+ 1, index_closing_bracket_location_block
			- index_opening_bracket_location_block - 1);
	location_parser.set_location_block_str(location_block_str);
	this->_location_parser.push_back(location_parser);
	location_parser.parse_location_block();
}

std::string ServerParser::get_location(std::string remaining_server_block,
										int index_start_location_block,
										int &index_opening_bracket_location_block)
{
	std::string location = "";
	std::vector<std::string> location_split = util::split(remaining_server_block,
															' ',
															3,
															index_start_location_block);
	if (location_split[1][0] == '{' || location_split[1][0] == '}')
		throw NoLocationDefinedInsideLocationBlock();
	this->get_location_string(location_split[1], location);
	index_opening_bracket_location_block = index_start_location_block
		+ std::string("location").length() + 1 + location.length();
	if (location.length() == location_split[1].length())
	{
		if (location_split[2][0] != '{')
			throw NoOpeningBracketInsideLocationBlock();
		index_opening_bracket_location_block += 1;
		return (location);
	}
	if (location_split[1][location.length()] != '{')
		throw NoOpeningBracketInsideLocationBlock();
	return (location);
}

void ServerParser::get_location_string(std::string src_str,
										std::string &res_location)
{
	for (std::string::iterator it = src_str.begin(); it != src_str.end(); ++it)
	{
		if (*it == '{' || *it == '}')
			break ;
		res_location += *it;
	}
}

void ServerParser::handle_server_directive_str(void)
{
	std::vector<std::string> key_value_strings;
	std::vector<std::string> key_value_vector;
	key_value_strings = util::split(this->_keywords_str, ';');
	std::vector<std::string>::iterator it_key_val;
	for (it_key_val = key_value_strings.begin(); it_key_val != key_value_strings.end(); it_key_val++)
	{
		key_value_vector = util::split(*it_key_val, ' ');
		std::map<std::string,
					void (ServerParser::*)(std::vector<std::string> &)>::iterator it = this->keyword_handlers.find(key_value_vector[0]);
		if (it != this->keyword_handlers.end())
		{
			(this->*(it->second))(key_value_vector);
		}
		else
			throw UnknownKeywordInServerBlock(key_value_vector[0]);
	}
}



void ServerParser::handle_index(std::vector<std::string> &key_val)
{
	this->_index_handler.check_and_add(key_val);
}
void ServerParser::handle_error_page(std::vector<std::string> &key_val)
{
	this->_error_page_handler.check_and_add(key_val);
}

void ServerParser::handle_client_max_body_size(std::vector<std::string> &key_val)
{
	this->_client_max_body_size_handler.check_and_add(key_val);
}

void ServerParser::handle_autoindex(std::vector<std::string> &key_val)
{
	this->_autoindex_handler.check_and_add(key_val);
}

void ServerParser::handle_root(std::vector<std::string> &key_val)
{
	std::vector<std::string> dummy;
	this->_root_handler.check_and_add(key_val, dummy);
}

void ServerParser::handle_listen(std::vector<std::string> &key_val)
{
	this->_listen_handler.check_and_add(key_val);
}

void ServerParser::handle_server_name(std::vector<std::string> &key_val)
{

	this->_server_name_handler.check_and_add(key_val);
}

ServerParser::UnknownKeywordInServerBlock::UnknownKeywordInServerBlock(std::string keyword_name)
	: _keyword_name(keyword_name)
{
}

ServerParser::UnknownKeywordInServerBlock::~UnknownKeywordInServerBlock() throw()
{
}

const char *ServerParser::UnknownKeywordInServerBlock::what() const throw()
{
	this->_msg = "keyword: ";
	this->_msg += this->_keyword_name;
	this->_msg += "\n";
	this->_msg
		+= "There was an unknown keyword encountered inside a server block!";
	return (this->_msg.c_str());
}

const char *ServerParser::ClosingBracketForLocationBlockNotFound::what() const throw()
{
	return ("The closing bracket for a location block couldn't be found or unsupported nesting inside the location block identified!\n");
}

const char *ServerParser::NoOpeningBracketInsideLocationBlock::what() const throw()
{
	return ("Opening Bracket was not found after the first argument within location block!\n");
}

const char *ServerParser::NoLocationDefinedInsideLocationBlock::what() const throw()
{
	return ("No location was given inside a location block opening bracket cam directly after location keyword!\n");
}
