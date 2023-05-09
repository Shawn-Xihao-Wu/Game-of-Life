# Game-of-Life
### By Shawn Xihao Wu

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a classic cellular automaton simulation created by mathematician John Conway in 1970. The game consists of a grid of cells that can be in one of two states, either "alive" or "dead". The game proceeds in generations, with the state of each cell in the next generation being determined by a set of rules based on the states of its neighbors in the current generation.

In my implementation with C, I have used a sparse matrix using a hash table to cut down the runtime complexity from O(n^2) to O(n). Instead of representing the entire grid with a large array, I only store the coordinates of the "alive" cells in a hash table, which allows for more efficient memory usage and faster processing of each generation. I want to thank [Ibarasti](https://lbarasti.com/post/game_of_life/) for this method and you can click on his name to see more of his formulation.