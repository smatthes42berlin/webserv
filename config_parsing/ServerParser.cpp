/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:47:54 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/02 16:02:35 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"
#include "external.hpp"

ServerParser::ServerParser(std::string server_str) : _server_str(server_str)
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
	this->parse_location_strings();
	// extract location blocks and parse seperately
	// parse rest and identify keywords
	// parse_server_blocks
	// split by ;
	// isolate keywords
	// isolate locations
	// check for double location definitions
}

void ServerParser::parse_location_strings(void)
{
	int	num_location_blocks;

	num_location_blocks = 0;
	std::string remaining_server_block = this->_server_str;
	this->_server_str = "";
	while (remaining_server_block.length() > 0)
	{
		if (this->extract_location_block(remaining_server_block) < 0)
		{
			if (num_location_blocks == 0)
				this->_keywords_str = this->_server_str;
			break ;
		};
		num_location_blocks++;
	}
}

int ServerParser::extract_location_block(std::string remaining_server_block)
{
	int				index_start_location_block;
	int				index_opening_bracket_location_block;
	LocationParser	location_parser;

	// find location
	// get actual location
	// get block from opening to closing bracket
	// copy stuff over
	index_start_location_block = remaining_server_block.find("location");
	if (index_start_location_block < 0)
		return (-1);
	location_parser.set_location(this->get_location(remaining_server_block,
			index_start_location_block, index_opening_bracket_location_block));
	// this->check_opening_closing_brackets();
	return (1);
}

std::string ServerParser::get_location(std::string remaining_server_block,
	int index_start_location_block, int &index_opening_bracket_location_block)
{
	for (std::string::const_iterator it = remaining_server_block.begin() + ; it != input.end(); ++it)
	{
		if (std::isspace(*it))
		{
			if (!inWhitespace)
			{
				result += ' ';
				inWhitespace = true;
			}
		}
		else
		{
			result += *it;
			inWhitespace = false;
		}
	}
	return (result);
	// std::vector<std::string> loc_split = util::split(remaining_server_block,
			' ', 3);
	// if(util::get_last_char(loc_split[1]) == '{')
	// {
	// 	if (loc_split[1] == "{")
	// 		throw IncorrectDefinitionOfLocationBlock();
	// }
	// else
	// {
	// 	if(loc_split[2][0] != '{')
	// 		throw OpeningBracketForLocationBlockNotFound();
	// }
	// if (util::get_last_char(loc_split[1]) != '{' && loc_split[2][0] != '{')
	// 	throw
	// return ("");
	// location   / {
	// location   /{
	// location   /{{{{
	// location   /    {
	// location /   {
	// location {
}

// void ServerParser::check_opening_closing_brackets()
// {
// 	int	index_opening_bracket_1;
// 	int	index_opening_bracket_2;
// 	int	index_closing_bracket_1;

// 	index_opening_bracket_1 = remaining_server_block.find("{", index_location);
// 	if (index_opening_bracket_1 < 0)
// 		throw OpeningBracketForLocationBlockNotFound();
// 	index_closing_bracket_1 = remaining_server_block.find("}",
// 			index_opening_bracket_1);
// 	if (index_closing_bracket_1 < 0)
// 		throw ClosingBracketForLocationBlockNotFound();
// 	index_opening_bracket_2 = remaining_server_block.find("{",
// 			index_opening_bracket_1);
// 	if (index_opening_bracket_2 > 0
// 		&& index_opening_bracket_2 < index_closing_bracket_1)
// 		throw NestingWithinLocationBlockNotSupported();
// }

const char *ServerParser::OpeningBracketForLocationBlockNotFound::what() const throw()
{
	return ("An opening bracket after the location keyword couldn't be found!\n");
}

const char *ServerParser::ClosingBracketForLocationBlockNotFound::what() const throw()
{
	return ("The closing bracket for a location block couldn't be found!\n");
}

const char *ServerParser::NestingWithinLocationBlockNotSupported::what() const throw()
{
	return ("Nesting within a location block is not supported!\n");
}

const char *ServerParser::IncorrectDefinitionOfLocationBlock::what() const throw()
{
	return ("Opening Bracket was not found after the first argument within location block!\n");
}
