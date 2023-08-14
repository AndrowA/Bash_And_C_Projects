#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Name: Androw Abd El Malak
// Program: Software Engineering 
// Faculty: Engineering 

// Record / Node for the linked list.
typedef struct PersonalInfoRecord
{ 
	char id[10];
	char ptype;
	char name[31];

	union
	{
		struct
		{
			char dept[31];
			int hireyear;
			char tenured;
		}prof;
		struct
		{
			char faculty[31];
			int admyear;
		}stud;
	}info;

	struct PersonalInfoRecord *next;
} PersonalInfoRecord;

// Function to free all memory at the end
void freeAll(struct PersonalInfoRecord *head){
	
	// Temporary node
	struct PersonalInfoRecord *temp;
	
	// Iterate through the list and delete everything
	while (head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}

}

// Function to print the list 
void printList(struct PersonalInfoRecord *ptr, char output, FILE *file)
{
    while (ptr != NULL) {
			//Print a prof
      if (ptr->ptype == 'P'){
        if (output == 'N'){
					// Print to standart output
          printf("%s,%c,%s,%s,%d,%c\n", ptr->id, ptr->ptype, ptr->name, ptr->info.prof.dept, ptr->info.prof.hireyear, ptr->info.prof.tenured); 
        }else{
					// Write to file
          fprintf(file,"%s,%c,%s,%s,%d,%c\n", ptr->id, ptr->ptype, ptr->name, ptr->info.prof.dept, ptr->info.prof.hireyear, ptr->info.prof.tenured);
        }
			//Print a student
      }else{
				// Print to standart output
        if (output == 'N'){
          printf("%s,%c,%s,%s,%d\n", ptr->id, ptr->ptype, ptr->name, ptr->info.stud.faculty, ptr->info.stud.admyear);
        }else{
          //write to file
					fprintf(file,"%s,%c,%s,%s,%d\n", ptr->id, ptr->ptype, ptr->name, ptr->info.stud.faculty, ptr->info.stud.admyear);
        }
      }   
			// Iterate to next node
      ptr = ptr->next;
    }   
}

// Function to update a record 
void updateRecord(struct PersonalInfoRecord *ptr, char* id, char* ptype, char* name, char* dept, int hireyear, char* tenured, char* faculty, int admyear)
{
	// Update the name 
	if (strcmp(name, "") != 0){
		strcpy(ptr->name, name);
	}
	
	// If it's a professor
	if (ptr->ptype == 'P'){
		// Update the department
  	if (strcmp(dept, "") != 0){
			strcpy(ptr->info.prof.dept, dept);
		}
		// Update teh hire year
		if (hireyear != 0){
			ptr->info.prof.hireyear = hireyear;
		}
		// Update tenured
		if (tenured[0] != '\0'){
			ptr->info.prof.tenured = tenured[0];
		}
	// If it's a student
	}else{
		// Update the faculty
    if (strcmp(faculty, "") != 0){
			strcpy(ptr->info.stud.faculty,faculty);
    }
		// Update the administration year
		if (admyear != 0){
			ptr->info.stud.admyear = admyear;
  	}
	} 
}

//Insertion, Deletion, And Printing
struct PersonalInfoRecord* updateList(char* command, struct PersonalInfoRecord *ptr, char* id, char* ptype, char* name, char* dept, int hireyear, char* tenured, char* faculty, int admyear, FILE *file)
{		
	if (strcmp(command, "I") == 0){
	
		//create variables
		struct PersonalInfoRecord *temp = (struct PersonalInfoRecord *) malloc(sizeof(struct PersonalInfoRecord)); 
		struct PersonalInfoRecord *head = ptr;
		
		// adding data to 1 node
		strcpy(temp->id, id);
		temp->ptype = ptype[0];
		strcpy(temp->name, name);
		
		if (temp->ptype == 'P'){
			strcpy(temp->info.prof.dept, dept);
			temp->info.prof.hireyear = hireyear;
			temp->info.prof.tenured = tenured[0];
		}else{
      strcpy(temp->info.stud.faculty,faculty);
      temp->info.stud.admyear = admyear;
		}
		///// 
		
		//Set the next pointer to null (since we are adding it at the end)
		temp->next = NULL;
		
		//If we're adding the first node
		if (head == NULL){	
			head = temp;
		}
		// If a node becomes the head
		else if (atoi(temp->id) < atoi(head->id)){
			temp->next = head;
			head = temp;
		}
		// Update a record and free the temporary memory
		else if (atoi(temp->id) == atoi(head->id)){
			updateRecord(ptr,id, ptype, name, dept, hireyear, tenured, faculty, admyear);
			free(temp);	
		} 
		else{
			struct PersonalInfoRecord *prev;
			int update = 0;
			while (ptr->next != NULL){
				prev = ptr;
				ptr = ptr->next; 
				//Stop if the next one is bigger
				if (atoi(ptr->id) > atoi(temp->id)){
        	break;
				}
				//Stop if it's the same value
				if (atoi(ptr->id) == atoi(temp->id)){
					update = 1;
					break;
				}
			} 
			// Update a node and free temporary memory
			if (update == 1){
				free(temp);
				updateRecord(ptr,id, ptype, name, dept, hireyear, tenured, faculty, admyear);
			}
			// Add at end
			else if (atoi(temp->id) > atoi(ptr->id)){
				ptr->next=temp;
        temp->next=NULL;
			// Add middle
			}else{
				temp->next = prev->next;
	      prev->next = temp;
			}

		}

		//Return the head of the list
		return head;
		
		//Delete 
		}else if (strcmp(command, "D") == 0){
			struct PersonalInfoRecord *head = ptr;
			struct PersonalInfoRecord *prev;
			struct PersonalInfoRecord *temp;
			
			//Iterate through the lsit until we find the node we want to delete
			while (ptr->next != NULL){
     		prev = ptr;
				ptr = ptr->next;
				//Stop if the next one is bigger
        if (atoi(ptr->id) == atoi(id)){
          break;
        }
   		}  		
				
			//Removing the head
			if (atoi(head->id) == atoi(id)){
				temp = head;
				head = head->next;
				free(temp);
			}
			//Remove nodes
			if (atoi(ptr->id) == atoi(id)){
				prev->next = ptr->next;
				free(ptr);
			}
		
			//Return the head of the list
    	return head;
			
			}
			//Print the list
			else if (strcmp(command, "LIST") == 0){
				struct PersonalInfoRecord *head = ptr;
				
				printList(ptr,'N',file);

				return head; 
			}
		
}

// The main of your application
int main(int argc, char *argv[])
{
	// If the wrong amount of arguments is entered return error
	if (argc != 2) {
    printf("Error, please pass the database filename as argument.\nUsage ./pimapp <dbfile>\n");
    exit(1);
  }

	char inputbuffer[100], *input; // to store each input line;
	
	// Parameters that I will pass 
	struct PersonalInfoRecord *pointer = NULL;
	char* id = NULL; 
	char* ptype = NULL;
	char* name = NULL;
	char* dept = NULL;
	int hireyear;
	char* tenured = NULL;
	char* faculty = NULL;
	int admyear;
	int type;
	char *command =	NULL;
	FILE *file = fopen(argv[1], "wt");

	// create an empty head
	struct PersonalInfoRecord *head = NULL; 	

	while (fgets(input=inputbuffer, 100, stdin) != NULL) // Get each input line.
	{
		//Terminate and save when END is entered
		if(strncmp(input, "END", 3) == 0){
			if (file == NULL){
				printf("Error, unable to open %s for writing.\n", argv[1]);
				exit(3);
			}
			printList(head,'S',file);
			freeAll(head);
			exit(0);
		}
		
		int field = 1; char*fielddata;
		
		// Set the parameters according to the field 
		while( (fielddata = strsep(&input, ",\n")) != NULL){
			
			if (field == 1){
				command = fielddata;
			}
			
			if (field == 2){
				id = fielddata;
			}

			if (field == 3){
        ptype = fielddata;
      	if (strcmp(fielddata, "P") == 0){ 
          type=1;
        }else{
          type=2;
        }
			}

			if (field == 4){
        name = fielddata;
      }
			
			if (type == 1){
        if (field == 5){
        	dept = fielddata;
      	}

      	if (field == 6){
        	hireyear = atoi(fielddata);
     	}

      	if (field == 7){
        	tenured = fielddata;
      	}
				faculty=NULL;
				admyear=0;
      }
			else{
				if (field == 5){
          faculty = fielddata;
        }

        if (field == 6){
          admyear = atoi(fielddata);
        }
				dept = NULL;
				hireyear = 0;
				tenured = NULL;
			}

			field++;
		}
		// Update teh value of head everytime we add a node
		head = updateList(command, head, id, ptype, name, dept, hireyear, tenured, faculty, admyear, file);
	}
	
	return 0;

}
