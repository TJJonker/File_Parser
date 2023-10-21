# File Parser
The File Parser project is a Hello World project for XML and JSON parsing with [rapidjson](https://rapidjson.org/) and [tinyxml 2](https://github.com/leethomason/tinyxml2).
The aim of the project is to create a preferences system where the user's preferences will be saved to an external JSON/XML file.
The external files will be read and used in the program. When the user makes adjustments, the changes will be applied to the external files.

### How to build
To save memory, the folder doesn't contain a solution file and/or bin and bin-int folder. Premake5 is integrated into the project and is responsible for building the necessary files. 
Clicking the 'GenerateFiles' WBF (Windows Batch File) will open the command prompt and run Premake5. This will generate the files, after which the user can click any button to close the command prompt.
A solution file should appear in the folder, which can be opened. This project already contains all the necessary links and project settings. Clicking the 'Run' or 'Debug' button should run the program without issues.

### Project structure
All the code written for this project can be found in the [src folder](File_Parser/src). With the exception of [vendor](File_Parser/src/Vendor). The source folder is split into different modules:
- **File Handler**: Responsible for reading and writing files.
- **Preferences manager**: (De)serializes the external file and turns them into structs.
- **Language library**: Manages the language files and provides safe and quick access values from a map.
- **Serializers**: API to (de)serialize external files.
- **Statemachine**: Keeps track of the current state and runs methods accordingly.

### Using the solution
By default, the project is using the XML Serializer. To change this, inside [Main](File_Parser/src/Main.cpp), switch the commented code. The project will now proceed to use the JSON Serializer and files.

### Known limitations
- JSON file is not formatted to a human-understandable layout.
- Expanding upon the preferences file will lead to errors and/or crashes.

### Evaluation
This is not one of my proudest works, but it's functional. The states and state machine codebases are a mess will all the dependencies. Same story for the ISerializer and inherited classes and the XML Serializer doesn't use the FileHandler to write files. But for the time I spent on the project and the fact that new libraries were used, I think it's okay. I'll take the new things I've learned with me to future projects. 
