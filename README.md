# Wacle
If you want to run or update a task when certain files are updated or you are looking for a easy and fast way to automate a task, Wacle can come handy for Windows users.
Wacle is inspired by make/makefile utility tools.

#### How it works?
Wacle requires a wfile, which define a set of tasks to be executed.
Ofcourse the first step is to install Wacle.
After the installation is complete we can run our wfile in the command line using the command 
     `wackle [your_file.wfl]`
     
#### How to write a wfile?
Mastering making a wfile is very easy as wacle uses an easy to learn syntax.Just follow the the examples below!

#### Some examples

* ##### Print something to the terminal!
`print "Hello World"`

Note that print function does not work exclusively for strings so something like this:

`print 46`

is accepted.

* ##### Variables!

`MyVariable : string`

after the declaration we can assign a value to it

`MyVariable = "Hello World"`

and use it in the context!

`print MyVariable`


* ##### Use "Brut Commands" in order to insert a bash command directly into the command line!
`BrutCommand "g++ [...]"` or `BrutCommand "tracert [...]"` :grin:

* ##### Event triggers on files !

`FileEvent "filename.txt" [change] {
print "file has changed"
}`

Note the syntax! 
FileEvent function requires "flags" in order to tell the Event Manager what type of event you want!

Event Flag | Effect
------------ | -------------
change | Triggers when the file has been changed
delete | Triggers when the file has been deleted


* ##### Timers !

`SetInterval 3000 {
print "Block Executed once every 3 miliseconds"
}`

`SetTimeOut 3000 {
print "Block executed after 3000 miliseconds"
}`

* ##### Read from files/documents !
Reading from a document requires a variable in which will be stored the data.

`myVariable : string`


`ReadFile "filename.txt" [settings] myVariable {
print myVariable
}`

Setting | Effect
------------ | -------------
lines | Read the document line by line
words | Read the document word by word
chars | Read the document char by char


