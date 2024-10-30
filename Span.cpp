/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:52:06 by smatthes          #+#    #+#             */
/*   Updated: 2024/10/06 16:46:23 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include "external.hpp"

Span::Span(void)
{
	std::cout << "<default constructor> Span" << std::endl;
	return ;
}

Span::Span(unsigned int n)
	: _max_size(n), _content(std::vector<int>())
{
	std::cout << "<size constructor> Span" << std::endl;
	return ;
}

Span::Span(const Span &other)
	: _max_size(other._max_size), _content(other._content)
{
	std::cout << "<copy constructor> Span" << std::endl;
}

Span &Span::operator=(const Span &other)
{
	std::cout << "<copy assignment operator> Span" << std::endl;
	if (this != &other)
	{
		this->_max_size = other._max_size;
		this->_content = other._content;
	}
	return (*this);
}

Span::~Span(void)
{
	std::cout << "<destructor> Span" << std::endl;
	return ;
}

void Span::addNumber(int num)
{
	if (this->_content.size() >= this->_max_size)
		throw Span::AddNumberException();
	else
		this->_content.push_back(num);
}



unsigned int Span::longestSpan(void) const
{
	if (this->_content.size() < 2)
		throw Span::GetSpanForLessThanTwoNumbersException();

	int min = *std::min_element(this->_content.begin(), this->_content.end());
	int max = *std::max_element(this->_content.begin(), this->_content.end());

	return (max - min);
}

unsigned int Span::shortestSpan(void) const
{
	if (this->_content.size() < 2)
		throw Span::GetSpanForLessThanTwoNumbersException();

	std::vector<int> sortedContent = this->_content;
	std::sort(sortedContent.begin(), sortedContent.end());

	int shortest = *(sortedContent.begin() + 1) - *(sortedContent.begin());

	for (std::vector<int>::iterator it = sortedContent.begin(); it != sortedContent.end()
			- 1; it++)
	{
		int span = *(it + 1) - *it;
		if (span < shortest)
			shortest = span;
	}

	return (shortest);
}

const char *Span::AddNumberException::what() const throw()
{
	return ("Cannot add number: span is full.");
}

const char *Span::AddNumbersException::what() const throw()
{
	return ("Cannot add numbers: span size is too small.");
}

const char *Span::GetSpanForLessThanTwoNumbersException::what() const throw()
{
	return ("Cannot calculate shortest or longest Span: Span contains less than 2 numbers!");
}

void	print_int(int i)
{
	std::cout << i << " ";
}

void Span::print(void) const
{
	if (this->_content.size() == 0)
	{
		std::cout << ">>Empty Span<<";
	}
	else
		std::for_each(this->_content.begin(), this->_content.end(), print_int);
	std::cout << std::endl;
}
