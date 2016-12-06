# Algorithm-Project2
An Algorithm Project In SYSU Algorithm Lesson( Project 2 for calculating the Closest Pair).<br>
Using command **make** to compile the project in **src folder**.<br>
And it will have two exe files called **cp***(using Algorithm 1&2&3)* and **cp2***(using Algorithm 1&2&4)*<br>
And you can use the following commands to start the exe files, like:
```
$ ./cp -d 784 -n 60000 -f db
$ ./cp2 -d 784 -n 60000 -f db
```
The param d is the dimensionality of one object.<br>
The param n is the number of Objects in db to calculate the Closest Pair.<br>
The param f is the filename of db and it provide those objects to calculate. [database infomation](http://yann.lecun.com/exdb/mnist/)<br>
And we limit the number of the random projection lines to 100. 
## Cost Time
**cp***(using Algorithm 1&2&3)* about **34.7s** AND **cp2***(using Algorithm 1&2&4)* about **34.2s**<br>
But it will has different time because of the random algorithm is uncertain, but **cp2** mostly faster than **cp**
