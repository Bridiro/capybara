#ifndef Map_h
#define Map_h

#include <Arduino.h>

class Map {
  public:
                                // Attributes
    char campo[15][15];                                    // Matrix that contains the map
    uint8_t dimCampo = 15;
    uint8_t visited[15][15];                               // Used for finding the prio path
    uint8_t posx, posy;                                    // Position of the robot in the map
    bool finished;                                      // bool variable to stop the robot when finished mapping
    int8_t dir;                                            // Direction of the robot in the map
    uint8_t checkX, checkY;                                // Position of the last chekpoint seen

                                // Methods
    void init();                                           // Initialize the map and the position
    void printMap();                                       // Print the map in the Serial
    void printVisited();                                   // Print the visited matrix in the Serial
    void scanNeighbors(bool north, bool east, bool south, bool west);   // Modify the map when scanning the walls around the robot
    void turnRight();                                      // Modify dir variable to turn 90 degree right
    void turnLeft();                                       // Modify dir variable to turn 90 degree left
    void turn180();                                        // Modify dir variable to turn 180 degree
    void straight();                                       // Modify posx or posy variable based on dir
    void back();                                           // Modify posx or posy variable based on dir
    int8_t suggestDirection();                             // Suggest the best direction to follow
    void blackFinded();                                    // Place walls where black tile is finded
    void checkpointFinded();                               // Function to store the last ckeckpoint finded
    void lackOfProgress();                                 // Function called with the lack of progress to start from the previous checkpoint

  private:
                                // Attributes
    uint8_t k;                                             // Steps made in the bfs prio finder
    uint8_t xySize=60;
    int8_t x[60];                                          // Contains the movements on the x axis to do for the prio path
    int8_t y[60];                                          // Contains the movements on the y axis to do for the prio path
    uint8_t countPrio;                                     // Count how many prio founded

                                // Methods
    int8_t findNearPriority();                             // Search priority path around the robot
    bool pathTo(char dest);                             // To find the prio path via bfs
    void initializeVisited();                              // Initialize the visited matrix to 0
    bool makeStep(char dest);                           // Step for searching with bfs
    bool checkIfFinded();                               // Check if dest has been reached
    void getPrio(char dest);                               // Function to get the prio path from the visited matrix
};

#endif
