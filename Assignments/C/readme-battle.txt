File: cattleships.c

My goal for this extension was to create a simplified version of the game Battleships, where you play against the computer. Each ship is of size 1 and the board is only 5x5, so that the game goes by quickly. To play, compile the code and execute "./battleships" and follow the instructions. The objective is to shoot all the computer's ships before it shoots your's. The player can see their own ships but not the computer's ships.

Initially, I wanted to create an "AI" that had a 50% chance of getting a hit, but that became a little complicated because I generate each player's board randomly. As there is no real pattern to the player's ship placement, it was difficult to program a method of finding a ship based on whether the last shot was a hit or miss, so the computer randomly selects points on the grid. 

I was hoping to build it into a proper game of battleships, allowing the player to set up their ships as desired, but I got stuck on various aspects of this program so I couldn't make it work in the time I had left. What I found most difficult was making sure that a move that had already been played could not be replayed, for both the player and the computer.

Known bugs:
- The player gets prompted for the coordinates twice. This bug appeared after I changed the way the boards were displayed, but I have not been able to get rid of it.
- Occasionally the program dumps out into a segmentation fault, which happens because the computer's random point has already been hit/missed before, but I haven't noticed the bug pop-up recently so I think it may be rectified.