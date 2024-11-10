/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_Index.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:42:13 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/10 18:44:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Directive.hpp"
#include "external.hpp"
#include "util.hpp"

class Directive_Index : public Directive
{
  public:
	Directive_Index();
	Directive_Index(const Directive_Index &other);
	Directive_Index &operator=(const Directive_Index &other);
	virtual ~Directive_Index(void);

	void check_and_add(std::vector<std::string> key_val);

	std::vector<std::string> &get_config_defs(void);

  private:
	std::vector<std::string> _config_defs;
};
