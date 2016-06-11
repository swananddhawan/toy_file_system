#Toy File System

####AUTHORS:

- [Laxmi Ahire](https://github.com/laxmisahire02 "Laxmi's github profile")

- [Swanand Dhawan](https://github.com/swananddhawan "Swanand's github profile")


####DESCRIPTION:
This was an semester long assignment given to us for the course, 
`CS-202: Data Structures` during the academic year 2013-2014, with the aim
to understand the role of data structures in a software.
We had referred the chapters corresponding to UFS(Unix File System) from 
Maurice J. Bach's book, `The Design of the UNIX Operating Systems`.

Our file system images are stored with `.fs` extension.
We have provided a terminal like interface to access the files in our file
system as well as our file system.

For more detailed information, please refer the
[documentation]().


####BUILDING AND USING THE FILE SYSTEM:

- #####Dependency:`libreadline6`

  The GNU Readline library provides a set of functions for use
  by applications that allow users to edit command lines as they are typed in.
  Both Emacs and vi editing modes are available. The Readline library includes
  additional functions to maintain a list of previously-entered command lines,
  to recall and perhaps reedit those lines, and perform csh-like history
  expansion on previous commands.

  *Installing __`libreadline6`__ in Debian based distros:*  `sudo apt-get install libreadline6`


- #####Build:
  Type `make` in your terminal/console to build the source code and make the
  executable. The final output i.e. the executable, named *`file_system`* will be installed in 
  `bin` directory.


- #####Executing the application:
  Enter `make run` to execute `file_system` file present in `bin` directory.
  For futher help, type `help` in `file_system`'s terminal after executing `make run`. 


- #####Clean project:
  Enter `make clean` to remove all the object files and the final executable.
