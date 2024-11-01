/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:22:33 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/01 20:11:06 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external.hpp"

namespace util
{
std::string &ltrim(std::string &str)
{
	std::string::iterator it = str.begin();
	while (it != str.end() && std::isspace(*it))
	{
		it++;
	}
	str.erase(str.begin(), it);
	return (str);
}

std::string &rtrim(std::string &str)
{
	std::string::reverse_iterator rit = str.rbegin();
	while (rit != str.rend() && std::isspace(*rit))
	{
		++rit;
	}
	str.erase(rit.base(), str.end());
	return (str);
}

std::string &trim(std::string &str)
{
	return (ltrim(rtrim(str)));
}
std::vector<std::string> split(const std::string &str, char delimiter,
		size_t maxTokens = std::string::npos)
{
	size_t	tokenCount;

	std::vector<std::string> tokens;
	std::string token;
	tokenCount = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == delimiter)
		{
			if (!token.empty())
			{
				tokens.push_back(trim(token));
				token.clear();
				tokenCount++;
			}
			if (maxTokens != std::string::npos && tokenCount >= maxTokens)
				break ;
		}
		else
		{
			token += str[i];
		}
	}
	if (!token.empty() && (maxTokens == std::string::npos
			|| tokenCount < maxTokens))
		tokens.push_back(trim(token));
	return (tokens);
}
} // namespace util