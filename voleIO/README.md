# The platformIO side of Vole

This directory is a platformIO project where all deployed source is stored!

### How are you handling multiple source files?

I ran into this issues when I was evaulating platformIO as a tool - there was not innate support for multiple source files! What I interpreted as the platformIO 'mission' was to have a toolchain that was supportive for compiling different code to different microcontrollers. I had no such problem, and was deploying different code to the *same* microcontroller! My current solution is to seperate each source file into its own enviroment in the platformio.ini file. Each enviroment sets its own special build flag, and each source file is surrounded by a c++ #ifdef statement that corresponds to that enviroment. When a specific peice of source needs to be compiled, the 'default_envs' setting at the highest level of the .ini file is set to the proper enviroment! Additionally, the framework / board settings are set at the [env] level, because all the specific enviroments derive from it, and are the same physical board!