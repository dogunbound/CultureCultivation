# Culture Cultivation
\
This game is about class, culture, cultivation, and chaos all put together the most convoluted way possible, multi-threading.\
\
This game will be a work of art for multi-threading for years to come.


## Dependencies
cmake\
sfml\
boost
## How to build and run

Be in the `/build` directory.\
If this is a newly cloned project, do: `mkdir build` in project root\
\
Build CMakeConfig:\
`cmake ../src/`\
\
Make Project:\
`make`\
\
Run Project:\
`./Culture_Cultivation`

## Design notes:

There are 4 main threads:

### Main thread
Responsible for passing memory to and from other threads.

**user inputs**
**world clock**  - Used to sync the clocks running in all the other threads.
**Map**
**basic info**

### Render thread
This thread is reponsible for output new frames based on what the main thread has stored in memory. This is on it's own thread for smoothness purposes.

**SFML**


### Sound thread
This thread is responsible for outputting sound. Will read from main thread for sounds that need to be played.

**SFML**

### I/O thread
This is responsible for reading/writing stuff to disk. It's own it's own thread because why not.

**SFML**

### M-Threads
These threads have the responsibility of computing the actual game. 
I will figure out a way to ensure full scalability with multithreading on this partition.

**Clock**
**ai**
**map_id**
