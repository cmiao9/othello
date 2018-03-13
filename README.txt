
~~~ Group member contributions: ~~~

Cathy - wrote player initialization and basic Player::DoMove

Rona - implemented timer in Player::DoMove

both - implemented minimax algorithm last week, worked on improved heuristic + increased depth (improving AI, this week)

~~~ AI improvements: ~~~

1. Improved heuristic: Added weights to corners and edges, seemed to work better earlier in the game, so added a max # tokens on the board for this to be applicable. Current weights are: +3 for corners, -3 for adjacent to corners, 0 for edges/edge adjacent, applicable use is with <20 tokens on the board (approximately the first third of the game, decided with trial and error).

2. Tried to implement iterative deepening recursively, ran into some trouble, instead decided to:

3. Increase depth from 2 (last week) to 3, then 4. Current code searches to depth 4 (with weighting heuristic, see part 1), and beats ConstantTimePlayer somewhat consistently ~60-70% of the time, and SimplePlayer ~90-100% of the time, but loses pretty consistently to BetterPlayer (~70-80% of the time) even though it searches to a further depth? Is there an error in the code?
