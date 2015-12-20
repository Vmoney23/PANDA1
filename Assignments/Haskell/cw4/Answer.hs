module Answer where

import Shape
import City
import Control.Monad.State
import Control.Monad.Random
import System.Random

mkShape :: [String] -> Shape
mkShape ["robot"]       = robot
mkShape ["tower", n]    = tower (read n)
mkShape ["city"]        = shape city
mkShape ["cubes", n, d] = cubes (read n) (read d)
mkShape args            = error ("mkShape: " ++ show args ++ " not found!")


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

-- TODO #1.1
cubes :: Double -> Double -> Shape
cubes n d = Union [Cuboid n n n, Shift 0 (n + d) (Cuboid n n n), Shift (n + d) (n + d) (Cuboid n n n), Shift (n + d) 0 (Cuboid n n n)]


-- TODO #2.1
cuboids :: Shape -> Int
cuboids s = foldShape alg 
 where
  alg = ShapeAlg empty cuboid shift stack union
  empty        = 0
  cuboid w d h = 1
  shift x y ps = undefined
  stack ps     = undefined
  union ps     = undefined

-- TODO #2.2
height :: Shape -> Double
height = undefined


-- TODO #3.1
instance Functor Bush where
  fmap f (Leaf a) = Leaf (f a)
  fmap f (Fork a) = Fork (map (fmap f) a)

city :: City
city = fmap build land

-- TODO #3.2
build :: (Size, Pos) -> (Building, Pos)
build ((width,depth), pos) = (Cuboid (width-2) (depth-2) (10 * log (width * depth)), pos)

land :: Land
land = evalRand (plan 3 (0,0) (300, 300)) (mkStdGen 42)


