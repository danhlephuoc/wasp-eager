## Run WASP with eager propagators:

To run WASP with eager propagators run the script *run_eager.sh* with *encoding* *constraints* and *instance*

Example

    $ ./run_eager.sh encoding constraints instance

*constraints* is the file containing the set of constraints to be unit propagated 
*encoding* and *instance* are two ASP files

It computes the answer sets of the ASP program given by the union of *encoding*, *instance* and *constraints*

## Requirements
In order to run wasp with eager propagators you need an ASP grounder.

*gringo* is the grounder used in the *run_eager.sh* script

    $ sudo apt install gringo
