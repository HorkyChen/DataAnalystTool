#Readme
##Setup Environment in Mac OS
<li>Install GNUPlot 
 For example, install it through MacPort: sudo port install gnuplot
 Type gnuplot in the console to confirm it had been installed.
<li>Build sqlite_extension target first.
<li>Build and Run DataAnalyst
  It will try to load the sqlite_extension library and communication with gnupplot.

For the first time run, you could choose the simple configuration: choose a CSV file with header, choose a Text plotter, then click run, a simple text file named TextOutput.txt will be generated in the working path.
 
