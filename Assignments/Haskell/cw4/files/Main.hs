module Main where

import qualified Graphics.UI.GLUT as GL
import Graphics.UI.GLUT (($=))
import Display
import Shape
import City
import Answer

main :: IO ()
main = do
  GL.initialWindowSize $= GL.Size 600 600
  (_progName, args) <- GL.getArgsAndInitialize
  execute (mkShape args)
