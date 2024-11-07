path_to_nginx_config=/home/smatthes/42cursus/projects42/webserv/config_parsing/nginx.conf


# ~/nginx/sbin/nginx -s stop
# ~/nginx/sbin/nginx -t -c $path_to_nginx_config
~/nginx/sbin/nginx -c $path_to_nginx_config

~/nginx/sbin/nginx -s stop


exit



