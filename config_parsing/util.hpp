/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:22:33 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/02 15:51:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external.hpp"

namespace util
{
std::string &ltrim(std::string &str);
std::string &rtrim(std::string &str);
std::string &trim(std::string &str);
std::vector<std::string> split(const std::string &str, char delimiter,
	size_t maxTokens);
std::string join_lines(const std::vector<std::string> &lines);
int		find_first_opening_bracket_only_ws(const std::string &str,
			size_t start_pos);
int		find_matching_closing_bracket(const std::string &str, int openPos);
std::string ensure_only_one_consecutive_ws(const std::string &input);
char	get_last_char(std::string &str);

} // namespace util
