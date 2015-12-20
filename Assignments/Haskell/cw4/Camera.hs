module Camera where

import Graphics.UI.GLUT (Vertex3 (..), GLdouble)
import Data.Fixed (mod')

data Camera = Camera
  { x :: GLdouble
  , y :: GLdouble
  , z :: GLdouble
  , pivot :: GLdouble
  , pitch :: GLdouble
  , radius :: GLdouble
  , dpivot :: GLdouble
  , dpitch :: GLdouble
  , dradius :: GLdouble
  }

cameraInit :: Camera
cameraInit = Camera 0 0 0 0 45 300 0.1 0 0

cameraPos :: Camera -> Vertex3 GLdouble
cameraPos (Camera x y z pivot pitch radius _ _ _) =
  Vertex3 (x + radius * cosPitch * cosPivot)
          (y + radius * cosPitch * sinPivot)
          (z + radius * sinPitch)
 where
  cosPitch = cos (degrees pitch)
  sinPitch = sin (degrees pitch)
  cosPivot = cos (degrees pivot)
  sinPivot = sin (degrees pivot)

degrees d = d * pi / 180

cameraUpdate :: Camera -> Camera
cameraUpdate (Camera x y z pivot pitch radius dpivot dpitch dradius) =
             (Camera x y z pivot' pitch' radius' dpivot dpitch dradius)
 where
  pivot'  = (pivot + dpivot)   `mod'` 360
  pitch'  = ((pitch + dpitch)  `min` 85) `max` (-45)
  radius' = (radius + dradius) `min` 1000

cameraStop :: Camera -> Camera
cameraStop camera = camera { dpivot = 0, dpitch = 0, dradius = 0 }
