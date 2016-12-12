# CoolCompiler
Yet another COOL Compiler Project. 

Co-Developed by Oscar Li, Kelukin Lau, Sunny Xiao.

## Contents
1. [Know Before you start](#know)

    1.1 [About Cool Language](#abcl)
    
    1.2 [About This Project](#abtp)
   
2. [Tools and Environment](#tool)

    2.1 [Download Preconfigured VM](#dpvm)
    
    2.2 [Environment Test](#ents)

3. [Appendix](#appe) 
    
    3.1 [VirtualBox VM setup](#vmsu)
    
    3.2 [Getting VirtualBox](#gtvb)
    
    3.3 [Getting our VM image](#gtvm)

    3.4 [Using the VM](#usvm)
    
<a name="know"></a>
## 1. Know Before you start 
<a name="abcl"></a>
### About Cool Language 
Cool the Classroom Object Oriented Language, is a small programming language for teaching the basics of compiler construction to undergraduate computer science majors.  

Cool is designed to be implemented by individuals or teams of two using C++ [Str91] in a Unix environment in a single semester.
At Berkeley, 80% - 90% of the student teams complete the pro ject each semester. 
The project has been designed to be relatively easy to modify so shorter or longer pro jects are possible. 

In this paper, Cool refers both to the language and to the complete compiler project(of which the language is one part).
<a name="abtp"></a>
### About this project 

Compiler project usually are divided into 4 assignments: 

1.  Lexical analysis
2.  Parsing
3.  Semanic Analysis
4.  Code Generation

<a name="tool"></a>
## 2. Tools And Environment  

* FLex/JLex
* Yacc

<a name="dpvm"></a>
### Download Preconfigured VM  

In order to use tools need for COOL. A Linux Environment is highly suggested. 
Due to the complexity of getting all the needed tools installed correctly, we provide a pre-configured Linux 
system via VirtualBox VM. 

[**Click here to downLoad Pre-configured VM.**](https://s3-us-west-1.amazonaws.com/prod-edx/Compilers/VM/compilers-vm.zip)

[**Click here to downLoad VirtualBox.**](https://www.virtualbox.org/wiki/Downloads)

VirtualBox allows you to install the VM on your own computer. 

<a name="ents"></a>
### Environment Test 

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
             
<a name="appe"></a>
## 3. Appendix

<a name="vmsu"></a>
### VirtualBox VM setup 

If you have not used a VM before, the idea is that you will be running an entire operating system inside a program (VirtualBox) that looks to the virtual guest operating system like real hardware. We provide a downloadable image of the guest OS with everything installed, so that you only need to do minimal setup to get started.

Note that since a VM contains a whole second operating system, the system requirements are high. **The VM will take a bit over 512MB of ram (so you will probably want to have 2GB of total ram to keep Windows or Mac OS X running smoothly), plus a bit over 2GB of hard disk space.**

<a name="gtvb"></a>
**Getting VirtualBox** 

*   First, download Oracle's VirtualBox, either from the VirtualBox website at [https://www.virtualbox.org/wiki/Downloads](https://www.virtualbox.org/wiki/Downloads), or from Oracle's download page at [http://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html](http://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html). Choose the version for the operating system you are running on your computer.
*   Once the download completes, run the installer to install VirtualBox. You will need administrator access on your computer to do so.

<a name="gtvm"></a>
**Getting our VM image** 

*   Download our linux virtual machine image [here](https://s3-us-west-1.amazonaws.com/prod-edx/Compilers/VM/compilers-vm.zip), or if you have a BitTorrent client installed, you can use the torrent [here](http://spark-university.s3.amazonaws.com/stanford-compilers/vm/compilers-vm.zip?torrent). Note that this download is approximately 750MB.
*   Unzip the file into a convenient directory. The unzipped files are about 2GB, so make sure you have enough disk space available. If you are a Windows XP user and have trouble opening the zip file, try WinZip (shareware) or 7-Zip (free, open source) instead of the built-in zip support in Windows.
*   Once you have unzipped the VM, double-click on the file "Compilers.vbox". This should open the VM in VirtualBox.

<a name="usvm"></a>
**Using the VM** 

*   **The provided account is "compilers" and the password is "cool"**.
*   To start the VM, click the green "Start" button. This should make the VM boot.
*   To shut down the VM, click on the round "Bodhi" button at the bottom left and click System. Then choose Power Off.
*   We have installed what you need to do the assignments, plus a few other programs, such as vim and emacs. If you want to install other packages, you can use the Aptitude graphical package manager (under the Bodhi menu-&gt;Applications-&gt;Preferences) or the apt-get command line tool. If you are not familiar with these, there are many tutorials online that you can find through a quick Google search.
*   To get a terminal, click on the terminal icon at the bottom of the screen. This should get you to the point where you can start the assignments.

This VM is based on Bodhi Linux, which is itself based on the popular linux distribution Ubuntu. We used Bodhi Linux in order to keep the download size more manageable, since a full Ubuntu install is quite large. However, since it is based on Ubuntu, most Ubuntu software packages can be installed on Bodhi Linux as well.
