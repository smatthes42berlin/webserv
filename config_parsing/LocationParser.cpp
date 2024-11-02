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

LocationParser::LocationParser(std::string location_block_str) : _location_block_str(location_block_str)
{
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

void	LocationParser::set_location_block_str(std::string location_block_str)
{
	this->_location_block_str = location_block_str;
}

void	LocationParser::set_location(std::string location)
{
	this->_location = location;
}
