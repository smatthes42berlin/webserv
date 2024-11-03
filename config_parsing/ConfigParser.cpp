/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:41:28 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/03 18:24:50 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "external.hpp"

ConfigParser::ConfigParser(std::string file_path)
	: _file_path(file_path)
{
	return ;
}

ConfigParser::ConfigParser(const ConfigParser &other)
{
	(void)other;
	return ;
}

ConfigParser &ConfigParser::operator=(const ConfigParser &other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

ConfigParser::~ConfigParser(void)
{
	return ;
}

void ConfigParser::parse_config()
{
	this->read_whole_file();
	this->trim_each_line();
	this->remove_empty_lines();
	this->remove_comments();
	this->check_for_invalid_key_words();
	this->lines_to_one_big_string();
	this->ensure_only_one_consecutive_ws();
	this->isolate_server_block_strings();
	this->parse_server_blocks();
}

void ConfigParser::ensure_only_one_consecutive_ws()
{
	this->_file_processed_one_string = util::ensure_only_one_consecutive_ws(this->_file_processed_one_string);
}
void ConfigParser::parse_server_blocks()
{
	for (std::vector<std::string>::const_iterator it = this->_server_block_strings.begin(); it != this->_server_block_strings.end(); ++it)
	{
		ServerParser parser(*it);
		parser.parse_server_block();
		this->_server_parser.push_back(parser);
	}
}

// void ConfigParser::parse_server_block(std::string server_block)
// {
// 	std::vector<std::string> location_blocks;
// 	this->isolate_location_block_strings(server_block, location_blocks);
// 	// extract loction blocks
// 	// extrace remaining properties
// }

void ConfigParser::lines_to_one_big_string()
{
	this->_file_processed_one_string = util::join_lines(this->_file_line_by_line);
}

void ConfigParser::isolate_server_block_strings()
{
	std::string remaining_config = this->_file_processed_one_string;
	while (remaining_config.length() > 0)
	{
		remaining_config = this->isolate_server_block(remaining_config);
	}
}

std::string &ConfigParser::isolate_server_block(std::string &remaining_config)
{
	int	index_opening_bracket;
	int	index_closing_bracket;

	if (remaining_config.find("server") != 0)
		throw InvalidConfigKeyWord();
	index_opening_bracket = util::find_first_opening_bracket_only_ws(remaining_config,
																		std::string("server").length());
	if (index_opening_bracket < 0)
		throw OpeningBracketForServerBlockNotFound();
	index_closing_bracket = util::find_matching_closing_bracket(remaining_config,
																index_opening_bracket);
	if (index_closing_bracket < 0)
		throw ClosingBracketForServerBlockNotFound();
	std::string server_block = remaining_config.substr(index_opening_bracket
			+ 1, index_closing_bracket - index_opening_bracket - 1);
	remaining_config = remaining_config.substr(index_closing_bracket + 1,
												std::string::npos);
	remaining_config = util::trim(remaining_config);
	std::cout << server_block << std::endl;
	this->_server_block_strings.push_back(server_block);
	return (remaining_config);
}

void ConfigParser::check_for_invalid_key_words()
{
	bool	found;

	std::string first_word_of_line;
	for (std::vector<std::string>::iterator it_line = this->_file_line_by_line.begin(); it_line != this->_file_line_by_line.end(); ++it_line)
	{
		found = false;
		first_word_of_line = util::split(*it_line, ' ', 1, 0)[0];
		for (std::vector<std::string>::const_iterator it_keyword = ConfigParser::ALLOWED_CONFIG_KEYS.begin(); it_keyword != ConfigParser::ALLOWED_CONFIG_KEYS.end(); ++it_keyword)
		{
			if (first_word_of_line == *it_keyword)
			{
				found = true;
				break ;
			}
		}
		if (!found)
			throw InvalidConfigKeyWord();
	}
}

void ConfigParser::trim_each_line()
{
	for (std::vector<std::string>::iterator it = this->_file_line_by_line.begin(); it != this->_file_line_by_line.end(); ++it)
	{
		util::trim(*it);
	}
}

void ConfigParser::remove_empty_lines()
{
	std::vector<std::string>::iterator it = this->_file_line_by_line.begin();
	while (it != this->_file_line_by_line.end())
	{
		if (it->empty())
			it = this->_file_line_by_line.erase(it);
		else
			++it;
	}
}
void ConfigParser::remove_comments()
{
	std::vector<std::string>::iterator it = this->_file_line_by_line.begin();
	while (it != this->_file_line_by_line.end())
	{
		if ((*it)[0] == '#')
			it = this->_file_line_by_line.erase(it);
		else
			++it;
	}
}

void ConfigParser::read_whole_file()
{
	this->check_file_access();
	std::ifstream ifs(this->_file_path.c_str());
	if (!ifs.is_open())
		throw FileAccessError();
	std::string line;
	while (std::getline(ifs, line))
	{
		this->_file_line_by_line.push_back(line);
	}
	if (!ifs.eof() && (ifs.fail() || ifs.bad()))
		throw ReadFileStreamError();
	ifs.close();
}

void ConfigParser::check_file_access()
{
	struct stat	pathStat;

	if (access(this->_file_path.c_str(), R_OK) != 0)
		throw FileAccessError();
	if (stat(this->_file_path.c_str(), &pathStat) != 0)
		throw FileAccessError();
	if (S_ISDIR(pathStat.st_mode))
		throw FileAccessError();
	if (pathStat.st_size < 20)
		throw FileTooSmall();
}

void ConfigParser::print_file_line_by_line(void)
{
	for (std::vector<std::string>::const_iterator it = this->_file_line_by_line.begin(); it != this->_file_line_by_line.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void ConfigParser::print_server_blocks(void)
{
	for (std::vector<std::string>::const_iterator it = this->_server_block_strings.begin(); it != this->_server_block_strings.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

const char *ConfigParser::FileAccessError::what() const throw()
{
	return ("Could not access/open config-file! Possible reasons include:\n"
			"- file does not exist\n"
			"- unable to retrieve file information\n"
			"- no access permissions for file\n"
			"- file is a directory\n");
}

const char *ConfigParser::FileTooSmall::what() const throw()
{
	return ("Config-file is too small and thus can't be a valid config file!\n");
}

const char *ConfigParser::ReadFileStreamError::what() const throw()
{
	return ("File stream reading the config file encountered and error!\n");
}

const char *ConfigParser::InvalidConfigKeyWord::what() const throw()
{
	return ("An invalid keyword was encountered while parsing the config file!\n");
}

const char *ConfigParser::OpeningBracketForServerBlockNotFound::what() const throw()
{
	return ("An opening bracket after the server keyword couldn't be found!\n");
}

const char *ConfigParser::ClosingBracketForServerBlockNotFound::what() const throw()
{
	return ("The closing bracket for a server block couldn't be found!\n");
}

static std::vector<std::string> create_allowed_config_keys()
{
	std::vector<std::string> keys;
	keys.push_back("server");
	keys.push_back("location");
	keys.push_back("listen");
	keys.push_back("root");
	keys.push_back("index");
	keys.push_back("server_name");
	keys.push_back("error_page");
	keys.push_back("client_max_body_size");
	keys.push_back("methods");
	keys.push_back("autoindex");
	keys.push_back("alias");
	keys.push_back("{");
	keys.push_back("}");
	// keys.push_back("send_timeout");
	// keys.push_back("CGI");
	// keys.push_back("exec");
	// keys.push_back("php");
	return (keys);
}

const std::vector<std::string> ConfigParser::ALLOWED_CONFIG_KEYS = create_allowed_config_keys();
