/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:51:56 by smatthes          #+#    #+#             */
/*   Updated: 2024/10/06 16:43:10 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"

class Span
{
  public:
	Span(unsigned int n);
	Span(const Span &other);
	Span &operator=(const Span &other);
	virtual ~Span(void);

	void addNumber(int num);

	template <typename InputIterator>
	void addNumbers(InputIterator begin, InputIterator end)
	{
		unsigned int newNumbersCount;

		newNumbersCount = std::distance(begin, end);
		if (_content.size() + newNumbersCount > _max_size)
			throw AddNumbersException();
		std::copy(begin, end, std::back_inserter(_content));
	}
	void print(void) const;
	unsigned int shortestSpan(void) const;
	unsigned int longestSpan(void) const;

	class GetSpanForLessThanTwoNumbersException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class AddNumberException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class AddNumbersException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

  private:
	unsigned int _max_size;
	std::vector<int> _content;

	Span(void);
};
