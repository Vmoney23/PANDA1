Readme for part A:

Files: ring.h, ring.c, history.c

I made a program that emulates a basic web-browsing cache using a doubly linked ring list. It shows you the websites you visited in reverse chronological order (latest first) and allows you to navigate between the links. This is done incrementally to show that both shift functions work correctly. The user can also delete links from their history (as you can in a real browser) and print the number of links still stored. Additionally, the user can print out all the links stored, starting from the latest backwards in chronological order.

Readme for part B:

Files: map.h, map.c, phone.c

I made a program that emulates a basic phone-book where you can add, find and update contacts. It also keeps track of the number of contacts you have stored. The find function works by traversing the tree until it finds a node with the same 'key' (ie name of contact) as you have searched for. The downside of using the name as the key is that while it does allow lookup by name, it will start to break down if there are multiple contacts with the same name.