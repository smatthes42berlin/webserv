/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:43:17 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/08 18:45:15 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"

class Directive
{
  public:
	std::string get_directive_name(void) const;

  protected:
	Directive();
	Directive(const Directive &other);
	Directive &operator=(const Directive &other);
	virtual ~Directive(void);

	std::vector<std::string> _key_val;
	std::string _directive_name;
	bool _many_args_allowed;
	bool _duplicate_definition_allowed;
	std::vector<std::string> _allowed_values;

	void check_for_invalid_num_args(void);
	void check_for_allowed_values(void);

	void set_key_val(std::vector<std::string> new_key_val);

	template <typename T>
	void check_for_duplicate_identifier(const std::vector<T> &vector)
	{
		if (!this->_duplicate_definition_allowed)
		{
			if (vector.size() > 0)
				throw DuplicateIdentifier(this);
		}
	}

	class InvalidNumberOfArguments
	{
		public:
		InvalidNumberOfArguments(const Directive *dir);
		virtual const char *what() const throw();

		private:
		Directive const *directive;
	};

	class DuplicateIdentifier
	{
		public:
		DuplicateIdentifier(const Directive *dir);
		virtual const char *what() const throw();

		private:
		Directive const *directive;
	};

	class UnallowedArgumentForDirective
	{
		public:
		UnallowedArgumentForDirective(const Directive *dir);
		virtual const char *what() const throw();

		private:
		Directive const *directive;
	};
};
