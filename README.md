# doublet-solver
A program that solves doublet puzzles of length 5 using a Graph and DoubletSolver class.

A doublet puzzle transforms one word to another word by changing one letter at a time.

Example:
flour floor flood blood brood broad bread

## Notes:
- Doublet solver only works for words of length 5

- The graph is implemented using an adjacency list. Edges will connect 2 words differing
  at exactly one position (4 characters in common). The puzzle is solved by finding the
  shortest path between the start word and end word. This is achieved through
  breadth-first traversal.
  
- Dictionary created from knuth.txt

- No possible path will output “None”  
	   
## Output:
![alt text](https://user-images.githubusercontent.com/34634457/34194519-ed0eda8e-e50d-11e7-8026-9ec3ed83c929.png)
