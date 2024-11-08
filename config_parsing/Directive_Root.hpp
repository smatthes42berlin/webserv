/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Root.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:42:31 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/08 18:40:29 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive.hpp"
#include "external.hpp"
#include "util.hpp"

class Directive_Root : public Directive
{
  public:
	Directive_Root();
	Directive_Root(const Directive_Root &other);
	Directive_Root &operator=(const Directive_Root &other);
	virtual ~Directive_Root(void);

	void check_and_add(std::vector<std::string> key_val,
			std::vector<std::string> alias);

	class AliasNotAllowedWithRoot
	{
		public:
		AliasNotAllowedWithRoot(const Directive *dir);
		virtual const char *what() const throw();

		private:
		Directive const *directive;
	};

  private:
	std::vector<std::string> _config_defs;
};
