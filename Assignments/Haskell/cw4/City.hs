{-# LANGUAGE FlexibleInstances #-}
module City where

import Shape
import Control.Monad.Random
import Data.List

type Pos   = (Double, Double)
type Size  = (Double, Double)
type Building = Shape

type City = Bush (Building, Pos)
type Land = Bush (Size, Pos)

data Bush a = Leaf a
            | Fork [Bush a]


plan :: MonadRandom m => Int -> Pos -> Size -> m (Bush (Size, Pos))
plan 0     pos size = return (Leaf (size, pos))
plan level pos@(x,y) size@(width, depth)
  | width < 2 || depth < 2 = return (Leaf (size, pos))
  | width > depth = do
      shifts <- splits 5 (0, width)
      let widths = zipWith (-) (tail shifts) shifts
      plots  <- sequence [ plan (level - 1) (x+shift,y) (width', depth)
                         | (width',shift) <- zip widths shifts ]
      return (Fork plots)
  | otherwise = do
      shifts <- splits 5 (0, depth)
      let depths = zipWith (-) (tail shifts) shifts
      plots  <- sequence [ plan (level - 1) (x,y+shift) (width,depth')
                         | (depth',shift) <- zip depths shifts ]
      return (Fork plots)

splits :: (Num a, Ord a, Random a, MonadRandom m) => Int -> (a, a) -> m [a]
splits lambda (x, y) = do
  n  <- poisson lambda
  us <- getRandomRs (x, y)
  return (crop (sort (x : take n us ++ [y])))

poisson :: MonadRandom m => Int -> m Int
poisson lambda = do
  us <- getRandomRs (0, 1 :: Double)
  return (length (takeWhile (> exp (fromIntegral (-lambda))) (scanl (*) 1 us)))

crop :: Eq a => [a] -> [a]
crop []       = []
crop [x]      = [x]
crop (x:xs@(x':xs'))
  | x == x'   = crop xs
  | otherwise = x : crop xs

instance Shapeable City where
  shape (Fork bushs)     = Union (map shape bushs)
  shape (Leaf (p,(x,y))) = Shift x y p
