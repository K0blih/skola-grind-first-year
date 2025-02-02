type Maze = [String]

sample1 :: Maze
sample1 = ["       ",
           " ##### ",
           "  ***  ",
           "  * *  ",
           "  ***  ",
           "     * ",
           "       "]

printMaze :: Maze -> IO ()
printMaze x = putStr (concat (map (++"\n") x))
-- printMaze sample1 

incrementCell :: Char -> Char
incrementCell c
  | c == ' ' = '1'  -- If the cell is empty, set it to '1'
  | c `elem` ['1'..'8'] = succ c  -- Increment if it's already a number
  | otherwise = c  -- Ignore walls and other characters

-- Helper function to find all positions of a specific character in the maze
findPositions :: Maze -> Char -> [(Int, Int)]
findPositions maze char = [(r, c) | r <- [0..length maze - 1], c <- [0..length (head maze) - 1], maze !! r !! c == char]

updateAroundMine :: Maze -> (Int, Int) -> Maze
updateAroundMine maze (r, c) =
  foldl (\acc (dr, dc) -> updateCell acc (r + dr, c + dc)) maze deltas
  where
    deltas = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    updateCell m (row, col)
      | row < 0 || row >= length m || col < 0 || col >= length (head m) = m  -- Out of bounds
      | m !! row !! col == '*' = m  -- Ignore walls
      | otherwise = take row m ++ [updateRow (m !! row) col] ++ drop (row + 1) m
      where
        updateRow row col = take col row ++ [incrementCell (row !! col)] ++ drop (col + 1) row

minesInMaze :: Maze -> Maze
minesInMaze maze =
  let minePositions = findPositions maze '*'  -- Find all mine positions
  in foldl updateAroundMine maze minePositions  -- Update the maze around each mine