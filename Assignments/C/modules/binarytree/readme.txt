Readme for part B:

Files: map.h, map.c, phone.c

I made a program that emulates a basic phone-book where you can add, find and update contacts. It also keeps track of the number of contacts you have stored. The find function works by traversing the tree until it finds a node with the same 'key' (ie name of contact) as you have searched for. The downside of using the name as the key is that while it does allow lookup by name, it will start to break down if there are multiple contacts with the same name.