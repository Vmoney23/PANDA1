module Shape where

data Shape
  = Empty
  | Cuboid Double Double Double
  | Shift Double Double Shape
  | Stack [Shape]
  | Union [Shape]
  deriving Show

data ShapeAlg a = ShapeAlg
  { empty     :: a
  , cuboid    :: Double -> Double -> Double -> a
  , shift     :: Double -> Double -> a -> a
  , stack     :: [a] -> a
  , union     :: [a] -> a
  }

foldShape :: ShapeAlg a -> Shape -> a
foldShape alg (Empty)             = (empty alg)
foldShape alg (Cuboid w d h)      = (cuboid alg) w d h
foldShape alg (Shift x y s)       = (shift alg) x y (foldShape alg s)
foldShape alg (Stack us)          = (stack alg) (map (foldShape alg) us)
foldShape alg (Union us)          = (union alg) (map (foldShape alg) us)


type Bound = (Double, Double, Double)

bounds :: Shape -> (Bound, Bound)
bounds = foldShape alg where
  alg :: ShapeAlg (Bound, Bound)
  alg = ShapeAlg empty cuboid shift stack union

  empty = ((0,0,0),(0,0,0))

  cuboid w d h = ((0,0,0),(w,d,h))

  shift x y ((ux,uy,uz), (vx,vy,vz)) = ((ux+x,uy+y,uz), (vx+x,vy+y,vz))

  stack uvs = ( (mx-vx, my-vy, head uzs)
              , (mx+vx, my+vy, head uzs + sum (zipWith (-) vzs uzs)) )
    where (us, vs)        = unzip uvs
          (uxs, uys, uzs) = unzip3 us
          (vxs, vys, vzs) = unzip3 vs
          vx = maximum mxs
          vy = maximum mys
          mx = head uxs + head mxs
          my = head uys + head mys
          mxs = (map (/ 2) (zipWith (-) vxs uxs))
          mys = (map (/ 2) (zipWith (-) vys uys))

  union uvs = ((minimum uxs, minimum uys, minimum uzs), (maximum vxs, maximum vys, maximum vzs))
    where (us, vs)        = unzip uvs
          (uxs, uys, uzs) = unzip3 us
          (vxs, vys, vzs) = unzip3 vs

-- shapeInfo shape = (x, y, z, h) of the shape.
shapeInfo :: Shape -> (Double, Double, Double, Double)
shapeInfo shape = ((ux+vx) / 2, (uy+vy) / 2, uz, vz - uz)
  where ((ux,uy,uz), (vx,vy,vz)) = bounds shape

class Shapeable s where
  shape :: s -> Shape

instance Shapeable Shape where
  shape = id

instance Shapeable () where
  shape () = Empty
