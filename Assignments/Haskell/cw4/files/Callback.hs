{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE UndecidableInstances #-}

module Callback where

import qualified Graphics.UI.GLUT as GL
import Graphics.UI.GLUT (($~!), ($~), ($=), Vertex3 (..), Vector3 (..), GLdouble)
import Data.IORef
import System.Exit
import Camera

timer :: IORef Camera -> GL.TimerCallback
timer cameraRef = do
  GL.addTimerCallback 25 (timer cameraRef)
  modifyIORef cameraRef cameraUpdate
  GL.postRedisplay Nothing

reshape :: GL.ReshapeCallback
reshape size@(GL.Size w h) = do
  GL.viewport   $= (GL.Position 0 0, size)
  GL.matrixMode $= GL.Projection
  GL.loadIdentity
  GL.perspective 60 (fromIntegral w / fromIntegral h) 2 2000
  GL.matrixMode $= GL.Modelview 0

display :: IORef Camera -> GL.DisplayList -> GL.DisplayCallback
display cameraRef displayList = do
  GL.loadIdentity
  GL.clearColor $= GL.Color4 0.9 0.9 0.9 0.5
  GL.clear [ GL.DepthBuffer, GL.ColorBuffer ]

  camera <- GL.get cameraRef

  GL.lookAt (cameraPos camera) (Vertex3 0 0 0) (Vector3 0 0 1)

  GL.callList displayList
  GL.swapBuffers

keyboardMouse :: IORef Camera -> GL.KeyboardMouseCallback
keyboardMouse cameraRef key GL.Down modifiers pos = case key of
  (GL.Char '\27') -> exitSuccess
  (GL.Char 'q')   -> exitSuccess

  (GL.Char 'e')   -> GL.polygonMode $~ togglePolygonMode
  (GL.Char 'r')   -> cameraRef $~! (\camera -> camera { dpivot  = 0.2 } )
  (GL.Char 'w')   -> cameraRef $~! (\camera -> camera { dpitch  = -2 } )
  (GL.Char 's')   -> cameraRef $~! (\camera -> camera { dpitch  = 2 } )
  (GL.Char 'a')   -> cameraRef $~! (\camera -> camera { dpivot  = -2 } )
  (GL.Char 'd')   -> cameraRef $~! (\camera -> camera { dpivot  = 2 } )
  (GL.Char 'S')   -> cameraRef $~! (\camera -> camera { dradius = 10 } )
  (GL.Char 'W')   -> cameraRef $~! (\camera -> camera { dradius = -10 } )
  otherwise       -> return ()
keyboardMouse cameraRef key GL.Up modifiers pos = case key of
  (GL.Char '\27') -> exitSuccess
  (GL.Char 'q')   -> exitSuccess
  (GL.Char 'r')   -> return ()
  otherwise       -> cameraRef $~! cameraStop

togglePolygonMode :: (GL.PolygonMode, GL.PolygonMode) -> (GL.PolygonMode, GL.PolygonMode)
togglePolygonMode (GL.Fill,x)  = (GL.Line, x)
togglePolygonMode (GL.Line,x)  = (GL.Point, x)
togglePolygonMode (GL.Point,x) = (GL.Fill, x)
