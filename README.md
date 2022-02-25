# Culture Cultivation
\
This is a proof of work engine written in c++ for multithreading. I've moved over to RUST for better memory protection.

## Dependencies
cmake\
sfml\
boost
## How to build and run

## Quickstart script 
`./quickstart.sh`

## Release 
Be in the `/release` directory.\
If this is a newly cloned project, do: `mkdir release` in project root\
Then do `mkdir release/assets/ ; cp -r src/assets/* release/assets`\
\
Build CMakeConfig:\
`cmake ../src/`\
\
Make Project:\
`make -j8`\
\
Run Project:\
`./Culture_Cultivation`\
\
This is also a quicker version of the above cmake:\
`clear ; cmake ../src/ && make -j18 && ./Culture_Cultivation`

## Debug

Be in the `/debug` directory.\
If this is a newly cloned project, do: `mkdir debug` in project root\
Then do `mkdir debug/assets ; cp -r src/assets/* debug/assets`\
\
Build CMakeConfig:\
`cmake -DCMAKE_BUILD_TYPE=Debug ../src/`\
\
Make Project:\
`make -j8`\
\
Run Project:\
`./Culture_Cultivation`\
\
This is also a quicker version of the above cmake:\
`clear ; cmake -DCMAKE_BUILD_TYPE=Debug ../src/ && make -j18`
