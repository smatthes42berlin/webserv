/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:07 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/08 18:50:35 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directive.hpp"
#include "external.hpp"

Directive::Directive()
	: _directive_name("default"),
		_many_args_allowed(true),
		_duplicate_definition_allowed(true)
{
	return ;
}

Directive::Directive(const Directive &other)
{
	this->_key_val = other._key_val;
	this->_directive_name = other._directive_name;
	this->_many_args_allowed = other._many_args_allowed;
	this->_duplicate_definition_allowed = other._duplicate_definition_allowed;
	this->_allowed_values = other._allowed_values;
	return ;
}

Directive &Directive::operator=(const Directive &other)
{
	if (this != &other)
	{
		this->_key_val = other._key_val;
		this->_directive_name = other._directive_name;
		this->_many_args_allowed = other._many_args_allowed;
		this->_duplicate_definition_allowed = other._duplicate_definition_allowed;
		this->_allowed_values = other._allowed_values;
	}
	return (*this);
}

Directive::~Directive(void)
{
	return ;
}

void Directive::check_for_invalid_num_args(void)
{
	if (this->_key_val.size() < 2)
		throw InvalidNumberOfArguments(this);
	if (!this->_many_args_allowed)
		if (this->_key_val.size() != 2)
			throw InvalidNumberOfArguments(this);
}

std::string Directive::get_directive_name(void) const
{
	return (this->_directive_name);
}

void Directive::set_key_val(std::vector<std::string> new_key_val)
{
	this->_key_val = new_key_val;
}

void Directive::check_for_allowed_values(void)
{
	if (this->_allowed_values.size() > 0)
	{
		for (std::vector<std::string>::iterator it = this->_key_val.begin()
				+ 1; it != this->_key_val.end(); ++it)
		{
			if (std::find(this->_allowed_values.begin(),
							this->_allowed_values.end(),
							*it) == this->_allowed_values.end())
				throw UnallowedArgumentForDirective(this);
		}
	}
}

Directive::DuplicateIdentifier::DuplicateIdentifier(const Directive *dir)
	: directive(dir){}

const char *Directive::DuplicateIdentifier::what() const throw()
{
	std::string msg = "directive: ";
	msg += this->directive->get_directive_name().c_str();
	msg += "\n";
	msg += "Has been defined more than once inside a block!";
	return (msg.c_str());
}

Directive::InvalidNumberOfArguments::InvalidNumberOfArguments(const Directive *dir)
	: directive(dir){}

const char *Directive::InvalidNumberOfArguments::what() const throw()
{
	std::string msg = "directive: ";
	msg += this->directive->get_directive_name().c_str();
	msg += "\n";
	msg += "An invalid number of arguments has been provided!";
	return (msg.c_str());
}

Directive::UnallowedArgumentForDirective::UnallowedArgumentForDirective(const Directive *dir)
	: directive(dir){}

const char *Directive::UnallowedArgumentForDirective::what() const throw()
{
	std::string msg = "directive: ";
	msg += this->directive->get_directive_name().c_str();
	msg += "\n";
	msg += "An unallowed argument has been provided for the directive!";
	return (msg.c_str());
}
