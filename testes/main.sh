clang -Wall -Wextra -Werror -g3 -fsanitize=address -D BUFFER_SIZE=$1 main.c ../get_next_line.c -o main -L../libft/ -lft
# clang -Wall -Wextra -Werror -D BUFFER_SIZE=$1 main.c ../get_next_line.c -o main -L../libft/ -lft
