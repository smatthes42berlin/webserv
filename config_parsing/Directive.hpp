/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:43:17 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/08 17:48:07 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"

class Directive
{
  public:
	std::string get_directive_name(void);

  private:
	Directive();
	Directive(const Directive &other);
	Directive &operator=(const Directive &other);
	virtual ~Directive(void);

  protected:
	std::vector<std::string> > _key_val;
	std::string _directive_name;
	bool _many_args_allowed;
	bool _duplicate_definition_allowed;
	std::vector<std::string> _allowed_values;

	void check_for_invalid_num_args(void);
	void check_for_allowed_values(void);

	void set_key_val(std::vector<std::string> > new_key_val);

	template <std::vector<typename T>>
	void check_for_duplicate_identifier(<std::vector<T>> vector)
	{
		if (!this->_duplicate_definition_allowed)
			if (vector.size() > 0)
				throw DuplicateIdentifier();
	}

	class InvalidNumberOfArguments : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class DuplicateIdentifier : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class UnallowedArgumentForDirective : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
};
