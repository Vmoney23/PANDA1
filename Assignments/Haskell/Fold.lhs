Preamble
========

The following lines define this module and make sure that your
definitions won't conflict with those from the `Prelude`.

> module Fold where
> import Prelude hiding (sum, product, length, and, or, all, some, filter)

Tasks
=====

The tasks for you to complete are below:

> -- DONE #F1
> sum :: Num a => [a] -> a
> sum xs = foldr (+) 0 xs

> -- DONE #F2
> product :: Num a => [a] -> a
> product xs = foldr (*) 1 xs

> -- DONE #F3
> and :: [Bool] -> Bool
> and xs = foldr (&&) True xs

> -- DONE #F4
> or :: [Bool] -> Bool
> or xs = foldr (||) False xs

> -- DONE #F5
> all :: (a -> Bool) -> [a] -> Bool
> all p  xs = foldr f True xs
>     where f x y = p(x) && y

> -- DONE #F6
> some :: (a -> Bool) -> [a] -> Bool
> some p xs = foldr f False xs
>     where f x y = p(x) || y

> -- DONE #F7
> length :: [a] -> Int
> length xs = foldr f 0 xs
>     where f x y = y + 1

> -- DONE #F8
> filter :: (a -> Bool) -> [a] -> [a]
> filter p xs = foldr f [] xs
>     where f x y = if p(x) then x:y else y

> -- DONE #F9
> group :: Eq a => [a] -> [[a]]
> group = foldr f []
>  where f x [] = [[x]]
>        f x (zs@(z:_):zss)
>          | x == z = (x:zs):zss
>          | otherwise = [x]:zs:zss

> -- DONE #F10
> transpose :: [[a]] -> [[a]]
> transpose = foldr (zipWith (:)) (repeat [])

> -- TODO #F11
> permute :: [a] -> [[a]]
> permute = foldr (concatMap.f) [[]]
>  where 	
>		f x [] = [[x]]
>  		f x (y:ys) = (x:y:ys):[y:hold | hold <- f x ys]
