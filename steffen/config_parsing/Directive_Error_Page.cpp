/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Error_Page.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:48:28 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/15 17:45:00 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directive_Error_Page.hpp"
#include "external.hpp"

Directive_Error_Page::Directive_Error_Page()
{
	this->_directive_name = "error_page";
	this->_duplicate_definition_allowed = true;
	this->_many_args_allowed = true;
	return ;
}

Directive_Error_Page::Directive_Error_Page(const Directive_Error_Page &other)
	: Directive()
{
	this->_error_pages = other._error_pages;
	return ;
}

Directive_Error_Page &Directive_Error_Page::operator=(const Directive_Error_Page &other)
{
	if (this != &other)
	{
		this->_error_pages = other._error_pages;
	}
	return (*this);
}

Directive_Error_Page::~Directive_Error_Page(void)
{
	return ;
}

void Directive_Error_Page::check_and_add(std::vector<std::string> key_val)
{
	this->set_key_val(key_val);
	if (key_val.size() < 3)
		throw InvalidNumberOfArguments(this->get_directive_name());
	if (!this->check_error_codes())
		throw InvalidErrorCodeFormat(this->get_directive_name());
	for (std::vector<std::string>::const_iterator it = key_val.begin()
			+ 1; it != key_val.end() - 1; ++it)
	{
		this->_error_pages[*it].push_back(key_val.back());
	}
}

bool Directive_Error_Page::check_error_codes()
{
	int		num;
	bool	valid;

	valid = true;
	std::vector<std::string>::iterator it_key_val;
	for (it_key_val = this->_key_val.begin() + 1; it_key_val != this->_key_val.end()
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

std::map<std::string,
			std::vector<std::string> > &
Directive_Error_Page::get_error_pages(void)
{
	return (this->_error_pages);
}

Directive_Error_Page::InvalidErrorCodeFormat::InvalidErrorCodeFormat(std::string directive_name)
	: _directive_name(directive_name)
{
}

Directive_Error_Page::InvalidErrorCodeFormat::~InvalidErrorCodeFormat() throw()
{
}

const char *Directive_Error_Page::InvalidErrorCodeFormat::what() const throw()
{
	this->_msg = "directive: ";
	this->_msg += this->_directive_name;
	this->_msg += "\n";
	this->_msg
		+= "The provided error codes for the error_page keyword must be only numbers between 300 and 599!";
	return (this->_msg.c_str());
}
