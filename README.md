# Cub3D_RA

make &&
valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all ./cub3D map.cub

make bonus &&
valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all ./cub3D mapSprite.cub