/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:54 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/03 17:42:23 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"
#include "external.hpp"

ServerParser::ServerParser(std::string server_str)
	: _server_str(server_str)
{
	return ;
}

ServerParser::ServerParser(const ServerParser &other)
{
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

void ServerParser::parse_server_block(void)
{
	this->handle_location_strings();
	// extract location blocks and parse seperately
	// parse rest and identify keywords
	// parse_server_blocks
	// split by ;
	// isolate keywords
	// isolate locations
	// check for double location definitions
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
	location_parser.print();
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
