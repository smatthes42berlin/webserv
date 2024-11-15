/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Allowed_Methods.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:21:44 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive.hpp"
#include "external.hpp"
#include "util.hpp"

class Directive_Allowed_Methods : public Directive
{
  public:
	Directive_Allowed_Methods();
	Directive_Allowed_Methods(const Directive_Allowed_Methods &other);
	Directive_Allowed_Methods &operator=(const Directive_Allowed_Methods &other);
	virtual ~Directive_Allowed_Methods(void);

	void check_and_add(std::vector<std::string> key_val);

	std::map<std::string, bool> &get_config_defs(void);


  private:
	std::map<std::string, bool> _config_defs;
};
