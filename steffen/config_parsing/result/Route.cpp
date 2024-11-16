/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:39 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/16 18:54:35 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Route.hpp"
#include "external.hpp"

Route::Route()
	: _location(""),
		_root("./"),
		_alias_is_defined(false),
		_alias(""),
		_client_max_body_size(1024 * 1024),
		_autoindex(false)
{
	this->_allowed_methods["get"] = true;
	this->_allowed_methods["post"] = false;
	this->_allowed_methods["delete"] = false;
	this->_index.push_back("index.html");
	this->_error_pages["404"].push_back("404.html");
	return ;
}

Route::Route(const Route &other)
{
	this->_location = other.get_location();
	this->_root = other.get_root();
	this->_alias_is_defined = other.get_alias_is_defined();
	this->_alias = other.get_alias();
	this->_client_max_body_size = other.get_client_max_body_size();
	this->_autoindex = other.get_autoindex();
	this->_allowed_methods = other.get_allowed_methods();
	this->_index = other.get_index();
	this->_error_pages = other.get_error_pages();
	return ;
}

Route &Route::operator=(const Route &other)
{
	if (this != &other)
	{
		this->_location = other.get_location();
		this->_root = other.get_root();
		this->_alias_is_defined = other.get_alias_is_defined();
		this->_alias = other.get_alias();
		this->_client_max_body_size = other.get_client_max_body_size();
		this->_autoindex = other.get_autoindex();
		this->_allowed_methods = other.get_allowed_methods();
		this->_index = other.get_index();
		this->_error_pages = other.get_error_pages();
	}
	return (*this);
}

Route::~Route(void)
{
	return ;
}

void Route::set_location(std::string new_val)
{
	this->_location = new_val;
}

void Route::set_root(std::string new_val)
{
	this->_root = new_val;
}

void Route::set_alias_is_defined(bool new_val)
{
	this->_alias_is_defined = new_val;
}

void Route::set_alias(std::string new_val)
{
	this->set_alias_is_defined(true);
	this->_alias = new_val;
}

void Route::set_client_max_body_size(uint new_val)
{
	this->_client_max_body_size = new_val;
}

void Route::set_autoindex(bool new_val)
{
	this->_autoindex = new_val;
}

void Route::set_index(std::vector<std::string> new_val)
{
	this->_index = new_val;
}

void Route::set_error_pages(std::map<std::string,
										std::vector<std::string> > new_val)
{
	this->_error_pages = new_val;
}

void Route::set_allowed_methods(std::map<std::string, bool> new_val)
{
	this->_allowed_methods = new_val;
}

std::string Route::get_location() const
{
	return (this->_location);
}

std::string Route::get_root() const
{
	return (this->_root);
}

std::vector<std::string> Route::get_index() const
{
	return (this->_index);
}

std::map<std::string, std::vector<std::string> > Route::get_error_pages() const
{
	return (this->_error_pages);
}

std::vector<std::string> Route::get_error_page(std::string page) const
{
	std::map<std::string,
				std::vector<std::string> >::const_iterator it = this->_error_pages.find(page);
	if (it != this->_error_pages.end())
	{
		return (it->second);
	}
	std::vector<std::string> empty;
	return (empty);
}

uint Route::get_client_max_body_size() const
{
	return (this->_client_max_body_size);
}

bool Route::get_autoindex() const
{
	return (this->_autoindex);
}

bool Route::get_alias_is_defined() const
{
	return (this->_alias_is_defined);
}

std::string Route::get_alias() const
{
	return (this->_alias);
}

std::map<std::string, bool> Route::get_allowed_methods() const
{
	return (this->_allowed_methods);
}

bool Route::is_method_allowed(std::string method)
{
	std::map<std::string,
				bool>::iterator it = this->_allowed_methods.find(method);
	if (it != this->_allowed_methods.end())
	{
		if (it->second)
			return (true);
	}
	return (false);
}

std::ostream &operator<<(std::ostream &os, Route const &route)
{
	
	std::map<std::string, std::string> col_map = util::get_color_map();

	os << std::endl
		<< std::endl
		<< std::endl;
	os << "Route";
	os << std::endl;
	os << col_map["red"];
	os << "[string] ";
	os << col_map["green"];
	os << "location: ";
	os << col_map["reset"];
	os << route.get_location();
	os << std::endl;
	os << col_map["red"];
	os << "[string] ";
	os << col_map["green"];
	os << "root: ";
	os << col_map["reset"];
	os << route.get_root();
	os << std::endl;
	os << col_map["red"];
	os << "[bool] ";
	os << col_map["green"];
	os << "alias_is_defined: ";
	os << col_map["reset"];
	os << route.get_alias_is_defined();
	os << std::endl;
	os << col_map["red"];
	os << "[string] ";
	os << col_map["green"];
	os << "alias: ";
	os << col_map["reset"];
	os << route.get_alias();
	os << std::endl;
	os << col_map["red"];
	os << "[uint] ";
	os << col_map["green"];
	os << "client_max_body_size: ";
	os << col_map["reset"];
	os << route.get_client_max_body_size();
	os << std::endl;
	os << col_map["red"];
	os << "[bool] ";
	os << col_map["green"];
	os << "autoindex: ";
	os << col_map["reset"];
	os << route.get_autoindex();
	os << std::endl;
	os << col_map["red"];
	os << "[map<string, bool>] ";
	os << col_map["green"];
	os << "allowed_methods: ";
	os << col_map["reset"];
	os << std::endl;
	std::map<std::string, bool> allowed_methods = route.get_allowed_methods();
	for (std::map<std::string,
					bool>::iterator it = allowed_methods.begin();
			it != allowed_methods.end();
			++it)
	{
		os << it->first << ": " << it->second;
		os << std::endl;
	}
	os << std::endl;
	os << col_map["red"];
	os << "[vector<string>] ";
	os << col_map["green"];
	os << "index: ";
	os << col_map["reset"];
	std::vector<std::string> indexes = route.get_index();
	for (std::vector<std::string>::iterator vec_it = indexes.begin(); vec_it != indexes.end(); ++vec_it)
	{
		os << *vec_it << " ";
	}
	os << std::endl;
	os << col_map["red"];
	os << "[map<string, vector<string>>] ";
	os << col_map["green"];
	os << "error_pages: ";
	os << col_map["reset"];
	os << std::endl;
	std::map<std::string,
				std::vector<std::string> >
		error_pages = route.get_error_pages();
	for (std::map<std::string,
					std::vector<std::string> >::iterator it = error_pages.begin();
			it != error_pages.end();
			++it)
	{
		os << it->first << " ";
		const std::vector<std::string> &values = it->second;
		for (std::vector<std::string>::const_iterator vec_it = values.begin(); vec_it != values.end(); ++vec_it)
		{
			os << *vec_it << " ";
		}
		os << std::endl;
	}
	os << std::endl
		<< std::endl
		<< std::endl;
	return (os);
}
