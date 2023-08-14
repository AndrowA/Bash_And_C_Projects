#include <stdio.h>
#include <string.h>
#include <math.h>

int main () 
{

	// Setting up variables for the grid
	int end = 0; 
	char input[100];
	char tempInput[100];
	int activeGrid = 0; 
	char drawingChar = '*';

	int gridHeight = 0;
	int gridWidth = 0;
	char GRID[1000][1000];
	int xAxis = 0;
	int yAxis = 0;

	// While loop 
	while (end != 1){
		
		// Get The Input 
		fgets(input, 100, stdin);
 	  
		strcpy(tempInput, input);

		// Verify if we want to end the program
		if (strcmp(input, "END\n") == 0){
			end = 1;
		}		
 	
		// Separating the string into sub-strings 
		char* subInput1 = strtok(input, " ");		
		char* subInput2 = strtok(NULL, " ");
		char* subInput3 = strtok(NULL, " ");
		
		// Setting the chracter 
		if (strcmp(subInput1, "CHAR") == 0){
			drawingChar = *subInput2;
		}
		
		// Setting the GRID 
		else if( activeGrid == 0 && strcmp(subInput1, "GRID") == 0 ){
			
			int subInput2i; 
    	sscanf(subInput2, "%d", &subInput2i);

			int subInput3i;
 	   	sscanf(subInput3, "%d", &subInput3i);

			if ( subInput2i <= 1000 && subInput2i > 0 && subInput3i <= 1000 && subInput3i > 0 )
			{
				gridHeight = subInput3i;
				gridWidth = subInput2i;
				for (int y=0; y<=gridHeight; y++){
					for (int x=0; x<=gridWidth; x++){
						GRID[y][x] = ' ';
					}
				}
				//Setting the Grid 	
				for (int y=0; y<=gridHeight; y++){
					for (int x=0; x<=gridWidth; x++){
						
						// (0,0)
						if (x == 0 && y == 0){
							GRID[y][x] = ' ';
						}
						// y-axis
						if (x == 0 && y != 0){
							GRID[y][x] = yAxis + '0';	
						}
						// x-axis
						if (y == 0 && x != 0){
							GRID[y][x] = xAxis + '0';
						}
						// Doing the counting for the vertices 
						if(x!=0){
							xAxis = xAxis + 1;
						}

						if (xAxis == 10){
							xAxis = 0;
						}
					}
					
					if (y!=0){
						yAxis = yAxis + 1;
					}
					
					if (yAxis == 10){
						yAxis = 0;
					}
				}
				activeGrid = 1;
			} else{
         printf("Only CHAR command is allowed before the grid size is set.\n");
 	    }
		}
		
		// Error if he wants to set the GRID a second time 
		else if ( activeGrid == 1 && strcmp(subInput1, "GRID") == 0 ){
			printf("GRID was already set to %d,%d.\n", gridWidth, gridHeight);
		}
		
		// Now that the grid is made, we draw the shapes 
		else if (activeGrid == 1){
			
			// Draw a line 
			if (strcmp(subInput1, "LINE") == 0){
				char* input1 = strtok(subInput2, ",");
        char* input2 = strtok(NULL, ",");
        char* input3 = strtok(subInput3, ",");
        char* input4 = strtok(NULL, ",");
       
			 	// Transforming the input into integer
				
        int x1;
      	sscanf(input1, "%d", &x1);
				x1=x1+1;
        
				int y1;
				sscanf(input2, "%d", &y1);
				y1=y1+ 1;
        
				int x2; 
        sscanf(input3, "%d", &x2);
        x2=x2+1;
        
        int y2; 
        sscanf(input4, "%d", &y2);
        y2=y2+ 1;

				// maximum values
				int yMin;
				int yMax;
				int yNext;

				if (x1 >= x2){
					int tempx = x2;
					int tempy = y2;
					x2 = x1;
					x1 = tempx;
					y2 = y1;
					y1 = tempy;
				}

				if (y2 >= y1){
					yMax = y2;
					yMin = y1;
				}else{
					yMax = y1;
          yMin = y2;

				}
				
				double m = 0;

				//Finding the formula
				if (x1 != x2){
					m = (double) (y2-y1)/(x2-x1);
				}

				double factor = (double) x2*m;
				int garbage = 2*6;
				int garbage2 = 2*6;
				double c = (double) y2-factor;
				
				//Drawing the line
				for (int y=yMin; y<=yMax; y++){
          for (int x=x1; x<=x2; x++){
					  
						if (x>=0 && x<= 1000 && y>=0 && y<= 1000){
						if (x+1 <= x2){
							yNext = (int) (m*(x+1) + c);
						}
						
						if (x1==x2 && x==x1 ){
							GRID[y][x] = drawingChar;
						}

						// Normal Filling
						if (y == (int) (m*x + c)){
							GRID[y][x] = drawingChar;
						}

						// FIll in Gaps
						if (y < yNext && y > (int) (m*x + c) && y2 == yMax){
							GRID[y][x] = drawingChar;
						}

						if (y > yNext && y < (int) (m*x + c) && y2 == yMin){
							GRID[y][x] = drawingChar;
						}
						}
					}
				}
			}
			// Draw a rectangle 
			else if (strcmp(subInput1, "RECTANGLE") == 0){
				char* input1 = strtok(subInput2, ",");
				char* input2 = strtok(NULL, ",");
				char* input3 = strtok(subInput3, ",");
				char* input4 = strtok(NULL, ",");
				
				// Transform inputs into integers
				int x1;
        sscanf(input1, "%d", &x1);
        x1=x1+1;

        int y1;
        sscanf(input2, "%d", &y1);
        y1=y1+ 1;

        int x2;
        sscanf(input3, "%d", &x2);
        x2=x2+1;

        int y2;
        sscanf(input4, "%d", &y2);
        y2=y2+ 1;
				
				// Draw the rectangle 
				for (int y=y2; y<=y1; y++){
          for (int x=x1; x<=x2; x++){
						if (y == y1){ 
							GRID[y][x] = drawingChar;
            }
						if (y == y2){
              GRID[y][x] = drawingChar;
            }
						if (x == x1){
              GRID[y][x] = drawingChar;
            }
            if (x == x2){
              GRID[y][x] = drawingChar;
            }
          }
        }
			}
			// Draw a circle
			else if (strcmp(subInput1, "CIRCLE") == 0){
				char* input1 = strtok(subInput2, ",");
        char* input2 = strtok(NULL, ",");
       	
				// center and radius
				int x1;
        sscanf(input1, "%d", &x1);
        x1=x1+1;

        int y1;
        sscanf(input2, "%d", &y1);
        y1=y1+ 1;

        double r;
        sscanf(subInput3, "%lf", &r);
				
				// 4 limits of circle
				int topY = y1 + r;
				int botY = y1 - r;
				int rightX = x1 + r;
				int leftX = x1 - r;
				
				// Point that is being tracked
				int pointX;
				int pointY;
				
				double r1;
				double r2;
				double r3;
				
				//reflexion
				int reflexionX;
				int reflexionY;
				
				// Draw the circle
				for (int y=topY; y>=y1; y--){
          for (int x=x1; x<rightX; x++){
          	
						if (x == x1 && y == y1){
							pointX = x1;
							pointY = topY;
					 		
							//top
							GRID[pointY][pointX] = drawingChar;
							reflexionY = pointY - y1;
	            
							//bottom
							GRID[pointY-reflexionY-reflexionY][pointX] = drawingChar;
							
							//left
							GRID[y1][leftX] = drawingChar;
							
							//rigth:
							GRID[y1][rightX] = drawingChar;
						}
						
						// Check for all radius

						r1 = r-(sqrt((pointX+1-x1)*(pointX+1-x1) + (pointY-y1)*(pointY-y1))); // right
						r2 = r-(sqrt((pointX-x1)*(pointX-x1) + (pointY-1-y1)*(pointY-1-y1))); // bottom
						r3 = r-(sqrt((pointX+1-x1)*(pointX+1-x1) + (pointY-1-y1)*(pointY-1-y1))); //bottom right
						
						if (r1 < 0){
							r1 = r1 * -1;
						}
						if (r2 < 0){
              r2 = r2 * -1;
            }
						if (r1 < 0){
              r2 = r2 * -1;
            }

						// Check for right
						if (r1 < r2 && r1 < r3){
							pointX = pointX + 1;
              pointY = pointY;
						}


						// Check for point on bottom
						if (r2 < r1 && r2 < r3){
							pointX = pointX;
							pointY = pointY-1;
						}

						// Check for point on bottom right
						if (r3 < r1 && r3 < r2){
							pointX = pointX+1;
              pointY = pointY-1;
						}
						
						if (pointX>=0 && pointX<= 1000 && pointY>=0 && pointY<= 1000){
						// Top Right Quadrant 
							GRID[pointY][pointX] = drawingChar;
						
							// Top Left Quadrant
            	GRID[pointY][x1+x1-pointX] = drawingChar;

							// Put an if statement here to check for range
						
            	// Bottom Right Quadrant
            	GRID[y1+y1-pointY][pointX] = drawingChar;
						
            	// BottomLeft Quadrant
            	GRID[y1+y1-pointY][x1+x1-pointX] = drawingChar;
						}
					}
        }				
				
				// connecting the dots
					for (int y=topY; y>=y1; y--){
          for (int x=x1; x<=rightX; x++){
            if (x == pointX && y >= y1 && y <= pointY){
    					
              // right quadrant
              GRID[y][x] = drawingChar;

              // left quadrant
              reflexionX = x - x1; 
              GRID[y][x-reflexionX-reflexionX] = drawingChar;
    
              // Bottom Right Quadrant
              reflexionY = y - y1; 
              GRID[y-reflexionY-reflexionY][x] = drawingChar;
  
              // BottomLeft Quadrant
              GRID[y-reflexionY-reflexionY][x-reflexionX-reflexionX] = drawingChar;

            }
          }
        }
				pointX = 0;
				pointY = 0;

			}else if (strcmp(input, "DISPLAY\n") == 0){
				// Display the GRID
        for (int row=gridHeight; row>=0; row--){
          for (int col=0; col<=gridWidth; col++){
            printf("%c", GRID[row][col]);
          }
          printf("\n");
        }
			}
			else{
				// Tell the user he made a mistake in the command
				if (strcmp(subInput1, "END\n") != 0){
					printf("Error did not understand %s", tempInput);
				}
			}

		}else{
			// Tells to put a grid before using any command
			if (strcmp(subInput1, "END\n") != 0){
        printf("Only CHAR command is allowed before the grid size is set.\n");
    	}
		}
	 	
 	}	
}
