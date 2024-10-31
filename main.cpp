/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:01:18 by smatthes          #+#    #+#             */
/*   Updated: 2024/10/31 12:47:28 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external.hpp"

int	main(void)
{
	int socket_fd;
	struct sockaddr_in sockaddr_in;
	const int enable = 1;

	// Create the socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		std::cerr << "Socket creation failed" << std::endl;
		return (-1);
	}

	// Set socket options
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable,
			sizeof(int)) < 0)
	{
		std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
	}

	// Bind the socket to a port
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(4000);
	sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socket_fd, (struct sockaddr *)&sockaddr_in,
			sizeof(sockaddr_in)) < 0)
	{
		std::cerr << "Bind failed" << std::endl;
		close(socket_fd);
		return (-1);
	}

	// Listen for incoming connections
	if (listen(socket_fd, 10) < 0)
	{
		std::cerr << "Listen failed" << std::endl;
		close(socket_fd);
		return (-1);
	}

	std::cout << "Server is listening on port 4000" << std::endl;

	while (true)
	{ // Main loop to keep the server running
		int client_fd;
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);

		// Accept a new client connection
		client_fd = accept(socket_fd, (struct sockaddr *)&client_addr,
				&client_addr_len);
		if (client_fd < 0)
		{
			std::cerr << "Accept failed" << std::endl;
			close(socket_fd);
			return (-1);
		}

		// Receive HTTP request from the client
		char buffer[4096];
		memset(buffer, 0, sizeof(buffer));
		ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes_received < 0)
		{
			std::cerr << "Error receiving data" << std::endl;
			close(client_fd);
			continue ; // Continue to next connection attempt
		}

		std::cout << "Received HTTP request:\n"
					<< buffer << std::endl;

		// Prepare a simple HTTP response
		const char *http_response =
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Connection: keep-alive\r\n"
			"\r\n"
			"<html>"
			"<head><title>My C++ HTTP Server</title></head>"
			"<body><h1>Hello from the C++ server!</h1></body>"
			"</html>";

		// Send the HTTP response
		ssize_t bytes_sent = send(client_fd, http_response,
				strlen(http_response), 0);
		if (bytes_sent < 0)
		{
			std::cerr << "Error sending response" << std::endl;
		}

		// Close the client connection
		close(client_fd);
	}

	// Close the server socket (not reachable in this example)
	close(socket_fd);
	return (0);
}
