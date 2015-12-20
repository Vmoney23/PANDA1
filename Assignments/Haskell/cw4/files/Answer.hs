module Answer where

import Shape
import City
import Control.Monad.State
import Control.Monad.Random
import System.Random

mkShape :: [String] -> Shape
mkShape ["robot"]           = robot
mkShape ["tower", n]        = tower (read n)
mkShape ["city"]            = shape city
mkShape ["cubes", n, d]     = cubes (read n) (read d)
mkShape ["pyramid", n, p]   = pyramid (read n) (read p)
mkShape args                = error ("mkShape: " ++ show args ++ " not found!")


robot :: Shape
robot =
  Stack [ -- legs
          Union [Cuboid 5  10 30, Shift 10  0 (Cuboid 5 10 30)]
          -- torso and arms
        , Union [Cuboid 20 15 10, Shift 20 10 (Cuboid 15 5 5), Shift (-15) 10 (Cuboid 15 5 5)]
          -- head
        , Cuboid 10 10 10]

tower :: Int -> Shape
tower n = Stack [Cuboid (10 * x') (10 * x') (10 * x') 
                | x <- [n, n-1 .. 0]
                , let x' = fromIntegral x ]

-- DONE #1.1
cubes :: Double -> Double -> Shape
cubes n d = Union [Cuboid n n n, Shift 0 (n + d) (Cuboid n n n), Shift (n + d) (n + d) (Cuboid n n n), Shift (n + d) 0 (Cuboid n n n)]


-- DONE #2.1
cuboids :: Shape -> Int
cuboids = foldShape alg 
 where
  alg = ShapeAlg empty cuboid shift stack union
  empty        = 0
  cuboid w d h = 1
  shift x y ps = ps
  stack ps     = sum ps
  union ps     = sum ps

-- DONE #2.2
height :: Shape -> Double
height = foldShape alg 
 where
  alg = ShapeAlg empty cuboid shift stack union
  empty        = 0
  cuboid w d h = h
  shift x y ps = ps
  stack ps     = sum ps
  union ps     = maximum ps


-- DONE #3.1
instance Functor Bush where
  fmap f (Leaf a) = Leaf (f a)
  fmap f (Fork a) = Fork (map (fmap f) a)

city :: City
city = fmap build land

-- Creates a pyramid for buildings larger than 30x30
-- Smaller buildings (in terms of base) are shorter than taller ones
-- DONE #3.2
build :: (Size, Pos) -> (Building, Pos)
build ((width,depth), pos) = 
  if width > 30 && depth > 30
    then
      (pyramid width depth, pos)
  else if width <= 10 || depth <= 10
    then
    (Cuboid (width-1) (depth-1) (abs (6 * log ((width-3)*(depth-3)))), pos)
  else if (width >= 10 && width <= 20) || (depth >= 10 && depth <= 20)
    then
    (Cuboid (width-1) (depth-1) (abs (10 * log ((width-1)*(depth-1)))), pos)
  else
      (Stack [
        Cuboid (abs (width-5)) (abs (depth-5)) (abs (15  * log ((width * depth))))
      ], pos)
      
-- Changed mkStdGen to 250
land :: Land
land = evalRand (plan 3 (0,0) (250, 250)) (mkStdGen 250)

pyramid :: Double -> Double -> Shape
pyramid n p = Stack [Cuboid ((n-2) * x) ((p-2) * x) (30 * x) 
                | x <- [1, 0.9 .. 0]]
