# Games Analytics
## Heat Maps & Trajectories

This software is a simple program to create a heatmap for the player positions from the quake 3 engine. It was an assignment for creator at the University of Lincoln and has now become a small project for the creator to work on for his portfolio. This program is designed as a visual aid for analysing data from player positions and trajectories. The data was obtained by my own logging files in the Quake 3 engine and this analyzing is written in C++ using OpenGL and FreeType.

Currently there are three are log files linked in the code that can be read and analysed by the program. The output shows heatmaps and trajectories of individual players with controls. Instructions on how to use the program are shown in the program.

### Features
- 3 Log files, editable within the code.
- 2 Heat Maps (Positions & Death Positions).
- Trajectories (Follows a specific player).
- Togglable Instructions for use.
- Zooming and Panning of the Maps.

### How does it work?
The program is very simple in itself, the position data is loaded in to a number of vector arrays and the position co-ordinates are normalised to be rendered for the trajectories. For the trajectories, each player has his/her own colour and you are able to switch between the different players.

For the HeatMap, an array of squares is created in the form of a giant square which is sighted as bigger the normalised position co-ordinates. Once the giant square of squares is created, the player positions are compared with the positions of the small squares and if a position is within a square, the colour is changed. 

### Install & Running
1 - Download/ Clone from the Github.
2 - Go to the File with the solution, (File Named: 'Heatmapping').
3 - Enter the 'Release' folder.
4 - Run the executable application 'HeatMapping.exe'.

### Still to Come?
As this is a portfolio piece, there is still plenty more the creator wishes to do with program in terms of additional features and improvements. These are just a few major features he wishes to implement.
- Allow the user to input the data text files for analysing on the fly.
- Better/ More Heatmaps.
- Trajectories over time, showing how they move as time goes by within the game.
- Showing points of interest (Weapon spawns/ Health Packs).
- Better user controls such mouse input.
- Full screen option.

While this is a working piece of software, there are many improvements that will be added over time.
