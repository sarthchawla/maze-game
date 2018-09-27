Let's consider a maze as a 2-D array of spaces, where between each space there is a wall or not. The start point of the maze will be the upper left and the finish point is the lower right. 

Notice that the maze has a width and height, and we index spaces in the maze with (w,h). The top left index is (0,0), and the bottom right index is (width-1,height-1). The maze will always start in the upper left and finish in the bottom right. We will describe two spaces as "reachable" if they are adjacent and do not have a wall between them.

Let's design this game with two stages and at each level we will be having back end board and front end board (as discussed in class). Also at frontend, user can make moves from keyboard with keys, A for backward, S for downward, D for forward and W for upward directions respectively:

Level 1:

Solve backend for reference path availability. The process of solving a maze with queue is a lot like "hunting" out the end point from the start point. To do that, we must ensure that we test all possible paths. The queue will allow us to track which spaces we should visit next.

The basic routine works as follows:

    Initialize a queue with the start index (0,0)
    Loop Until: queue is empty
        Dequeue current index and mark it as visited
        If current index is the finish point
            Break! We've found the end
        Enqueue all indexes for reachable and unvisited neighbors of the current index
        Continue the loop.

Looking over this routine, imagine the queue, full of spaces. Each time you dequeue space you are searching around for more spaces to search out next. If you find any, you add them to the queue to eventually be analyzed later.

Because of the FIFO nature of a queue, the resulting search pattern is a lot like a water rushing out from the start space, through all possible path in the maze until the end is reached.

Solve front end by marking * on every move. Make sure if any movement is made on a wall or boundary in between, then Life is reduced by 1 from a total of 3 lives; user will restart from 5 positions before death and score will be reset to 0.

On every movement, score is increased by one. 

If a user moves at position that is not marked at backend, even then the life is reduced by 1 with same policy as discussed earlier.

Once user reaches the destination, then user switches to Level 2.

 

Level 2:

Solve backend for reference path availability. 

The process of drawing a maze is very similar to solving a maze, but instead the goal is to explore all spaces, removing walls along the way, such that there exist a path between any two spaces through a series of reachable spaces. That also means that there will exist a path from the from the start to the end.

The algorithm to ensure all reachability will work as follows:

    Initialize a stack with the start index (0,0)
    Loop Until: stack is empty
        pop current index off the stack and mark it as visited
        If current index has any unvisited neighbors
            Choose a random unvisited neighbor index
            Remove the wall between the chosen neighbor index and the current index
            push the current index on the stack
            push the randomly choose neighbor index on the stack
        Continue the loop.

Looking over this routine, you should be able to invision how this procedure will dive through the maze randomly, like a snake, until the snake reaches a dead end (a space without any unlisted neighbors).

Solve front end by marking * on every move. Make sure if any movement is made on a wall or boundary in between, then Life is reduced by 1 from a total of 3 lives; user will restart from 5 positions before death and score will be reset to 0.

On every movement, score is increased by one. 

If a user moves at position that is not marked at backend, even then the life is reduced by 1 with same policy as discussed earlier.

Once user reaches the destination, then print "Congratulations".

 

Once user looses 3 lives at any stage, print "Game Over" and exit
