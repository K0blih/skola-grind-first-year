type Maze = [String]

sample1 :: Maze
sample1 = ["*********",
           "* *   * *",
           "* * * * *",
           "* * * * *",
           "*   *   *",
           "******* *",
           "        *",
           "*********"]
sample2 :: Maze
sample2 = ["       ",
           "       ",
           "  ***  ",
           "  ***  ",
           "  ***  ",
           "       ",
           "       "]
sample3 :: Maze
sample3 = ["  * *  ",
           " ##### ",
           "  ***  ",
           "  * *  ",
           "  ***  ",
           "     * ",
           "       "]
sample4 :: Maze
sample4 = ["*********",
           "*s*   *e*",
           "*       *",
           "* *   * *",
           "* *   * *",
           "******* *",
           "        *",
           "*********"]
arrow :: Maze
arrow = [ "....#....",
          "...###...",
          "..#.#.#..",
          ".#..#..#.",
          "....#....",
          "....#....",
          "....#####"]

printMaze :: Maze -> IO ()
printMaze x = putStr (concat (map (++"\n") x))

above :: Maze -> Maze -> Maze
above x y = x ++ y

sideBySide :: Maze -> Maze -> Maze
sideBySide x y = zipWith (++) x y


rotateR :: Maze -> Maze
rotateR [x] = [x]
rotateR xs
    | any null xs = [] 
    | otherwise = reverse (map head xs) : rotateR (map tail xs)

rotateL :: Maze -> Maze
rotateL [x] = [x]
rotateL xs 
    |any null xs = []
    |otherwise=rotateL (map tail xs) ++ [map head xs]

getFromMaze :: Maze -> (Int, Int) -> Char
getFromMaze maze (r, c) = (maze !! r) !! c

putIntoMaze:: Maze -> [(Int,Int,Char)] -> Maze
putIntoMaze maze updates = foldl splitMaze maze updates

splitMaze :: Maze -> (Int, Int, Char) -> Maze
splitMaze maze (r,c,char) = take r maze ++ [placeChar (maze !! r) (r,c,char)] ++ drop (r+1) maze

placeChar :: String -> (Int, Int, Char) -> String
placeChar maze (r,c,char) = take c maze ++ [char] ++ drop (c+1) maze

getPart :: Maze -> (Int, Int) -> (Int, Int) -> Maze
getPart maze (startRow, startCol) (height, width) = [take width (drop startCol row) | row <- take height (drop startRow maze)]

solveMaze :: Maze -> Int
solveMaze maze = bfs [(startRow, startCol, 0)]
  where
    startRow = fst (head [(r, c) | r <- [0..length maze - 1], c <- [0..length (head maze) - 1], maze !! r !! c == 's'])
    startCol = snd (head [(r, c) | r <- [0..length maze - 1], c <- [0..length (head maze) - 1], maze !! r !! c == 's'])
    endRow   = fst (head [(r, c) | r <- [0..length maze - 1], c <- [0..length (head maze) - 1], maze !! r !! c == 'e'])
    endCol   = snd (head [(r, c) | r <- [0..length maze - 1], c <- [0..length (head maze) - 1], maze !! r !! c == 'e'])

    bfs ((r, c, steps):queue)
      | (r, c) == (endRow, endCol) = steps
      | otherwise = bfs (queue ++ [(nr, nc, steps + 1) | (nr, nc) <- [(r-1, c), (r+1, c), (r, c-1), (r, c+1)],
                                                          nr >= 0, nr < length maze, nc >= 0, nc < length (head maze),
                                                          maze !! nr !! nc /= '*', notElem (nr, nc) (map (\(x, y, _) -> (x, y)) queue)])