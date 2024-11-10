/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Root.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:42:31 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/10 18:29:16 by smatthes         ###   ########.fr       */
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
			std::vector<std::string> &alias);

	std::vector<std::string> &get_config_defs(void);


  private:
	std::vector<std::string> _config_defs;
};
