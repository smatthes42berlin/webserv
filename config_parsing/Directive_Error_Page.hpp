/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Error_Page.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:48:49 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/10 18:57:27 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive.hpp"
#include "external.hpp"
#include "util.hpp"

class Directive_Error_Page : public Directive
{
  public:
	Directive_Error_Page();
	Directive_Error_Page(const Directive_Error_Page &other);
	Directive_Error_Page &operator=(const Directive_Error_Page &other);
	virtual ~Directive_Error_Page(void);

	void check_and_add(std::vector<std::string> key_val);
	bool check_error_codes();


	std::map<std::string, std::vector<std::string> > &get__error_pages(void);


	class InvalidErrorCodeFormat : public std::exception
	{
		public:
		InvalidErrorCodeFormat(std::string directive_name);
		virtual ~InvalidErrorCodeFormat() throw();
		virtual const char *what() const throw();

		private:
		std::string _directive_name;
		mutable std::string _msg;
	};


  private:
	std::map<std::string, std::vector<std::string> > _error_pages;
};
