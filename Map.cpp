#include "Map.h"


/**
 * @brief Initialize the map @endif
 * 
 */
void Map::init() {
  dir = 1;      

  campo[int(dimCampo/2)][int(dimCampo/2)]='s';

  posx = int(dimCampo/2);
  posy = int(dimCampo/2);

  checkX = posx;
  checkY = posy;
}


/**
 * @brief Print the map on Serial @endif
 * 
 */
void Map::printMap() {
  for(int i=0; i<dimCampo; i++) {
    for(int j=0; j<dimCampo; j++) {
      if(i==posx && j==posy) {
        if(dir==1) {
          Serial.print("^  ");
        }
        else if(dir==0) {
          Serial.print(">  ");
        }
        else if(dir==2) {
          Serial.print("<  ");
        }
        else if(dir==3) {
          Serial.print("v  ");
        }
      }
      else{
        if(campo[i][j]==0) {
          Serial.print("   ");
        }
        else if(campo[i][j]=='?') {
          Serial.print("?  ");
        }
        else if(campo[i][j]=='w') {
          Serial.print('w');
          Serial.print("  ");
        }
        else if(campo[i][j]=='e') {
          Serial.print("   ");
        }
        else{
          Serial.print(campo[i][j]);
          Serial.print("  ");
        }
      }
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}


/**
 * @brief Print the visited matrix @endif
 * 
 */
void Map::printVisited() {
  for(int i=0; i<dimCampo; i++) {
    for(int j=0; j<dimCampo; j++) {
      Serial.print(visited[i][j]);
      Serial.print(" ");
      if(visited[i][j]<10) {
        Serial.print(" ");
      }
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}


/**
 * @brief Update the map based on the 4 parameters @endif
 * 
 * @param north North wall
 * @param east Wast wall
 * @param south South wall
 * @param west West wall
 */
void Map::scanNeighbors(bool north, bool east, bool south, bool west) {
  if(campo[posx][posy]=='?') {
    campo[posx][posy]='e';
  }

  campo[posx+1][posy+1]='w';
  campo[posx-1][posy+1]='w';
  campo[posx+1][posy-1]='w';
  campo[posx-1][posy-1]='w';

  if(north) {
    campo[posx-1][posy]='w';
    if(campo[posx-2][posy]=='?') {
      if(((campo[posx-3][posy]!='e')&&(campo[posx-2][posy+1]!='e')&&(campo[posx-2][posy-1]!='e')) && ((campo[posx-3][posy]!='p')&&(campo[posx-2][posy+1]!='p')&&(campo[posx-2][posy-1]!='p'))) {
        campo[posx-2][posy]=0;
      }
    }
  }
  else{
    if(campo[posx-1][posy]!='p' && campo[posx-1][posy]!='w') {
      campo[posx-1][posy]='e';
    }
    if(campo[posx-2][posy]==0) {
      campo[posx-2][posy]='?';
    }
    if(campo[posx-1][posy]=='w' && campo[posx-2][posy]!='n') {
      campo[posx-1][posy]='e';
      if(campo[posx-2][posy]!='e' && campo[posx-2][posy]!='s' && campo[posx-2][posy]!='p') {
        campo[posx-2][posy]='?';
      }
    }
  }

  if(east) {
    campo[posx][posy+1]='w';
    if(campo[posx][posy+2]=='?') {
      if(((campo[posx][posy+3]!='e')&&(campo[posx+1][posy+2]!='e')&&(campo[posx-1][posy+2]!='e')) && ((campo[posx][posy+3]!='p')&&(campo[posx+1][posy+2]!='p')&&(campo[posx-1][posy+2]!='p'))) {
        campo[posx][posy+2]=0;
      }
    }
  }
  else{
    if(campo[posx][posy+1]!='p' && campo[posx][posy+1]!='w') {
      campo[posx][posy+1]='e';
    }
    if(campo[posx][posy+2]==0) {
      campo[posx][posy+2]='?';
    }
    if(campo[posx][posy+1]=='w' && campo[posx][posy+2]!='n') {
      campo[posx][posy+1]='e';
      if(campo[posx][posy+2]!='e' && campo[posx][posy+2]!='s' && campo[posx][posy+2]!='p') {
        campo[posx][posy+2]='?';
      }
    }
  }

  if(south) {
    campo[posx+1][posy]='w';
    if(campo[posx+2][posy]=='?') {
      if(((campo[posx+3][posy]!='e')&&(campo[posx+2][posy+1]!='e')&&(campo[posx+2][posy-1]!='e')) && ((campo[posx+3][posy]!='p')&&(campo[posx+2][posy+1]!='p')&&(campo[posx+2][posy-1]!='p'))) {
        campo[posx+2][posy]=0;
      }
    }
  }
  else{
    if(campo[posx+1][posy]!='p' && campo[posx+1][posy]!='w') {
      campo[posx+1][posy]='e';
    }
    if(campo[posx+2][posy]==0) {
      campo[posx+2][posy]='?';
    }
    if(campo[posx+1][posy]=='w' && campo[posx+2][posy]!='n') {
      campo[posx+1][posy]='e';
      if(campo[posx+2][posy]!='e' && campo[posx+2][posy]!='s' && campo[posx+2][posy]!='p') {
        campo[posx+2][posy]='e';
      }
    }
  }

  if(west) {
    campo[posx][posy-1]='w';
    if(campo[posx][posy-2]=='?') {
      if(((campo[posx][posy-3]!='e')&&(campo[posx+1][posy-2]!='e')&&(campo[posx-1][posy-2]!='e')) && ((campo[posx][posy-3]!='p')&&(campo[posx+1][posy-2]!='p')&&(campo[posx-1][posy-2]!='p'))) {
        campo[posx][posy-2]=0;
      }
    }
  }
  else{
    if(campo[posx][posy-1]!='p' && campo[posx][posy-1]!='w') {
      campo[posx][posy-1]='e';
    }
    if(campo[posx][posy-2]==0) {
      campo[posx][posy-2]='?';
    }
    if(campo[posx][posy-1]=='w' && campo[posx][posy-2]!='n') {
      campo[posx][posy-1]='e';
      if(campo[posx][posy-2]!='e' && campo[posx][posy-2]!='s' && campo[posx][posy-2]!='p') {
        campo[posx][posy-2]='?';
      }
    }
  }
}


/**
 * @brief Modify 'dir' to turn 90° @endif
 * 
 */
void Map::turnRight() {
  dir = dir + 3;
  dir = dir % 4;
}


/**
 * @brief Modify 'dir' to turn -90° @endif
 * 
 */
void Map::turnLeft() {
  dir = dir + 1;
  dir = dir % 4;
}


/**
 * @brief Modify 'dir' to turn 180° @endif
 * 
 */
void Map::turn180() {
  Map::turnRight();
  Map::turnRight();
}


/**
 * @brief Change 'posx' or 'posy' to move forward @endif
 * 
 */
void Map::straight() {
  if(campo[posx][posy]=='p') {
    campo[posx][posy]='e';
  }
  
  if(dir==1) {
    posx = posx - 1;
  }
  else if(dir==0) {
    posy = posy + 1;
  }
  else if(dir==2) {
    posy = posy - 1;
  }
  else if(dir==3) {
    posx = posx + 1;
  }

  if(campo[posx][posy]=='p') {
    campo[posx][posy]='e';
  }

  if(dir==1) {
    posx = posx - 1;
  }
  else if(dir==0) {
    posy = posy + 1;
  }
  else if(dir==2) {
    posy = posy - 1;
  }
  else if(dir==3) {
    posx = posx + 1;
  }

  if(campo[posx][posy]=='p') {
    campo[posx][posy]='e';
  }
}


/**
 * @brief Modify 'posx' and 'posy' to move backwards @endif
 * 
 */
void Map::back() {
  Map::turn180();
  Map::straight();
  Map::turn180();
}


/**
 * @brief Based on the surrounding cells decide where to move @endif 
 * 
 * if find a near priority return the direction to reach it, 
 * if finded a '?', so a not visited cell, return the direction for it,
 * if there is not priority and no '?' near it calls MAP::pathTo() to find the target cell
 * 
 * @return 0 for right, 1 for straight, 2 for left, 3 for back, 4 for nothing
 */
int8_t Map::suggestDirection() {
  int dir_scan = 0, directionP;
  bool finded = false;

  if((campo[posx+1][posy]=='p') || (campo[posx][posy+1]=='p') || (campo[posx-1][posy]=='p') || (campo[posx][posy-1]=='p')) {
    finded=true;
    Serial.println("Prio di suggest_dir");
    if(campo[posx-1][posy]=='p') {
      if(dir==1) {
        dir_scan=1;
      }
      else if(dir==0) {
        dir_scan=2;
      }
      else if(dir==2) {
        dir_scan=0;
      }
      else if(dir==3) {
        dir_scan=3;
      }
    }

    if(campo[posx][posy+1]=='p') {
      if(dir==1) {
        dir_scan=0;
      }
      else if(dir==0) {
        dir_scan=1;
      }
      else if(dir==2) {
        dir_scan=3;
      }
      else if(dir==3) {
        dir_scan=2;
      }
    }

    if(campo[posx+1][posy]=='p') {
      if(dir==1) {
        dir_scan=3;
      }
      else if(dir==0) {
        dir_scan=0;
      }
      else if(dir==2) {
        dir_scan=2;
      }
      else if(dir==3) {
        dir_scan=1;
      }
    }

    if(campo[posx][posy-1]=='p') {
      if(dir==1) {
        dir_scan=2;
      }
      else if(dir==0) {
        dir_scan=3;
      }
      else if(dir==2) {
        dir_scan=1;
      }
      else if(dir==3) {
        dir_scan=0;
      }
    }
  }

  else{
    if(dir==1) {
      if(campo[posx][posy+1]!='w' && campo[posx][posy+2]=='?') {
        Serial.println("dir 1 dir_scan 0 suggest_dir");
        dir_scan=0;
        finded=true;
      }

      if(!finded && campo[posx-1][posy]!='w' && campo[posx-2][posy]=='?') {
        Serial.println("dir 1 dir_scan 1 suggest_dir");
        dir_scan=1;
        finded=true;
      }

      if(!finded && campo[posx][posy-1]!='w' && campo[posx][posy-2]=='?') {
        Serial.println("dir 1 dir_scan 2 suggest_dir");
        dir_scan=2;
        finded=true;
      }

      if(!finded && campo[posx+1][posy]!='w' && campo[posx+2][posy]=='?') {
        Serial.println("dir 1 dir_scan 3 suggest_dir");
        dir_scan=3;
        finded=true;
      }
    }

    else if(dir==0) {
      if(!finded && campo[posx+1][posy]!='w' && campo[posx+2][posy]=='?') {
        Serial.println("dir 0 dir_scan 0 suggest_dir");
        dir_scan=0;
        finded=true;
      }

      if(!finded && campo[posx][posy+1]!='w' && campo[posx][posy+2]=='?') {
        Serial.println("dir 0 dir_scan 1 suggest_dir");
        dir_scan=1;
        finded=true;
      }

      if(!finded && campo[posx-1][posy]!='w' && campo[posx-2][posy]=='?') {
        Serial.println("dir 0 dir_scan 2 suggest_dir");
        dir_scan=2;
        finded=true;
      }

      if(!finded && campo[posx][posy-1]!='w' && campo[posx][posy-2]=='?') {
        Serial.println("dir 0 dir_scan 3 suggest_dir");
        dir_scan=3;
        finded=true;
      }
    }

    else if(dir==3) {
      if(!finded && campo[posx][posy-1]!='w' && campo[posx][posy-2]=='?') {
        Serial.println("dir 3 dir_scan 0 suggest_dir");
        dir_scan=0;
        finded=true;
      }

      if(!finded && campo[posx+1][posy]!='w' && campo[posx+2][posy]=='?') {
        Serial.println("dir 3 dir_scan 1 suggest_dir");
        dir_scan=1;
        finded=true;
      }

      if(!finded && campo[posx][posy+1]!='w' && campo[posx][posy+2]=='?') {
        Serial.println("dir 3 dir_scan 2 suggest_dir");
        dir_scan=2;
        finded=true;
      }

      if(!finded && campo[posx-1][posy]!='w' && campo[posx-2][posy]=='?') {
        Serial.println("dir 3 dir_scan 3 suggest_dir");
        dir_scan=3;
        finded=true;
      }
    }

    else if(dir==2) {
      if(!finded && campo[posx-1][posy]!='w' && campo[posx-2][posy]=='?') {
        Serial.println("dir 2 dir_scan 0 suggest_dir");
        dir_scan=0;
        finded=true;
      }

      if(!finded && campo[posx][posy-1]!='w' && campo[posx][posy-2]=='?') {
        Serial.println("dir 2 dir_scan 1 suggest_dir");
        dir_scan=1;
        finded=true;
      }

      if(!finded && campo[posx+1][posy]!='w' && campo[posx+2][posy]=='?') {
        Serial.println("dir 2 dir_scan 2 suggest_dir");
        dir_scan=2;
        finded=true;
      }

      if(!finded && campo[posx][posy+1]!='w' && campo[posx][posy+2]=='?') {
        Serial.println("dir 2 dir_scan 3 suggest_dir");
        dir_scan=3;
        finded=true;
      }
    }
  }

  if(!finded) {
    Serial.println("Cerco ?");
    bool bFind = Map::pathTo('?');
    if(!bFind) {
      Serial.println("Cerco S");
      bFind = Map::pathTo('s');
      if(bFind) {
        directionP = Map::findNearPriority();
        Serial.print("directionP: ");
        Serial.println(directionP);
        if(directionP==-1) {
          return 4;
        }
        else if(campo[posx][posy]=='s') {
          return 4;
        }
        else{
          return directionP;
        }
      }
      else{
        return 4;
      }
    }
    else{
      directionP = Map::findNearPriority();
      return directionP;
    }
  }
  else{
    Serial.print("dir_scan: ");
    Serial.println(dir_scan);
    return dir_scan;
  }
}


/**
 * @brief Watch for 'p' in the near cells @endif
 * 
 * @return 0 for right, 1 for straight, 2 for left, 3 for back
 */
int8_t Map::findNearPriority() {

  bool finded=false;
  int dir_scan;
  
  if(campo[posx+1][posy]=='p' || campo[posx][posy+1]=='p' || campo[posx-1][posy]=='p' || campo[posx][posy-1]=='p') {
    finded=true;
    if(campo[posx-1][posy]=='p') {
      Serial.println("Prio a nord");
      if(dir==1) {
        dir_scan=1;
      }
      else if(dir==0) {
        dir_scan=2;
      }
      else if(dir==2) {
        dir_scan=0;
      }
      else if(dir==3) {
        dir_scan=3;
      }
    }

    if(campo[posx][posy+1]=='p') {
      Serial.println("Prio a est");
      if(dir==1) {
        dir_scan=0;
      }
      else if(dir==0) {
        dir_scan=1;
      }
      else if(dir==2) {
        dir_scan=3;
      }
      else if(dir==3) {
        dir_scan=2;
      }
    }

    if(campo[posx+1][posy]=='p') {
      Serial.println("Prio a sud");
      if(dir==1) {
        dir_scan==3;
      }
      else if(dir==0) {
        dir_scan=0;
      }
      else if(dir==2) {
        dir_scan=2;
      }
      else if(dir==3) {
        dir_scan=1;
      }
    }

    if(campo[posx][posy-1]=='p') {
      Serial.println("Prio a ovest");
      if(dir==1) {
        dir_scan=2;
      }
      else if(dir==0) {
        dir_scan=3;
      }
      else if(dir==2) {
        dir_scan=1;
      }
      else if(dir==3) {
        dir_scan=0;
      }
    }
  }

  if(finded) {
    return dir_scan;
  }
  else{
    return -1;
  }
}


/**
 * @brief Places 'w' over the black tile @endif
 * 
 */
void Map::blackFinded() {
  if(campo[posx][posy]!='s') {
    campo[posx][posy]='n';
    campo[posx-1][posy]='w';
    campo[posx+1][posy]='w';
    campo[posx-1][posy-1]='w';
    campo[posx-1][posy+1]='w';
    campo[posx+1][posy-1]='w';
    campo[posx+1][posy+1]='w';
    campo[posx][posy-1]='w';
    campo[posx][posy+1]='w';
  }
}


/**
 * @brief Remember in 'checkX' and 'checkY' the last checkpoint position @endif
 * 
 */
void Map::checkpointFinded() {
  checkX = posx;
  checkY = posy;
}


/**
 * @brief Reset 'dir' to 1 and 'posx' and 'posy' to 'checkX' and 'checkY' @endif
 * 
 */
void Map::lackOfProgress() {
  dir=1;
  posx=checkX;
  posy=checkY;
}


/**
 * @brief Uses BFS to search the nearest 'dest' in the map @endif
 * 
 * The function uses an additional matrix of uint8_t.
 * First the matrix get initialized to 0 and the actual position set to 1
 * Then just to be careful it search for all the 'p' in 'campo[][]' and change it to 'e'
 * Erase 'x[]' and 'y[]' and then starts to loop until it can't step in the labirinth anymore
 * or 'dest' is finded.
 * Then if 'dest' is finded save the path in 'x[]' and 'y[]'
 * 
 * @param dest Character to search
 * @return True if finded, False if not
 */
bool Map::pathTo(char dest) {

  bool step_made=true, nottrovato=true;

  Map::initializeVisited();

  for(int i=0; i<dimCampo; i++) {
    for(int j=0; j<dimCampo; j++) {
      if(campo[i][j]=='p') {
        campo[i][j]='e';
      }
    }
  }

  for(int i=0; i<xySize; i++) {
    x[i] = 0;
    y[i] = 0;
  }

  k=0;

  while(step_made && nottrovato) {
    k += 1;
    step_made = Map::makeStep(dest);
    nottrovato = Map::checkIfFinded();
  }

  if(!(nottrovato)) {
    Map::getPrio(dest);
  }

  Map::printVisited();

  return !(nottrovato);
}


/**
 * @brief Initialize 'visited[][]' to 0, the actual position to 1 @endif
 * 
 */
void Map::initializeVisited() {
  for(int i=0; i<dimCampo; i++) {
    for(int j=0; j<dimCampo; j++) {
      visited[i][j]=0;
    }
  }
  visited[posx][posy]=1;
}


/**
 * @brief Make a step in every possible direction after the actual 'k' value @endif
 * 
 * Watch every cell in the map, and based on what there is in 'campo[][]' and 'visited[][]'
 * add 'k' in 'visited[][]' if the step is possible.
 * Stops when find 'dest'
 * Set 'x[0]' and 'y[0]' to -1 if not finded
 * 
 * @param dest Character to search
 * @return True if step made, False if not
 */
bool Map::makeStep(char dest) {
  
  bool step_made=false;

  for(int i=0; i<dimCampo; i++) {
    for(int j=0; j<dimCampo; j++) {
      if(visited[i][j]==k) {
        if(i>0 && visited[i-1][j]==0 && (campo[i-1][j]=='e' || campo[i-1][j]=='?' || campo[i-1][j]=='s')) {
          visited[i-1][j]=k+1;
          step_made=true;
          if(campo[i-1][j]==dest) {
            x[0]=i-1;
            y[0]=j;
            return false;
          }
        }
        if(j>0 && visited[i][j-1]==0 && (campo[i][j-1]=='e' || campo[i][j-1]=='?' || campo[i][j-1]=='s')) {
          visited[i][j-1]=k+1;
          step_made=true;
          if(campo[i][j-1]==dest) {
            x[0]=i;
            y[0]=j-1;
            return false;
          }
        }
        if(i<dimCampo && visited[i+1][j]==0 && (campo[i+1][j]=='e' || campo[i+1][j]=='?' || campo[i+1][j]=='s')) {
          visited[i+1][j]=k+1;
          step_made=true;
          if(campo[i+1][j]==dest) {
            x[0]=i+1;
            y[0]=j;
            return false;
          }
        }
        if(j<dimCampo && visited[i][j+1]==0 && (campo[i][j+1]=='e' || campo[i][j+1]=='?' || campo[i][j+1]=='s')) {
          visited[i][j+1]=k+1;
          step_made=true;
          if(campo[i][j+1]==dest) {
            x[0]=i;
            y[0]=j+1;
            return false;
          }
        }
      }
    }
  }
  x[0]=-1;
  y[0]=-1;
  return step_made;
}


/**
 * @brief Check 'x[0]' and 'y[0]' if finded @endif
 * 
 * @return True if finded, False if not
 */
bool Map::checkIfFinded() {
  if(x[0]==-1 && y[0]==-1) {
    return true;
  }
  else{
    return false;
  }
}


/**
 * @brief Get in 'x[]' and 'y[]' the path to reach 'dest' @endif
 * 
 * Starting from 'k', get in 'x[]' and 'y[]' the cell coordinates of 'k-1' in 'visited[][]'
 * Then print to the Serial all the coordinates found and set all the 'p' in 'campo[][]'
 * 
 * @param dest Character to search
 */
void Map::getPrio(char dest) {
  int c=0;
  countPrio=1;
  k+=1;
  Serial.print("K = ");
  Serial.println(k);
  while(k>1) {
    if(visited[x[c]-1][y[c]]==(k-1)) {
      x[c+1]=x[c]-1;
      y[c+1]=y[c];
      k-=1;
      c+=1;
      countPrio+=1;
    }
    else if(visited[x[c]][y[c]-1]==(k-1)) {
      x[c+1]=x[c];
      y[c+1]=y[c]-1;
      k-=1;
      c+=1;
      countPrio+=1;
    }
    else if(visited[x[c]+1][y[c]]==(k-1)) {
      x[c+1]=x[c]+1;
      y[c+1]=y[c];
      k-=1;
      c+=1;
      countPrio+=1;
    }
    else if(visited[x[c]][y[c]+1]==(k-1)) {
      x[c+1]=x[c];
      y[c+1]=y[c]+1;
      k-=1;
      c+=1;
      countPrio+=1;
    }
  }

  for(int i=0; i<countPrio; i++) {
    Serial.print("xp: ");
    Serial.print(x[i]);
    Serial.print("    yp: ");
    Serial.println(y[i]);

    if(!(campo[x[i]][y[i]]=='s' || campo[x[i]][y[i]]=='?')) {
      campo[x[i]][y[i]]='p';
    }
  }
}
