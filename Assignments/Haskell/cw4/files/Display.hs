module Display where

import qualified Graphics.UI.GLUT as GL
import Graphics.UI.GLUT (($~!), ($~), ($=), Vertex3 (..), Vector3 (..), GLdouble)
import Data.List
import Shape
import Callback
import Camera
import Data.IORef
import Control.Monad

execute :: Shape -> IO ()
execute model = do
  cameraRef <- newIORef cameraInit
  GL.initialDisplayMode $= [GL.WithDepthBuffer, GL.DoubleBuffered]
  GL.initialDisplayCapabilities $=
    [ GL.With  GL.DisplayRGB
    , GL.With  GL.DisplayDouble
    , GL.Where GL.DisplayDepth GL.IsAtLeast 16
    , GL.Where GL.DisplayRed GL.IsEqualTo 8
    , GL.Where GL.DisplayGreen GL.IsEqualTo 8
    , GL.Where GL.DisplayBlue GL.IsEqualTo 8
    ]
  _window <- GL.createWindow "Metropolys"

  -- Model
  displayList <- GL.defineNewList GL.Compile (render $ Stack [Empty,model])

  -- Callbacks
  GL.displayCallback       $= display cameraRef displayList
  GL.reshapeCallback       $= Just reshape
  GL.keyboardMouseCallback $= Just (keyboardMouse cameraRef)
  GL.addTimerCallback 25 (timer cameraRef)

  -- Scene
  GL.clearColor $= GL.Color4 0 0 0 0
  GL.clearDepth $= 1

  -- Materials
  GL.materialAmbient    GL.Front $= GL.Color4 0.9 0.9 0.9 1
  GL.materialDiffuse    GL.Front $= GL.Color4 0.2 0.2 0.2 1
  GL.materialSpecular   GL.Front $= GL.Color4 0.5 0.5 0.5 1
  GL.materialShininess  GL.Front $= 0.9

  -- Lights
  GL.lighting              $= GL.Enabled
  GL.ambient  (GL.Light 0) $= GL.Color4 0.1 0.1 0.1 1.0
  GL.diffuse  (GL.Light 0) $= GL.Color4 0.9 0.9 0.9 1.0
  GL.specular (GL.Light 0) $= GL.Color4 0.2 0.2 0.2 1.0
  GL.position (GL.Light 0) $= GL.Vertex4 500 0 (-500) 0
  GL.light    (GL.Light 0) $= GL.Enabled

  -- Rendering
  GL.shadeModel  $= GL.Flat            -- Flat | Smooth
  GL.polygonMode $= (GL.Fill, GL.Line) -- Point Line Fill, (front, back)
  GL.depthFunc   $= Just GL.Less
  GL.cullFace    $= Just GL.Back
  GL.hint GL.PerspectiveCorrection $= GL.Nicest
  GL.normalize   $= GL.Enabled

  -- Textures
  GL.texture GL.Texture2D $= GL.Enabled

  GL.mainLoop

render :: Shape -> IO ()
render (Empty) = return ()

render (Cuboid x y z) =
  mapM_ (GL.renderPrimitive GL.TriangleStrip . renderTriangleStrip False (Vertex3 0 0 0) (Vertex3 0 0 0))
    [nest bot, nest' top, mid ]
 where
  bot = [ GL.Vertex3 0  0  0 , GL.Vertex3 x' 0  0
        , GL.Vertex3 x' y' 0 , GL.Vertex3 0  y' 0
        , GL.Vertex3 0  0  0]
  top = [ GL.Vertex3 0  0  z' , GL.Vertex3 x' 0  z'
        , GL.Vertex3 x' y' z' , GL.Vertex3 0  y' z'
        , GL.Vertex3 0  0  z']
  mid = interleave top bot
  x' = realToFrac x :: GLdouble
  y' = realToFrac y :: GLdouble
  z' = realToFrac z :: GLdouble

render (Stack ps) =
  forM_ (zip4 xoffsets yoffsets zoffsets ps) $ \(x, y, z, p) -> do
    GL.translate (Vector3 (realToFrac x) (realToFrac y) (realToFrac z :: GLdouble))
    render p
    GL.translate (Vector3 (realToFrac (-x)) (realToFrac (-y)) (realToFrac (-z) :: GLdouble))
   where xoffsets               = map ((+ head xs) . negate) xs
         yoffsets               = map ((+ head ys) . negate) ys
         zoffsets               = zipWith (-) (scanl (+) 0 heights) uzs
         (xs, ys, uzs, heights) = unzip4 (map shapeInfo ps)

render (Shift x y s) = do
  GL.translate (Vector3 (realToFrac x) (realToFrac y) 0 :: Vector3 GLdouble)
  render s
  GL.translate (Vector3 (realToFrac (-x)) (realToFrac (-y)) 0 :: Vector3 GLdouble)

render (Union us) = mapM_ render us



renderTriangleStrip :: (Show a, GL.VertexComponent a, GL.NormalComponent a, Num a) =>
  Bool -> GL.Vertex3 a -> GL.Vertex3 a -> [GL.Vertex3 a] -> IO ()
renderTriangleStrip _ _ _ [] = return ()
renderTriangleStrip parity u v (w:ws) = do
  GL.normal $ if parity then crossNorm u v w else crossNorm v u w
  GL.vertex w
  renderTriangleStrip (not parity) v w ws

{-# INLINE crossNorm #-}
crossNorm :: (Show a, GL.VertexComponent a, GL.NormalComponent a, Num a) =>
  GL.Vertex3 a -> GL.Vertex3 a -> GL.Vertex3 a -> GL.Normal3 a
crossNorm (GL.Vertex3 ux uy uz) (GL.Vertex3 vx vy vz) (GL.Vertex3 wx wy wz) =
  GL.Normal3 nx ny nz
 where
  ax = vx - ux
  ay = vy - uy
  az = vz - uz
  bx = wx - ux
  by = wy - uy
  bz = wz - uz
  nx = ay * bz - az * by
  ny = az * bx - ax * bz
  nz = ax * by - ay * bx

nest :: [a] -> [a]
nest xs = take (length xs) (interleave xs (reverse xs))

nest' :: [a] -> [a]
nest' xs = take (length xs) (interleave (reverse xs) xs)

interleave :: [a] -> [a] -> [a]
interleave []     ys = ys
interleave (x:xs) ys = x : interleave ys xs

