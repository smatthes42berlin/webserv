/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Alias.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes  <smatthes@student.42berlin>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:11:17 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/11 14:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive.hpp"
#include "external.hpp"
#include "util.hpp"

class Directive_Alias : public Directive
{
  public:
	Directive_Alias();
	Directive_Alias(const Directive_Alias &other);
	Directive_Alias &operator=(const Directive_Alias &other);
	virtual ~Directive_Alias(void);

	void check_and_add(std::vector<std::string> key_val,
			std::vector<std::string> &root);

	std::vector<std::string> &get_config_defs(void);

  private:
	std::vector<std::string> _config_defs;
};
