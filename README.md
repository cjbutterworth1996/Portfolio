# Portfolio
A portfolio of the best work I've done in C++ since starting to code

The book review database is a dynamic database that keeps track of users, book objects, and reviews.

The DNA sequencer is a program that can find matching genome sequences in DNA.

The Oregon Trail Game is my version of the classic Oregon Trail Game where you try to make your way to the West coast while dealing with diseases, bandits, and other misfortunes along the way. It has several mechanics implemented such as shopping, hunting, travelling, and combat.

The word count with probability file is a program that parses a text file of a books contents and then puts out the probability of the next 10 words (starting from the probability index of your choice). I.e. If you chose index 25, it would show you the probability of the next 10 most likely words. It also ignores the top 50 most common words in the English language.

In order to run these, you should compile them and then use the command line to run them. "g++ oregonTrail.cpp Months.cpp NPC.cpp Stats.cpp Store.cpp -std=c++11 -o ot" followed by "./ot" would run the Oregon Trail Game. 
