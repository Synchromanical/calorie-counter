/*Students: Amir Djibo & Alex Cen
PROG1955 Final Project
Date Of Program Creation: Nov 9 2021
Purpose: Calorie Counter*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char foodName[30];
    int calorie;
}food;

typedef struct
{
    char name[30];
    int age;
    food* next;
}person;

int totalCalorie(food* a);
void addInformation(person* profile, int count, int len);
void deleteInformation(person* profile);
void editInformation(person* profile);
void showInformation(person* profile, int len, int count);
void sortInformation(person* profile, food* list, int len, int count);

int main(void)
{
    person userArray[10] = { 0 };
    person* userArrayPtr = &userArray;
    food foodArray[5] = { 0 };
    food* foodArrayPtr = &foodArray;
    userArrayPtr->next = foodArrayPtr;

    int inputMain;
    int inputProfileMenu = 0;
    int numFoods = 2;
    int counter = 0;

    FILE* cfPtr;

    if ((cfPtr = fopen("profile.bin", "r+")) == NULL)
    {
        printf("File could not be opened");
    }
    else
    {
        printf("Calorie counter\n");

        printf("Main menu\n");

        printf("Press 1 to manage existing profiles\n");
        printf("Press 2 to create a new profile\n");
        scanf("%d", &inputMain);




        if (inputMain == 1)
        {
            printf("Welcome back");

            puts(" ");
        }
        else
        {
            for (int a = 0; a < 1; a++)
            {   
                printf("Enter your name\n");
                while (getchar() != '\n');
                fscanf(stdin, "%[^\n]", userArrayPtr[a].name);
                fseek(cfPtr, a * sizeof(person), SEEK_SET);
                fwrite(userArrayPtr, sizeof(person), 1, cfPtr);

                printf("Enter your age\n");
                fscanf(stdin, "%d", &userArrayPtr[a].age);
                fseek(cfPtr, a * sizeof(person), SEEK_SET);
                fwrite(userArrayPtr, sizeof(person), 1, cfPtr);
                

                for (int i = 0; i < numFoods; i++)
                {

                    printf("Enter the name of food #%d\n", i + 1);
                    while (getchar() != '\n');
                    fscanf(stdin, "%s", userArrayPtr->next[i].foodName);
                    fseek(cfPtr, i * sizeof(person), SEEK_SET);
                    fwrite(userArrayPtr, sizeof(person), 1, cfPtr);
                    

                    printf("Enter the calories of food #%d\n", i + 1);
                    fscanf(stdin, "%d", &userArrayPtr->next[i].calorie);
                    fseek(cfPtr, i * sizeof(person), SEEK_SET);
                    fwrite(userArrayPtr, sizeof(person), 1, cfPtr);
           
                }
            }

            puts(" ");
        }

        while (inputProfileMenu != 6)
        {
            int total = totalCalorie(userArrayPtr->next);
            rewind(cfPtr);

            while (!feof(cfPtr))
            {
              
                int result = fread(userArrayPtr, sizeof(person), 1, cfPtr);

                if (result != 1 && userArrayPtr->name != NULL)
                {
                    fprintf(stdout, "Welcome to your profile menu %s\n", userArrayPtr->name);
                    fprintf(stdout, "The total number of calories is: %d\n", total);
                    fprintf(stdout, "%s\t\t\t%s\n", "Food", "Calorie");

                    for (int i = 0; i < numFoods; i++)
                    {
                        fprintf(stdout, "%s\t\t\t%d\n", userArrayPtr->next[i].foodName, userArrayPtr->next[i].calorie);
                    }
                }
            }

            printf("Press 1: Add person information\n");
            printf("Press 2: Delete person information\n");
            printf("Press 3: Edit person information\n");
            printf("Press 4: Show all persons information\n");
            printf("Press 5: Sort person information by calorie\n");
            printf("Press 6: Log out\n");

            scanf("%d", &inputProfileMenu);
            puts(" ");

            if (inputProfileMenu == 1)
            {
                counter++;
                addInformation(userArrayPtr, counter, numFoods);
            }
            else if (inputProfileMenu == 2)
            {
                deleteInformation(userArrayPtr);
                counter--;
            }
            else if (inputProfileMenu == 3)
            {
                editInformation(userArrayPtr);
            }
            else if (inputProfileMenu == 4)
            {
                showInformation(userArrayPtr, numFoods, counter);
            }
            else if (inputProfileMenu == 5)
            {
                sortInformation(userArrayPtr, foodArrayPtr, numFoods, counter);
            }

            //rewind(cfPtr);
        }
        fclose(cfPtr);
    }

    return 0;
}


int totalCalorie(food* a)
{
    int total = 0;

    for (int i = 0; i < 5; i++)
    {
        total += a[i].calorie;
    }

    return total;
}


void addInformation(person* profile, int count, int len)
{
    if (count < 10)
    {
        for (int a = 0; a < 1; a++)
        {
            printf("Enter a name\n");
            while (getchar() != '\n');
            scanf("%[^\n]", profile[count].name);

            printf("Enter an age\n");
            scanf("%d", &profile[count].age);

            food* foodArrayPtr = malloc(5 * sizeof(food));
            profile[count].next = foodArrayPtr;

            for (int i = 0; i < len; i++)
            {
                printf("Enter the name of food #%d\n", i + 1);
                while (getchar() != '\n');
                scanf("%s", foodArrayPtr[i].foodName);
                printf("Enter the calories of food #%d\n", i + 1);
                scanf("%d", &foodArrayPtr[i].calorie);
            }

            //free(foodArrayPtr)
        }
    }
    puts(" ");
}

void deleteInformation(person* profile)
{
    int pos = 0;
    int num = 5;
    printf("Current profiles: \n");

    for (int i = 0; i < 10; i++)
    {
        if (profile[i].name != NULL)
        {
            printf("Profile %d: %s\n", i + 1, profile[i].name);
        }
    }

    printf("Enter the profile number you want to delete\n");
    scanf("%d", &pos);

    for (int s = pos - 1; s < num - 1; s++)
    {

        profile[s] = profile[s + 1];
    }

    num--;
    puts(" ");
}

void editInformation(person* profile)
{
    int pos = 0;
    int num = 5;
    printf("Current profiles: \n");

    for (int i = 0; i < 10; i++)
    {
        if (profile[i].name != NULL)
        {
            printf("Profile %d: %s\n", i + 1, profile[i].name);
        }
    }

    printf("Enter the profile number you want to edit\n");
    scanf("%d", &pos);

    for (int a = 0; a < 1; a++)
    {
        printf("Enter a name\n");
        while (getchar() != '\n');
        scanf("%[^\n]", profile[pos - 1].name);

        printf("Enter an age\n");
        scanf("%d", &profile[pos - 1].age);
    }
    puts(" ");
}

void showInformation(person* profile, int len, int count)
{
    int total = 0;
    printf("Current profiles: \n");

    for (int a = 0; a < count + 1; a++)
    {
        total = totalCalorie(profile[a].next);
        printf("Profile number %d\n", a + 1);
        printf("Name: %s\n", profile[a].name);
        printf("Age: %d", profile[a].age);
        printf("Number of calories: %d\n", total);
        printf("%s\t\t\t%s\n", "Food", "Calorie");

        for (int i = 0; i < len; i++)
        {
            printf("%s\t\t\t%d\n", profile[a].next[i].foodName, profile[a].next[i].calorie);
        }
    }

    puts(" ");
}

void sortInformation(person* profile, food* list, int len, int count)
{
    int total = 0;
    int hold = 0;
    printf("Current profiles: \n");
    /*
    for (int a = 0; a < count + 1; a++)
    {
        for (int pass = 1; pass < len; ++pass)
        {
            for (int i = 0; i < len - 1; i++)
            {
                if (list[i].calorie > list[i + 1].calorie)
                {
                    hold[i] = profile->next[i].calorie;
                    profile->next[i].calorie = profile->next[i].calorie;
                    profile->next[i].calorie = hold[i];
                }
            }
        }
        
        total = totalCalorie(profile[a].next);
        printf("Profile number %d\n", a + 1);
        printf("Name: %s\n", profile[a].name);
        printf("Age: %d\n", profile[a].age);
        printf("Number of calories: %d\n", total);
        printf("%s\t\t\t%s\n", "Food", "Calorie");

        for (int i = 0; i < len; i++)
        {
            printf("%s\t\t\t%d\n", profile->next[i].foodName, hold[i]);
        }
        
    }
    */
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (profile->next[i].calorie > profile->next[j].calorie)
            {
                hold = profile->next[i].calorie;
                profile->next[i].calorie = profile->next[j].calorie;
                profile->next[j].calorie = hold;

                total = totalCalorie(profile[i].next);
                printf("Profile number %d\n", i + 1);
                printf("Name: %s\n", profile[i].name);
                printf("Age: %d\n", profile[i].age);
                printf("Number of calories: %d\n", total);
                printf("%s\t\t\t%s\n", "Food", "Calorie");

                for (int a = 0; a < len; a++)
                {
                    printf("%s\t\t\t%d\n", profile->next[i].foodName, hold);
                }
            }
        }
    }
    

    puts(" ");
}