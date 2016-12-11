# CoolCompiler
Yet another COOL Compiler Project. 

Co-Developed by Oscar Li, Kelukin Lau, Sunny Xiao.
## Know Before you start

### About Cool Language 
Cool the Classroom Object Oriented Language, is a small programming language for teaching the basics of compiler construction to undergraduate computer science majors.  

Cool is designed to be implemented by individuals or teams of two using C++ [Str91] in a Unix environment in a single semester. 
At Berkeley, 80% - 90% of the student teams complete the pro ject each semester. 
The project has been designed to be relatively easy to modify so shorter or longer pro jects are possible. 

In this paper, Cool refers both to the language and to the complete compiler project(of which the language is one part).

### About this project

Compiler project usually are divided into 4 assignments: 

1.  Lexical analysis
2.  Parsing
3.  Semanic Analysis
4.  Code Generation

### Tools

* FLex/JLex
* Yacc

### Download Preconfigured VM

In order to use tools need for COOL. A Linux Environment is highly suggested. 
Due to the complexity of getting all the needed tools installed correctly, we provide a pre-configured Linux 
system via VirtualBox VM.

VirtualBox allows you to install the VM on your own computer. Instructions on setting up VirtualBox are available [#here#]https://class.stanford.edu/courses/Engineering/Compilers/Fall2014/7b74698308574f3c89d2ed498f26a019/.

Once the VM is set up, you can compile the example programs. 
Once the assignments become available, you will be able to work on these inside the VM as well.

To play around with the example cool programs, make a directory and copy over one or more examples from the /usr/class/cs143/examples directory. 

These examples are the same as the ones posted on the website. 
The coolc command will run the reference compiler to generate the assembly output (.s) file, which you can run using the spim simulator. 
For example, to compile and run "hello_world.cl", run in a terminal (where $ represents the prompt):

    $ mkdir examples
    $ cd examples
    $ cp /usr/class/cs143/examples/hello_world.cl .
    $ coolc hello_world.cl
    $ spim hello_world.s
    SPIM Version 6.5 of January 4, 2003
    Copyright 1990-2003 by James R. Larus (larus@cs.wisc.edu).
    All Rights Reserved.
    See the file README for a full copyright notice.
    Loaded: /usr/class/cs143/cool/lib/trap.handler
    Hello, World.
    COOL program successfully executed
    Stats -- #instructions : 152
             #reads : 27  #writes 22  #branches 28  #other 75
