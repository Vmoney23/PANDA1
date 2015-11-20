module Paths_cw3 (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/Users/vanshdassani/Desktop/Bristol/PANDA1/Assignments/Haskell/fractals/.cabal-sandbox/bin"
libdir     = "/Users/vanshdassani/Desktop/Bristol/PANDA1/Assignments/Haskell/fractals/.cabal-sandbox/lib/x86_64-osx-ghc-7.10.2/cw3-0.1.0.0-5yofkp6gE221S1S6BpIjiL"
datadir    = "/Users/vanshdassani/Desktop/Bristol/PANDA1/Assignments/Haskell/fractals/.cabal-sandbox/share/x86_64-osx-ghc-7.10.2/cw3-0.1.0.0"
libexecdir = "/Users/vanshdassani/Desktop/Bristol/PANDA1/Assignments/Haskell/fractals/.cabal-sandbox/libexec"
sysconfdir = "/Users/vanshdassani/Desktop/Bristol/PANDA1/Assignments/Haskell/fractals/.cabal-sandbox/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "cw3_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "cw3_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "cw3_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "cw3_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "cw3_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
