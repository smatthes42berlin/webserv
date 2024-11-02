/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:01:18 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/02 15:41:37 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "external.hpp"

void	test_bad_configs(void);
void	test_bad_config(std::string file_path);

int	main(void)
{
	// test_bad_configs();
	std::string path = "config.conf";
	ConfigParser parser(path);
	try
	{
		parser.parse_config();
		parser.print_file_line_by_line();
		parser.print_server_blocks();
	}
	catch (std::exception &err)
	{
		std::cerr << err.what();
	}
	return (0);
}

void	test_bad_configs(void)
{
	std::string subfolder = "bad_configs/";
	std::string file_name;
	std::vector<std::string> test_config_names;
	test_config_names.push_back("directory.conf");
	test_config_names.push_back("no_access_rights.conf");
	test_config_names.push_back("empty.conf");
	test_config_names.push_back("too_small.conf");
	test_config_names.push_back("invalid_keyword_1.conf");
	test_config_names.push_back("invalid_keyword_2.conf");
	test_config_names.push_back("invalid_keyword_3.conf");
	test_config_names.push_back("invalid_keyword_4.conf");
	test_config_names.push_back("invalid_keyword_5.conf");
	test_config_names.push_back("no_opening_bracket_server_block_1.conf");
	test_config_names.push_back("no_opening_bracket_server_block_2.conf");
	test_config_names.push_back("no_opening_bracket_server_block_3.conf");
	test_config_names.push_back("no_closing_bracket_server_block_1.conf");
	test_config_names.push_back("no_closing_bracket_server_block_2.conf");
	test_config_names.push_back("no_closing_bracket_server_block_3.conf");
	test_config_names.push_back("invalid_keyword_after_first_server_block.conf");
	for (std::vector<std::string>::const_iterator it = test_config_names.begin(); it != test_config_names.end(); ++it)
	{
		test_bad_config(subfolder + *it);
	}
	std::cout << std::endl << std::endl;
	std::cout << std::endl << std::endl;
}

void	test_bad_config(std::string file_path)
{
	ConfigParser parser(file_path);
	try
	{
		parser.parse_config();
		std::cout << "BAD ERROR NOT FOUND" << std::endl;
		std::cout << "File: " << file_path << std::endl;
		std::cout << std::endl << std::endl;
	}
	catch (std::exception &err)
	{
		std::cerr << "OK" << std::endl;
		std::cerr << err.what();
		std::cout << std::endl << std::endl;
	}
}
