/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Listen.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:50:18 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 17:24:18 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directive_Listen.hpp"
#include "external.hpp"

Directive_Listen::Directive_Listen()
{
	this->_directive_name = "listen";
	this->_duplicate_definition_allowed = true;
	this->_many_args_allowed = false;
	return ;
}

Directive_Listen::Directive_Listen(const Directive_Listen &other)
	: Directive()
{
	this->_config_defs = other._config_defs;
	return ;
}

Directive_Listen &Directive_Listen::operator=(const Directive_Listen &other)
{
	if (this != &other)
	{
		this->_config_defs = other._config_defs;
	}
	return (*this);
}

Directive_Listen::~Directive_Listen(void)
{
	return ;
}

void Directive_Listen::check_and_add(std::vector<std::string> key_val)
{
	this->set_key_val(key_val);
	this->check_for_invalid_num_args();
	this->check_for_duplicate_identifier(this->_config_defs);
	this->_config_defs.push_back(this->_key_val[1]);
	this->process_port_n_ip(this->_key_val[1]);
}

void Directive_Listen::process_port_n_ip(std::string port_n_ip)
{
	int	port;

	util::Address ip_n_port_struct;
	std::string port_str;
	std::string ip_str = "0.0.0.0";
	this->check_port_n_ip_basic_form(port_n_ip, port_str, ip_str);
	this->verify_port_str(port_str, port);
	this->verify_ip_str(ip_str);
	ip_n_port_struct.ip = ip_str;
	ip_n_port_struct.port = port;
	// check, port not already used alone
	// ip and port combination not already used
	this->_ips_n_ports.push_back(ip_n_port_struct);
}

void Directive_Listen::verify_port_str(std::string port_str, int &port)
{
	if (!util::is_digits_only(port_str))
		throw InvalidListenArgumentFormat(port_str);
	port = atoi(port_str.c_str());
	if (port < 0 || port > 65535)
		throw InvalidListenArgumentFormat(port_str);
}

void Directive_Listen::verify_ip_str(std::string &ip_str)
{
	int	dot_count;
	int	num;

	dot_count = std::count(ip_str.begin(), ip_str.end(), '.');
	if (dot_count != 3)
		throw InvalidListenArgumentFormat(ip_str);
	std::vector<std::string> ip_parts = util::split(ip_str, '.');
	if (ip_parts.size() != 4)
		throw InvalidListenArgumentFormat(ip_str);
	for (std::vector<std::string>::iterator it = ip_parts.begin(); it != ip_parts.end(); ++it)
	{
		if (!util::is_digits_only(*it))
			throw InvalidListenArgumentFormat(ip_str);
		num = atoi((*it).c_str());
		if (num < 0 || num > 255)
			throw InvalidListenArgumentFormat(ip_str);
	}
}

void Directive_Listen::check_port_n_ip_basic_form(std::string port_n_ip,
													std::string &port_str,
													std::string &ip_str)
{
	int	colon_count;

	colon_count = std::count(port_n_ip.begin(), port_n_ip.end(), ':');
	if (colon_count > 1)
		throw InvalidListenArgumentFormat(port_n_ip);
	if (colon_count == 0)
		port_str = port_n_ip;
	else
	{
		std::vector<std::string> ip_port_separated = util::split(port_n_ip,
																	':');
		if (ip_port_separated.size() < 2)
			throw InvalidListenArgumentFormat(port_n_ip);
		ip_str = ip_port_separated[0];
		port_str = ip_port_separated[1];
	}
}

std::vector<std::string> &Directive_Listen::get_config_defs(void)
{
	return (this->_config_defs);
}

Directive_Listen::InvalidListenArgumentFormat::InvalidListenArgumentFormat(std::string argument)
	: _argument(argument)
{
}

Directive_Listen::InvalidListenArgumentFormat::~InvalidListenArgumentFormat() throw()
{
}

const char *Directive_Listen::InvalidListenArgumentFormat::what() const throw()
{
	this->_msg = "argument: ";
	this->_msg += this->_argument;
	this->_msg += "\n";
	this->_msg
		+= "There was an invalid argument encountered inside a listen directive!\n";
	this->_msg += "Ports must be between 0 and 65535!\n";
	this->_msg += "IPs must be valid ipv4 addresses!\n ";
	return (this->_msg.c_str());
}