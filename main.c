/* Name : E.krishnaveni
   File name : main.c
   Date : 17-06-2026
   Description :  Displays the menu and performs Address Book operations
*/
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structure declarations */
    int option;
    struct Contacts contact_details[100];
    int contact_count = 0;
    FILE *Fptr;
    // open file in read more
    Fptr = fopen("list.txt", "r");
    // Reading data from the list.txt file
    if (Fptr != NULL)
    {
        // Read the total number of contacts from the file
        fscanf(Fptr, "#%d", &contact_count);

        for (int i = 0; i < contact_count; i++)
        {
            fscanf(Fptr, "%[^,],%[^,],%[^\n]\n",
                   contact_details[i].Name,
                   contact_details[i].Mobile_number,
                   contact_details[i].Mail_ID);
        }
        fclose(Fptr);
    }
    // Display the Address Book menu continuously until the user exits
    while (1)
    {
        printf("\n***********Address book menu************\n"); /* Give a prompt message for a user */
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contacts\n7.Exit\n");
        printf("Enter the option : ");
        scanf("%d", &option);
        // Perform the selected operation
        switch (option)
        {
        case 1:
        {
            create_contact(contact_details, &contact_count); // Function call for create_contact
            break;
        }

        case 2:
        {
            printf("Search Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
            search_contacts(contact_details, &contact_count);                                                    // Function call for search contact
            break;
        }
        case 3:
            printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
            int found = 0;
            edit_contact(contact_details, &contact_count, found); // Function call for edit contact
            break;

        case 4:
        {
            printf("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            delete_contact(contact_details, &contact_count); // function call for delete contact
            break;
        }
        case 5:
        {
            printf("------------------------------------------------------------------------------------------\n");
            printf("S.NO    %-30s %-18s  %-18s\n", "Name", "Phone Number", "Email");
            printf("------------------------------------------------------------------------------------------\n");
            list_contacts(contact_details, &contact_count); // function call for list contacts
            break;
        }
        case 6:
        {
            save_contact(contact_details, &contact_count); // function call for save contact
            break;
        }
        case 7:
            printf("save and Exit\n");
            save_contact(contact_details, &contact_count); // Function call for save contact and exit
            return 0;                                      // save all contacts and exit the program

        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}
