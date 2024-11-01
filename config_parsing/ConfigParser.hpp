/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:41:35 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/01 19:51:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"

class ConfigParser
{
  public:
	ConfigParser(std::string file_path);
	ConfigParser(const ConfigParser &other);
	ConfigParser &operator=(const ConfigParser &other);
	virtual ~ConfigParser(void);

	void parse_config();
	void read_whole_file();
	void check_file_access();
	void print_file_line_by_line();
	void remove_empty_lines();
	void remove_comments();
	void trim_each_line();
	void check_for_invalid_key_words();
	void isolate_server_block_strings();

	class FileAccessError : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class FileTooSmall : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class ReadFileStreamError : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
	
	class InvalidConfigKeyWord : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	// separate server blocks
	// bracket not closed
	// other keyword than server
	// ignore comments
	// drop comments at first
	// open file
	// read whole file

	// find server {} blocks
	// remove empty lines
	static const std::vector<std::string> ALLOWED_CONFIG_KEYS;

  private:
	std::string _file_path;
	std::vector<std::string> _file_line_by_line;
	std::vector<std::string> _server_block_strings;
};
