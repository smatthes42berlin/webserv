/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:01:18 by smatthes          #+#    #+#             */
/*   Updated: 2024/11/08 18:54:19 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "external.hpp"

void	test_bad_configs(void);
void	normal(void);
void	test_bad_config(std::string file_path);

int	main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;
	// if (argc <= 1)
	// 	normal();
	// else
	test_bad_configs();
	return (0);
}

void	normal(void)
{
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
}

void	test_bad_configs(void)
{
	std::string subfolder = "bad_configs/";
	std::string file_name;
	std::vector<std::string> test_config_names;
	// test_config_names.push_back("directory.conf");
	// test_config_names.push_back("no_access_rights.conf");
	// test_config_names.push_back("empty.conf");
	// test_config_names.push_back("too_small.conf");
	// test_config_names.push_back("invalid_keyword_1.conf");
	// test_config_names.push_back("invalid_keyword_2.conf");
	// test_config_names.push_back("invalid_keyword_3.conf");
	// test_config_names.push_back("invalid_keyword_4.conf");
	// test_config_names.push_back("invalid_keyword_5.conf");
	// test_config_names.push_back("no_opening_bracket_server_block_1.conf");
	// test_config_names.push_back("no_opening_bracket_server_block_2.conf");
	// test_config_names.push_back("no_opening_bracket_server_block_3.conf");
	// test_config_names.push_back("no_closing_bracket_server_block_1.conf");
	// test_config_names.push_back("no_closing_bracket_server_block_2.conf");
	// test_config_names.push_back("no_closing_bracket_server_block_3.conf");
	// test_config_names.push_back("invalid_keyword_after_first_server_block.conf");
	// test_config_names.push_back("bad_location_definition_1.conf");
	// test_config_names.push_back("bad_location_definition_2.conf");
	// test_config_names.push_back("bad_location_definition_3.conf");
	// test_config_names.push_back("bad_location_definition_4.conf");
	// test_config_names.push_back("bad_location_definition_5.conf");
	// test_config_names.push_back("bad_location_definition_6.conf");
	// test_config_names.push_back("invalid_keyword_inside_location_block_1.conf");
	// test_config_names.push_back("invalid_keyword_inside_location_block_2.conf");
	// test_config_names.push_back("invalid_keyword_inside_location_block_3.conf");
	test_config_names.push_back("location_block_root_1.conf");
	test_config_names.push_back("location_block_root_2.conf");
	test_config_names.push_back("location_block_root_3.conf");
	test_config_names.push_back("location_block_root_4.conf");
	// test_config_names.push_back("location_block_index_1.conf");
	// test_config_names.push_back("location_block_alias_1.conf");
	// test_config_names.push_back("location_block_alias_2.conf");
	// test_config_names.push_back("location_block_alias_3.conf");
	// test_config_names.push_back("location_block_alias_4.conf");
	// test_config_names.push_back("location_block_error_page_1.conf");
	// test_config_names.push_back("location_block_error_page_2.conf");
	// test_config_names.push_back("location_block_error_page_3.conf");
	// test_config_names.push_back("location_block_error_page_4.conf");
	// test_config_names.push_back("location_block_error_page_5.conf");
	// test_config_names.push_back("location_block_client_body_size_1.conf");
	// test_config_names.push_back("location_block_client_body_size_2.conf");
	// test_config_names.push_back("location_block_client_body_size_3.conf");
	// test_config_names.push_back("location_block_client_body_size_4.conf");
	// test_config_names.push_back("location_block_client_body_size_5.conf");
	// test_config_names.push_back("location_block_client_body_size_6.conf");
	// test_config_names.push_back("location_block_client_body_size_7.conf");
	// test_config_names.push_back("location_block_client_body_size_8.conf");
	// test_config_names.push_back("location_block_client_body_size_9.conf");
	// test_config_names.push_back("location_block_client_body_size_10.conf");
	// test_config_names.push_back("location_block_client_body_size_11.conf");
	// test_config_names.push_back("location_block_client_body_size_12.conf");
	// test_config_names.push_back("location_block_client_body_size_13.conf");
	// test_config_names.push_back("location_block_client_body_size_14.conf");
	// test_config_names.push_back("location_block_client_body_size_15.conf");
	// test_config_names.push_back("location_block_client_body_size_16.conf");
	// test_config_names.push_back("location_block_client_body_size_17.conf");
	// test_config_names.push_back("location_block_allowed_methods_1.conf");
	// test_config_names.push_back("location_block_allowed_methods_2.conf");
	// test_config_names.push_back("location_block_allowed_methods_3.conf");
	// test_config_names.push_back("location_block_allowed_methods_4.conf");
	// test_config_names.push_back("location_block_allowed_methods_5.conf");
	// test_config_names.push_back("location_block_allowed_methods_6.conf");
	// test_config_names.push_back("location_block_allowed_methods_7.conf");
	// test_config_names.push_back("location_block_allowed_methods_8.conf");
	// test_config_names.push_back("location_block_allowed_methods_9.conf");
	// test_config_names.push_back("location_block_autoindex_1.conf");
	// test_config_names.push_back("location_block_autoindex_2.conf");
	// test_config_names.push_back("location_block_autoindex_3.conf");
	// test_config_names.push_back("location_block_autoindex_4.conf");
	// test_config_names.push_back("location_block_autoindex_5.conf");
	// test_config_names.push_back("location_block_autoindex_6.conf");
	// test_config_names.push_back("location_block_autoindex_7.conf");
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
