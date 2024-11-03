/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:41:35 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/03 09:28:32 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "external.hpp"
#include "util.hpp"
#include "ServerParser.hpp"

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
	void remove_empty_lines();
	void remove_comments();
	void trim_each_line();
	void check_for_invalid_key_words();
	void lines_to_one_big_string();
	void ensure_only_one_consecutive_ws();
	void isolate_server_block_strings();
	std::string &isolate_server_block(std::string &remaining_config);
	void parse_server_blocks();
	// void parse_server_block(std::string server_block);
	void isolate_location_block_strings(std::string &server_block,
		std::vector<std::string> &location_blocks);

	void print_file_line_by_line();
	void print_server_blocks();

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

	class OpeningBracketForServerBlockNotFound : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class ClosingBracketForServerBlockNotFound : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	static const std::vector<std::string> ALLOWED_CONFIG_KEYS;

  private:
	std::string _file_path;
	std::string _file_processed_one_string;
	std::vector<std::string> _file_line_by_line;
	std::vector<std::string> _server_block_strings;
	std::vector<ServerParser> _server_parser;
};
