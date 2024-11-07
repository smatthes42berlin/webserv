/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:22:33 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/07 15:34:10 by smatthes         ###   ########.fr       */
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
std::vector<std::string> split(const std::string &str, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == delimiter)
		{
			if (!token.empty())
			{
				tokens.push_back(trim(token));
				token.clear();
			}
		}
		else
			token += str[i];
	}
	if (!token.empty())
		tokens.push_back(trim(token));
	return (tokens);
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

std::vector<std::string> split(const std::string &str, char delimiter,
		size_t maxTokens = std::string::npos, size_t start_index = 0)
{
	size_t	tokenCount;

	std::vector<std::string> tokens;
	std::string token;
	tokenCount = 0;
	for (size_t i = start_index; i < str.size(); ++i)
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

std::string join_lines(const std::vector<std::string> &lines)
{
	return (std::accumulate(lines.begin(), lines.end(), std::string("")));
}

int	find_first_opening_bracket_only_ws(const std::string &str,
										size_t start_pos = 0)
{
	while (start_pos < str.length() && std::isspace(str[start_pos]))
		++start_pos;
	if (start_pos < str.length() && str[start_pos] == '{')
		return (start_pos);
	else
		return (-1);
}

int	find_matching_closing_bracket(const std::string &str, int openPos)
{
	int	counter;

	if (str[openPos] != '{')
		return (-1);
	counter = 1;
	for (size_t i = openPos + 1; i < str.size(); ++i)
	{
		if (str[i] == '{')
			++counter;
		else if (str[i] == '}')
		{
			--counter;
			if (counter == 0)
				return (i);
		}
	}
	return (-1);
}

int	find_matching_closing_bracket_no_nesting(const std::string &str,
												int openPos)
{
	if (str[openPos] != '{')
		return (-1);
	for (size_t i = openPos + 1; i < str.size(); ++i)
	{
		if (str[i] == '{')
			break ;
		if (str[i] == '}')
			return (i);
	}
	return (-1);
}

std::string ensure_only_one_consecutive_ws(const std::string &input)
{
	bool	inWhitespace;

	std::string result;
	inWhitespace = false;
	for (std::string::const_iterator it = input.begin(); it != input.end(); ++it)
	{
		if (std::isspace(*it))
		{
			if (!inWhitespace)
			{
				result += ' ';
				inWhitespace = true;
			}
		}
		else
		{
			result += *it;
			inWhitespace = false;
		}
	}
	return (result);
}

char	get_last_char(std::string &str)
{
	return (str[str.length()]);
}

bool is_digits_only(const std::string &str) {
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }
    return true;
}

} // namespace util
