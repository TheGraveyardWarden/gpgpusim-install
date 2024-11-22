#include <stdio.h>

int main()
{
	
}

/*
 *
 * check for program deps and install them if required
 *
 * should run as root
 * check for completed steps
 * ask to continue or restart or quit
 * list of steps
 * go thru each step and do the step
 * if it was successful write it down somewhere in the /var/log or someshit
 * so next time the application was ran uk wassap
 *
 * if it failed show the user path to log file where the output is logged
 * tellem to fix it manually and rerun the program
 *
 * we could have some automatic error fixers for each step but that would be so wild
 * not to implement but to guess whats wrong
 *
 * utils:
 * we need a method to run commands easily and check for their return values
 *
 * echo '### running ls'
 * ls > logfile 2> logfile
 * echo
 *
 * installing debian wheezy ... DONE
 * setting up environment ... DONE
 * installing gcc 5 ... DONE
 *
 *
 * */
